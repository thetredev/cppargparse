#include <iostream>

#include <cppargparse/cppargparse.h>


void print_usage(const cppargparse::parser::ArgumentParser &arg_parser)
{
    std::cout << arg_parser.usage();
}


int main(int argc, char *argv[])
{
    using namespace cppargparse;
    parser::ArgumentParser arg_parser(argc, argv, "cppargparse sample -- usage -- callback");

    arg_parser.add_help_with_callback(&print_usage);

    return 0;
}
