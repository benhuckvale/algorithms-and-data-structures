#include <algorithm>
#include <vector>
#undef CHECK // Undefine conflicting macro
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

/// Binary search delegated to std::lower_bound
int search0(std::vector<int>& sorted, int target)
{
    auto itr{std::lower_bound(sorted.cbegin(), sorted.cend(), target)};
    return (itr!=sorted.cend() && (*itr == target)) ? std::distance(sorted.cbegin(), itr) : -1;
}

/// Binary search that uses an iterator and a count, like the possible
/// implementation for std::lower_bound as seen in
/// https://en.cppreference.com/w/cpp/algorithm/lower_bound
int search1(std::vector<int>& sorted, int target) {
    auto begin{sorted.cbegin()};
    auto end{sorted.cend()};
    auto count{std::distance(begin, end)};
    auto itr{begin};
    while(count > 0) {
        const auto step{count/2};
        std::cout<<"count="<<count<<" step="<<step<<" itr="<<std::distance(sorted.cbegin(), itr)<<" target="<<target<<std::endl;
        std::advance(itr, step);
        if (*itr < target) {
            // Undershot
            ++itr;
            count -= step + 1;
        } else {
            // Overshot or have hit
            std::advance(itr, -step);
            count = step;
        }
    }
    return (itr!=end && (*itr == target)) ? std::distance(begin, itr) : -1;
}

/// Binary search that uses start and end indexes
int search2(std::vector<int>& sorted, int target) {
    size_t x{0};
    size_t y{sorted.size()};
    while( x!=y ) {
        size_t m{(x+y)/2};
        std::cout<<"x="<<x<<" y="<<y<<" m="<<m<<" target="<<target<<std::endl;
        int v{sorted[m]};
        if (v<target) {
            x=m+1;
        } else if (v>target) {
            y=m;
        } else {
            return m;
        }
    };
    return -1;
}

TEST_CASE("List is empty") {
    std::vector<int> v;
    int target{0};
    int expected{-1};
    CHECK(search0(v, target) == expected);
    CHECK(search1(v, target) == expected);
    CHECK(search2(v, target) == expected);
}

TEST_CASE("List has one element") {
    std::vector<int> v = {0};
    WHEN("Target is element") {
        int target{0};
        int expected{0};
        CHECK(search0(v, target) == expected);
        CHECK(search1(v, target) == expected);
        CHECK(search2(v, target) == expected);
    }
    WHEN("Target is non-existant") {
        int target{1};
        int expected{-1};
        CHECK(search0(v, target) == expected);
        CHECK(search1(v, target) == expected);
        CHECK(search2(v, target) == expected);
    }
}

TEST_CASE("List is longer") {
    std::vector<int> v = {-1,0,3,5,9,12};
    WHEN("Target is first element") {
        int target{0};
        int expected{1};
        CHECK(search0(v, target) == expected);
        CHECK(search1(v, target) == expected);
        CHECK(search2(v, target) == expected);
    }
    WHEN("Target is element not at either end") {
        int target{9};
        int expected{4};
        CHECK(search0(v, target) == expected);
        CHECK(search1(v, target) == expected);
        CHECK(search2(v, target) == expected);
    }
    WHEN("Target is element at end") {
        int target{12};
        int expected{5};
        CHECK(search0(v, target) == expected);
        CHECK(search1(v, target) == expected);
        CHECK(search2(v, target) == expected);
    }
    WHEN("Target is non-existant") {
        int target{2};
        int expected{-1};
        CHECK(search0(v, target) == expected);
        CHECK(search1(v, target) == expected);
        CHECK(search2(v, target) == expected);
    }
}

int main(int argc, char* argv[])
{
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    if (context.shouldExit()) return context.run();

    return 0;
}
