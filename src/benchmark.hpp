#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

// Library Includes:
#include <tabulate/table.hpp>

// Includes:
#include "debug/log.hpp"


// Aliases:
using TimingPair = std::pair<std::string_view, int>;

// Functions:
auto unpack([[maybe_unused]] tabulate::Table& t_table) -> void
{}

template<typename... Args>
auto unpack(tabulate::Table& t_table, TimingPair t_pair, Args&&... t_args)
  -> void
{
  using namespace tabulate;

  std::stringstream ss;
  ss << t_pair.second;

  t_table.add_row({t_pair.first, ss.str()});

  unpack(t_table, std::forward<Args>(t_args)...);
}

// TODO: Add alternating colors for the first column?
template<typename... Args>
auto benchmark(Args&&... t_args) -> void
{
  using namespace tabulate;

  Table timing;
  timing.add_row({"Phase", "Time (in ns)"});

  // Heading styling
  timing[0]
    .format()
    .font_align(FontAlign::center)
    .font_style({FontStyle::underline, FontStyle::bold})
    .font_background_color(Color::red);

  // TODO: Does not work?
  // Column styling
  // timing.column(0).format().font_style({FontStyle::bold});

  // Add rows
  unpack(timing, std::forward<Args>(t_args)...);

  DBG_PRINTLN(timing);
}


#endif // BENCHMARK_HPP
