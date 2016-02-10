#pragma once

#ifndef _GENETIC_CODING_CODER_
#define _GENETIC_CODING_CODER_

namespace genetic {
	namespace coding {
		template<typename _Src, typename _Dst>
		class coder {
		public:
			using src = _Src;
			using dst = _Dst;
			virtual dst encode(const src &) const = 0;
			virtual src decode(const dst &) const = 0;
		};
	};
};

#endif
