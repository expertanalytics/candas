
/* Copyright 2017 Expert Analytics AS
 *
 * This file is licensed under the terms of the MIT license.
 * See <https://github.com/expertanalytics/candas/blob/master/LICENSE.txt>
 */

#include "catch.hpp"

#include <vector>

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

        WHEN("A row is appended as separate l-value arguments") {
            int c1 = 1, c2 = 10;
            double c3 = 1., c4 = 10.;

            df.append_row(c1, c2, c3, c4);

            THEN("The size of the dataframe increases") {
                REQUIRE( df.rows() == 1 );

                AND_THEN("The row can be retreived as the last record") {
                    dataframe::row_tuple_type res = df.get_tuple_for_row(0);
                    REQUIRE( res == std::make_tuple(c1, c2, c3, c4) );
                }
            }
        }

        WHEN("A row is appended as separate r-value arguments") {
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


SCENARIO(
    "Create dataframes with appended columns",
    "[dataframe][inserters][add-columns]"
) {
    GIVEN("A dataframe type and a instance of it with some rows") {
        using dataframe = candas::dataframe<int, int, double, double>;

        dataframe df{};
        df.append_row(1, 10, 100., 1000.);
        df.append_row(2, 20, 200., 2000.);
        df.append_row(3, 30, 300., 3000.);

        WHEN("We generate a new dataframe type with an appended column and the old data moved") {
            std::vector<char> new_column{'a', 'b', 'c'};
            auto df_appended = df.appended_column(new_column);

            THEN("The new dataframes column count have increased") {
                REQUIRE( df_appended.columns() == 5 );
            }

            THEN("Rows retreived from the new dataframe contains the new elements") {
                auto row = df_appended.get_tuple_for_row(1);

                REQUIRE( row == std::make_tuple(2, 20, 200., 2000., 'b') );
            }
        }

        WHEN("We generate a new dataframe type with an appended column and the old data moved") {
            auto df_appended = df.appended_column(std::vector<char>{'a', 'b', 'c'});

            THEN("The new dataframes column count have increased") {
                REQUIRE( df_appended.columns() == 5 );
            }

            THEN("Rows retreived from the new dataframe contains the new elements") {
                auto row = df_appended.get_tuple_for_row(1);

                REQUIRE( row == std::make_tuple(2, 20, 200., 2000., 'b') );
            }
        }
    }
}


SCENARIO(
    "Create dataframes with prepended columns",
    "[dataframe][inserters][add-columns]"
) {
    GIVEN("A dataframe type and a instance of it with some rows") {
        using dataframe = candas::dataframe<int, int, double, double>;

        dataframe df{};
        df.append_row(1, 10, 100., 1000.);
        df.append_row(2, 20, 200., 2000.);
        df.append_row(3, 30, 300., 3000.);

        WHEN("We generate a new dataframe type with an prepended column and the old data moved") {
            std::vector<char> new_column{'a', 'b', 'c'};
            auto df_prepended = df.prepended_column(new_column);

            THEN("The new dataframes column count have increased") {
                REQUIRE( df_prepended.columns() == 5 );
            }

            THEN("Rows retreived from the new dataframe contains the new elements") {
                auto row = df_prepended.get_tuple_for_row(1);

                REQUIRE( row == std::make_tuple('b', 2, 20, 200., 2000.) );
            }
        }

        WHEN("We generate a new dataframe type with a prepended column and the old data moved") {
            auto df_prepended = df.prepended_column(std::vector<char>{'a', 'b', 'c'});

            THEN("The new dataframes column count have increased") {
                REQUIRE( df_prepended.columns() == 5 );
            }

            THEN("Rows retreived from the new dataframe contains the new elements") {
                auto row = df_prepended.get_tuple_for_row(1);

                REQUIRE( row == std::make_tuple('b', 2, 20, 200., 2000.) );
            }
        }
    }
}

