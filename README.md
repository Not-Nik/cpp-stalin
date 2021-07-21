# cpp-stalin is a C++ standard library implementation

stalin currently only supports a small percentage of the standard.
Feel free to contribute to any existing code, or start implementing
something new.

## Structure

 * `include/` - The main include directory
 * `src/` - The source directory. Any implementations for non-template functions are here
 * `test/` - Test directory. Contains tests to ensure the functionality of cpp-stalin

## Configuration

Stalin allows you to set the library version and strictness in the `include/__config` file.
Defining `STALIN_CXX_STD_VERSION_XX` will set the library version to match the standard.
Defining `STALIN_CXX_STD_STRICT` will make the library comply more strictly to the standard.
In non-strict mode stalin will add the `[[maybe_unused]]` and `[[nodiscard]]` attributes in various
places, to silence and generate unused warnings where appropriate.
