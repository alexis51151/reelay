/*
 * Copyright (c) 2019 Dogan Ulus
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "functional"
#include "map"
#include "memory"
#include "string"


#include "reelay/builders.hpp"
#include "reelay/networks.hpp"
#include "reelay/settings.hpp"

#include "reelay/intervals.hpp"

namespace reelay {

template <typename input_t>
struct monitor {
  using factory = untimed_setting::factory<input_t>;

  using network_t = typename factory::network_t;
  using network_ptr_t = typename factory::network_ptr_t;

  using function_t = typename factory::function_t;

  static network_ptr_t from_temporal_logic(
      std::string pattern,
      std::map<std::string, function_t> predicates =
          std::map<std::string, function_t>()) {
    return make_network<factory>::from_temporal_logic(pattern, predicates);
  }
  //    static type from_regular_expressions();
};

template <typename output_t>
struct robustness {
    template <typename input_t>
    struct monitor {
      using factory = untimed_robustness_setting::factory<input_t, output_t>;

      using network_t = typename factory::network_t;
      using network_ptr_t = typename factory::network_ptr_t;

      using function_t = typename factory::function_t;

      static network_ptr_t
      from_temporal_logic(std::string pattern,
                          std::map<std::string, function_t> predicates =
                              std::map<std::string, function_t>()) {
        return make_network<factory>::from_temporal_logic(pattern, predicates);
      }
    };
};

template <typename time_t>
struct discrete_timed {
  template <typename input_t>
  struct monitor {
    using factory = discrete_timed_setting::factory<input_t, time_t>;

    using network_t = typename factory::network_t;
    using network_ptr_t = typename factory::network_ptr_t;

    using function_t = typename factory::function_t;

    static network_ptr_t from_temporal_logic(
        std::string pattern,
        std::map<std::string, function_t> predicates =
            std::map<std::string, function_t>()) {
      return make_network<factory>::from_temporal_logic(pattern, predicates);
    }
    // static network_ptr_t from_regular_expressions();
  };

  template <typename output_t> struct robustness {
    template <typename input_t> struct monitor {
      using factory = 
        discrete_timed_robustness_setting::factory<input_t, output_t, time_t>;

      using network_t = typename factory::network_t;
      using network_ptr_t = typename factory::network_ptr_t;

      using function_t = typename factory::function_t;
      using predicates_t = std::map<std::string, function_t>;

      static network_ptr_t
      from_temporal_logic(std::string pattern,
                          predicates_t predicates = predicates_t()) {
        return make_network<factory>::from_temporal_logic(pattern, predicates);
      }
    };
  };
};

template <typename time_t, int order=0>
struct dense_timed {
  template <typename input_t>
  struct monitor {
    using factory = dense_timed_setting::factory<input_t, time_t, order>;

    using state_t = typename factory::state_t;
    using state_ptr_t = typename factory::state_ptr_t;

    using network_t = typename factory::network_t;
    using network_ptr_t = typename factory::network_ptr_t;
    using function_t = typename factory::function_t;

    static network_ptr_t from_temporal_logic(
        std::string pattern,
        std::map<std::string, function_t> predicates =
            std::map<std::string, function_t>()) {
      return make_network<factory>::from_temporal_logic(pattern, predicates);
    }

    // static type from_regular_expressions();
  };

  // template <typename output_t> struct robustness {
  //   template <typename input_t> struct monitor {
  //     using factory =
  //       dense_timed_robustness_setting::factory<input_t, output_t, time_t>;

  //     using network_t = typename factory::network_t;
  //     using network_ptr_t = typename factory::network_ptr_t;

  //     using function_t = typename factory::function_t;
  //     using predicates_t = std::map<std::string, function_t>;

  //     static network_ptr_t
  //     from_temporal_logic(std::string pattern,
  //                         predicates_t predicates = predicates_t()) {
  //       return make_network<factory>::from_temporal_logic(pattern, predicates);
  //     }
  //   };
  // };
};
}  // namespace reelay
