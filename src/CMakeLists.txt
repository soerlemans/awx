project(src)

# Add source files
add_executable(${PROJECT_NAME} main.cpp file_buffer.cpp file_position.hpp)

# Add subdirectories
add_subdirectory(debug)
add_subdirectory(config)

add_subdirectory(exception)

add_subdirectory(lexer)
add_subdirectory(token)

add_subdirectory(parser)
add_subdirectory(node)

add_subdirectory(visitor)
