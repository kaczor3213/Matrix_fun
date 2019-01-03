#pragma once

#include <vector>

namespace Mat
{
	template <typename T>
	class Matrix
	{
	private:
		using _m = std::vector<std::vector<T>>;
		_m<T> arr;
	public:
		_m& data() {
			return arr;
		}
		_m& operator[](int index) {
			return arr[index];
		}
		const _m& operator[](int index) const {
			return arr[index];
		}

		void swap_columns(unsigned X, unsigned Y) {
			if (X == Y)
				return;
			for (int i{}; i < arr[X].size(); i++)
				std::swap(arr[X][i], arr[Y][i]);
		}

		void swap_rows(unsigned X, unsigned Y) {
			if (X == Y)
				return;
			std::swap(arr[X], arr[Y]);
		}
	};

	
}
