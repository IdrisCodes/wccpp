#include <string_view>
#include <gmock/gmock.h>

#include <wctool/wctool.hpp>

using namespace testing;

TEST(CountWordsTests, CountWordsEmptyString)
{
    std::wstring_view emptyString{L""};
    wctool counter;

    counter << emptyString;
    EXPECT_THAT(counter.getWordCount(), Eq(0));
}

TEST(CountWordsTests, CountWordsOneString)
{
    std::wstring_view oneLiner{L"The weather is nice."};
    wctool counter;

    counter << oneLiner;
    EXPECT_THAT(counter.getWordCount(), Eq(4U));
}

TEST(CountWordsTests, CountWordsTwoStringWordSplit)
{
    std::wstring_view firstLine{L"The weather is ni"};
    std::wstring_view secondLine{L"ce."};
    wctool counter;

    counter << firstLine << secondLine;
    EXPECT_THAT(counter.getWordCount(), Eq(4U));
}

TEST(CountWordsTests, CountWordsTwoLines)
{
    std::wstring_view firstLine{L"The weather is nice.\n"};
    std::wstring_view secondLine{L"Time to go!\n"};
    wctool counter;

    counter << firstLine << secondLine;
    EXPECT_THAT(counter.getWordCount(), Eq(7U));
}
