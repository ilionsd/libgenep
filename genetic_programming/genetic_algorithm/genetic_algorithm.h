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
			using population_t = std::vector<code_t>;
			using population_ref = std::vector<size_t>;

		private:
			//-- Initialization --
			//	initial population count
			function<population_t, size_t> initializer;

			//-- Selection --
			//	Fitness function evaluations
			function<population_ref, std::vector<double>> selector;

			//-- Crossover --
			function<population_t, population_ref> crossover;

			//-- Mutation --
			function<population_t, population_ref> mutator;

			//-- Reduction --
			function<void, population_t> reductor;

			//-- Terminate condition --
			function<bool, void> terminator;



		};
	};
};
