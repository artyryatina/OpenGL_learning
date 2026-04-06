cmake_minimum_required(VERSION 3.10)
project(OpenGL_learning)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

add_subdirectory(external)

set(libs
        ${OPENGL_LIBRARY}
        glfw
        glad
        glm
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${libs})
