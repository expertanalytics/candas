#pragma once

#include <vector>
#include <utility>
#include <tuple>

#include "candas/detail/emplacer.hpp"
#include "candas/detail/pack_tools.hpp"

namespace candas {

template <
        bool IsView,
        typename ... DTypes
    >
class dataframe;

// ================================================================================

namespace detail {

template < typename Type, std::size_t Idx >
using DataType = Type;

template <
        bool IV,
        typename T, std::size_t N,
        typename Idxs = std::make_index_sequence<N>
    >
struct make_dataframe;

template <
        bool IV,
        typename T, std::size_t N,
        std::size_t ... Idxs >
struct make_dataframe<IV, T, N, std::index_sequence<Idxs... > > {
    using df_type = dataframe<IV, DataType<T, Idxs>... >;
};

}

// ----------------------------------------

template < typename Type, std::size_t Columns >
using homogeneous_dataframe = typename detail::make_dataframe<false, Type, Columns>::df_type;
template < typename Type, std::size_t Columns >
using hdf = homogeneous_dataframe<Type, Columns >;

// ----------------------------------------

template < typename ... Types >
using inhomogeneous_dataframe = dataframe<false, Types... >;
template < typename ... Types >
using ihdf = inhomogeneous_dataframe<Types... >;

// ================================================================================

template <
        typename ... DTypes
    >
class dataframe<false, DTypes... > {

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
        static constexpr bool is_view = false;

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
            detail::emplacer<columns, dframe_type, row_tuple_type >(
                    std::forward<dframe_type>(this->_dataframe),
                    std::forward<row_tuple_type>(values)
                );
        }
        void append_row(const row_tuple_type & values) {
            detail::emplacer<columns, dframe_type, const row_tuple_type >(
                    std::forward<dframe_type>(this->_dataframe),
                    std::forward<const row_tuple_type>(values)
                );
        }

};

// ================================================================================

// TODO reimplement after non-homogeneous column types
// template <
//         std::size_t Columns,
//         typename DType
//     >
// class dataframe<Columns, DType, true> {
//
//     public:
//         using dtype = DType;
//         // -----
//         static constexpr std::size_t columns = Columns;
//         static constexpr bool is_view = true;
//         // -----
//         friend dataframe<Columns, DType, true>;  // material version
//
// };

}

