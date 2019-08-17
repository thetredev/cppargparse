#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include <cppargparse/cppargparse.h>


void do_quick_format(const cppargparse::parser::ArgumentParser &)
{
    std::cout << "Quickly formatting drive..." << '\n';
}


void add_five(const cppargparse::parser::ArgumentParser &, int value)
{
    std::cout << value << " + 5 = " << value + 5 << '\n';
}


void parse_xml(const cppargparse::parser::ArgumentParser &, const std::string &filename)
{
    std::cout << "Parsing XML: " << filename << '\n';

    // parse the XML file here
}


void print_sum(const cppargparse::parser::ArgumentParser &, const std::vector<int> &values)
{
    std::cout << "Sum for -s: " << std::accumulate(values.cbegin(), values.cend(), 0) << '\n';
}


int main(int argc, char *argv[])
{
    using namespace cppargparse;
    parser::ArgumentParser arg_parser(argc, argv, "cppargparse sample -- required options -- callback");


    arg_parser.add_flag_with_callback("-q", "--quick-format", "Quickly format a drive", &do_quick_format);


    arg_parser.add_arg_with_callback<int>("-f", "--five", "Add 5 to the given input", &add_five);

    arg_parser.add_arg_with_callback<std::string>("-x", "--xml", "Parse an XML file", &parse_xml);

    arg_parser.add_arg_with_callback<std::vector<int>>("-s", "--sum", "Print the sum of an integer sequence", &print_sum);


    return 0;
}
