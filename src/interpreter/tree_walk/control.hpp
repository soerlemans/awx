#ifndef AWX_INTERPRETER_TREE_WALK_CONTROL_HPP
#define AWX_INTERPRETER_TREE_WALK_CONTROL_HPP


namespace interpreter::tree_walk {
// These exceptions are for implementing control flow functionality in the Tree
// Walk interpreter
struct BreakExcept {};
struct ContinueExcept {};
struct ExitExcept {};
struct NextExcept {};
struct ReturnExcept {};
} // namespace interpreter::tree_walk

#endif // AWX_INTERPRETER_TREE_WALK_CONTROL_HPP
