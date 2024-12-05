cmake_minimum_required(VERSION 3.28)
project(Project3)

set(CMAKE_CXX_STANDARD 17)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include_directories(src)


include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(Project3
        src/Maze.cpp
        src/Maze.h
        main.cpp
        src/dfs.cpp
        src/dfs.h
        src/bfs.cpp
        src/bfs.h)
target_link_libraries(Project3 PRIVATE sfml-graphics)
target_compile_features(Project3 PRIVATE cxx_std_17)
include_directories(${SFML_INCLUDE_DIRS})

if(WIN32)
    add_custom_command(
            TARGET Project3
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Project3>
            VERBATIM)
endif()