cmake_minimum_required(VERSION 3.10)
project(RecipeProject LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Network)

add_subdirectory(client)
add_subdirectory(server)
