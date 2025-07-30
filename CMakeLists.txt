cmake_minimum_required(VERSION 3.13)

project(Voxels)
add_subdirectory("include/glad")
add_subdirectory("include/glfw-3.4")
add_subdirectory("include/stb")

set(CMAKE_CXX_STANDARD 17)

# Define MY_SOURCES to be a list of all the source files for my project
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(Voxels  "${MY_SOURCES}")

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/res/") # This is useful to get an ASSETS_PATH in your IDE during development but you should comment this if you compile a release version and uncomment the next line
# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./res/") # Uncomment this line to setup the ASSETS_PATH macro to the final assets directory when you share the project

target_link_libraries(Voxels glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(Voxels OpenGL::GL)
target_include_directories(Voxels PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_include_directories(Voxels PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/glad")
target_include_directories(Voxels PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/glad/KHR")
target_include_directories(Voxels PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/glfw-3.4/include/GLFW")
target_include_directories(Voxels PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/stb")
target_include_directories(Voxels PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/glm")
target_link_libraries(Voxels glad stb_image)