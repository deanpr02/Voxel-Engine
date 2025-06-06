cmake_minimum_required(VERSION 3.27.0)
project(VoxelEngine VERSION 0.0.0)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/glad.c src/shader.cpp src/camera.cpp src/q_math.cpp src/engine.cpp src/renderer.cpp src/chunk_manager.cpp src/generator.cpp src/physics.cpp src/player.cpp src/stb_image.cpp src/weapon.cpp src/spells.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm
                    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/gtc
                    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stbimage)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw EXCLUDE_FROM_ALL)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)