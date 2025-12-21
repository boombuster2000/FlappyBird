file(GLOB_RECURSE GAME_SOURCES
        CONFIGURE_DEPENDS
        src/*.cpp
)

add_executable(FlappyBird)

target_include_directories(FlappyBird
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(FlappyBird
        PRIVATE
        ${GAME_SOURCES}
)

target_link_libraries(FlappyBird
        PRIVATE engine
)
