#pragma once

#include <cmath>
#include <iostream>
#include <vector>

namespace Mat
{
	template <typename T>
	class Matrix
	{
	private:
		using v = std::vector<T>;
		v<v<T>> arr;
	public:
		v<T>& data() {
			return arr;
		}
		v<T>& operator[](int index) {
			return arr[index];
		}
		const _m& operator[](int index) const {
			return arr[index];
		}

		void print_matrix() {
			for (const auto row : arr)
			{
				for(const auto element : row)
					std::
			}
		}

		unsigned max_in_column(unsigned y, unsigned from)
		{
			unsigned maxIndex = from;
			for (int i = from+1; i < arr[0].size(); i++)
				if (abs(arr[i][y]) > arr[maxIndex][y]) maxIndex = i;
			return maxIndex;
		}

		unsigned max_in_row(unsigned x, unsigned from)
		{
			unsigned maxIndex = from;
			for (int i = from+1; i < arr[0].size(); i++)
				if (abs(arr[x][i]) > arr[x][maxIndex]) maxIndex = i;
			return maxIndex;
		}

		void swap_columns(unsigned yFirst, unsigned ySecond) {
			if (yFirst == ySecond)
				return;
			for (int i{}; i < arr[yFirst].size(); i++)
				std::swap(arr[i][yFirst], arr[i][ySecond]);
		}

		void swap_rows(unsigned X, unsigned Y) {
			if (X == Y)
				return;
			std::swap(arr[X], arr[Y]);
		}
	};

	
}
