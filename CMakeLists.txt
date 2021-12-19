cmake_minimum_required(VERSION 3.22)
project(ArchitectureOfComputingSystems_HW5)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(ArchitectureOfComputingSystems_HW5 main.cpp)
target_link_libraries(ArchitectureOfComputingSystems_HW5 Threads::Threads)