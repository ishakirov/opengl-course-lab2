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

# glm
add_subdirectory(lib/glm)
include_directories(lib/glm)

file(GLOB SRC_DIR
    "src/*.hpp"
    "src/*.cpp"
)

add_executable(main ${SRC_DIR})
target_link_libraries(main glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY} ${GLEW_LIBRARY})

# copy shaders dir
file(COPY "shaders" DESTINATION ${PROJECT_BINARY_DIR})
