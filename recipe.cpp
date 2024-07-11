#include <iostream>

#include "recipe.hpp"

ingredient* create_ingredient_array(int n) {
	return new ingredient[n];
}

void delete_ingredient_array(ingredient*& array) {
	delete [] array;
	array = nullptr;
}

std::string* create_steps_array(int n) {
	return new std::string[n];
}

void delete_steps_array(std::string*& array) {
	delete [] array;
	array = nullptr;
}

void delete_recipe(recipe& the_recipe) {
	delete_ingredient_array(the_recipe.ingredients);
	the_recipe.n_ingredients = 0;
	delete_steps_array(the_recipe.steps);
	the_recipe.n_steps = 0;
}

std::string read_recipe_name(std::ifstream& file) {
	std::string name;
	std::getline(file, name);
	return name;
}

double read_recipe_yield_quantity(std::ifstream& file) {
	std::string yield_quantity_string;
	std::getline(file, yield_quantity_string);
	return std::stod(yield_quantity_string);
}

std::string read_recipe_yield_unit(std::ifstream& file) {
	std::string unit;
	std::getline(file, unit);
	return unit;
}

int read_num_ingredients(std::ifstream& file) {
	std::string num_ingredients_string;
	std::getline(file, num_ingredients_string);
	return std::stoi(num_ingredients_string);
}

int read_num_steps(std::ifstream& file) {
	std::string num_steps_string;
	std::getline(file, num_steps_string);
	return std::stoi(num_steps_string);
}

std::string read_step(std::ifstream& file) {
	std::string step;
	std::getline(file, step);
	return step;
}

recipe read_recipe(std::ifstream& file) {
	recipe result;

	// Populate result's member variables with data read from the file
	result.name = read_recipe_name(file);
	result.yield_quantity = read_recipe_yield_quantity(file);
	result.yield_unit = read_recipe_yield_unit(file);
	result.n_ingredients = read_num_ingredients(file);

	result.ingredients = create_ingredient_array(result.n_ingredients);

	for (int i = 0; i < result.n_ingredients; i++) {
		// Read the ith ingredient from the file, and store it
		// in result.ingredients[i]
		result.ingredients[i] = read_ingredient(file);
	}

	result.n_steps = read_num_steps(file);

	result.steps = create_steps_array(result.n_steps);

	for (int i = 0; i < result.n_steps; i++) {
		// Read the ith step from the file, and store it in
		// result.steps[i]
		result.steps[i] = read_step(file);
	}

	return result;
}

void print_yield(const recipe& the_recipe, double batch_quantity) {
	std::cout << "Yields: " << (batch_quantity * the_recipe.yield_quantity)
		<< " " << the_recipe.yield_unit << std::endl;
}

void print_recipe(const recipe& the_recipe, double batch_quantity) {
	print_yield(the_recipe, batch_quantity);
	std::cout << "Ingredients:" << std::endl;
	for (int i = 0; i < the_recipe.n_ingredients; i++) {
		print_ingredient(the_recipe.ingredients[i], batch_quantity);
	}

	std::cout << std::endl;

	for (int i = 0; i < the_recipe.n_steps; i++) {
		// Print the ith step
		std::cout << (i + 1) << ". " << the_recipe.steps[i]
			<< std::endl;
	}

	std::cout << std::endl;
}

recipe deep_copy_recipe(const recipe& the_recipe) {
	recipe result;
	result.name = the_recipe.name;
	result.yield_quantity = the_recipe.yield_quantity;
	result.yield_unit = the_recipe.yield_unit;
	result.n_ingredients = the_recipe.n_ingredients;
	result.n_steps = the_recipe.n_steps;

	result.ingredients = create_ingredient_array(result.n_ingredients);
	result.steps = create_steps_array(result.n_steps);

	for (int i = 0; i < result.n_ingredients; i++) {
		result.ingredients[i] = the_recipe.ingredients[i];
	}
	for (int i = 0; i < result.n_steps; i++) {
		result.steps[i] = the_recipe.steps[i];
	}

	return result;
}

void save_recipe_name(
		std::ofstream& file,
		const recipe& the_recipe) {
	file << the_recipe.name << std::endl;
}

void save_recipe_yield_quantity(
		std::ofstream& file,
		const recipe& the_recipe) {
	file << the_recipe.yield_quantity << std::endl;
}

void save_recipe_yield_unit(
		std::ofstream& file,
		const recipe& the_recipe) {
	file << the_recipe.yield_unit << std::endl;
}

void save_recipe(
		std::ofstream& file,
		const recipe& the_recipe) {
	save_recipe_name(file, the_recipe);
	save_recipe_yield_quantity(file, the_recipe);
	save_recipe_yield_unit(file, the_recipe);
	file << the_recipe.n_ingredients << std::endl;
	for (int i = 0; i < the_recipe.n_ingredients; i++) {
		save_ingredient(file, the_recipe.ingredients[i]);
	}
	file << the_recipe.n_steps << std::endl;
	for (int i = 0; i < the_recipe.n_steps; i++) {
		file << the_recipe.steps[i] << std::endl;
	}
}
