cmake_minimum_required(VERSION 3.17)
project(another_test)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 14)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(another_test main.cpp Manager.cpp Manager.h TextureLoader.cpp TextureLoader.h Collision.cpp Collision.h Entity.cpp Entity.h Player.cpp Player.h Weapon.cpp Weapon.h Character.cpp Character.h Button.cpp Button.h)
target_link_libraries(another_test ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf)
