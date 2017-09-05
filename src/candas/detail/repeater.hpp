#pragma once

#include <utility>


namespace candas::detail {

// definition

template <
        std::size_t,                      ///< Repeat count
        typename,                         ///< Type to repeat
        template <typename ... > class,   ///< Container type
        typename,                         ///< SFINAE parameter
        typename ...                      ///< Packed type sequence
    >
struct repeater_detail;

// reqursive case

template < std::size_t Count, typename Type, template <typename ... > class Container, typename ... Sequence >
struct repeater_detail<
        Count, Type, Container,
        typename std::enable_if<( Count > 0u )>::type, Sequence... >
    : repeater_detail<
        (Count - 1u), Type, Container, void,
        Sequence..., Type
    > { };

// base case -> defines container type

template <
    typename Type,
    template <typename ... > class Container,
    typename ... Sequence
>
struct repeater_detail<
        0u, Type, Container, void, Sequence... >
{
    using type = Container<Sequence... >;
};

// 'public' type -> hides sfinae parameters

template <
        std::size_t Count,                        ///< Repeat count.
        typename Type,                            ///< Type to repeat.
        template <typename ... > class Container  ///< Container type
    >
struct repeater {

    using type = typename repeater_detail<Count - 1u, Type, Container, void, Type>::type;

};

}

