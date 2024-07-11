#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <string>

#include "ingredient.hpp"

struct recipe {
	std::string name;
	double yield_quantity;
	std::string yield_unit;
	ingredient* ingredients = nullptr;
	int n_ingredients = 0;
	std::string* steps = nullptr;
	int n_steps = 0;
};

ingredient* create_ingredient_array(int n);

std::string* create_steps_array(int n);

void delete_ingredient_array(ingredient*& array);

void delete_recipe(recipe& the_recipe);

std::string read_recipe_name(std::ifstream& file);

double read_recipe_yield_quantity(std::ifstream& file);

std::string read_recipe_yield_unit(std::ifstream& file);

int read_num_ingredients(std::ifstream& file);

int read_num_steps(std::ifstream& file);

std::string read_step(std::ifstream& file);

recipe read_recipe(std::ifstream& file);

void print_yield(const recipe& the_recipe, double batch_quantity);

void print_recipe(const recipe& the_recipe, double batch_quantity);

recipe deep_copy_recipe(const recipe& the_recipe);

void save_recipe_name(
	std::ofstream& file,
	const recipe& the_recipe
);

void save_recipe_yield_quantity(
	std::ofstream& file,
	const recipe& the_recipe
);

void save_recipe_yield_unit(
	std::ofstream& file,
	const recipe& the_recipe
);

void save_recipe(std::ofstream& file, const recipe& the_recipe);

#endif
