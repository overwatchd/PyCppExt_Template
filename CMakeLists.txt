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

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:Py_DEBUG>)
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

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:${PROJECT_NAME}>
            ${CMAKE_SOURCE_DIR}/test/
        COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${CMAKE_SOURCE_DIR}/test $<$<CONFIG:Debug>:python_d> $<$<NOT:$<CONFIG:Debug>>:python> -m pytest ${CMAKE_SOURCE_DIR}/test
        COMMENT "Running test"
    )
endif()
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/test" CACHE PATH "Installation Directory" FORCE)
