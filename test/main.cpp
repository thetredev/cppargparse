#include <iostream>
#include <limits>

#include <string>
#include <vector>

#include <cppargparse/cppargparse.h>


int main(int argc, char *argv[])
{
    /* Prepare command-line args */
    using namespace cppargparse;
    algorithm::collect_cmdargs(argc, argv);


    /* Flag parsing */

    bool e = parser::parse_flag("-e");
    std::cout << "-e passed: " << (e ? "yes" : "no") << '\n';


    /* String parsing with exception handling */

    try
    {
        std::string t = parser::parse_arg<std::string>("-t");
        std::cout << "-t = " << t << '\n';
    }
    catch (const parser::errors::ParserError &ex)
    {
        std::cout << ex.what() << '\n';

        // Exit application here, because "-t" is required.
        return -1;
    }

    try
    {
        std::string u = parser::parse_arg<std::string>("-u");
        std::cout << "-u = " << u << '\n';
    }
    catch (const parser::errors::ParserError &ex)
    {
        std::cout << ex.what() << '\n';

        // Don't exit application here, "-t" is not required.
    }

    std::vector<std::string> x = parser::parse_arg<std::vector<std::string>>("-L", std::vector<std::string>());

    std::vector<int> ints = parser::parse_arg<std::vector<int>>("-I");
    std::cout << "-I: ";

    for (auto i : ints)
    {
        std::cout << i << ",";
    }

    std::cout << '\n';


    /* Numerical parsing without exception handling */

    std::cout.precision(std::numeric_limits<long double>::max_digits10);

    // int
    int f = parser::parse_arg<int>("-f");
    std::cout << "-f = " << f << '\n';

    // float
    float y = parser::parse_arg<float>("-y", static_cast<float>(3.9312671));
    std::cout << "-y = " << y << '\n';

    // double
    double d = parser::parse_arg<double>("-d", 30.1251);
    std::cout << "-d = " << d << '\n';

    // long double
    long double ld = parser::parse_arg<long double>("-ld", static_cast<long double>(3333.11851715731095712754325121788));
    std::cout << "-ld = " << ld << '\n';


    return 0;
}
