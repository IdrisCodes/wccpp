#include <string_view>
#include <gmock/gmock.h>

#include <wctool/wctool.hpp>

using namespace testing;


TEST(CountCharsTests, MultibyteChar)
{
    std::string_view str("水");
    wctool wc;

    wc << str;
    
    EXPECT_THAT(wc.getCharCount(), 1U);
    EXPECT_THAT(wc.getByteCount(), 3U);
}