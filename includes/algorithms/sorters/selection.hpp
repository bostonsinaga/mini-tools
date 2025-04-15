#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__SELECTION_HPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__SELECTION_HPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

	template <inspector::NUMBER T, class U>
	class Selection {
	private:
		static void process(
			VEC_PAIR2<T, U> &messy,
			CR_ORDER_ENUM order
		);

	public:
		static void solve(
			VEC_PAIR2<T, U> &messy,
			CR_ORDER_ENUM order = ORDER_ASCENDING
		);
	};
}}}

#include "algorithms/sorters/selection.tpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__SELECTION_HPP__