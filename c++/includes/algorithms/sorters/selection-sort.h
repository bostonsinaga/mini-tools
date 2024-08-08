#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__SELECTION_SORT_H__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__SELECTION_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

	template <class T, class U = std::nullptr_t>
	class Selection {
	private:
		static void process(
			std::vector<T> &messy,
			std::vector<U> *attached,
			bool &ascending
		);

	public:
		static void solve(
			std::vector<T> &messy,
			std::vector<U> &attached,
			bool ascending = true
		);

		static void solve(
			std::vector<T> &messy,
			bool ascending = true
		);
	};
}}}

#include "selection-sort.cpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__SELECTION_SORT_H__