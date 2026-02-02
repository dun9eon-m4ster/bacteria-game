cmake_minimum_required(VERSION 3.5)

project(bacteria-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/SFML/include)

target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system)
