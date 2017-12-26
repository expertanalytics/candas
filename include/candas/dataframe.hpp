#pragma once

/* Copyright 2017 Expert Analytics AS
 *
 * This file is licensed under the terms of the MIT license.
 * See <https://github.com/expertanalytics/candas/blob/master/LICENSE.txt>
 */

#include <tuple>
#include <utility>
#include <vector>

#include "candas/detail/emplacer.hpp"
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

    public:
        template < std::size_t Column >
        struct dtype_at {
            using type = typename detail::pack_at<Column, DTypes... >::type;
        };
        template < typename Type >
        struct has_dtype {
            static constexpr bool value = detail::pack_has<Type, DTypes... >::value;
        };
        // -----
        template < typename T >
        using column_type = std::vector<T>;
        using dframe_type = std::tuple<column_type<DTypes>... >;
        using row_tuple_type = std::tuple<DTypes... >;
        // -----
        static constexpr std::size_t columns = sizeof...(DTypes);

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

    public:
        const dframe_type & dframe() const {
            return this->_dataframe;
        }
        // -----
        std::size_t rows() const {
            return std::get<0>(this->_dataframe).size();
        }
        // -----
        row_tuple_type get_tuple_for_row(std::size_t i) const {
            return this->get_tuple_for_row_impl(i, std::index_sequence_for<DTypes...>{});
        }
        // -----
        void append_row(const row_tuple_type & values) {
            detail::emplacer<dframe_type, const row_tuple_type >(
                    std::forward<dframe_type>(this->_dataframe),
                    std::forward<const row_tuple_type>(values)
                );
        }
        void append_row(row_tuple_type && values) {
            detail::emplacer<dframe_type, row_tuple_type >(
                    std::forward<dframe_type>(this->_dataframe),
                    std::forward<row_tuple_type>(values)
                );
        }
        void append_row(const DTypes & ... values) {
            this->append_row(std::make_tuple(values...));
        }
        void append_row(DTypes && ... values) {
            this->append_row(std::make_tuple(std::forward<DTypes>(values)...));
        }

    private:
        template < std::size_t ... I >
        row_tuple_type get_tuple_for_row_impl(std::size_t i, std::index_sequence<I...>) const {
            return row_tuple_type(
                   std::get<I>(this->_dataframe)[i]...
            );
        }

};

}

