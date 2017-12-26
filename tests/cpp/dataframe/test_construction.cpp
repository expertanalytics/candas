
/* Copyright 2017 Expert Analytics AS
 *
 * This file is licensed under the terms of the MIT license.
 * See <https://github.com/expertanalytics/candas/blob/master/LICENSE.txt>
 */

#include "catch.hpp"

#include <utility>

#include "candas/dataframe.hpp"


SCENARIO(
    "Dataframe is constructible",
    "[dataframe][init]"
) {
    GIVEN("A dataframe type with primitive type columns") {
        using primitive_dataframe = candas::dataframe<char, int, float, long, double>;

        WHEN("The dataframe is default constructed") {
            primitive_dataframe df{};

            THEN("The dataframe has zero rows") {
                REQUIRE( df.rows() == 0 );
            }
        }
    }
}


SCENARIO(
    "A dataframe is copyable",
    "[dataframe][init]"
) {
    GIVEN("A dataframe type with copyable column types and a instance of it with a row") {
        using dataframe = candas::dataframe<char, int, float, long, double>;

        dataframe::row_tuple_type row_data{ 'a', 42, 84.f, 126l, 168. },
                                  new_data{ 'b', 43, 86.f, 129l, 172. };

        dataframe df{};
        df.append_row(row_data);

        WHEN("A new dataframe is copy-constructed and a new row is added") {
            dataframe copied_df(df);
            copied_df.append_row(new_data);

            THEN("The original dataframe still contains only one row") {
                REQUIRE( df.rows() == 1 );
                REQUIRE( df.get_tuple_for_row(0) == row_data );

                REQUIRE( copied_df.rows() == 2 );
                REQUIRE( copied_df.get_tuple_for_row(0) == row_data );
                REQUIRE( copied_df.get_tuple_for_row(1) == new_data );
            }
        }

        WHEN("A new dataframe is made by copy-assignment and a new row is added") {
            dataframe copied_df = df;
            copied_df.append_row(new_data);

            THEN("The original dataframe still contains only one row") {
                REQUIRE( df.rows() == 1 );
                REQUIRE( df.get_tuple_for_row(0) == row_data );

                REQUIRE( copied_df.rows() == 2 );
                REQUIRE( copied_df.get_tuple_for_row(0) == row_data );
                REQUIRE( copied_df.get_tuple_for_row(1) == new_data );
            }
        }
    }
}


SCENARIO(
    "A dataframe is movable",
    "[dataframe][init]"
) {
    GIVEN("A dataframe type with copyable column types and a instance of it with a row") {
        using dataframe = candas::dataframe<char, int, float, long, double>;

        dataframe::row_tuple_type row_data{ 'a', 42, 84.f, 126l, 168. };

        dataframe df{};
        df.append_row(row_data);

        WHEN("A new dataframe is move-constructed") {
            dataframe moved_df(std::move(df));

            THEN("The new dataframe contains the data from the old") {
                REQUIRE( moved_df.rows() == 1 );
                REQUIRE( moved_df.get_tuple_for_row(0) == row_data );
            }
        }

        WHEN("A new dataframe is move-assigned") {
            dataframe moved_df = std::move(df);

            THEN("The new dataframe contains the data from the old") {
                REQUIRE( moved_df.rows() == 1 );
                REQUIRE( moved_df.get_tuple_for_row(0) == row_data );
            }
        }
    }
}

