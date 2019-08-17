#include <iostream>

#include <cppargparse/cppargparse.h>


int main(int argc, char *argv[])
{
    using namespace cppargparse;
    parser::ArgumentParser arg_parser(argc, argv, "cppargparse sample -- usage -- traditional");

    arg_parser.add_help();

    if (arg_parser.get_flag("-h") || arg_parser.get_flag("--help"))
    {
        std::cout << arg_parser.usage();
    }

    return 0;
}
