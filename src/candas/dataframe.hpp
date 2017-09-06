#pragma once

#include <vector>
#include <utility>
#include <tuple>

#include "candas/detail/emplacer.hpp"
#include "candas/detail/repeater.hpp"


namespace candas {

template <
        std::size_t Columns,
        typename DType = double,
        bool IsView = false
    >
class dataframe;

// ================================================================================

template <
        std::size_t Columns,
        typename DType
    >
class dataframe<Columns, DType, false> {

    public:
        using dtype = DType;
        using dframe_backend = typename detail::repeater<Columns, std::vector<dtype>, std::tuple>::type;
        using row_tuple = typename detail::repeater<Columns, double, std::tuple>::type;
        // -----
        static constexpr std::size_t columns = Columns;
        static constexpr bool is_view = false;
        // -----
        friend dataframe<Columns, DType, false>;  // view version

    private:
        dframe_backend _dataframe;

    public:
        const dframe_backend & dframe() const {
            return this->_dataframe;
        }
        // -----
        std::size_t rows() const {
            return std::get<0>(this->_dataframe).size();
        }
        void append_row(row_tuple && values) {
            detail::emplacer<Columns, dframe_backend, row_tuple >(
                    std::forward<dframe_backend>(this->_dataframe),
                    std::forward<row_tuple>(values)
                );
        }
        void append_row(const row_tuple & values) {
            detail::emplacer<Columns, dframe_backend, const row_tuple >(
                    std::forward<dframe_backend>(this->_dataframe),
                    std::forward<const row_tuple>(values)
                );
        }

};

// ================================================================================

template <
        std::size_t Columns,
        typename DType
    >
class dataframe<Columns, DType, true> {

    public:
        using dtype = DType;
        // -----
        static constexpr std::size_t columns = Columns;
        static constexpr bool is_view = true;
        // -----
        friend dataframe<Columns, DType, true>;  // material version

};

}

