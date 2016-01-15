#pragma once


namespace genetic {
	namespace coding {
		template<typename _Tsrc, typename _Tdst>
		class coder {
		public:
			using source_t = _Tsrc;
			using destination_t = _Tdst;
			virtual destination_t encode(const source_t &source) const = 0;
			virtual source_t decode(const destination_t &code) const = 0;
		};
	};
};