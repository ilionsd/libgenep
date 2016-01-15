#pragma once

#include <type_traits>

#include "coder.h"

namespace genetic {
	namespace coding {
		template<typename T1, typename T2>
		class combiner : public coder<typename T1::source_t, typename T2::destination_t> {
			static_assert(std::is_same<T1::destination_t, T2::source_t>::value_type, "");
		public:

			template<typename T>
			combiner(const coder<source_t, T> &coder1, const coder<T, destination_t> &coder2) :
				coder1(coder1),
				coder2(coder2)
			{};

			virtual inline destination_t encode(const source_t &source) const override {
				return 
			};

		private:
			coder<source_t, T> coder1;
			coder<T, destination_t> coder2;
		};
	};
};