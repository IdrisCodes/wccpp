#include <string_view>
#include <filesystem>
#include <gmock/gmock.h>

#include <wctool/wctool.hpp>

using namespace testing;

#ifndef TEST_FILE_PATH
#error "Must specify path for the Art of war text file."
#endif

constexpr size_t TestFileLineCount{7143ULL};
constexpr size_t TestFileByteCount{342160ULL};
constexpr size_t TestFileCharCount{339262ULL};
constexpr size_t TestFileWordCount{58164ULL};

TEST(ArtOfWarTests, CountLines)
{
    std::filesystem::path testPath(TEST_FILE_PATH);
    wctool wc;

    wc << testPath;
    EXPECT_THAT(wc.getLineCount(), Eq(TestFileLineCount));
}

TEST(ArtOfWarTests, CountWords)
{
    std::filesystem::path testPath(TEST_FILE_PATH);
    wctool wc;

    wc << testPath;
    EXPECT_THAT(wc.getWordCount(), Eq(TestFileWordCount));
}


TEST(ArtOfWarTests, CountCharacters)
{
    std::filesystem::path testPath(TEST_FILE_PATH);
    wctool wc;

    wc << testPath;
    EXPECT_THAT(wc.getCharCount(), Eq(TestFileCharCount));
}



