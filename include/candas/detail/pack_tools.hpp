#pragma once

/* Copyright 2017 Expert Analytics AS
 *
 * This file is licensed under the terms of the MIT license.
 * See <https://github.com/expertanalytics/candas/blob/master/LICENSE.txt>
 */

#include <type_traits>
#include <utility>

namespace candas::detail {
namespace inner {

// ================================================================================

template <  // definition
        std::size_t Idx, typename /* SFINAE */, typename Head, typename ... Body
    >
struct pack_at;

template <  // base case
        typename Head, typename ... Body
    >
struct pack_at<0u, void, Head, Body... > { using type = Head; };

template <  // recursive step
        std::size_t Idx, typename Head, typename ... Body
    >
struct pack_at<
        Idx, typename std::enable_if<( Idx > 0 )>::type, Head, Body...
    > : pack_at<Idx - 1u, void, Body... > { };

// ================================================================================

template <  // definition
        typename /* SFINAE */,
        typename Type,
        typename Head,
        typename ... Types >
struct pack_has;

template <  // base case - false
        typename Type,
        typename Head >
struct pack_has<
        typename std::enable_if<! std::is_same<Type, Head>::value >::type,
        Type, Head > : std::false_type { };

template <  // base case - true
        typename Type,
        typename Head,
        typename ... Types >
struct pack_has<
        typename std::enable_if<std::is_same<Type, Head>::value >::type,
        Type, Head, Types...
    > : std::true_type { };

template <  // recursive step
        typename Type,
        typename Head,
        typename ... Types >
struct pack_has<
        typename std::enable_if<! std::is_same<Type, Head>::value >::type,
        Type, Head, Types...
    > : pack_has<void, Type, Types... > { };

}  // inner

///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief  Get a type at index from a parameter pack.
///
/// \tparam Idx    Index into Types.
/// \tparam Types  Parameter pack to index into.
///////////////////////////////////////////////////////////////////////////////////////////////////
template <
        std::size_t Idx,  
        typename ... Types >
struct pack_at {
    static_assert( Idx < sizeof...(Types), "index out of bounds" );
    using type = typename inner::pack_at<Idx, void, Types... >::type;  ///< Type at index
};

///////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief  Check if a parameter pack has a specific type.
///
/// \tparam Type   Type to check for.
/// \tparam Types  Parameter pack to check.
///////////////////////////////////////////////////////////////////////////////////////////////////
template <
        typename Type,
        typename ... Types >
struct pack_has {
    static constexpr bool value = inner::pack_has<void, Type, Types... >::value; ///< Whether `Types` contain `Type`
};

}  // candas::detail

