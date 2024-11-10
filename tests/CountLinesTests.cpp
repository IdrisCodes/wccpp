#include <string_view>
#include <gmock/gmock.h>

#include <wctool/wctool.hpp>

using namespace testing;


TEST(CountLinesTests, CountZeroLines)
{
    std::wstring_view emptyString{L""};
    wctool counter;

    counter << emptyString;
    EXPECT_THAT(counter.getLineCount(), Eq(0));
}


TEST(CountLinesTests, CountOneLineSingleStatement)
{
    std::wstring_view oneLine{L"A man walks his dog."};
    wctool counter;

    counter << oneLine;
    EXPECT_THAT(counter.getLineCount(), Eq(1));
}

TEST(CountLinesTests, CountTwoLinesSingleStatement)
{
    std::wstring_view twoLines{L"A man walks his dog.\nThe wind blows."};
    wctool counter;

    counter << twoLines;
    EXPECT_THAT(counter.getLineCount(), Eq(2));
}

TEST(CountLinesTests, CountZeroLinesTwoStatements)
{
    std::wstring_view emptyString{L""};
    wctool counter;

    counter << emptyString;
    counter << emptyString;
    EXPECT_THAT(counter.getLineCount(), Eq(0));
}

TEST(CountLinesTests, CountOneLineTwoStatements)
{
    std::wstring_view halfLine1 {L"A man walks his dog. "};
    std::wstring_view halfLine2 {L"The weather was lovely."};
    wctool counter;

    counter << halfLine1 << halfLine2;
    EXPECT_THAT(counter.getLineCount(), Eq(1));
}

TEST(CountLinesTests, CountTwoLinesTwoStatements)
{
    std::wstring_view halfLine1 {L"A man walks his dog.\n"};
    std::wstring_view halfLine2 {L"The weather was lovely."};
    wctool counter;

    counter << halfLine1 << halfLine2;
    EXPECT_THAT(counter.getLineCount(), Eq(2));
}
