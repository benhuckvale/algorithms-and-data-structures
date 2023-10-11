cmake_minimum_required(VERSION 3.27)

project(algorithms)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG        v2.4.10
)
FetchContent_MakeAvailable(doctest)

set(EXES
  binary_search
  boyer_moore
)

foreach(EXE ${EXES})
  add_executable(${EXE} ${EXE}/${EXE}.cpp)
  target_link_libraries(${EXE} PRIVATE doctest)
endforeach()
