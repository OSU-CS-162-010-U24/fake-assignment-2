#include <iostream>

#include "ingredient.hpp"

std::string read_ingredient_name(std::ifstream& file) {
	std::string name;
	std::getline(file, name);
	return name;
}

double read_ingredient_quantity(std::ifstream& file) {
	std::string quantity_string;
	std::getline(file, quantity_string);
	return std::stod(quantity_string);
}

std::string read_ingredient_unit(std::ifstream& file) {
	std::string unit;
	std::getline(file, unit);
	return unit;
}

ingredient read_ingredient(std::ifstream& file) {
	ingredient result;

	// Populate result's member variables with data read from 
	// the file
	result.name = read_ingredient_name(file);
	result.quantity = read_ingredient_quantity(file);
	result.unit = read_ingredient_unit(file);

	return result;
}

void print_ingredient(const ingredient& the_ingredient, double batch_quantity) {
	std::cout << (batch_quantity * the_ingredient.quantity) << " " <<
		the_ingredient.unit << " " << the_ingredient.name << std::endl;
}


void save_ingredient_name(
		std::ofstream& file,
		const ingredient& the_ingredient) {
	file << the_ingredient.name << std::endl;
}

void save_ingredient_quantity(
		std::ofstream& file,
		const ingredient& the_ingredient) {
	file << the_ingredient.quantity << std::endl;
}

void save_ingredient_unit(
		std::ofstream& file,
		const ingredient& the_ingredient) {
	file << the_ingredient.unit << std::endl;
}

void save_ingredient(std::ofstream& file, const ingredient& the_ingredient) {
	save_ingredient_name(file, the_ingredient);
	save_ingredient_quantity(file, the_ingredient);
	save_ingredient_unit(file, the_ingredient);
}
