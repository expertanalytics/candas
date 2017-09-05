
#include <tuple>

#include "candas/dataframe.hpp"


int main(int argc, char * argv[]) {

    candas::dataframe<2> df;

    auto & [ v1, v2 ] = df.dframe();

}

