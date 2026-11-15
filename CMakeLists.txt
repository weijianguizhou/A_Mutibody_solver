cmake_minimum_required(VERSION 3.16)
project(my_solver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Eigen (header-only) ----
set(MBS_EIGEN_DIR "D:/libs/eigen-5.0.0")
if(NOT EXISTS "${MBS_EIGEN_DIR}")
    message(FATAL_ERROR "Eigen 目录不存在: ${MBS_EIGEN_DIR}")
endif()
add_library(eigen INTERFACE)
target_include_directories(eigen INTERFACE ${MBS_EIGEN_DIR})

# ---- mbs 库 (header-only) ----
add_library(mbs INTERFACE)

target_include_directories(mbs INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(mbs INTERFACE eigen)

add_executable(my_solver_app src/main.cpp)
target_link_libraries(my_solver_app PRIVATE mbs)
target_compile_options(my_solver_app PRIVATE
    "$<$<CXX_COMPILER_ID:MSVC>:/W4;/utf-8>"
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall;-Wextra>
)
