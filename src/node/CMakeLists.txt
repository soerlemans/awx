

# Add source files
target_sources(${PROJECT_NAME} PRIVATE list.cpp expression.cpp nil.cpp)

# Add subdirectories
add_subdirectory(control)
add_subdirectory(functions)

add_subdirectory(io)

add_subdirectory(lvalue)
add_subdirectory(rvalue)

add_subdirectory(operators)
add_subdirectory(recipes)
