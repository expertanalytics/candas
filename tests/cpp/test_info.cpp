
#include <catch.hpp>

#include <cstring>

#include "candas/info.hpp"

SCENARIO(
    "The info header is populated",
    "[info]"
) {

    CHECK( candas::info::version_major >= 0 );
    CHECK( candas::info::version_minor >= 0 );
    CHECK( candas::info::version_patch >= 0 );

    CHECK( std::strlen(candas::info::git_rev_long) > 0 );
    CHECK( std::strlen(candas::info::git_rev_short) > 0 );

}

