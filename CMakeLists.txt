cmake_minimum_required(VERSION 2.8)
project(OpenGLSampleProject)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Please select another build directory")
endif()

# glfw
add_subdirectory(lib/glfw)
include_directories(lib/glfw/include)

add_executable(main
  src/main.cpp
  src/shader.hpp
  src/shader.cpp
)
target_link_libraries(main glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY} ${GLEW_LIBRARY})

# copy shaders dir
file(COPY "shaders" DESTINATION ${PROJECT_BINARY_DIR})
