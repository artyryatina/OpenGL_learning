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

set(UTILS_DIR src/utils)
file(GLOB_RECURSE UTILS_SRC
        ${UTILS_DIR}/*.cpp
        ${UTILS_DIR}/*.h
)

########### LESSON 1 ###########
set(LESSON_TARGET lesson1)

add_executable(${LESSON_TARGET} src/${LESSON_TARGET}/main.cpp
        src/utils/shader_utils.h
        src/utils/shader_utils.cpp)
target_link_libraries(${LESSON_TARGET} ${libs})


########### LESSON 2 ###########
set(LESSON_TARGET lesson2)
set(LESSON_DIR src/${LESSON_TARGET})

FILE(GLOB_RECURSE LESSON_SRC
        ${LESSON_DIR}/*.cpp
        ${LESSON_DIR}/*.h
)

MESSAGE("====" ${LESSON_SRC})
MESSAGE("====+++++++++++++++++++")
MESSAGE("====" ${UTILS_SRC})

add_executable(${LESSON_TARGET} ${LESSON_SRC} ${UTILS_SRC})


target_link_libraries(${LESSON_TARGET} ${libs})

target_include_directories(${LESSON_TARGET} PRIVATE ${UTILS_DIR})

add_custom_command(  # Копіює ресурси з папки src/res у build директорію
        TARGET ${LESSON_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/${LESSON_DIR}/res
        $<TARGET_FILE_DIR:${LESSON_TARGET}>/res
)

########### LESSON 3 ###########

set(LESSON_TARGET lesson3)
set(LESSON_DIR src/${LESSON_TARGET})

FILE(GLOB_RECURSE LESSON_SRC
        ${LESSON_DIR}/*.cpp
        ${LESSON_DIR}/*.h
)

add_executable(${LESSON_TARGET} ${LESSON_SRC} ${UTILS_SRC})

target_link_libraries(${LESSON_TARGET} ${libs})

target_include_directories(${LESSON_TARGET} PRIVATE ${UTILS_DIR})

add_custom_command(  # Копіює ресурси з папки src/res у build директорію
        TARGET ${LESSON_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/${LESSON_DIR}/res
        $<TARGET_FILE_DIR:${LESSON_TARGET}>/res
)

########### LESSON 4 ###########

set(LESSON_TARGET lesson4)
set(LESSON_DIR src/${LESSON_TARGET})

FILE(GLOB_RECURSE LESSON_SRC
        ${LESSON_DIR}/*.cpp
        ${LESSON_DIR}/*.h
)

add_executable(${LESSON_TARGET} ${LESSON_SRC} ${UTILS_SRC})

target_link_libraries(${LESSON_TARGET} ${libs})

target_include_directories(${LESSON_TARGET} PRIVATE ${UTILS_DIR})

add_custom_command(  # Копіює ресурси з папки src/res у build директорію
        TARGET ${LESSON_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/${LESSON_DIR}/res
        $<TARGET_FILE_DIR:${LESSON_TARGET}>/res
)

########### LESSON 5 ###########

set(LESSON_TARGET lesson5)
set(LESSON_DIR src/${LESSON_TARGET})

FILE(GLOB_RECURSE LESSON_SRC
        ${LESSON_DIR}/*.cpp
        ${LESSON_DIR}/*.h
)

add_executable(${LESSON_TARGET} ${LESSON_SRC} ${UTILS_SRC})

target_link_libraries(${LESSON_TARGET} ${libs})

target_include_directories(${LESSON_TARGET} PRIVATE ${UTILS_DIR})

add_custom_command(  # Копіює ресурси з папки src/res у build директорію
        TARGET ${LESSON_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/${LESSON_DIR}/res
        $<TARGET_FILE_DIR:${LESSON_TARGET}>/res
)