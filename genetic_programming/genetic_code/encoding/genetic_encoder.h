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
			typedef typename size_t		codesize_t;



			genetic_encoder(const codesize_t &codeSize) :
				mCodeSize(codeSize)
			{};

			virtual storage_type encode(const source_type &point) = 0;
			virtual source_type	decode(const storage_type &code) = 0;

		private:
			codesize_t mCodeSize;
		};
	}; //-- namespace encoding --
}; //-- namespace genetic --