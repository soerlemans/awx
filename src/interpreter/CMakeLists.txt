# Add source files
target_sources(${PROJECT_NAME} PRIVATE
	stringify.cpp
	field_store.cpp
)

# Add subdirectories
add_subdirectory(tree_walk)
