/*
 * Copyright (c) 2019-2020 Dogan Ulus
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "functional"
#include "memory"
#include "string"
//
#include "reelay/intervals.hpp"
#include "reelay/networks/basic_structure.hpp"
#include "reelay/parser/ptl.hpp"
#include "reelay/settings/discrete_timed/setting.hpp"
//
#include "reelay/options.hpp"

namespace reelay {

template <typename T, typename X>
struct discrete_timed_network : public discrete_timed_state<X, bool, T> {
  using time_t = T;
  using value_t = bool;
  using input_t = X;
  using output_t = bool;

  using type = discrete_timed_network<time_t, input_t>;
  using factory = discrete_timed_setting::factory<input_t, time_t>;

  using node_t = discrete_timed_node<output_t, time_t>;
  using state_t = discrete_timed_state<input_t, output_t, time_t>;

  using node_ptr_t = std::shared_ptr<node_t>;
  using state_ptr_t = std::shared_ptr<state_t>;

  using setting_t = discrete_timed_setting::factory<input_t, time_t>;
  using options_t = basic_options;

  node_ptr_t root;
  std::vector<state_ptr_t> states;

  time_t now = -1;

  discrete_timed_network(const node_ptr_t& n,
                         const std::vector<state_ptr_t>& ss)
      : root(n), states(ss) {}

  discrete_timed_network(const node_ptr_t& n,
                         const std::vector<state_ptr_t>& ss,
                         const options_t& options)
      : discrete_timed_network(n, ss) {}

  void update(const input_t& args, time_t tn) override {
    for (const auto& state : this->states) {
      state->update(args, tn);
    }
  }

  output_t output(time_t tn) override { return root->output(tn); }

  output_t update(const input_t& args) {
    now = now + time_t(1);
    this->update(args, now);
    return root->output(now);
  }

  output_t output() { return output(now); }

  static type make(const std::string& pattern,
                   const options_t& options = options_t()) {
    auto parser = ptl_parser<type>();
    return parser.parse(pattern, options);
  }

  static std::shared_ptr<type> make_shared(
      const std::string& pattern, const options_t& options = options_t()) {
    auto parser = ptl_parser<type>();
    return parser.make_shared(pattern, options);
  }
};

}  // namespace reelay
