#include "list.hpp"


using namespace nodes;

// Constructor:
List::List(): Node{NodeType::NODE_LIST}, std::list<NodePtr>{}
{}

// Methods:
auto List::accept([[maybe_unused]] NodeVisitor t_visitor) -> void
{}

auto List::print() const -> void
{
  for(auto& ptr : *this)
    ptr->print();
}

// Destructor:
List::~List()
{}
