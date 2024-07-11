#ifndef INGREDIENT_HPP
#define INGREDIENT_HPP

#include <fstream>
#include <string>

struct ingredient {
	std::string name;
	double quantity;
	std::string unit;
};

std::string read_ingredient_name(std::ifstream& file);

double read_ingredient_quantity(std::ifstream& file);

std::string read_ingredient_unit(std::ifstream& file);

ingredient read_ingredient(std::ifstream& file);

void print_ingredient(const ingredient& the_ingredient, double batch_quantity);

void save_ingredient_name(
	std::ofstream& file,
	const ingredient& the_ingredient
);

void save_ingredient_quantity(
	std::ofstream& file,
	const ingredient& the_ingredient
);

void save_ingredient_unit(
	std::ofstream& file,
	const ingredient& the_ingredient
);

void save_ingredient(std::ofstream& file, const ingredient& the_ingredient);

#endif
