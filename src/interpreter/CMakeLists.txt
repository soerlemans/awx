# Add source files
target_sources(${PROJECT_NAME} PRIVATE
	field_store.cpp
)

# Add subdirectories
add_subdirectory(tree_walk)
