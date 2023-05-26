#ifndef AWX_INTERPRETER_TREE_WALK_CONTROL_HPP
#define AWX_INTERPRETER_TREE_WALK_CONTROL_HPP


namespace interpreter::tree_walk {
/*! For our Tree Walk Interpreter we implement return statements as a standalone
 * exception as to not get caught by other exception handlers.
 */
struct ReturnExcept {};

/*! For our Tree Walk Interpreter we implement next statements as a standalone
 * exception as to not get caught by other exception handlers.
 */
struct NextExcept {};
} // namespace interpreter::tree_walk

#endif // AWX_INTERPRETER_TREE_WALK_CONTROL_HPP
