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
#include "vector"

#include "reelay/common.hpp"
#include "reelay/datafield.hpp"
#include "reelay/intervals.hpp"
#include "reelay/networks/basic_structure.hpp"

namespace reelay {
namespace untimed_robustness_setting {

template <typename X, typename V, typename K = std::string>
struct atomic_string final : public untimed_state<X, V> {
  using key_t = K;
  using input_t = X;
  using output_t = V;

  key_t key;
  std::string constant;

  output_t value = -reelay::infinity<output_t>::value();

  explicit atomic_string(const key_t &k, const std::string &c)
      : key(k), constant(c) {}

  explicit atomic_string(const kwargs &kw)
      : atomic_string(reelay::any_cast<key_t>(kw.at("key")),
                       reelay::any_cast<std::string>(kw.at("constant"))) {}

  void update(const input_t &args) override {

    if (not datafield<input_t>::contains(args, key)) {
      return; // Do nothing if the key does not exist - existing value persists
    }

    std::string new_data = datafield<input_t>::as_string(args, key);

    if (new_data == constant) {
      value = reelay::infinity<output_t>::value();
    } else {
      value = -reelay::infinity<output_t>::value();
    }
  }

  output_t output() override { return value; }
};

} // namespace untimed_setting
} // namespace reelay