#ifndef EVALUATE_VISITOR_HPP
#define EVALUATE_VISITOR_HPP

// STL Includes:
#include <variant>

// Local Includes:
#include "node_visitor.hpp"


class EvaluateVisitor : public NodeVisitor {
  private:
	std::variant<int> m_result;
  public:
	EvaluateVisitor() = default;

	~EvaluateVisitor() override = default;
};

#endif // EVALUATE_VISITOR_HPP
