cmake_minimum_required(VERSION 3.16)

# Project configuration following TalentHub Wellington proven patterns
project(PokenoSouthPrimary 
    VERSION 1.0.0
    DESCRIPTION "Student Management System for Pokeno South Primary School"
    LANGUAGES CXX
)

# C++17 standard requirement (TalentHub proven compatibility)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Cross-platform compiler support (GCC/Clang/MSVC)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC specific options
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Clang specific options
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC specific options
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
endif()

# Source files organization following TalentHub structure
set(SOURCES
    src/main.cpp
    src/common.cpp
    src/Student.cpp
    src/Course.cpp  
    src/Assessment.cpp
    src/System.cpp
    src/FileHandler.cpp
    src/Grade.cpp
    src/GradeCalculator.cpp
        src/Usings.hpp
)

set(HEADERS
    src/common.hpp
    src/Student.hpp
    src/Course.hpp
    src/Assessment.hpp
    src/System.hpp
    src/FileHandler.hpp
    src/Grade.hpp
    src/GradeCalculator.hpp
)

# Create executable target
add_executable(PokenoSouthPrimary ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Build configuration output
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building in Debug mode")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_BUILD)
else()
    message(STATUS "Building in Release mode")
    target_compile_definitions(${PROJECT_NAME} PRIVATE RELEASE_BUILD)
endif()

# Platform-specific configurations
if(WIN32)
    # Windows specific settings
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
elseif(APPLE)
    # macOS specific settings
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE FALSE
    )
elseif(UNIX)
    # Linux specific settings
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()

# Installation configuration (following TalentHub deployment patterns)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Copy data directory to build location for testing
file(COPY data/ DESTINATION ${CMAKE_BINARY_DIR}/data/)

# Print build information
message(STATUS "Project: ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")