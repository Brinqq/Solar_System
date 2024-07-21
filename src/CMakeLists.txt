CMAKE_MINIMUM_REQUIRED(VERSION 3.25.1)
project(solar-system)

set(GLFW ../lib/glfw)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(MSVC_LINK_FLAG "")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(DD engine/gfx/directx)

# setting files
file (GLOB ROOTFILES *.cpp)
file(GLOB ENGINEROOTFILES engine/*.cpp)
file(GLOB GAMEROOTFILES game/*.cpp)
file(GLOB GFXFILES engine/gfx/*.cpp)
file(GLOB ENTITIES game/entity/*.cpp)
file(GLOB WORLD game/world/*.cpp)
file(GLOB DIRECTXFILES ${DD}/*.cpp)

set(SRC ${ROOTFILES} ${ENGINEROOTFILES} ${DIRECTXFILES} ${GFXFILES} ${WORLD} ${ENTITIES})

add_executable(${PROJECT_NAME} ${SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/std:c++17 /Od")
target_link_directories(${PROJECT_NAME} PRIVATE c:/main/dev/libs/butils/bin/MSVC)
target_link_libraries(${PROJECT_NAME} glfw3 d3d11 d3dcompiler butils)

target_link_directories(${PROJECT_NAME}
  PUBLIC ${GLFW}/build/src
)
target_include_directories(${PROJECT_NAME}
  PUBLIC ../include/
  PUBLIC ../include/windows/
  PUBLIC ../include/windows/directx
  PUBLIC ${GLFW}/include
  PUBLIC C:/main/dev/libs/butils/include/
)
