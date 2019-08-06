#include <iostream>

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

    std::cout << "-t = " << t << '\n';
    std::cout << "-f = " << f << '\n';
    std::cout << "-y = " << y << '\n';

    return 0;
}
