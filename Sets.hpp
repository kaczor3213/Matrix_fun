#pragma once

#include "Matrix.hpp"

template <typename T>
struct Sets
{
	Matrix<T> A;
	std::vector<T> B;


	void elimination_by_row() {
		for (int i = 0; i < A.data().size(); i++)
			A.swap_row(i, A.max_in_column(i, i));
		std::swap(i, A.max_in_column(i, i));
	}

	void elimination_by_column() {
		for (int i = 0; i < A.data().size(); i++)
			A.swap_columns(i, A.max_in_row(i, i));
	}

	void solve_matrixes() {
		auto ratio;
		for (int i = 0; i < A.data().size(); i++) {
			for (int j = i + 1; j < A.data().size(); j++) {
				ratio = A[j][i] / A[i][i];
				for (int k = i + 1; k < A.data().size()-1; k++) {
					A[j][k] -= A[i][k] * ratio;
					B[k] -= B[i] * ratio;
				}
			}
		}
	}

	
};