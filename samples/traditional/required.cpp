#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include <cppargparse/cppargparse.h>



void add_five(const int value)
{
    std::cout << value << " + 5 = " << value + 5 << '\n';
}


void parse_xml(const std::string &filename)
{
    std::cout << "Parsing XML: " << filename << '\n';

    // parse the XML file here
}


void print_sum(const std::vector<int> &values)
{
    std::cout << "Sum for -s: " << std::accumulate(values.cbegin(), values.cend(), 0) << '\n';
}


int main(int argc, char *argv[])
{
    using namespace cppargparse;
    parser::ArgumentParser arg_parser(argc, argv, "cppargparse sample -- required options -- callback");


    const auto q = arg_parser.add_arg("-q", "--quick-format", "Quickly format a drive");
    const auto f = arg_parser.add_arg("-f", "--five", "Add 5 to the given input");
    const auto x = arg_parser.add_arg("-x", "--xml", "Parse an XML file");
    const auto s = arg_parser.add_arg("-s", "--sum", "Print the sum of an integer sequence");


    const bool quick_format = arg_parser.get_flag(q);
    std::cout << "quick format: " << quick_format << '\n';

    const int f_value = arg_parser.get_option<int>(f);
    add_five(f_value);

    const std::string xml = arg_parser.get_option<std::string>(x);
    parse_xml(xml);

    const std::vector<int> ints = arg_parser.get_option<std::vector<int>>(s);
    print_sum(ints);


    return 0;
}
