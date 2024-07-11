CXX = g++
CXXFLAGS = -g
EXE = recipe_database

$(EXE): ingredient.o recipe.o main.o
	$(CXX) $(CXXFLAGS) ingredient.o recipe.o main.o -o $(EXE)

ingredient.o: ingredient.cpp ingredient.hpp
	$(CXX) -c ingredient.cpp

recipe.o: recipe.cpp recipe.hpp
	$(CXX) -c recipe.cpp

main.o: main.cpp
	$(CXX) -c main.cpp

# `make clean` will delete all intermediate (.o) and binary ($EXE) files
# so that a subsequent `make` will rebuild everything from scratch, even if
# dependency information is incomplete for some targets
clean:
	rm -f *.o $(EXE)

# This is just special makefile syntax that tells the GNU Make utility that
# `make clean` doesn't ACTUALLY create a file called `clean`; it's a "phony"
# target.
.PHONY: clean
