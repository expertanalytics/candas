
#include <catch.hpp>

#include "candas/info.hpp"

SCENARIO(
    "The info header is populated",
    "[info]"
) {

    CHECK( candas::info::version_major >= 0 );
    CHECK( candas::info::version_minor >= 0 );
    CHECK( candas::info::version_patch >= 0 );

}

