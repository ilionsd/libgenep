#pragma once

namespace genetic {
	namespace algorithm {
		enum algorithm {
			div_rem = 0
		};
	};

	template<algorithm::algorithm>
	struct algoritm_selector {
		template<typename T>
		void implementation(T& object) {
			static_assert(false);
		};
	};
};