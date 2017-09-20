#pragma once

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
        using dframe_type = std::tuple<std::vector<DTypes>... >;
        using row_tuple_type = std::tuple<DTypes... >;
        // -----
        static constexpr std::size_t columns = sizeof...(DTypes);

    private:
        dframe_type _dataframe;

    public:
        const dframe_type & dframe() const {
            return this->_dataframe;
        }
        // -----
        std::size_t rows() const {
            return std::get<0>(this->_dataframe).size();
        }
        // -----
        void append_row(row_tuple_type && values) {
            detail::emplacer<dframe_type, row_tuple_type >(
                    std::forward<dframe_type>(this->_dataframe),
                    std::forward<row_tuple_type>(values)
                );
        }
        void append_row(const row_tuple_type & values) {
            detail::emplacer<dframe_type, const row_tuple_type >(
                    std::forward<dframe_type>(this->_dataframe),
                    std::forward<const row_tuple_type>(values)
                );
        }

};

}

