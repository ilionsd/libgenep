#pragma once 

#include <memory>
#include <vector>
#include <utility>

#include "genetic_code.h"
#include "../../nucleotide/wide_nucleotide.h"

namespace genetic {
	namespace storing {
		template<typename _Tcontainer>
		class wide_code : public genetic_code < _Tcontainer > {
		public:
			typedef typename genetic_code<_Tcontainer> base_t;
			typedef typename primitive::wide_nucleotide<typename base_t::container_t> nucleotide_t;

			wide_code(const base_t::codesize_t& codeSize) :
				genetic_code(codeSize), code_(codeSize)
			{};

			virtual std::unique_ptr< base_t::nucleotide_t > at(const base_t::codesize_t &index) override {
				typename base_t::container_t container = code_.at(index);
				std::unique_ptr<typename base_t::nucleotide_t> nucleotidePtr(new nucleotide_t(container));
				return nucleotidePtr;
			};
			virtual std::unique_ptr<base_t::nucleotide_t> at(const base_t::codesize_t &index) const override {
				typename base_t::container_t container = code_.at(index);
				std::unique_ptr<typename base_t::nucleotide_t> nucleotidePtr(new nucleotide_t(container));
				return std::move(nucleotidePtr);
			};

		private:
			std::vector<typename base_t::container_t> code_;
		};
	};
};