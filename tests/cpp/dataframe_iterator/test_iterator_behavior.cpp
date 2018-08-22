
/* Copyright 2017 Expert Analytics AS
 *
 * This file is licensed under the terms of the MIT license.
 * See <https://github.com/expertanalytics/candas/blob/master/LICENSE.txt>
 */

#include <catch2/catch.hpp>

#include "candas/dataframe.hpp"
#include "candas/dataframe_iterator.hpp"

#include <tuple>


SCENARIO(
    "Dataframe iterator is usable as an input iterator",
    "[dataframe-iterator][input-iterator]"
) {
    candas::homogeneous_dataframe<double, 2> df;

    df.append_row(std::make_tuple(1.0, 10.0));
    df.append_row(std::make_tuple(2.0, 20.0));
    df.append_row(std::make_tuple(3.0, 30.0));
    df.append_row(std::make_tuple(4.0, 40.0));

    int i = 1;
    for ( auto iter = df.begin(); iter != df.end(); ++iter, ++i ){
        CHECK( std::get<0>(*iter) == i );
        CHECK( std::get<1>(*iter) == 10.*i );
    }
}

