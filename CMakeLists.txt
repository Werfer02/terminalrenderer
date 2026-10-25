cmake_minimum_required(VERSION 3.20)

project(terminalrenderer LANGUAGES C CXX VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    cmakeutils
    GIT_REPOSITORY https://github.com/Werfer02/cmakeutils.git
    GIT_TAG main
)
FetchContent_MakeAvailable(cmakeutils)
include(${cmakeutils_SOURCE_DIR}/utils.Cmake)

FetchContent_Declare(
    coututils
    GIT_REPOSITORY https://github.com/Werfer02/coututils.git
    GIT_TAG main
)
FetchContent_MakeAvailable(coututils)
message(STATUS "coututils in: ${coututils_SOURCE_DIR}")

ghdownloadversion(https://github.com/nothings/stb/blob/master/stb_image.h master)

add_executable(out main.cpp 
                   src/fpoint.cpp
                   src/point.cpp
                   src/vec2D.cpp
                   src/color.cpp
                   src/screen.cpp
                   src/renderScreen.cpp
                   src/vertex.cpp)
target_include_directories(out PRIVATE "${coututils_SOURCE_DIR}" "${THIRD_PARTY_INCLUDES}" "include")