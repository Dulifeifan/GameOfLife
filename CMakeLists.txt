cmake_minimum_required(VERSION 3.12)
project(life)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
find_package(TBB COMPONENTS tbbmalloc tbbmalloc_proxy tbb_preview)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
include_directories(${OpenCV_INCLUDE_DIRS})

INCLUDE_DIRECTORIES(/usr/local/Cellar/opencv/3.4.3/include/opencv2)
INCLUDE_DIRECTORIES(/usr/local/Cellar/tbb)
add_executable(life main.cpp)
target_link_libraries(life ${OpenCV_LIBS})
target_link_libraries(life tbb)