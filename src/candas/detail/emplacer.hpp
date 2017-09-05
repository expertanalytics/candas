
#include <tuple>
#include <utility>


namespace candas::detail {

template <
        typename DFrame,
        typename ArgTuple,
        std::size_t ... Idx
    >
void emplacer_detail(
    DFrame & df, ArgTuple & args,
    std::index_sequence<Idx...>
) {
    auto ui = {
        // unpack Idx twice in parallel, and use the comma-operator to get 0u as result
        ( std::get<Idx>(df).emplace_back(std::get<Idx>(args)), 0u )...
    };
}

template <
        std::size_t Columns,
        typename DFrame,
        typename ArgTuple
    >
void emplacer(DFrame & df, ArgTuple & args) {
    emplacer_detail(df, args, std::make_index_sequence<Columns>{} );
}

}

