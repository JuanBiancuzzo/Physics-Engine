cmake_minimum_required(VERSION 3.16)
project(GameOfLifeMeetsPhysics)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -o3")

set(SOURCE_ENGINE "${PROJECT_SOURCE_DIR}/src/physics_engine")
set(SOURCE_HERRAMIENTAS "${PROJECT_SOURCE_DIR}/src/herramientas")

add_library(Core
)
add_executable(Main main/main.cpp)

target_link_libraries(Main Core)

# Testeo
set (gtest_force_shared_crt ON CACHE BOOL "MSVC defaults to shared CRT" FORCE)
add_subdirectory(third_party/googletest)
target_compile_definitions(gtest
  PUBLIC
    GTEST_LANG_CXX20
    GTEST_HAS_TR1_TUPLE=0
)
add_executable(tests)

set(TEST_ENGINE "${PROJECT_SOURCE_DIR}/tests/physics_engine")
set(TEST_HERRAMIENTAS "${PROJECT_SOURCE_DIR}/tests/herramientas")

target_sources(tests
)
set_target_properties(tests PROPERTIES COMPILE_FLAGS "${cxx_strict}")
target_link_libraries(tests gtest gtest_main Core)
