cmake_minimum_required(VERSION 3.22)

project(bsu-cpp)

set(CMAKE_CXX_STANDARD             23)
set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/tools/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

find_package(Catch REQUIRED)
find_package(Clang REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_CMAKE_DIR}")
# set(Clang_DIR "/usr/lib/llvm-17/lib/cmake/clang")
# set(LLVM_DIR "/usr/lib/llvm-17/lib/cmake/llvm")
include(AddLLVM)

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})

add_definitions(${LLVM_DEFINITIONS})
add_definitions(${CLANG_DEFINITIONS})

find_package(Clang CONFIG)

include(tools/cmake/TestSolution.cmake)
include(tools/cmake/BuildFlags.cmake)
include_directories(tools/util)

function(add_task name)
  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${name})
    add_subdirectory(${name})
  endif()
endfunction()

add_task(00_test/sum)

add_task(01_first_tasks/bin-pow)
add_task(01_first_tasks/diff-pairs)
add_task(01_first_tasks/long-sum)
add_task(01_first_tasks/permutations)
add_task(01_first_tasks/range)
add_task(01_first_tasks/reverse-map)
add_task(01_first_tasks/unique)
add_task(01_first_tasks/word-count)

add_task(02_basic_types/arithmetic-mean)
add_task(02_basic_types/collatz-conjecture)
add_task(02_basic_types/credit-card)
add_task(02_basic_types/fractal)
add_task(02_basic_types/polish-notation)
add_task(02_basic_types/split)

add_task(03_continues_functions/common-elements)
add_task(03_continues_functions/cyclic-shift)
add_task(03_continues_functions/filter-array)
add_task(03_continues_functions/least-missing-digit)
add_task(03_continues_functions/matrix-multiplication)
add_task(03_continues_functions/partition)
add_task(03_continues_functions/permutation)
add_task(03_continues_functions/reverse-array)

add_task(04_structs/entrance)
add_task(04_structs/factorization)
add_task(04_structs/pt-triangle)
add_task(04_structs/quadratic)
add_task(04_structs/sort-students)
add_task(04_structs/swap-sort)
add_task(04_structs/war)

add_task(05_classes_begin/images)

# add_task(09_control_work/kr1)
