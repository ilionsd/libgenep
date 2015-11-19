#pragma once

namespace genetic {
	namespace algorithm {
		template <typename _Tresult, typename... _Targs>
		class function 
		{
		public:
			using result_t = _Tresult;
			using args_t = _Targs;

			virtual result_t operator() (args_t ... args) = 0;
		};
	};
};