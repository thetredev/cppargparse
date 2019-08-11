#include <string>
#include <vector>

#include <cppargparse/cppargparse.h>


// Struct for parsed command line data
struct CmdValues
{
    bool t;

    int x;
    float z;
    double d;
    long double ld;

    std::string str;

    std::vector<int> ints;
    std::vector<std::string> strings;
};



int main(int argc, char *argv[])
{
    // Parse the command line arguments
    using namespace cppargparse;
    auto arg_parser = parser::ArgumentParser(argc, argv);

    // for example: "-t -x 50"

    // Add arguments
    arg_parser.add_arg("-t");
    arg_parser.add_arg("-x");



    // Create an instance for our parsed command line values
    CmdValues cmdvalues;

    // Check for the flag: -t
    // True if the user pass -t, false if not
    cmdvalues.t = arg_parser.get_flag("-t");


    // Check for the option: -x
    cmdvalues.x = arg_parser.get_option<int>("-x");

    // This above statement will raise an errors::CommandLineArgumentError,
    // if the user didn't pass -t as a command line argument.
    // To get around this, you can either use a try/catch block...

    try
    {
        cmdvalues.x = arg_parser.get_option<int>("-x");
    }

    // The user didn't pass -x
    catch (const errors::CommandLineArgumentError &error)
    {
        // do something with the error
        return -1;
    }

    // The value for -x couldn't be converted to type <int>
    catch (const errors::CommandLineOptionError &error)
    {
        // do something with the error
        return -1;
    }

    // ... or provide a default value for -x:
    cmdvalues.x = arg_parser.get_option<int>("-x", 0);

    // This will set cmdvalues.x to 0 if the user didn't pass -x <value>


    // Floats, doubles and long doubles are the same
    cmdvalues.z = arg_parser.get_option<float>("-z", 742.22f);
    cmdvalues.d = arg_parser.get_option<double>("-d");
    cmdvalues.ld = arg_parser.get_option<long double>("-ld");


    // Strings:
    cmdvalues.str = arg_parser.get_option<std::string>("--str", "--str NOT PASSED");


    // Vectors:
    cmdvalues.ints = arg_parser.get_option<std::vector<int>>("--ints", std::vector<int>());
    cmdvalues.strings = arg_parser.get_option<std::vector<std::string>>("--strings", std::vector<std::string>());


    return 0;
}
