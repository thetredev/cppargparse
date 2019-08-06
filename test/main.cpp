#include <iostream>
#include <limits>

#include <globals.h>
#include <parser.h>

#include <types.h>
#include <type_traits/type_traits.h>


int main(int argc, char *argv[])
{
    using namespace cppargparse;
    parser::parse_arg_list(argc, argv);


    std::string t = parser::parse_arg<std::string>("-t", "BLA");
    int f = parser::parse_arg<int>("-f");
    float y = parser::parse_arg<float>("-y", static_cast<float>(3.9312671));
    double d = parser::parse_arg<double>("-d", 30.1251);
    long double ld = parser::parse_arg<long double>("-ld", static_cast<long double>(3333.11851715731095712754325121788));

    std::cout.precision(std::numeric_limits<long double>::max_digits10);

    std::cout << "-t = " << t << '\n';
    std::cout << "-f = " << f << '\n';
    std::cout << "-y = " << y << '\n';
    std::cout << "-d = " << d << '\n';
    std::cout << "-ld = " << ld << '\n';

    return 0;
}
