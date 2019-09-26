# C++ ArgParse: command line parsing made simple

C++ ArgParse is an open source header-only C++11 library for parsing the command line (`argc`, `argv`) in a typed manner.

Due to the core's heavy usage of template magic, the library can expose a very easy-to-use interface, so you as an application developer only have to care about the good stuff. Think Python's [argparse](https://docs.python.org/3/library/argparse.html).

The source code documentation and code coverage results can be found here: https://backraw.github.io/cppargparse

# Build tests
Build requirements:
- `gcc`, `clang`, or `msvc`
- `cmake`

## Linux
```
git clone https://github.com/backraw/cppargparse.git
cd cppargparse

mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Profiling ..
make run_tests
```

Of course, you can use every generator that CMake supports like Ninja, etc.

## Windows
- Create the `build` directory inside the project directory
- Run `cmake -G"Visual Studio 14 Win64" -DCMAKE_BUILD_TYPE=Debug ..`
- Open `cppargparse.sln`
- Build `RUN_TESTS`

*Requires at least Visual Studio 2015. This is because of GTest, which cannot be compiled using Visual Studio 2013 (AFAIK).*

Or simply use MinGW and do it the Linux way on Windows.


# Code coverage
Coverage requirements:
- `gcov`
- `lcov`
- `genhtml`
- `python3`

Run `make coverage` inside the build directory. This will automatically execute `make run_tests` beforehand.


# Source code documentation
Requirements:
- `doxygen`
- `graphviz` (the `dot` command)

Running `doxygen Doxyfile` inside the project directory will update `docs/html`.


# Install
To install the library, run `sudo make install` inside the build directory.


# The library interface
Please have a look at the [examples](https://github.com/backraw/cppargparse/tree/master/samples).

You can mix [traditional](https://github.com/backraw/cppargparse/tree/master/samples/traditional) and [callback](https://github.com/backraw/cppargparse/tree/master/samples/callback) arguments as you wish. The [ArgumentParser](https://github.com/backraw/cppargparse/blob/master/include/cppargparse/parser.h#L242) class provides an interface for both and doesn't care which one you chose.


# The core
All the magic is done via the typed `cppargparse::argument` struct. Each such struct definition **must provide 3 static methods**:
- `T parse(cmd, position, cmdargs)`
- `T convert(cmd, position, cmdargs)`
- `const char *error_string(position)`

Parameter definition:
- `cmd` represents the whole command line inside a `std::vector<std::string>`
- `position` represents the argument iterator position inside `cmd`
- `cmdargs` represents the [command line argument struct object](https://github.com/backraw/cppargparse/blob/master/include/cppargparse/types.h#L41)

The [ArgumentParser](https://github.com/backraw/cppargparse/blob/master/include/cppargparse/parser.h#L242) class provides the `get_option<T>(cmdarg)`, `get_option<T>(cmdarg, default)` and `get_flag(cmdarg)` methods for calling the actual type converter methods provided by the `cppargparse::argument<T>` structs.

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
    static int parse(cmd, position, cmdargs)
    {
        return numerical_argument<int>::convert(cmd, std::next(position), &wrap, "int");
    }

    static int convert(cmd, position, cmdargs)
    {
        return numerical_argument<int>::convert(cmd, position, &wrap, "int");
    }

    static int wrap(const std::string &s)
    {
        return std::stoi(s);
    }
};
```

All it does is the following:
- Call `cppargparse::numerical_argument::parse<int>()` (or `::convert<int>()`) on a command line argument iterator position `position`
- Tell it to use `cppargparse::argument<int>::wrap()` as the conversion function

`wrap()` is needed, because `std::stoi()` (in the case of `int`) cannot be passed as a parameter, since it contains default parameters. `wrap()` just gets rid of them and makes the function "passable".

The `cppargparse::numerical_argument` struct wraps the actual convert-or-error mechanism:
```C++
template <typename T>
struct numerical_argument
{
    static T convert(cmd, position, numerical_converter, type_string)
    {
        if (position == cmd.cend())
        {
            throw errors::CommandLineOptionError(...)
        }

        try
        {
            return numerical_converter(*position);
        }

        catch (const std::invalid_argument &)
        {
            throw errors::CommandLineOptionError(...)
        }
        catch (const std::out_of_range &)
        {
            throw errors::CommandLineOptionError(...)
        }
    }

    static const std::string error_message(position, type_string)
    {
        ...
    }
}
```

`cppargparse::numerical_argument::convert()` calls `numerical_converter` with a string as the argument. `numerical_converter` can (currently) be one of the following:

|**Data type**|**Wrapped converter function**|C++ ArgParse implementation|
|---|---|---|
|`int`|`std::stoi`|[int.h](https://github.com/backraw/cppargparse/tree/master/include/cppargparse/arguments/int.h)
|`unsigned int`|`stou` (custom implementation)|[int.h](https://github.com/backraw/cppargparse/tree/master/include/cppargparse/arguments/int.h)
|`long`|`std::stol`|[long.h](https://github.com/backraw/cppargparse/tree/master/include/cppargparse/arguments/long.h)
|`long long`|`std::stoll`|[long.h](https://github.com/backraw/cppargparse/tree/master/include/cppargparse/arguments/long.h)
|`unsigned long`|`std::stoul`|[long.h](https://github.com/backraw/cppargparse/tree/master/include/cppargparse/arguments/long.h)
|`unsigned long long`|`std::stoull`|[long.h](https://github.com/backraw/cppargparse/tree/master/include/cppargparse/arguments/long.h)
|`float`|`std::stof`|[float.h](https://github.com/backraw/cppargparse/tree/master/include/cppargparse/arguments/float.h)
|`double`|`std::stod`|[double.h](https://github.com/backraw/cppargparse/tree/master/include/cppargparse/arguments/long.h)
|`long double`|`std::stold`|[double.h](https://github.com/backraw/cppargparse/tree/master/include/cppargparse/arguments/double.h)


## String types
Currently only `std::string` is implemented as a string type:
```C++
static const std::string convert(cmd, position, cmdargs)
{
    if (position == cmd.cend())
    {
        throw errors::CommandLineOptionError(...);
    }

    return *position;
}
```

It just checks whether the end of the command line argumnents list has been reached. If so, thrown an error, if not, return the string value for `position`.


## Vector types
Currently only `std::vector<T>` is implemented as a vector type:
```C++
template <typename T>
struct argument<std::vector<T>>
{
    static const std::vector<T> parse(cmd, position, cmdargs)
    {
        auto positions = get_option_positions(cmd, position, cmdargs);
        std::vector<T> values;

        for (auto position : positions)
        {
            // Use the underlying argument::convert() method and store the returned value
            values.emplace_back(argument<T>::convert(cmd, position, cmdargs));
        }

        return values;
    }


    static types::CommandLinePositions_t get_option_positions(cmd, position, cmdargs)
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
}
```

It collects all values tied to the argument and converts each value string to `T`.


## Custom types
... todo ...
