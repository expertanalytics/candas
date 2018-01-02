
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
    "Prepend rows to the dataframe",
    "[dataframe][inserters][insert-rows]"
) {
    GIVEN("An empty dataframe") {
        using dataframe = candas::dataframe<int, int, double, double>;

        dataframe df{};

        WHEN("Rows is prepended as l-value tuples") {
            dataframe::row_tuple_type row_0{ 1, 10, 1., 10. };
            dataframe::row_tuple_type row_1{ 2, 20, 2., 20. };

            df.prepend_row(row_1);
            df.prepend_row(row_0);

            THEN("The size of the dataframe increases correctly") {
                REQUIRE( df.rows() == 2 );

                AND_THEN("The row can be retreived at the expected position") {
                    dataframe::row_tuple_type res_0 = df.get_tuple_for_row(0);
                    dataframe::row_tuple_type res_1 = df.get_tuple_for_row(1);

                    REQUIRE( res_0 == row_0 );
                    REQUIRE( res_1 == row_1 );
                }
            }
        }

        WHEN("Rows is prepended as r-value tuples") {
            dataframe::row_tuple_type row_0{ 1, 10, 1., 10. };
            dataframe::row_tuple_type row_1{ 2, 20, 2., 20. };

            df.prepend_row(std::move(row_1));
            df.prepend_row(std::move(row_0));

            THEN("The size of the dataframe increases correctly") {
                REQUIRE( df.rows() == 2 );

                AND_THEN("The row can be retreived at the expected position") {
                    dataframe::row_tuple_type res_0 = df.get_tuple_for_row(0);
                    dataframe::row_tuple_type res_1 = df.get_tuple_for_row(1);

                    REQUIRE( res_0 == row_0 );
                    REQUIRE( res_1 == row_1 );
                }
            }
        }

        WHEN("Rows is prepended as separate l-value arguments") {
            int c1_0 = 1, c2_0 = 10,
                c1_1 = 2, c2_1 = 20;
            double c3_0 = 1., c4_0 = 10.,
                   c3_1 = 2., c4_1 = 20.;

            df.prepend_row(c1_1, c2_1, c3_1, c4_1);
            df.prepend_row(c1_0, c2_0, c3_0, c4_0);

            THEN("The size of the dataframe increases correctly") {
                REQUIRE( df.rows() == 2 );

                AND_THEN("The row can be retreived at the expected position") {
                    dataframe::row_tuple_type res_0 = df.get_tuple_for_row(0);
                    dataframe::row_tuple_type res_1 = df.get_tuple_for_row(1);

                    REQUIRE( res_0 == std::make_tuple(c1_0, c2_0, c3_0, c4_0) );
                    REQUIRE( res_1 == std::make_tuple(c1_1, c2_1, c3_1, c4_1) );
                }
            }
        }

        WHEN("Rows is prepended as separate r-value arguments") {
            df.prepend_row(2, 20, 2., 20.);
            df.prepend_row(1, 10, 1., 10.);

            THEN("The size of the dataframe increases correctly") {
                REQUIRE( df.rows() == 2 );

                AND_THEN("The row can be retreived at the expected position") {
                    dataframe::row_tuple_type res_0 = df.get_tuple_for_row(0);
                    dataframe::row_tuple_type res_1 = df.get_tuple_for_row(1);

                    REQUIRE( res_0 == std::make_tuple(1, 10, 1., 10.) );
                    REQUIRE( res_1 == std::make_tuple(2, 20, 2., 20.) );
                }
            }
        }
    }
}


SCENARIO(
    "Insert rows into the dataframe at arbitrary locations",
    "[dataframe][inserters][insert-rows]"
) {
    GIVEN("An empty dataframe") {
        using dataframe = candas::dataframe<int, int, double, double>;

        dataframe df{};

        WHEN("Rows is inserted as l-value tuples") {
            dataframe::row_tuple_type row_0{ 1, 10, 1., 10. };
            dataframe::row_tuple_type row_1{ 2, 20, 2., 20. };
            dataframe::row_tuple_type row_2{ 3, 30, 3., 30. };
            dataframe::row_tuple_type row_3{ 4, 40, 4., 40. };

            df.insert_row(0, row_1);
            df.insert_row(1, row_2);
            df.insert_row(0, row_0);
            df.insert_row(3, row_3);

            THEN("The size of the dataframe increases correctly") {
                REQUIRE( df.rows() == 4 );

                AND_THEN("The row can be retreived at the expected positions") {
                    dataframe::row_tuple_type res_0 = df.get_tuple_for_row(0);
                    dataframe::row_tuple_type res_1 = df.get_tuple_for_row(1);
                    dataframe::row_tuple_type res_2 = df.get_tuple_for_row(2);
                    dataframe::row_tuple_type res_3 = df.get_tuple_for_row(3);

                    REQUIRE( res_0 == row_0 );
                    REQUIRE( res_1 == row_1 );
                    REQUIRE( res_2 == row_2 );
                    REQUIRE( res_3 == row_3 );
                }
            }
        }

        WHEN("Rows is inserted as r-value tuples") {
            dataframe::row_tuple_type row_0{ 1, 10, 1., 10. };
            dataframe::row_tuple_type row_1{ 2, 20, 2., 20. };
            dataframe::row_tuple_type row_2{ 3, 30, 3., 30. };
            dataframe::row_tuple_type row_3{ 4, 40, 4., 40. };

            df.insert_row(0, std::move(row_1));
            df.insert_row(1, std::move(row_2));
            df.insert_row(0, std::move(row_0));
            df.insert_row(3, std::move(row_3));

            THEN("The size of the dataframe increases correctly") {
                REQUIRE( df.rows() == 4 );

                AND_THEN("The row can be retreived at the expected positions") {
                    dataframe::row_tuple_type res_0 = df.get_tuple_for_row(0);
                    dataframe::row_tuple_type res_1 = df.get_tuple_for_row(1);
                    dataframe::row_tuple_type res_2 = df.get_tuple_for_row(2);
                    dataframe::row_tuple_type res_3 = df.get_tuple_for_row(3);

                    REQUIRE( res_0 == row_0 );
                    REQUIRE( res_1 == row_1 );
                    REQUIRE( res_2 == row_2 );
                    REQUIRE( res_3 == row_3 );
                }
            }
        }

        WHEN("Rows is inserted as separate l-value arguments") {
            int c1_0 = 1, c2_0 = 10,
                c1_1 = 2, c2_1 = 20,
                c1_2 = 2, c2_2 = 20,
                c1_3 = 2, c2_3 = 20;
            double c3_0 = 1., c4_0 = 10.,
                   c3_1 = 2., c4_1 = 20.,
                   c3_2 = 2., c4_2 = 20.,
                   c3_3 = 2., c4_3 = 20.;

            df.insert_row(0, c1_1, c2_1, c3_1, c4_1);
            df.insert_row(1, c1_2, c2_2, c3_2, c4_2);
            df.insert_row(0, c1_0, c2_0, c3_0, c4_0);
            df.insert_row(3, c1_3, c2_3, c3_3, c4_3);

            THEN("The size of the dataframe increases correctly") {
                REQUIRE( df.rows() == 4 );

                AND_THEN("The row can be retreived at the expected positions") {
                    dataframe::row_tuple_type res_0 = df.get_tuple_for_row(0);
                    dataframe::row_tuple_type res_1 = df.get_tuple_for_row(1);
                    dataframe::row_tuple_type res_2 = df.get_tuple_for_row(2);
                    dataframe::row_tuple_type res_3 = df.get_tuple_for_row(3);

                    REQUIRE( res_0 == std::make_tuple(c1_0, c2_0, c3_0, c4_0) );
                    REQUIRE( res_1 == std::make_tuple(c1_1, c2_1, c3_1, c4_1) );
                    REQUIRE( res_2 == std::make_tuple(c1_2, c2_2, c3_2, c4_2) );
                    REQUIRE( res_3 == std::make_tuple(c1_3, c2_3, c3_3, c4_3) );
                }
            }
        }

        WHEN("Rows is inserted as separate r-value arguments") {
            df.insert_row(0, 2, 20, 2., 20.);
            df.insert_row(1, 3, 30, 3., 30.);
            df.insert_row(0, 1, 10, 1., 10.);
            df.insert_row(3, 4, 40, 4., 40.);

            THEN("The size of the dataframe increases correctly") {
                REQUIRE( df.rows() == 4 );

                AND_THEN("The row can be retreived at the expected positions") {
                    dataframe::row_tuple_type res_0 = df.get_tuple_for_row(0);
                    dataframe::row_tuple_type res_1 = df.get_tuple_for_row(1);
                    dataframe::row_tuple_type res_2 = df.get_tuple_for_row(2);
                    dataframe::row_tuple_type res_3 = df.get_tuple_for_row(3);

                    REQUIRE( res_0 == std::make_tuple(1, 10, 1., 10.) );
                    REQUIRE( res_1 == std::make_tuple(2, 20, 2., 20.) );
                    REQUIRE( res_2 == std::make_tuple(3, 30, 3., 30.) );
                    REQUIRE( res_3 == std::make_tuple(4, 40, 4., 40.) );
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

