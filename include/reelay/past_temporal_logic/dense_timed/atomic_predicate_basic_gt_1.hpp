/*
 * Copyright (c) 2019 Dogan Ulus
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "functional"
#include "memory"
#include "vector"


#include "reelay/intervals.hpp"
#include "reelay/networks/basic_structure.hpp"


namespace reelay {
namespace dense_timed_setting {

template <typename X, typename T>
struct basic_predicate_gt<X, T, 1>
    : public dense_timed_state<X, interval_set<T>, T> {
  using input_t = X;
  using time_t = T;

  using base_t = reelay::interval_set<time_t>;
  using output_t = reelay::interval_set<time_t>;

  using function_t =
      std::function<output_t(const input_t &, const input_t &, time_t, time_t)>;

  using interval = reelay::interval<time_t>;
  using interval_set = reelay::interval_set<time_t>;

  interval_set value = interval_set();
  function_t fn;

  basic_predicate_gt(std::string name, float c)
      : fn([name, c](const input_t &pargs, const input_t &args, time_t previous,
                     time_t now) {
          float y0 = std::stof(pargs.at(name));
          float y1 = std::stof(args.at(name));

          if (y0 < c and y1 < c) {
            return interval_set();
          } else if (y0 > c and y1 > c) {
            return interval_set(interval::left_open(previous, now));
          } else if (y0 > y1) {
            time_t crossing = now - (now - previous) * ((c - y1) / (y0 - y1));
            return interval_set(interval::left_open(previous, crossing));
          } else if (y0 < y1) {
            time_t crossing =
                previous + (now - previous) * ((c - y0) / (y1 - y0));
            return interval_set(interval::left_open(crossing, now));
          } else { // y0 == y1 == c is true
            return interval_set();
          }
        }) {}

  void update(const input_t &pargs, const input_t &args, time_t previous,
              time_t now) override {
    value = fn(pargs, args, previous, now);
  }

  output_t output(time_t previous, time_t now) override { return value; }
};

}  // namespace dense_timed_setting
}  // namespace reelay