project(parser)

# Add source files
add_executable(${PROJECT_NAME} ast.cpp parser.cpp awk_parser.cpp)
