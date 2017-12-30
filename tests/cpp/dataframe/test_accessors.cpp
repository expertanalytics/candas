
/* Copyright 2017 Expert Analytics AS
 *
 * This file is licensed under the terms of the MIT license.
 * See <https://github.com/expertanalytics/candas/blob/master/LICENSE.txt>
 */

#include "catch.hpp"

#include "candas/dataframe.hpp"


SCENARIO(
    "Check the number of columns",
    "[dataframe][accessors][counts]"
) {
    GIVEN("A dataframe type with some columns and a instance of it") {
        using dataframe = candas::dataframe<int, int, double, double>;
        dataframe df{};

        THEN("The instance reports the correct number of columns") {
            REQUIRE( df.columns() == 4 );
        }
    }
}

SCENARIO(
    "Check the number of rows",
    "[dataframe][accessors][counts]"
) {
    GIVEN("A dataframe instance with some rows") {
        using dataframe = candas::dataframe<int, int, double, double>;

        dataframe::row_tuple_type row0{ 1, 10, 1., 10. },
                                  row1{ 2, 20, 2., 20. },
                                  row2{ 3, 30, 3., 30. };

        dataframe df{};
        df.append_row(row0);
        df.append_row(row1);
        df.append_row(row2);

        THEN("The instance reports the correct number of rows") {
            REQUIRE( df.rows() == 3 );
        }
    }
}

SCENARIO(
    "Retreive rows",
    "[dataframe][accessors][row-accessors]"
) {
    GIVEN("A dataframe with copyable column types and some rows") {
        using dataframe = candas::dataframe<int, int, double, double>;

        dataframe::row_tuple_type row0{ 1, 10, 1., 10. },
                                  row1{ 2, 20, 2., 20. },
                                  row2{ 3, 30, 3., 30. };

        dataframe df{};
        df.append_row(row0);
        df.append_row(row1);
        df.append_row(row2);

        WHEN("We retreive a row with `get_tuple_for_row`") {
            dataframe::row_tuple_type res = df.get_tuple_for_row(1);

            THEN("The row we retreived matches the row we wanted") {
                REQUIRE(res == row1);

                AND_WHEN("The retreived row is modified") {
                    std::get<2>(res) = 200.;

                    THEN("The dataframe is not modified") {
                        dataframe::row_tuple_type new_res = df.get_tuple_for_row(1);
                        REQUIRE( new_res == row1 );
                    }
                }
            }
        }
    }
}

