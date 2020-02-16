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

#include "reelay/intervals.hpp"
#include "reelay/networks/basic_structure.hpp"
#include "reelay/networks/discrete_timed_network.hpp"

#include "reelay/settings/discrete_timed/atomic_record.hpp"
#include "reelay/settings/discrete_timed/atomic_custom.hpp"

#include "reelay/settings/discrete_timed/conjunction.hpp"
#include "reelay/settings/discrete_timed/disjunction.hpp"
#include "reelay/settings/discrete_timed/implication.hpp"
#include "reelay/settings/discrete_timed/negation.hpp"

#include "reelay/settings/discrete_timed/past_always.hpp"
#include "reelay/settings/discrete_timed/past_sometime.hpp"
#include "reelay/settings/discrete_timed/previous.hpp"
#include "reelay/settings/discrete_timed/since.hpp"

#include "reelay/settings/discrete_timed/past_always_bounded.hpp"
#include "reelay/settings/discrete_timed/past_sometime_bounded.hpp"
#include "reelay/settings/discrete_timed/since_bounded.hpp"

#include "reelay/settings/discrete_timed/past_always_bounded_half.hpp"
#include "reelay/settings/discrete_timed/past_sometime_bounded_half.hpp"
#include "reelay/settings/discrete_timed/since_bounded_half.hpp"

namespace reelay {
namespace discrete_timed_setting {

template <class X, class T>
struct factory {
  using input_t = X;
  using time_t = T;

  using value_t = bool;
  using output_t = bool;

  using function_t = std::function<bool(const input_t&)>;

  using interval = reelay::interval<time_t>;
  using interval_set = reelay::interval_set<time_t>;

  using node_t = reelay::discrete_timed_node<output_t, time_t>;
  using state_t = reelay::discrete_timed_state<input_t, output_t, time_t>;
  using network_t = reelay::discrete_timed_network<input_t, output_t, time_t>;

  using node_ptr_t = std::shared_ptr<node_t>;
  using state_ptr_t = std::shared_ptr<state_t>;
  using network_ptr_t = std::shared_ptr<network_t>;

  const static output_t top = true;
  const static output_t bottom = false;

  static node_ptr_t make_node(const std::string &name, const kwargs &kw) {

    node_ptr_t result;

    if (name == "disjunction") {
      result = std::make_shared<disjunction<input_t, time_t>>(kw);
    } else if (name == "conjunction") {
      result = std::make_shared<conjunction<input_t, time_t>>(kw);
    } else if (name == "negation") {
      result = std::make_shared<negation<input_t, time_t>>(kw);
    } else if (name == "implication") {
      result = std::make_shared<implication<input_t, time_t>>(kw);
    } else {
      throw std::invalid_argument(
          "Unsupported operator for the untimed setting");
    }

    return result;
  }

  static state_ptr_t make_state(const std::string &name, const kwargs &kw) {

    state_ptr_t result;

    if (name == "record") {
      result = std::make_shared<record<input_t, time_t>>(kw);
    } else if (name == "previous") {
      result = std::make_shared<previous<input_t, time_t>>(kw);
    } else if (name == "past_sometime") {
      result = std::make_shared<past_sometime<input_t, time_t>>(kw);
    } else if (name == "past_always") {
      result = std::make_shared<past_always<input_t, time_t>>(kw);
    } else if (name == "since") {
      result = std::make_shared<since<input_t, time_t>>(kw);
    } else if (name == "past_sometime_bounded") {
      result = std::make_shared<past_sometime_bounded<input_t, time_t>>(kw);
    } else if (name == "past_always_bounded") {
      result = std::make_shared<past_always_bounded<input_t, time_t>>(kw);
    } else if (name == "since_bounded") {
      result = std::make_shared<since_bounded<input_t, time_t>>(kw);
    } else if (name == "past_sometime_bounded_half") {
      result =
          std::make_shared<past_sometime_bounded_half<input_t, time_t>>(kw);
    } else if (name == "past_always_bounded_half") {
      result = std::make_shared<past_always_bounded_half<input_t, time_t>>(kw);
    } else if (name == "since_bounded_half") {
      result = std::make_shared<since_bounded_half<input_t, time_t>>(kw);
    } else if (name == "predicate") {
      result = std::make_shared<predicate<input_t, time_t>>(kw);
    } else {
      throw std::invalid_argument(
          "Unsupported operator for the untimed setting");
    }

    return result;
  }

};

}  // namespace discrete_timed_setting
}  // namespace reelay