#pragma once

#include "../genetic_code.h"

namespace genetic {
	namespace encoding {
		template<typename T>
		class binary_encoder : public virtual genetic_code < T > {
		public:
			binary_encoder()
		};
	}; //-- namespace encoding --
}; //-- namespace genetic --