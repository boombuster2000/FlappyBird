cmake_minimum_required(VERSION 3.25)
project(FlappyBird LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(FETCHCONTENT_BASE_DIR
        ${CMAKE_SOURCE_DIR}/_deps
        CACHE PATH "FetchContent base directory"
)

include(FetchContent)

add_subdirectory(engine)
add_subdirectory(game)
