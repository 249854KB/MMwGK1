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

# Link against necessary libraries (e.g., OpenGL, GLFW, etc.)
# Adjust the paths accordingly based on your actual file structure
target_link_libraries(myprogram
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libfreeglut.a
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libfreeglut_static.a
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libSOIL.a
    opengl32
    glu32
)




# Set the working directory to the location of the executable
set_property(TARGET myprogram PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# Other configurations...
