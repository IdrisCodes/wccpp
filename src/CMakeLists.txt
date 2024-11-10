
add_library(wctool INTERFACE ${CMAKE_CURRENT_LIST_DIR}/wctool/wctool.hpp)
target_include_directories(wctool INTERFACE ${CMAKE_CURRENT_LIST_DIR})


find_package(Boost
            1.86.0
            COMPONENTS program_options
            )

if(NOT Boost_FOUND)
message("Boost wasnt found on your system. Downloading could take a long time.")
include(FetchContent)

FetchContent_Declare(
    Boost
    GIT_REPOSITORY https://github.com/boostorg/boost
    GIT_TAG boost-1.86.0
)

set(BUILD_SHARED_LIBS OFF)
FetchContent_MakeAvailable(Boost)
endif()


add_executable(wccpp ccwc.cpp)
target_link_libraries(wccpp PRIVATE wctool boost_program_options)

install(TARGETS wccpp CONFIGURATIONS Release)