cmake_minimum_required(VERSION 3.10)

set(PROJECT "test")
set(LIB_FOLDER "lib")
set(BUILD_LIB_FOLDER "build/lib")

# set the project name
project(${PROJECT})

add_subdirectory(${LIB_FOLDER}/glm)
add_subdirectory(${LIB_FOLDER}/glfw)
add_subdirectory(${LIB_FOLDER}/glad)

aux_source_directory(src SRC_LIST)

# add the executable
add_executable(${PROJECT} ${SRC_LIST})

target_include_directories(${PROJECT} PRIVATE src)
set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 20)


target_include_directories(${PROJECT} PRIVATE "${LIB_FOLDER}/glm")
target_include_directories(${PROJECT} PRIVATE "${LIB_FOLDER}/glfw/include")
target_include_directories(${PROJECT} PRIVATE "${BUILD_LIB_FOLDER}/glad/include")

target_link_libraries(${PROJECT} glm)
target_link_libraries(${PROJECT} glfw)
target_link_libraries(${PROJECT} glad)
