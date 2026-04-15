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

########### LESSON 1 ###########
set(LESSON_TARGET lesson1)

add_executable(${LESSON_TARGET} src/${LESSON_TARGET}/main.cpp)
target_link_libraries(${LESSON_TARGET} ${libs})


########### LESSON 2 ###########
set(LESSON_TARGET lesson2)

add_executable(${LESSON_TARGET} src/${LESSON_TARGET}/main.cpp)
target_link_libraries(${LESSON_TARGET} ${libs})
