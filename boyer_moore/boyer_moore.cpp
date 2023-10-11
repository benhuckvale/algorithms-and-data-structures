#include <string>
#include <array>
#undef CHECK // Undefine conflicting macro
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

using BadCharacterTable = std::array<char, 128>;

/// Make a bad character table for a given "word"
///
/// Return a container such that, in the case of checking for a match by
/// aligning a word with some text, an offset can be looked up for the given
/// char observed in some text so that if that char does not align with the
/// word in its current position, the word should be moved by that offset to
/// find the next search position. If the char is not in the word at all, the
/// offset is such that the word can be moved entirely to a different position.
BadCharacterTable make_bad_character_table(const std::string& word)
{
    const auto size{word.size()};
    BadCharacterTable table;
    table.fill(size);
    for(int i{0}; i<size; ++i) {
        table[word[i]] = size-i-1;
    }
    return table;
}

TEST_CASE("make_bad_character_table")
{
    const auto table{make_bad_character_table("example")};
    CHECK(table['h'] == 7);
    CHECK(table['e'] == 0);
    CHECK(table['x'] == 5);
}

int main(int argc, char* argv[])
{
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    if (context.shouldExit()) return context.run();

    return 0;
}
