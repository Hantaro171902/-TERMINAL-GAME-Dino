cmake_minimum_required(VERSION 3.10)

# Project name and version
project(TerminalDinosaur VERSION 1.0)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set source and header files
set(SOURCES
    src/main.cpp
    # src/utils.cpp
    src/bird.cpp
    src/ground.cpp
    src/dinosaur.cpp
    src/cactus.cpp
    src/game.cpp
    src/cursor_input.cpp
    src/color.cpp
)

set(HEADERS
    # src/headers/utils.hpp
    src/headers/bird.hpp
    src/headers/ground.hpp
    src/headers/dinosaur.hpp
    src/headers/cactus.hpp
    src/headers/game.hpp
    src/headers/cursor_input.hpp
    src/headers/color.hpp
)

# Exe
add_executable(dino ${SOURCES} ${HEADERS})

target_include_directories(dino PRIVATE src/headers)

# Optional: copy asset folder into build dir
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
