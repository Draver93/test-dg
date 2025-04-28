# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.22.1)

project("testcube")


file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)
# Creates your game shared library. The name must be the same as the
# one used for loading in your Kotlin/Java or AndroidManifest.txt files.
message(STATUS "Sources: ${SOURCES}")

add_library(testcube SHARED ${SOURCES})


target_include_directories(testcube PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/third_party
                                            ${CMAKE_CURRENT_SOURCE_DIR}/third_party/json
                                            ${CMAKE_CURRENT_SOURCE_DIR}/third_party/stb)

# Searches for a package provided by the game activity dependency
find_package(game-activity REQUIRED CONFIG)

# Configure libraries CMake uses to link your target library.
target_link_libraries(testcube
        # The game activity
        game-activity::game-activity

        # EGL and other dependent libraries required for drawing
        # and interacting with Android system
        EGL
        GLESv3
        jnigraphics
        android
        log)