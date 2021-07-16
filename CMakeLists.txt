cmake_minimum_required(VERSION 3.16)
project(GameOfLifeMeetsPhysics)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -o3")
set(SOURCE "${PROJECT_SOURCE_DIR}/src")
set(SOURCE_CUERPOS "${PROJECT_SOURCE_DIR}/src/cuerpos")

add_library(Core
  ${SOURCE}/motorDeFisicas.cpp
  ${SOURCE}/quadtree.cpp
  ${SOURCE}/sistema.cpp
  ${SOURCE}/vector.cpp
  ${SOURCE_CUERPOS}/cuerpoRigido.cpp
  ${SOURCE_CUERPOS}/gjk.cpp
  ${SOURCE_CUERPOS}/linea.cpp
  ${SOURCE_CUERPOS}/circulo.cpp
  ${SOURCE_CUERPOS}/AABB.cpp
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

set(TEST "${PROJECT_SOURCE_DIR}/tests")

target_sources(tests PRIVATE 
    ${TEST}/vector_test.cpp
    ${TEST}/cuerpos_test.cpp
    # ${TEST}/quadtree_test.cpp
    ${TEST}/sistema_test.cpp
)
set_target_properties(tests PROPERTIES COMPILE_FLAGS "${cxx_strict}")
target_link_libraries(tests gtest gtest_main Core)
