include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)


add_library(engine STATIC)

file(GLOB_RECURSE ENGINE_SOURCES
        CONFIGURE_DEPENDS
        src/*.cpp
)

file(GLOB_RECURSE ENGINE_HEADERS
        CONFIGURE_DEPENDS
        "include/engine/*.h"
)

target_sources(engine
        PRIVATE
        ${ENGINE_SOURCES}
        PUBLIC
        ${ENGINE_HEADERS}
)

target_include_directories(engine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(engine
        PUBLIC raylib
)
