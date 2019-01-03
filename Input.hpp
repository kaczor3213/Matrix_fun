#pragma once

#include <exception>
#include <fstream>
#include <string>
#include "Sets.hpp"


template <typename T>
Sets<T> load_from_csv_file(std::istream& input) {
	unsigned matrix_size;
	Sets<T> tmp;
	T right;
	input >> matrix_size;
	input.ignore(matrix_size + 1);
	
	tmp.A.data().resize(matrix_size);
	for (auto& row : tmp.A.data())
		row.resize(matrix_size);

	for (auto& row : tmp.A.data()) {
		for (auto& element : row) {
			input >> element;
			input.ignore(1);
		}
		input.ignore(1);
		input >> right;
		tmp.B.push_back(right);
	}

	return tmp;
}

template <typename T>
Sets<T> load_from_csv_file(const std::string &filePath) {
	std::fstream file;
	file.open(filePath);
	if (!file.is_open())
		throw std::runtime_error("Couldn't open" + filePath + "file!\n");
	return 
}