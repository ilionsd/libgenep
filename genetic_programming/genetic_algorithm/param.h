#pragma once

namespace genetic {
	namespace algorithm {
		template<typename T>
		class param {
		public:
			

			T value() {
				return mValue;
			};

		private:
			T mValue;
		};
	};
};
