cmake_minimum_required(VERSION 3.27.0)
project(Inferno VERSION 0.0.0)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/glad.c src/shader.cpp src/camera.cpp src/q_math.cpp src/maze.cpp src/engine.cpp src/lighting.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm
                    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/gtc)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw EXCLUDE_FROM_ALL)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)