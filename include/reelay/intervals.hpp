/*
 * Copyright (c) 2019-2020 Dogan Ulus
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "boost/icl/interval.hpp"
#include "boost/icl/interval_set.hpp"
#include "boost/icl/interval_map.hpp"

namespace boost { namespace icl {

template <typename V> struct robustness_join {
  typedef V &first_argument_type;
  typedef const V &second_argument_type;

  typedef void result_type;

  typedef robustness_join<V> type;

  inline static V identity_element() { return -infinity<V>::value(); }

  void operator()(V &object, const V &operand) const {
    if (object < operand) {
      object = operand;
    }
  }
};

template <typename V> struct robustness_meet {
  typedef V &first_argument_type;
  typedef const V &second_argument_type;

  typedef void result_type;

  typedef robustness_meet<V> type;

  inline static V identity_element() { return infinity<V>::value(); }

  void operator()(V &object, const V &operand) const {
    if (object > operand) {
      object = operand;
    }
  }
};

template <class T> struct inverse<robustness_meet<T>> {
  typedef robustness_join<T> type;
};

template <class T> struct inverse<robustness_join<T>> {
  typedef robustness_meet<T> type;
};

}
}

namespace reelay {

template <class V>
using infinity = boost::icl::infinity<V>; // aka arbitrarily large finite number

template <class T>
using interval = boost::icl::interval<T>;

template <class T>
using interval_set = boost::icl::interval_set<T>;

template <class T, class V>
using robustness_interval_map =
    boost::icl::interval_map<T, V, boost::icl::total_enricher, std::less,
                             boost::icl::robustness_join>;
}  // namespace reelay