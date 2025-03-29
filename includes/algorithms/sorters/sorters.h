#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS_H__
#define __MINI_TOOLS__ALGORITHMS__SORTERS_H__

/** Enums for direction of sorting process */

namespace mini_tools {
namespace algorithms {
namespace sorters {

  enum ORDER_ENUM {ORDER_DESCENDING, ORDER_ASCENDING};
  enum PRIORITY_ENUM {PRIORITY_LOWERCASE, PRIORITY_UPPERCASE};

  typedef const ORDER_ENUM& CR_ORDER_ENUM;
  typedef const PRIORITY_ENUM& CR_PRIORITY_ENUM;
}}}

/** Inclusion */

#include "bubble.h"
#include "comb.h"
#include "insertion.h"
#include "merge.h"
#include "quick.h"
#include "selection.h"

#endif // __MINI_TOOLS__ALGORITHMS__SORTERS_H__