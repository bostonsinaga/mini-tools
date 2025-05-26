#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS_HPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS_HPP__

#include "types.hpp"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  /** Enums for direction of sorting process */

  enum ORDER_ENUM {ORDER_ASCENDING, ORDER_DESCENDING};
  enum PRIORITY_ENUM {PRIORITY_LOWERCASE, PRIORITY_UPPERCASE};

  typedef const ORDER_ENUM& CR_ORDER_ENUM;
  typedef const PRIORITY_ENUM& CR_PRIORITY_ENUM;
}}}

#include "bubble.hpp"
#include "comb.hpp"
#include "insertion.hpp"
#include "merge.hpp"
#include "quick.hpp"
#include "selection.hpp"

#endif // __MINI_TOOLS__ALGORITHMS__SORTERS_HPP__