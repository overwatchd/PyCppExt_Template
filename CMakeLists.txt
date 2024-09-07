cmake_minimum_required(VERSION 3.26)
project(PyCppExt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)
find_package(fmt REQUIRED)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${SRC_DIR}/*.h")
configure_file(src/config.h.in config.h)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    SUFFIX "${PYTHON_MODULE_EXTENSION}"
    DEBUG_POSTFIX ${Python3_DEBUG_POSTFIX}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pybind11::module
    fmt::fmt
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_BINARY_DIR}
)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/test" CACHE PATH "Installation Directory" FORCE)
