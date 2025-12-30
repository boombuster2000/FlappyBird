file(GLOB_RECURSE GAME_SOURCES
        CONFIGURE_DEPENDS
        src/*.cpp
)

add_executable(FlappyBird ${GAME_SOURCES})

target_include_directories(FlappyBird
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(FlappyBird
        PRIVATE engine
)

set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSETS_DST "$<TARGET_FILE_DIR:FlappyBird>/assets")

add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E rm -rf "${ASSETS_DST}"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_DIR}" "${ASSETS_DST}"
        COMMENT "Copying assets"
)

add_dependencies(FlappyBird copy_assets)