#pragma once

#include <type_traits>

#include "../genetic_code.h"

namespace genetic {
	namespace encoding {
		template<typename _Tsource, typename _Tstorage>
		class genetic_encoder {
			static_assert(std::is_base_of<genetic_code, _Tstorage>::value,
				"");
		public:
			typedef typename _Tstorage	storage_type;
			typedef typename _Tsource	source_type;

			genetic_encoder()
			{};

			virtual void encode() = 0;
			virtual void decode() = 0;

		private:
			storage_type code;
		};
	}; //-- namespace encoding --
}; //-- namespace genetic --