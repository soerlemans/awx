#ifndef AWX_INTERPRETER_TREE_WALK_BOOL_GUARD_HPP
#define AWX_INTERPRETER_TREE_WALK_BOOL_GUARD_HPP

// STL Includes:
#include <stdexcept>


namespace interpreter::tree_walk {
class BoolGuard {
  private:
  bool& m_ref;
  bool m_policy;

  public:
  BoolGuard(bool& t_ref): m_ref{t_ref}, m_policy{true}
  {
    m_ref = m_policy;
  }

  BoolGuard(bool& t_ref, bool t_policy): m_ref{t_ref}, m_policy{t_policy}
  {
    m_ref = m_policy;
  }

  virtual ~BoolGuard()
  {
    m_ref = !m_policy;
  }
};

} // namespace interpreter::tree_walk

#endif // AWX_INTERPRETER_TREE_WALK_BOOL_GUARD_HPP
