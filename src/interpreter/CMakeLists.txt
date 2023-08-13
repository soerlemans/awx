# Add source files
target_sources(${PROJECT_NAME} PRIVATE
	any.cpp
	field_store.cpp
)

# Add subdirectories
add_subdirectory(builtin)
add_subdirectory(tree_walk)
