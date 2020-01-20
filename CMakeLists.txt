cmake_minimum_required(VERSION 3.11)
project(mafia-slots)

find_package(raylib 2.5 QUIET) 

if (NOT raylib_FOUND) 
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) 

    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

  endif()

endif()

set(hdrs
    src/include/game.h
    src/include/screens.h
)

set(srcs
    src/game.c
    src/screens/screenGame.c
    src/screens/screenBonus.c
)

add_executable(${PROJECT_NAME} main.c ${hdrs} ${srcs})
target_link_libraries(${PROJECT_NAME} raylib)