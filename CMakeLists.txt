cmake_minimum_required(VERSION 3.1)
project(SWRPG)

include_directories("${PROJECT_SOURCE_DIR}/extlibs/SFML/include")
include_directories("${PROJECT_SOURCE_DIR}/extlibs/ChaiScript/include")
include_directories("${PROJECT_SOURCE_DIR}/extlibs/tmx")
include_directories("${PROJECT_SOURCE_DIR}/extlibs/ChaiScript/bin/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_C_COMPILER "/usr/bin/clang")

set(SOURCE_FILES main.cpp KeyBoardSystem.hpp SceneRenderingSystem.hpp Imports.hpp Application.hpp SceneRenderingSystem.cpp KeyBoardSystem.cpp Config.hpp Components.hpp MoveSystem.hpp MoveSystem.cpp AnimationSystem.hpp AnimationSystem.cpp CollisionSystem.hpp CollisionSystem.cpp Application.cpp)

add_executable(swrpg ${SOURCE_FILES})

target_link_libraries(swrpg tmx-loader)
target_link_libraries(swrpg entityx)
target_link_libraries(swrpg sfml-graphics)
target_link_libraries(swrpg sfml-window)
target_link_libraries(swrpg sfml-network)
target_link_libraries(swrpg sfml-system)
