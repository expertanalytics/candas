
#include <iostream>
#include <tuple>

#include "candas/dataframe.hpp"


int main(int argc, char * argv[]) {

    candas::dataframe<2> df;

    df.push_row(std::make_tuple(1., 2.));
    df.push_row(std::make_tuple(10., 20.));
    df.push_row(std::make_tuple(100., 200.));

    auto & [ v1, v2 ] = df.dframe();

    for ( std::size_t i = 0, rows = df.rows(); i < rows; ++i ) {
        std::cout << v1[i] << " " << v2[i] << '\n';
    }
    std::cout << std::endl;

}

