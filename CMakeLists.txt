cmake_minimum_required(VERSION 3.12)

project(Lab4)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the glm header directory to the include paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/main.cpp
)

# Add executable target
add_executable(myprogram ${SOURCES})

# Link against necessary libraries (e.g., OpenGL, GLFW, Devil, etc.)
# Adjust the paths accordingly based on your actual file structure
target_link_libraries(myprogram
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libfreeglut.a
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libfreeglut_static.a
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libSOIL.a
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/devIL.dll  # Link against Devil DLL
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/ILU.dll  # Link against Devil DLL
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/ILUT.dll  # Link against Devil DLL
    opengl32
    glu32
)

add_custom_command(TARGET myprogram POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/devil.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/ILU.dll"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/ILUT.dll"
    $<TARGET_FILE_DIR:myprogram>)

# Set the working directory to the location of the executable
set_property(TARGET myprogram PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# Other configurations...
