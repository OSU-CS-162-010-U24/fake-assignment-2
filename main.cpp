#include <iostream>
#include <fstream>

#include "ingredient.hpp"
#include "recipe.hpp"

void greet() {
	std::cout << "Welcome to the Recipe Database!" << std::endl <<
		std::endl;
}

int read_num_recipes(std::ifstream& file) {
	std::string num_recipes_string;
	std::getline(file, num_recipes_string);
	return std::stoi(num_recipes_string);
}

struct recipe_database {
	int n_recipes = 0;
	recipe* recipes = nullptr;
};

void print_recipe_names(const recipe_database& the_database) {
	for (int i = 0; i < the_database.n_recipes; i++) {
		std::cout << (i + 1) << ". " << the_database.recipes[i].name
			<< std::endl;
	}
	std::cout << std::endl;
}

recipe* create_recipe_array(int size) {
	return new recipe[size];
}

void delete_recipe_database(recipe_database& the_database) {
	for (int i = 0; i < the_database.n_recipes; i++) {
		// Delete the ith recipe's array of ingredients, and the
		// ith recipe's array of steps
		delete_recipe(the_database.recipes[i]);
	}
	
	delete [] the_database.recipes;
	the_database.recipes = nullptr;
	the_database.n_recipes = 0;
}

recipe_database read_recipe_database(std::ifstream& file) {
	recipe_database result;

	result.n_recipes = read_num_recipes(file);

	// create array of recipes
	result.recipes = create_recipe_array(result.n_recipes);

	for (int i = 0; i < result.n_recipes; i++) {
		// Read the ith recipe from the file and store it in
		// result.recipes[i]
		result.recipes[i] = read_recipe(file);
	}
	
	return result;
}

void print_menu() {
	std::cout << "What would you like to do?" << std::endl;
	std::cout << "1. View the list of all recipes" << std::endl;
	std::cout << "2. View details of a specific recipe" << std::endl;
	std::cout << "3. Add a new recipe" << std::endl;
	std::cout << "4. Remove a recipe" << std::endl;
	std::cout << "5. Exit" << std::endl;
	std::cout << std::endl;
}

int get_user_integer_input() {
	std::cout << "Your input: ";
	std::string user_input_string;
	std::getline(std::cin, user_input_string);
	std::cout << std::endl;
	return std::stoi(user_input_string);
}

int prompt_for_menu_option() {
	print_menu();
	return get_user_integer_input();
}

int prompt_for_valid_menu_option() {
	int option;
	bool first = true;
	do {
		if (!first) {
			std::cout << "Error! Bad option!" << std::endl
				<< std::endl;
		}
		// Ask the user for their option
		option = prompt_for_menu_option();

		first = false;
	} while(option < 1 || option > 5);
	return option;
}

int prompt_for_recipe_id(
		const recipe_database& the_database,
		const std::string& prompt_text) {
	std::cout << prompt_text << std::endl <<
		std::endl;
	print_recipe_names(the_database);
	return get_user_integer_input();
}

int prompt_for_valid_recipe_id(
		const recipe_database& the_database,
		const std::string& prompt_text) {
	int option;
	bool first = true;
	do {
		if (!first) {
			std::cout << "Error! Bad option!" << std::endl
				<< std::endl;
		}
		// Ask the user for their option
		option = prompt_for_recipe_id(the_database, prompt_text);

		first = false;
	} while(option < 1 || option > the_database.n_recipes);
	return option;
}

double prompt_for_positive_double(const std::string& prompt_text) {
	std::cout << prompt_text;
	std::string input_string;
	std::getline(std::cin, input_string);
	return std::stod(input_string);
}

double prompt_for_valid_positive_double(const std::string& prompt_text, const std::string& error_text) {
	double input;
	bool first = true;
	do {
		if (!first) {
			std::cout << error_text << std::endl << std::endl;
		}
		// Ask the user for their input
		input = prompt_for_positive_double(prompt_text);

		first = false;
	} while(input <= 0);
	return input;
}

void menu_option_view_specific_recipe(const recipe_database& the_database) {
	int recipe_id = prompt_for_valid_recipe_id(
		the_database,
		"Which recipe would you like to view?"
	);
	double batch_quantity = prompt_for_valid_positive_double(
		"How many batches would you like to make?: ",
		"Error! Batch quantity must be positive."
	);
	int recipe_index = recipe_id - 1;
	print_recipe(the_database.recipes[recipe_index], batch_quantity);
}

// How to remove an element to a dynamic array:
// 1. Create a new dynamic array that's smaller than the old one
// 2. Copy the elements from the old array to the new array, skipping the
// 	index of the element that we want to remove
// 3. Delete the old array from the heap
// 4. Reassign pointers

void remove_recipe(recipe_database& the_database, int recipe_index) {
	// 1. Create a new dynamic array that's smaller than the old one
	recipe* new_array = create_recipe_array(the_database.n_recipes - 1);

	// 2. Copy the elements from the old array to the new array, skipping
	// the index of the element that we want to remove
	
	// "Shallow copy": Your copy and your original structure share pointers
	// 	to the same internal dynamic memory. 
	//
	// "Deep copy": Your copy's pointers to dynamic memory point to their
	// 	OWN arrays of dynamic memory

	for (int i = 0; i < recipe_index; i++) {
		new_array[i] = deep_copy_recipe(the_database.recipes[i]);
	}
	for (int i = recipe_index + 1; i < the_database.n_recipes; i++) {
		new_array[i - 1] = deep_copy_recipe(the_database.recipes[i]);
	}

	int old_n_recipes = the_database.n_recipes;

	// 3. Delete the old array from the heap
	delete_recipe_database(the_database);

	// 4. Reassign pointers
	the_database.recipes = new_array;
	the_database.n_recipes = old_n_recipes - 1;
}

void menu_option_remove_recipe(recipe_database& the_database) {
	int recipe_id_to_remove = prompt_for_valid_recipe_id(
		the_database,
		"Which recipe would you like to remove?"
	);
	
	remove_recipe(the_database, recipe_id_to_remove - 1);
}

std::string prompt_for_recipe_name() {
	std::cout << "What is the name of your recipe?: ";
	std::string name;
	std::getline(std::cin, name);
	return name;
}

std::string prompt_for_yield_unit() {
	std::cout << "What is the yield unit?: ";
	std::string yield_unit;
	std::getline(std::cin, yield_unit);
	return yield_unit;
}

std::string prompt_for_ingredient_name() {
	std::cout << "What is the name of the next ingredient?: ";
	std::string name;
	std::getline(std::cin, name);
	return name;
}

std::string prompt_for_ingredient_unit() {
	std::cout << "What is the unit of the next ingredient?: ";
	std::string ingredient_unit;
	std::getline(std::cin, ingredient_unit);
	return ingredient_unit;
}

ingredient prompt_for_ingredient() {
	ingredient result;

	result.name = prompt_for_ingredient_name();
	result.quantity = prompt_for_valid_positive_double(
		"What is the quantity of the next ingredient?: ",
		"Error! Quantity must be positive!"
	);
	result.unit = prompt_for_ingredient_unit();

	return result;
}

char prompt_for_valid_yes_or_no(const std::string& prompt_text) {
	char yes_or_no;
	bool first = true;
	do {
		if (!first) {
			std::cout << "Error! Enter Y for yes or N for no!" <<
				std::endl << std::endl;
		}
		// Ask the user whether they'd like to add another ingredient
		std::cout << prompt_text;
		std::string yes_or_no_string;
		std::getline(std::cin, yes_or_no_string);
		yes_or_no = yes_or_no_string[0];

		first = false;
	} while(yes_or_no != 'Y' && yes_or_no != 'N');
	return yes_or_no;
}

// How to add an element to a dynamic array:
// 1. Create a new dynamic array that's bigger than the old one
// 2. Copy the elements from the old array to the new array
// 3. Add your new element to an empty spot at the end of the new array
// 4. Delete the old array from the heap
// 5. Reassign variables (pointer and size) to represent the new array rather
// 	than the old, deleted array
void prompt_for_ingredients(recipe& the_recipe) {
	ingredient* list_of_ingredients = nullptr;
	int n_ingredients = 0;

	do {
		std::cout << std::endl;
		ingredient next_ingredient = prompt_for_ingredient();
		std::cout << std::endl;

		ingredient* new_list_of_ingredients = create_ingredient_array(
			n_ingredients + 1
		);

		for (int i = 0; i < n_ingredients; i++) {
			new_list_of_ingredients[i] = list_of_ingredients[i];
		}

		new_list_of_ingredients[n_ingredients] = next_ingredient;

		if (list_of_ingredients != nullptr) {
			delete [] list_of_ingredients;
		}

		list_of_ingredients = new_list_of_ingredients;
		n_ingredients = n_ingredients + 1;
	} while(prompt_for_valid_yes_or_no(
			"Would you like to add another ingredient? (Y/N): "
		) == 'Y');

	the_recipe.ingredients = list_of_ingredients;
	the_recipe.n_ingredients = n_ingredients;
}

void prompt_for_steps(recipe& the_recipe) {
	std::string* list_of_steps = nullptr;
	int n_steps = 0;

	do {
		std::string next_step;
		std::cout << "Enter the next step: ";
		std::getline(std::cin, next_step);

		std::string* new_list_of_steps = create_steps_array(
			n_steps + 1
		);

		for (int i = 0; i < n_steps; i++) {
			new_list_of_steps[i] = list_of_steps[i];
		}

		new_list_of_steps[n_steps] = next_step;

		if (list_of_steps != nullptr) {
			delete [] list_of_steps;
		}

		list_of_steps = new_list_of_steps;
		n_steps = n_steps + 1;
	} while(prompt_for_valid_yes_or_no(
			"Would you like to add another step?: "
		) == 'Y');

	the_recipe.steps = list_of_steps;
	the_recipe.n_steps = n_steps;
}

recipe prompt_for_recipe() {
	recipe result;

	result.name = prompt_for_recipe_name();
	result.yield_quantity = prompt_for_valid_positive_double(
		"What is the yield quantity?: ",
		"Error! Yield quantity must be positive!"
	);
	result.yield_unit = prompt_for_yield_unit();
	prompt_for_ingredients(result);
	std::cout << std::endl;
	prompt_for_steps(result);

	return result;
}

// How to add an element to a dynamic array:
// 1. Create a new dynamic array that's bigger than the old one
// 2. Copy the elements from the old array to the new array
// 3. Add your new element to an empty spot at the end of the new array
// 4. Delete the old array from the heap
// 5. Reassign variables (pointer and size) to represent the new array rather
// 	than the old, deleted array
void add_recipe(recipe_database& the_database, const recipe& the_recipe) {
	recipe* new_recipes = create_recipe_array(the_database.n_recipes + 1);

	for (int i = 0; i < the_database.n_recipes; i++) {
		new_recipes[i] = deep_copy_recipe(the_database.recipes[i]);
	}

	new_recipes[the_database.n_recipes] = the_recipe;
	
	int old_n_recipes = the_database.n_recipes;

	delete_recipe_database(the_database);

	the_database.recipes = new_recipes;
	the_database.n_recipes = old_n_recipes + 1;
}

void menu_option_add_recipe(recipe_database& the_database) {
	recipe the_recipe = prompt_for_recipe();
	add_recipe(the_database, the_recipe);
}

void program_loop(recipe_database& the_database) {
	int valid_option;
	do {
		valid_option = prompt_for_valid_menu_option();

		if (valid_option == 1) {
			print_recipe_names(the_database);
		} else if (valid_option == 2) {
			menu_option_view_specific_recipe(the_database);
		} else if (valid_option == 3) {
			menu_option_add_recipe(the_database);
		} else if (valid_option == 4) {
			menu_option_remove_recipe(the_database);
		}
	} while(valid_option != 5);
}

void save_recipe_database(
		std::ofstream& file,
		const recipe_database& the_database) {
	file << the_database.n_recipes << std::endl;
	for (int i = 0; i < the_database.n_recipes; i++) {
		save_recipe(file, the_database.recipes[i]);
	}
}

int main() {
	greet();

	std::ifstream file;
	file.open("recipes.txt");
	if (file.fail()) {
		// File failed to open
		std::cout << "Error! Failed to open recipes.txt" << std::endl;
		return 1;
	}

	recipe_database the_database = read_recipe_database(file);

	file.close();

	program_loop(the_database);

	// Save the entire state of the_database to recipes.txt
	std::ofstream save_file;
	save_file.open("recipes.txt");
	save_recipe_database(save_file, the_database);

	delete_recipe_database(the_database);
}
