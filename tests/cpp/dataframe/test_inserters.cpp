
/* Copyright 2017 Expert Analytics AS
 *
 * This file is licensed under the terms of the MIT license.
 * See <https://github.com/expertanalytics/candas/blob/master/LICENSE.txt>
 */

#include "catch.hpp"

#include "candas/dataframe.hpp"


SCENARIO(
    "Append rows to the dataframe",
    "[dataframe][inserters][insert-rows]"
) {
    GIVEN("An empty dataframe") {
        using dataframe = candas::dataframe<int, int, double, double>;

        dataframe df{};

        WHEN("A row is appended as a l-value tuple") {
            dataframe::row_tuple_type row_0{ 1, 10, 1., 10. };
            df.append_row(row_0);

            THEN("The size of the dataframe increases") {
                REQUIRE( df.rows() == 1 );

                AND_THEN("The row can be retreived as the last record") {
                    dataframe::row_tuple_type res = df.get_tuple_for_row(0);
                    REQUIRE( res == row_0 );
                }
            }
        }

        WHEN("A row is appended as a r-value tuple") {
            dataframe::row_tuple_type row_0{ 1, 10, 1., 10. };
            df.append_row(std::move(row_0));

            THEN("The size of the dataframe increases") {
                REQUIRE( df.rows() == 1 );

                AND_THEN("The row can be retreived as the last record") {
                    dataframe::row_tuple_type res = df.get_tuple_for_row(0);
                    REQUIRE( res == row_0 );
                }
            }
        }

        WHEN("A row is appended as a r-value tuple") {
            df.append_row(1, 10, 1., 10.);

            THEN("The size of the dataframe increases") {
                REQUIRE( df.rows() == 1 );

                AND_THEN("The row can be retreived as the last record") {
                    dataframe::row_tuple_type res = df.get_tuple_for_row(0);
                    REQUIRE( res == std::make_tuple(1, 10, 1., 10.) );
                }
            }
        }
    }
}

