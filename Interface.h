// interface.h. How the program works!
#pragma once

#include "complex.h"
#include <iostream>
#include <limits>

// Shows the main menu and returns the chosen option (1‑5)
int showMenu();

// Prints a brief "how‑to" for the chosen operation
void explainOperation(int choice);

// Generates a random problem for the chosen operation, prints it,
// waits for the user to press Enter, then prints the answer.
void runProblem(int choice);
