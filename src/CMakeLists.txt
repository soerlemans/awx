# Add source files
target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
)

# Add subdirectories
add_subdirectory(debug)
add_subdirectory(config)
add_subdirectory(exception)
add_subdirectory(container)

add_subdirectory(token)
add_subdirectory(lexer)

add_subdirectory(node)
add_subdirectory(parser)

add_subdirectory(visitor)
add_subdirectory(interpreter)
