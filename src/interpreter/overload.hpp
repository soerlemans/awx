#ifndef AWX_INTERPRETER_OVERLOAD_HPP
#define AWX_INTERPRETER_OVERLOAD_HPP


namespace interpreter {
// Overload pattern:
//! Helper struct that selects correct lambda to execute in std::visit
template<class... Ts>
struct Overload : Ts... {
  using Ts::operator()...;
};

// Deduction guide for the struct to work
template<class... Ts>
Overload(Ts...) -> Overload<Ts...>;
} // namespace interpreter

#endif // AWX_INTERPRETER_OVERLOAD_HPP
