project(RecipeTests LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Test Core)

add_executable(${PROJECT_NAME}
    test_main.cpp
    test_manager.cpp
    test_manager.hpp
    ../src/recipemanager.cpp
    ../src/recipemanager.hpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Test Qt6::Core)

add_test(NAME RecipeLogicTest COMMAND ${PROJECT_NAME})
