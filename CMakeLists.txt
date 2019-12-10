cmake_minimum_required(VERSION 3.0)

# set project name from current directory
get_filename_component(BASENAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${BASENAME})

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "-Wall")

find_package (OpenCV REQUIRED NO_CMAKE_FIND_ROOT_PATH)

if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    message(STATUS "OpenCV library status:")
    message(STATUS "    version: ${OpenCV_VERSION}")
    message(STATUS "    libraries: ${OpenCV_LIBS}")
    message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
endif()


# define executable to build
include_directories("inc")
aux_source_directory(src SRC_FILES)
add_library(v4l2cpp SHARED ${SRC_FILES})
target_link_libraries(v4l2cpp ${OpenCV_LIBS})

add_executable(client test.cpp)
target_link_libraries(client v4l2cpp ${OpenCV_LIBS})
