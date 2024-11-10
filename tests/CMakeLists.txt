
include(FetchContent)

set(INSTALL_GTEST OFF)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG main
)


FetchContent_MakeAvailable(googletest)

#Download 'The art of war' file for testing

file(DOWNLOAD
    "https://www.gutenberg.org/cache/epub/132/pg132.txt"
    "${CMAKE_CURRENT_LIST_DIR}/test.txt")


add_executable(testrunner CountLinesTests.cpp CountWordsTests.cpp ArtOfWarTests.cpp CountCharsTests.cpp)
target_link_libraries(testrunner PRIVATE wctool GTest::gtest_main GTest::gmock)
target_compile_definitions(testrunner PRIVATE TEST_FILE_PATH="${CMAKE_CURRENT_LIST_DIR}/test.txt")

include(GoogleTest)
gtest_discover_tests(testrunner)