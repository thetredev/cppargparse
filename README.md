# C++ ArgParse: command line parsing made simple

C++ ArgParse is an open source header-only C++ library. Due to the core's heavy usage of template magic, the library can expose a very easy-to-use interface, so you as an application developer only have to care about the good stuff. Think Python's [argparse](https://docs.python.org/3/library/argparse.html).

[![Build Status](https://travis-ci.org/backraw/cppargparse.svg?branch=master)](https://travis-ci.org/backraw/cppargparse)

*Support for Windows is currently untested.*

If you want to skip the following example and core presentations, you can do so by going straight to [Build tests and install](#Build-tests-and-install).

The source code documentation can be found here: https://backraw.github.io/cppargparse


# The library interface
Let me throw some sample code in there:
```C++
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
```

For more examples see https://github.com/backraw/cppargparse/tree/master/samples.


# The core
All the magic is done via the typed `cppargparse::argument` struct. Each such struct definition **must provide 3 static methods**:
- `T parse(cmd, cmdarg, cmdargs)`
- `T convert(cmd, cmdarg, cmdargs)`
- `const char *error_string(cmdarg)`

Parameter definition:
- `cmd` represents the whole command line inside a `std::vector<std::string>`
- `cmdarg` represents the argument iterator position inside `cmd`
- `cmdargs` represents the command line argument map, e.g. `"arg1" => iterator position 0`

The `cppargparse::parser::ArgumentParser` class provides the `get_option<T>(arg)` and `get_flag(arg)` methods for calling the actual type converter methods provided by the `cppargparse::argument<T>` structs.


Assume the following command line arguments have been passed:
`-t 3 -n "My Name" --enable`
```C++
// -t 3
parse<int>(<cmd>, <argument iterator position 0>, <cmdargs>)
// calls and returns the value of
convert<int>(<cmd>, <argument iterator position 1>, <cmdargs>)
// which is the integer 3.


// -n "My Name"
parse<std::string>(<cmd>, <argument iterator position 2>, <cmdargs>)
// calls and returns the value of
convert<std::string>(<cmd>, <argument iterator position 3>, <cmdargs>)
// which is the string "My Name".


// --enable
// flags are checked only for their existence inside <cmd>,
// they don't provide any conversion methods.
```


## Primitive numerical types
Let's look at the `int` type, for example:
```C++
template <>
struct argument<int>
{
    static int parse(
            const types::CommandLine_t &,
            const types::CommandLineArgument_t &cmdarg,
            const types::CommandLineArgumentsMap_t &)
    {
        return numerical_argument::parse<int>(
            cmdarg,
            CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stoi),
            "integer"
        );
    }

    static int convert(
            const types::CommandLine_t &,
            const types::CommandLineArgument_t &cmdarg,
            const types::CommandLineArgumentsMap_t &)
    {
        return numerical_argument::convert<int>(
            cmdarg,
            CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stoi),
            "integer"
        );
    }
};
```

All it does is call `cppargparse::numerical_argument::parse<int>()` (or `cppargparse::numerical_argument::convert<int>()`) on a command line argument iterator position `cmdarg` and tell the former to use `std::stoi` as the conversion function.

`float`, `double`, and `long double` are implemented in the same way, using
- `std::stof`,
- `std::stod` and
- `std::stold`

as conversion functions, respectively.


The `cppargparse::numerical_argument` namespace provides the actual parser and converter functions:
```C++
template <typename T>
static T convert(
        const types::CommandLineArgument_t &cmdarg,
        const std::function<T(const std::string &, size_t *)> &numerical_converter,
        const std::string &type_string
    )
{
    try
    {
        return numerical_converter(*cmdarg, 0);
    }

    catch (std::invalid_argument const &)
    {
        throw errors::CommandLineOptionError(error_message(cmdarg, type_string));
    }
    catch (std::out_of_range const &)
    {
        throw errors::CommandLineOptionError(error_message(cmdarg, type_string));
    }
}

template <typename T>
static T parse(const types::CommandLineArgument_t &cmdarg,
        const std::function<T(const std::string &, size_t *)> &numerical_converter,
        const std::string &type_string)
{
    return convert(std::next(cmdarg), numerical_converter, type_string);
}
```

`cppargparse::convert()` calls `numerical_converter` with a string as the argument. `numerical_converter` can (currently) be one of the following:
- `std::stoi`
- `std::stof`
- `std::stod`
- `std::stold`

A conversion error is indicated by throwing `errors::CommandLineOptionError` with a custom error message.

`cppargparse::parse()` calls `cppargparse::convert()` with the command line argument next in line.


## String types
Currently only `std::string` is implemented as a string type:
```C++
static const std::string convert(
        const types::CommandLine_t &cmd,
        const types::CommandLineArgument_t &cmdarg,
        const types::CommandLineArgumentsMap_t &)
{
    if (cmdarg == cmd.cend())
    {
        throw errors::CommandLineOptionError(error_message(cmdarg));
    }

    return *cmdarg;
}
```

It just checks whether the end of the command line argumnents list has been reached. If so, thrown an error, if not, return its string value.


## Vector types
Currently only `std::vector<T>` is implemented as a vector type:
```C++
static const std::vector<T> parse(
        const types::CommandLine_t &cmd,
        const types::CommandLineArgument_t &cmdarg,
        const types::CommandLineArgumentsMap_t &cmdargs)
{
    auto options = get_option_values(cmd, cmdarg, cmdargs);
    std::vector<T> values;

    for (auto option : options)
    {
        values.emplace_back(argument<T>::convert(cmd, option, cmdargs));
    }

    return values;
}


static types::CommandLineArguments_t get_option_values(
        const types::CommandLine_t &cmd,
        const types::CommandLineArgument_t &cmdarg,
        const types::CommandLineArgumentsMap_t &cmdargs)
{
    types::CommandLineArguments_t values;

    for (auto cmdarg_value = std::next(cmdarg); cmdarg_value != cmd.end(); ++cmdarg_value)
    {
        if (cmdargs.find(*cmdarg_value) != cmdargs.cend())
        {
            break;
        }

        values.emplace_back(cmdarg_value);
    }

    return values;
}
```

It collects all values tied to the argument and converts each value string to `T`.


## Custom types
... todo ...


# Build tests and install
Build requirements:
- `gcc`, `clang`, or `msvc`
- `cmake`

Then you should be able to build the tests like this:
```
git clone https://github.com/backraw/cppargparse.git
cd cppargparse

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Profiling ..
make tests
```

Of course, you can use every generator that CMake supports.

To install the library, run `sudo make install` inside the build directory.
