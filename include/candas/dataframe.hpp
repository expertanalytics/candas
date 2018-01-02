#pragma once

/* Copyright 2017 Expert Analytics AS
 *
 * This file is licensed under the terms of the MIT license.
 * See <https://github.com/expertanalytics/candas/blob/master/LICENSE.txt>
 */

#include <tuple>
#include <utility>
#include <vector>

#include "candas/detail/pack_tools.hpp"

namespace candas {

template < typename ... DTypes >
class dataframe;

// ================================================================================

namespace detail {

template < typename Type, std::size_t Idx >
using DataType = Type;

template <
        typename T, std::size_t N,
        typename Idxs = std::make_index_sequence<N>
    >
struct make_dataframe;

template <
        typename T, std::size_t N,
        std::size_t ... Idxs >
struct make_dataframe<T, N, std::index_sequence<Idxs... > > {
    using df_type = dataframe<DataType<T, Idxs>... >;
};

}

// ----------------------------------------

template < typename Type, std::size_t Columns >
using homogeneous_dataframe = typename detail::make_dataframe<Type, Columns>::df_type;
template < typename Type, std::size_t Columns >
using hdf = homogeneous_dataframe<Type, Columns >;

// ----------------------------------------

template < typename ... Types >
using inhomogeneous_dataframe = dataframe<Types... >;
template < typename ... Types >
using ihdf = inhomogeneous_dataframe<Types... >;

// ================================================================================

template < typename ... DTypes >
class dataframe {

    static_assert(sizeof...(DTypes) > 0, "dataframe have no columns");

    // dataframes with different column specifications should have private access to one another
    template < typename ... ODTs >
    friend class dataframe;

    public:
        template < std::size_t I >
        struct column_type_at
        {
            using type = typename detail::pack_at<I, DTypes... >::type;
        };
        template < std::size_t I >
        using column_type_at_t = typename column_type_at<I>::type;
        // -----
        template < typename T >
        constexpr static bool has_column_type() {
            return detail::pack_has<T, DTypes... >::value;
        }
        // -----
        template < typename T, typename ... As >
        using column_type = std::vector<T, As...>;
        using row_tuple_type = std::tuple<DTypes... >;
        using dframe_type = std::tuple<column_type<DTypes>... >;

    private:
        dframe_type _dataframe;

    public:
        dataframe() = default;
        ~dataframe() = default;
        // copy
        dataframe(const dataframe<DTypes...> & ) = default;
        dataframe<DTypes...> & operator=(const dataframe<DTypes...> & ) = default;
        // move
        dataframe(dataframe<DTypes...> && ) = default;
        dataframe<DTypes...> & operator=(dataframe<DTypes...> && ) = default;

    private:
        constexpr explicit dataframe(const column_type<DTypes> & ... columns)
          : _dataframe{ std::forward<const column_type<DTypes>>(columns)... } { }
        constexpr explicit dataframe(column_type<DTypes> && ... columns)
          : _dataframe{ std::forward<column_type<DTypes>>(columns)... } { }

    public:
        constexpr static std::size_t columns() {
            return sizeof...(DTypes);
        }
        std::size_t rows() const {
            return std::get<0>(this->_dataframe).size();
        }
        // -----
        row_tuple_type get_tuple_for_row(std::size_t i) const {
            return this->get_tuple_for_row_impl(i, std::index_sequence_for<DTypes...>{});
        }
        // -----
        void append_row(const DTypes & ... values) {
            this->append_row(std::make_tuple(values...));
        }
        void append_row(DTypes && ... values) {
            this->append_row(std::make_tuple(std::forward<DTypes>(values)...));
        }
        void append_row(const row_tuple_type & values) {
            this->emplacer(
                    std::forward<const row_tuple_type>(values),
                    std::index_sequence_for<DTypes...>{}
                );
        }
        void append_row(row_tuple_type && values) {
            this->emplacer(
                    std::forward<row_tuple_type>(values),
                    std::index_sequence_for<DTypes...>{}
                );
        }
        // -----
        template < typename T >
        dataframe<DTypes..., T> appended_column(
                const column_type<T> & column
        ) {
            return this->appended_column_impl(
                    std::forward<const column_type<T>>(column),
                    std::index_sequence_for<DTypes...>{}
                );
        }
        template < typename T >
        dataframe<DTypes..., T> appended_column(
                column_type<T> && column
        ) {
            return this->appended_column_impl(
                    std::forward<column_type<T>>(column),
                    std::index_sequence_for<DTypes...>{}
                );
        }
        // -----
        template < typename T >
        dataframe<T, DTypes...> prepended_column(
                const column_type<T> & column
        ) {
            return this->prepended_column_impl(
                    std::forward<const column_type<T>>(column),
                    std::index_sequence_for<DTypes...>{}
                );
        }
        template < typename T >
        dataframe<T, DTypes...> prepended_column(
                column_type<T> && column
        ) {
            return this->prepended_column_impl(
                    std::forward<column_type<T>>(column),
                    std::index_sequence_for<DTypes...>{}
                );
        }

    private:
        template < std::size_t ... I >
        row_tuple_type get_tuple_for_row_impl(std::size_t i, std::index_sequence<I...>) const {
            return row_tuple_type{
                   std::get<I>(this->_dataframe)[i]...
            };
        }
        // -----
        template < typename T,
                   std::size_t ... I >
        void emplacer(T && row_tuple, std::index_sequence<I...>) {
            auto ui = {
                // unpack Idx to get matching elements from the dataframe and the row tuple,
                //   and use the comma-operator to get 0u as result
                (
                    std::get<I>(std::forward<dframe_type>(this->_dataframe))
                        .emplace_back(std::get<I>(std::forward<T>(row_tuple))),
                    0u
                )...
            };
        }
        // -----
        template< typename T,
                  std::size_t ... I >
        dataframe<DTypes..., T> appended_column_impl(const column_type<T> && column, std::index_sequence<I...>) {
            return dataframe<DTypes..., T>{
                std::get<I>(std::forward<dframe_type>(this->_dataframe))...,
                std::forward<const column_type<T>>(column)
            };
        }
        template< typename T,
                  std::size_t ... I >
        dataframe<DTypes..., T> appended_column_impl(column_type<T> && column, std::index_sequence<I...>) {
            return dataframe<DTypes..., T>{
                std::get<I>(std::forward<dframe_type>(this->_dataframe))...,
                std::forward<column_type<T>>(column)
            };
        }
        // -----
        template< typename T,
                  std::size_t ... I >
        dataframe<T, DTypes...> prepended_column_impl(const column_type<T> && column, std::index_sequence<I...>) {
            return dataframe<T, DTypes...>{
                std::forward<const column_type<T>>(column),
                std::get<I>(std::forward<dframe_type>(this->_dataframe))...
            };
        }
        template< typename T,
                  std::size_t ... I >
        dataframe<T, DTypes...> prepended_column_impl(column_type<T> && column, std::index_sequence<I...>) {
            return dataframe<T, DTypes...>{
                std::forward<column_type<T>>(column),
                std::get<I>(std::forward<dframe_type>(this->_dataframe))...
            };
        }

};

}

