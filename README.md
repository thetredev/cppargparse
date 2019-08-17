# C++ ArgParse: command line parsing made simple

C++ ArgParse is an open source header-only C++ library. Due to the core's heavy usage of template magic, the library can expose a very easy-to-use interface, so you as an application developer only have to care about the good stuff. Think Python's [argparse](https://docs.python.org/3/library/argparse.html).

[![Build Status](https://travis-ci.org/backraw/cppargparse.svg?branch=master)](https://travis-ci.org/backraw/cppargparse)

*Support for Windows is currently untested.*

If you want to skip the following example and core presentations, you can do so by going straight to [Build tests and install](#Build-tests-and-install).

The source code documentation can be found here: https://backraw.github.io/cppargparse


# The library interface
Please have a look at the [examples](https://github.com/backraw/cppargparse/tree/master/samples).

You can mix [traditional](https://github.com/backraw/cppargparse/tree/master/samples/traditional) and [callback](https://github.com/backraw/cppargparse/tree/master/samples/callback) arguments as you wish. The [ArgumentParser](https://github.com/backraw/cppargparse/blob/master/include/cppargparse/parser.h) class provides an interface for both and doesn't care which one you chose.


# The core
All the magic is done via the typed `cppargparse::argument` struct. Each such struct definition **must provide 3 static methods**:
- `T parse(cmd, position, cmdargs)`
- `T convert(cmd, position, cmdargs)`
- `const char *error_string(position)`

Parameter definition:
- `cmd` represents the whole command line inside a `std::vector<std::string>`
- `position` represents the argument iterator position inside `cmd`
- `cmdargs` represents the command line argument map, e.g. `"arg1" => iterator position 0`

The `cppargparse::parser::ArgumentParser` class provides the `get_option<T>(arg)`, `get_option<T>(arg, default)` and `get_flag(arg)` methods for calling the actual type converter methods provided by the `cppargparse::argument<T>` structs.


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
            const types::CommandLinePosition_t &position,
            const types::CommandLineArguments_t &)
    {
        return numerical_argument::parse<int>(
            position,
            CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stoi),
            "int"
        );
    }

    static int convert(
            const types::CommandLine_t &,
            const types::CommandLinePosition_t &position,
            const types::CommandLineArguments_t &)
    {
        return numerical_argument::convert<int>(
            position,
            CPPARGPARSE_NUMERICAL_ARGUMENT_CONVERTER_OVERLOADS(std::stoi),
            "int"
        );
    }
};
```

All it does is call `cppargparse::numerical_argument::parse<int>()` (or `cppargparse::numerical_argument::convert<int>()`) on a command line argument iterator position `position` and tell the former to use `std::stoi` as the conversion function.

`float`, `double`, and `long double` are implemented in the same way, using
- `std::stof`,
- `std::stod` and
- `std::stold`

as conversion functions, respectively.


The `cppargparse::numerical_argument` namespace provides the actual parser and converter functions:
```C++
template <typename T>
static T convert(
        const types::CommandLinePosition_t &position,
        const std::function<T(const std::string &, size_t *)> &numerical_converter,
        const std::string &type_string
    )
{
    try
    {
        return numerical_converter(*position, 0);
    }

    catch (std::invalid_argument const &)
    {
        throw errors::CommandLineOptionError(error_message(position, type_string));
    }
    catch (std::out_of_range const &)
    {
        throw errors::CommandLineOptionError(error_message(position, type_string));
    }
}

template <typename T>
static T parse(const types::CommandLinePosition_t &position,
        const std::function<T(const std::string &, size_t *)> &numerical_converter,
        const std::string &type_string)
{
    return convert(std::next(position), numerical_converter, type_string);
}
```

`cppargparse::numerical_argument::convert()` calls `numerical_converter` with a string as the argument. `numerical_converter` can (currently) be one of the following:
- `std::stoi`
- `std::stof`
- `std::stod`
- `std::stold`

A conversion error is indicated by throwing `errors::CommandLineOptionError` with a custom error message.

`cppargparse::numerical_argument::parse()` calls `cppargparse::numerical_argument::convert()` with the command line argument next in line.


## String types
Currently only `std::string` is implemented as a string type:
```C++
static const std::string convert(
        const types::CommandLine_t &cmd,
        const types::CommandLinePosition_t &position,
        const types::CommandLineArguments_t &)
{
    if (position == cmd.cend())
    {
        throw errors::CommandLineOptionError(error_message(position));
    }

    return *position;
}
```

It just checks whether the end of the command line argumnents list has been reached. If so, thrown an error, if not, return its string value.


## Vector types
Currently only `std::vector<T>` is implemented as a vector type:
```C++
static const std::vector<T> parse(
        const types::CommandLine_t &cmd,
        const types::CommandLinePosition_t &position,
        const types::CommandLineArguments_t &cmdargs)
{
    auto positions = get_option_positions(cmd, position, cmdargs);
    std::vector<T> values;

    for (auto position : positions)
    {
        values.emplace_back(argument<T>::convert(cmd, position, cmdargs));
    }

    return values;
}


static types::CommandLinePositions_t get_option_positions(
        const types::CommandLine_t &cmd,
        const types::CommandLinePosition_t &position,
        const types::CommandLineArguments_t &cmdargs)
{
    types::CommandLinePositions_t positions;

    for (auto current = std::next(position); current != cmd.end(); ++current)
    {
        if (algorithm::find_arg(cmdargs, *current) != cmdargs.cend())
        {
            break;
        }

        positions.emplace_back(current);
    }

    return positions;
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
