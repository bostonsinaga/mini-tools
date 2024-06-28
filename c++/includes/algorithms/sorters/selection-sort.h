#ifndef __ALGORITHMS__SORTERS__SELECTION_SORT_H__
#define __ALGORITHMS__SORTERS__SELECTION_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithm {
namespace sorters {

	class Selection {
	public:
		static void solve(std::vector<int> &messy) {
			int i, j, least; 

			for (i = 0; i < messy.size() - 1; i++) {
				least = i; 

				for (j = i + 1; j < messy.size(); j++) {
					if (messy[j] < messy[least]) least = j;
				}

				std::swap(messy[least], messy[i]);
			}
		}
	};
}}}

#endif // __ALGORITHMS__SORTERS__SELECTION_SORT_H__