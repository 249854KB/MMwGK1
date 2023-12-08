cmake_minimum_required(VERSION 3.12)

project(Lab4)
# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the glm header directory to the include paths
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/glm)

# Add source files
set(SOURCES
    src/glad.c
    src/main.cpp
)

# Add executable target
add_executable(myprogram ${SOURCES})

# Link against necessary libraries (e.g., OpenGL, GLFW, etc.)
# Adjust the paths accordingly based on your actual file structure
target_link_libraries(myprogram
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw3dll.a
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libfreeglut.a
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/libfreeglut_static.a
    opengl32
    glu32
)

# Copy glfw3.dll to the output directory
add_custom_command(TARGET myprogram POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/glfw3.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/freeglut.dll
    $<TARGET_FILE_DIR:myprogram>
)

# Set the working directory to the location of the executable
set_property(TARGET myprogram PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# Other configurations...
