// cpp-stalin (c) Nikolas Wipper 2021

#include <cassert>
#include <type_traits>
#include <initializer_list>

int main() {
    std::initializer_list<int> empty_list;

    // create initializer lists using list-initialization
    std::initializer_list<int> digits {1, 2, 3, 4, 5};

    assert(digits.size() == 5);

    // special rule for auto means 'fractions' has the
    // type std::initializer_list<double>
    auto fractions = {3.14159, 2.71828};

    assert(fractions.size() == 2);
    static_assert(std::is_same<typename decltype(fractions)::value_type, double>::value);

    static_assert(std::initializer_list<int>{1,2,3,4}.size() == 4);
}
