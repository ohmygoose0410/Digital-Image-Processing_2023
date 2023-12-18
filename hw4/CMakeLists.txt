cmake_minimum_required(VERSION 2.8)
project( main_restoration )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# fetch latest argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

add_executable( main_restoration ./src/main_restoration.cpp ./src/dip.cpp ./src/bitmap.cpp ./src/define.cpp ./src/freq_helper.cpp ./src/argparse.cpp)
target_link_libraries( main_restoration ${OpenCV_LIBS} argparse)
