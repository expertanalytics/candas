/* Copyright 2017 Expert Analytics AS
 *
 * This file is licensed under the terms of the MIT license.
 * See <https://github.com/expertanalytics/candas/blob/master/LICENSE.txt>
 */

#include <catch.hpp>
#include "candas/dataframe_iterator.hpp"
#include <iostream>

SCENARIO(
    "Mock iterator works",
    "[iterator]"
) {
    auto df = candas::mock_df(4);
    std::get<0>(df.data[0]) = 0;
    std::get<0>(df.data[1]) = 1;
    std::get<0>(df.data[2]) = 2;
    std::get<0>(df.data[3]) = 3;
    CHECK(4 == df.data.size());
    int i = 0;
    for (auto iter = df.begin(); iter != df.end(); ++iter){
        CHECK(std::get<0>(*iter) == i++);
    }
}
