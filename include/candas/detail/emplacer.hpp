#pragma once

/* Copyright 2017 Expert Analytics AS
 *
 * This file is lisenced under the terms of the MIT lisence.
 * See <https://github.com/expertanalytics/candas/blob/master/LICENSE.txt>
 */

#include <tuple>
#include <utility>

namespace candas::detail {
namespace inner {

template <
        typename DFrame,
        typename ArgTuple,
        std::size_t ... Idx >
void emplacer(
    DFrame && df, ArgTuple && args,
    std::index_sequence<Idx...>
) {
    auto ui = {
        // unpack Idx twice in parallel, and use the comma-operator to get 0u as result
        ( std::get<Idx>(std::forward<DFrame>(df)).emplace_back(std::get<Idx>(std::forward<ArgTuple>(args))), 0u )...
    };
}

}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief   Emplace elements from `args` at the end of `df`.
/// \detail  The number and type of elements in the two tuples have to match.
///
/// \tparam DFrameTuple  Dataframe column tuple type.
/// \tparam ArgTuple     Argument tuple. This should have exactly one element per column in
///                      DFrame, with types matching DFrame's columns.
///
/// \param df    Tuple of dataframe columns to insert into.
/// \param args  Argument tuple.
///////////////////////////////////////////////////////////////////////////////////////////////////
template <
        typename DFrameTuple,
        typename ArgTuple >
void emplacer(DFrameTuple && df, ArgTuple && args) {
    static_assert(std::tuple_size<DFrameTuple>::value == std::tuple_size<ArgTuple>::value,
                  "dataframe and argument tuple mismatch");
    inner::emplacer(
            std::forward<DFrameTuple>(df),
            std::forward<ArgTuple>(args),
            std::make_index_sequence<std::tuple_size<DFrameTuple>::value >{}
        );
}

}

