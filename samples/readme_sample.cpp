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
    // For convenience...
    using namespace cppargparse;

    // Collect all passed command line arguments
    algorithm::collect_cmdargs(static_cast<size_t>(argc), const_cast<const char**>(argv));

    // for example: -t -x 50


    // Create an instance for our parsed command line values
    CmdValues cmdvalues;

    // Check for the flag: -t
    // True if the user pass -t, false if not
    cmdvalues.t = parser::parse_flag("-t");


    // Check for the option: -x
    cmdvalues.x = parser::parse_arg<int>("-x");

    // This above statement will raise an errors::CommandLineArgumentError,
    // if the user didn't pass -t as a command line argument.
    // To get around this, you can either use a try/catch block...

    try
    {
        cmdvalues.t = parser::parse_arg<int>("-x");
    }
    catch (const errors::CommandLineArgumentError &error)
    {
        // do something with the error
        return -1;
    }

    // ... or provide a default value for -x:
    cmdvalues.x = parser::parse_arg<int>("-x", 0);

    // This will set cmdvalues.x to 0 if the user didn't pass -x <value>


    // Floats, doubles and long doubles are the same
    cmdvalues.z = parser::parse_arg<float>("-z", 742.22f);
    cmdvalues.d = parser::parse_arg<double>("-d");
    cmdvalues.ld = parser::parse_arg<long double>("-ld");


    // Strings:
    cmdvalues.str = parser::parse_arg<std::string>("--str", "--str NOT PASSED");


    // Vectors:
    cmdvalues.ints = parser::parse_arg<std::vector<int>>("--ints", std::vector<int>());
    cmdvalues.strings = parser::parse_arg<std::vector<std::string>>("--strings", std::vector<std::string>());

    return 0;
}
