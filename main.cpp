#include "interface.h"
#include <iostream>
#include <limits>

int main()
{
    while (true)
    {
        std::cout << "\n=== Complex Number Tutor ===\n";
        std::cout << "1) Add two complex numbers\n";
        std::cout << "2) Subtract two complex numbers\n";
        std::cout << "3) Multiply two complex numbers\n";
        std::cout << "4) Divide two complex numbers\n";
        std::cout << "5) Quit\n";
        std::cout << "Choose an option (1 - 5): ";

        int choice;
        std::cin >> choice;

        // **Input validation** ------------------------------------
        if (!std::cin)                    // non‑numeric input
        {
            std::cin.clear();             // reset fail flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid option, please try again.\n";
            continue;                     // back to menu
        }

        if (choice == 5)  // Quit
        {
            std::cout << "Good - bye!\n";
            break;
        }

        if (choice < 1 || choice > 4)
        {
            std::cout << "Invalid option, please try again.\n";
            continue;
        }

        explainOperation(choice);
        runProblem(choice);
    }

    return 0;
}