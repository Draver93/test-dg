# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.22.1)

project("testcube")


# FetchContent is the preferred way to add external dependencies
include(FetchContent)

# Clone GLM from GitHub
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG        0.9.9.8  # or latest stable tag
)
FetchContent_MakeAvailable(glm)

# tinygltf repo
FetchContent_Declare(
        tinygltf
        GIT_REPOSITORY https://github.com/syoyo/tinygltf.git
        GIT_TAG        v2.8.21  # Use latest stable tag or omit for latest HEAD
)
FetchContent_MakeAvailable(tinygltf)


file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)
# Creates your game shared library. The name must be the same as the
# one used for loading in your Kotlin/Java or AndroidManifest.txt files.
message(STATUS "Sources: ${SOURCES}")

add_library(testcube SHARED ${SOURCES})

target_include_directories(testcube PUBLIC  ${tinygltf_SOURCE_DIR})

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
        log
        glm)