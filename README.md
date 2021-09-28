# cpp-stalin is a C++ standard library implementation

stalin currently only supports a small percentage of the standard. Feel free to contribute to any existing code, or start implementing something new.

## Structure

* `include/` - The main include directory
* `src/` - The source directory. Any implementations for non-template functions are here
* `test/` - Test directory. Contains tests to ensure the functionality of cpp-stalin

## Configuration

Stalin allows you to configure the library to your needs in the `include/__config` file.

* Defining `STALIN_CXX_STD_VERSION_XX` will set the library version to match the standard.
* Defining `STALIN_CXX_STD_STRICT` will make the library comply more strictly to the standard. In non-strict mode stalin will add the `[[maybe_unused]]`
  and `[[nodiscard]]` attributes in various places, to silence and generate unused warnings where appropriate.
* Defining `STALIN_CXX_STD_NO_IO` will prevent `basic_filebuf` and the default streams `cin`, `cout`, `cerr` and `clog` as well as their wide counterparts from being
  defined. This reduces the actual dependencies<sup>[1](#fn_one)</sup> <sup>[2](#fn_two)</sup> of cpp-stalin to the basic memory management functions `malloc`, `realloc`
  and `free` and default types defined in `stddef.h` and
  `stdio.h`.
* Defining `STALIN_CXX_STD_FREESTANDING` will limit headers to the [freestanding library standard](https://en.cppreference.com/w/cpp/freestanding). Including any other
  headers will do nothing.

<a name="fn_one"><sup>1</sup></a>: In practice stalin also requires the rest of the C standard library for the `using` directives in the `c*` headers. Most modern
compilers support some way of checking whether a function or type exists so this shouldn't be a big issue.

<a name="fn_two"><sup>2</sup></a>: Even if you don't declare/define these functions, your compiler likely won't complain, as long as the stalin functions using them
aren't instantiated. This means that the required functions depend on your usage of the library.
