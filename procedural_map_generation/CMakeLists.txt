cmake_minimum_required(VERSION 3.20)
project(MazeProject)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable static linking for SFML (optional but makes repo more portable)
add_definitions(-DSFML_STATIC)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all source files
file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

# Add executable
add_executable(Maze ${SOURCES})

# Find SFML (works with vcpkg or manual installation if SFML_DIR is set)
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Link SFML libraries (static version)
target_link_libraries(Maze
    sfml-graphics-s
    sfml-window-s
    sfml-system-s
)

# Add any additional required system libraries for static SFML
if(MSVC)
    target_link_libraries(Maze
        winmm
        gdi32
        opengl32
        freetype
        jpeg
    )
endif()