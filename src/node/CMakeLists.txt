project(node)

# Add source files
add_executable(${PROJECT_NAME} node.cpp list.cpp expression.cpp)

# Add subdirectories
add_subdirectory(control)
add_subdirectory(functions)

add_subdirectory(io)

add_subdirectory(lvalue)
#add_subdirectory(rvalue)

add_subdirectory(operators)
add_subdirectory(recipes)
