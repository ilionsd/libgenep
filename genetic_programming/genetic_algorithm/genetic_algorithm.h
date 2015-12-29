#pragma once

#include <functional>
#include <map>
#include <vector>

#include "function.h"


namespace genetic {
	namespace algorithm {
		template<typename _Tcoder>
		class genetic_algorithm {
		public:
			using coder_t = _Tcoder;
			using code_t = coder_t::storage_t;

			using individuals_t = std::vector<code_t>;
			using individuals_ref_t = std::vector<size_t>;

		private:
			//-- Initialization --
			//	initial population count
			function<individuals_t, size_t> initializer;

			//-- Selection --
			//	Fitness function evaluations
			function<individuals_ref_t, std::vector<double>> selector;

			//-- Crossover --
			function<individuals_t, individuals_ref_t> crossover;

			//-- Mutation --
			function<individuals_t, individuals_ref_t> mutator;

			//-- Reduction --
			function<void, individuals_t> reductor;

			//-- Terminate condition --
			function<bool, void> terminator;



		};
	};
};
