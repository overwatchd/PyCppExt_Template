cmake_minimum_required(VERSION 3.26)
project(PyCppExt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES "${CMAKE_SOURCE_DIR}/conan_provider.cmake")

# Options
option(BUILD_TESTING "Build tests" ON)

# C++ standard settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find required packages
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)
find_package(fmt REQUIRED)

# Source files
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${SRC_DIR}/*.h")
configure_file(src/config.h.in config.h)

# Main library target
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

# Set Python module properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    SUFFIX "${PYTHON_MODULE_EXTENSION}"
    DEBUG_POSTFIX ${Python3_DEBUG_POSTFIX}
    POSITION_INDEPENDENT_CODE ON
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

# Compile definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE 
    $<$<CONFIG:Debug>:Py_DEBUG>
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    pybind11::module
    fmt::fmt
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_BINARY_DIR}
    ${SRC_DIR}
)

# Post-build copy to test directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${PROJECT_NAME}>
        ${CMAKE_SOURCE_DIR}/test/
    COMMENT "Copying module to test directory"
)

# Testing
if(BUILD_TESTING)
    enable_testing()
    
    if(WIN32)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E env 
                PYTHONPATH=${CMAKE_SOURCE_DIR}/test 
                $<$<CONFIG:Debug>:python_d> 
                $<$<NOT:$<CONFIG:Debug>>:python> 
                -m pytest ${CMAKE_SOURCE_DIR}/test
            COMMENT "Running tests"
        )
    endif()
endif()