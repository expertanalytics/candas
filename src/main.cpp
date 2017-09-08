
#include <iostream>
#include <tuple>

#include "candas/dataframe.hpp"


int main(int argc, char * argv[]) {

    candas::ihdf<double, unsigned int, long long> ihdf;

    using type2 = decltype(ihdf)::dtype_at<2>::type;

    std::cout << "decltype(ihdf)::columns = " << decltype(ihdf)::columns << '\n';
    std::cout << "ihdf has double column:   " << decltype(ihdf)::has_dtype<double>::value << '\n';
    std::cout << "ihdf has int column:      " << decltype(ihdf)::has_dtype<int>::value << '\n';

    ihdf.append_row(std::make_tuple(1., 1u, 1ll));
    ihdf.append_row(std::make_tuple(10., 10u, 10ll));
    ihdf.append_row(std::make_tuple(100., 100u, 100ll));

    auto t4 = std::make_tuple(1000., 1000u, 1000ll);
    ihdf.append_row(t4);

    const auto df_t5 = std::make_tuple(10000., 10000u, 10000ll);
    ihdf.append_row(df_t5);

    auto & [ v1, v2, v3 ] = ihdf.dframe();

    for ( std::size_t i = 0, rows = ihdf.rows(); i < rows; ++i ) {
        std::cout << "ihdf[" << i << "] :: " << v1[i] << " " << v2[i] << " " << v3[i] << '\n';
    }
    std::cout << std::endl;

    // ====================

    candas::hdf<double, 5> hdf;

    std::cout << "decltype(hdf)::columns = " << decltype(hdf)::columns << '\n';
    std::cout << "hdf has double column:   " << decltype(hdf)::has_dtype<double>::value << '\n'
              << "hdf has int column:      " << decltype(hdf)::has_dtype<int>::value << '\n';

    hdf.append_row(std::make_tuple(1., 2., 3., 4., 5.));

    auto hdf_r2 = std::make_tuple(10., 20., 30., 40., 50.);
    hdf.append_row(hdf_r2);

    const auto hdf_r3 = std::make_tuple(100., 200., 300., 400., 500.);
    hdf.append_row(hdf_r3);

    auto [ hv1, hv2, hv3, hv4, hv5 ] = hdf.dframe();

    for ( std::size_t i = 0, rows = hdf.rows(); i < rows; ++i ) {
        std::cout << "hdf[" << i << "] :: " << hv1[i] << " " << hv2[i] << " " << hv3[i] << " " << hv4[i] << " " << hv5[i] << '\n';
    }
    std::cout << std::endl;
}

