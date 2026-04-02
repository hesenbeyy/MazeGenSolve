cmake_minimum_required(VERSION 3.15)
project(MazeGenerator VERSION 1.0 LANGUAGES CXX)

# Force C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find SFML (This works automatically on Linux if libsfml-dev is installed)
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# 2. Identify Source Files
set(SOURCES main.cpp)

# 3. Create the Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# 4. Link SFML Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

# 5. Handle Windows-specific settings (doesn't hurt Linux/Mac)
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
