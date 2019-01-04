#pragma once

#include "Matrix.hpp"

template <typename T>
class Sets
{
public:
	Matrix<T> A;
	std::vector<T> B;

	Matrix<T> generate_matrix() {
		Matrix<T> tmp = A;
		for (auto &row : tmp.data())
			for (auto &element : row)
				element = 0;
		return tmp;
	}

	void print_matrix() {
		for (auto i = 0; i < A.data().size(); i++)
		{
			for (const auto element : A[i])
				std::cout << element << "\t";
			std::cout << " : " << B[i] << "\n";
		}
	}
};

template <typename T>
class Gauss : public Sets<T>
{
private:
	Matrix<T> L;
	std::vector<T> U;
	std::vector<T> swap;
	std::vector<T> results;
public:
	Gauss() {}
	Gauss(const Sets<T> &other) {
		Sets<T>::A = other.A;
		Sets<T>::B = other.B;
		L = Sets<T>::A;
		U = Sets<T>::B;
	}
	void elimination_by_row() {
		for (int i = 0; i < L.data().size(); i++) {
			std::swap(U[i], U[L.max_in_column(i, i)]);
			L.swap_rows(i, L.max_in_column(i, i));
		}
	}

	void elimination_by_column() {
		
		for (int i = 0; i < L.data().size(); i++)
			L.swap_columns(i, L.max_in_row(i, i));
	}

	void solve_matrixes() {
		T ratio;
		for (int i = 0; i < L.data().size(); i++) {
			for (int j = i + 1; j < L.data().size(); j++) {
				ratio = L[j][i] / L[i][i];
				for (int k = i + 1; k < L.data().size(); k++) {
					L[j][k] -= L[i][k] * ratio;
				}
				U[j] -= U[i] * ratio;
			}
		}
	}

	void use_hand()	{
		for (int i = 0; i < L.data().size(); i++)
			swap.push_back(i);
		int max{};
		for (int i = 0; i < L.data().size(); i++)
		{
			max = swap[i];
			for (int j = 0; j < L.data().size(); j++)
				if (max < swap[j])
				{
					max = swap[j];
					std::swap(swap[i], swap[j]);
					std::swap(results[i], results[j]);
				}
		}
		swap.clear();
	}

	void calculate_results(int c) {
		results.resize(L.data().size());
		for (int i = L.data().size() - 1; i >= 0; i--)
		{
			results[i] = U[i];
			for (int j = L.data().size() - 1; j > i; j--)
				results[i] -= L[i][j] * results[j];
			results[i] /= L[i][i];
		}
		if (c == 3 || c == 4) use_hand();
	}

	void print_results() {
		std::cout << "Wyniki: \n";
		for (int i = 0; i < results.size(); i++)
			std::cout << "X" << i << " : " << results[i] << "\n";
		results.clear();
		L = Sets<T>::A;
		U = Sets<T>::B;
	}
};

template <typename T>
class Choleski : public Sets<T>
{
private:
	Matrix<T> L;
	Matrix<T> U;
	std::vector<T> y_results;
	std::vector<T> x_results;
public:
	Choleski() {}
	Choleski(const Sets<T> &other) {
		Sets<T>::A = other.A;
		Sets<T>::B = other.B;
	}

	bool check_symmetry() {
		
		for (int i = 0; i < Sets<T>::A.data().size(); i++)
			for (int j = 0; j < Sets<T>::A.data().size(); j++)
				if (Sets<T>::A[i][j] != Sets<T>::A[j][i]) return false;
		return true;
	}

	bool check_minors() {
		L = Sets<T>::generate_matrix();
		U = Sets<T>::generate_matrix();
		fill_diagonal(L);
		solve_LU();
		for (int i = 0; i < U.data().size(); i++)
			if (U[i][i] == 0) return false;
		return true;
	}

	void fill_diagonal(Matrix<T> &L) {
		for (int i = 0; i < L.data().size(); i++)
			L[i][i] = 1;
	}

	void solve_LU() {
		T tmp{};
		for (int i = 0; i < L.data().size(); i++)
		{
			for (int j = i; j < L.data().size(); j++)
			{
				for (int k = 0; k < i; k++)
				{
					tmp += L[i][k] * U[k][j];
				}
				U[i][j] = Sets<T>::A[i][j] - tmp;
				L[j][i] = (Sets<T>::A[i][j] - tmp) / U[i][i];
				tmp = 0;
			}
		}
	}

	void solve_matrixes() {
		L = Sets<T>::generate_matrix();
		calculate_L();
		find_y(L);
		transponate_matrix(L);
		find_x(L);
	}

	void find_y(Matrix<T> &M) {
		T tmp{};
		y_results.resize(M.data().size());
		for (int i = 0; i < M.data().size(); i++) {
			tmp = Sets<T>::B[i];
			for (int j = 0; j < M.data().size(); j++)
				tmp -= y_results[j] * M[i][j];
			y_results[i] = (tmp / M[i][i]);
		}
	}

	void find_x(Matrix<T> &M) {
		T tmp{};
		x_results.resize(M.data().size());
		for (int i = M.data().size() - 1; i >= 0; i--)
		{
			tmp = y_results[i];
			for (int j = M.data().size() - 1; j >= i; j--)
				tmp -= x_results[j] * M[i][j];
			x_results[i] = tmp / M[i][i];
		}
	}

	void transponate_matrix(Matrix<T> &M) {
		Matrix<T> tmp = M;
		for (int i = 0; i < M.data().size(); i++)
			for (int j = 0; j < M.data().size(); j++)
				tmp[i][j] = M[j][i];
		M = std::move(tmp);
	}

	void calculate_L() {
		T tmp{};
		for (int i = 0; i < L.data().size(); i++) {
			for (int j = 0; j < i; j++)
				tmp += pow(L[i][j], 2);
			L[i][i] = sqrt(Sets<T>::A[i][i] - tmp);
			tmp = 0;
			for (int j = i + 1; j < L.data().size(); j++) {
				for (int k = 0; k < L.data().size(); k++)
					tmp += L[j][k] * L[i][k];
				L[j][i] = (Sets<T>::A[j][i] - tmp) / L[i][i];
			}
			tmp = 0;
		}
	}

	void print_results() {
		std::cout << "Rozwiazania X:\n";
		for (const auto x : x_results)
			std::cout << x <<"\t" ;
		std::cout << "\nRozwiazania Y:\n";
		for (const auto y : y_results)
			std::cout << y << "\t";
		std::cout << "\n\n";
		x_results.clear();
		y_results.clear();
	}
};