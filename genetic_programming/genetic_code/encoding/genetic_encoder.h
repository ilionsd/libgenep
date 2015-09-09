#pragma once

#include <cmath>
#include <vector>
#include <cstdlib>
#include <type_traits>

#include "../genetic_code.h"

namespace genetic {
	namespace encoding {
		template<typename _Tsource, typename _Tstorage>
		class genetic_encoder {
			static_assert(genetic::is_base_of_template_t<genetic_code, _Tstorage>::value,
				"Storage should be derived from genetic_code");
			
		public:
			typedef typename _Tstorage								storage_t;
			typedef typename _Tsource								source_t;
			typedef typename storage_t::container_t					container_t;
			typedef typename genetic_code<container_t>::codesize_t	codesize_t;

			inline genetic_encoder(const codesize_t &codeSize, const int &spaceSize) :
				mCodeSize_(codeSize), mSpaceSize_(spaceSize)
			{};
			inline genetic_encoder(const source_t &points_number, const int &spaceSize) :
				genetic_encoder(get_code_size(points_number), spaceSize)
			{};
			codesize_t code_size() const {
				return mCodeSize_;
			};
			int space_size() const {
				return mSpaceSize_;
			};

			virtual storage_t encode(const std::vector<source_t> &point) const = 0;
			virtual std::vector<source_t> decode(const storage_t &code) const = 0;

		private:
			inline static codesize_t get_code_size(const source_t &points_number) {
				return static_cast<codesize_t>(ceil(log(points_number)));
			};

			codesize_t mCodeSize_;
			int mSpaceSize_;


		};
	}; //-- namespace encoding --
}; //-- namespace genetic --