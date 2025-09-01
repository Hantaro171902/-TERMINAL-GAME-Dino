cmake_minimum_required(VERSION 3.15...3.27)

# Project name and version
project(TerminalDinosaur VERSION 1.0)

include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE
         "Enable -ftime-trace to generate time tracing .json files on clang"
         OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(project_options INTERFACE -ftime-trace)
  endif()
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# allow for Sanitizers
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

# Set source and header files
set(SOURCES
    src/main.cpp
    src/bird.cpp
    src/cactus.cpp
    src/game.cpp
    src/ground.cpp
    src/dinosaur.cpp
    src/ansi_renderer.cpp
    src/color.cpp
)

set(HEADERS
    src/headers/bird.hpp
    src/headers/cactus.hpp
    src/headers/game.hpp
    src/headers/ground.hpp
    src/headers/dinosaur.hpp
    src/headers/ansi_renderer.hpp
    src/headers/color.hpp
)

# Exe
add_executable(Dino ${SOURCES} ${HEADERS})

target_include_directories(Dino PRIVATE src/headers)

# target_sources(dinosaur_game PRIVATE src/main.cpp src/game.cpp src/obstacles.cpp src/player.cpp)

target_link_libraries(Dino PRIVATE project_options project_warnings)

include(cmake/CreateTargetLink.cmake)
CreateTargetLink(Dino)
