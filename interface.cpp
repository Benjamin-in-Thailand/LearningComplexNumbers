#include "interface.h"

void explainOperation(int choice)
{
    std::cout << "\n--- How to perform this operation ---\n";
    switch (choice)
    {
    case 1: std::cout << "Add the real parts and the imaginary parts separately.\n"; break;
    case 2: std::cout << "Subtract the real parts and the imaginary parts separately.\n"; break;
    case 3: std::cout << "Use (ac-bd) for the real part and (ad+bc) for the imaginary part.\n"; break;
    case 4: std::cout << "Multiply by the conjugate: (a+bi)/(c+di) = ((a+bi)(c-di))/(c^2+d^2).\n"; break;
    }
}

void runProblem(int choice)
{
    Complex z1 = randomComplex(-10, 10);
    Complex z2 = randomComplex(-10, 10);

    std::string op;
    switch (choice)
    {
    case 1: op = "+"; break;
    case 2: op = "-"; break;
    case 3: op = "*"; break;
    case 4: op = "/"; break;
    }

    std::cout << "\nSolve:\n";
    std::cout << "  (" << z1.toString() << ") " << op
        << " (" << z2.toString() << ")\n";

    /* --------------- Wait for the user --------------- */
    std::cout << "Press ENTER to see the answer...";
    std::cout.flush();                           
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard any leftover input
    std::cin.get();                               
    /* --------------------------------------------------- */

    Complex ans;
    switch (choice)
    {
    case 1: ans = add(z1, z2); break;
    case 2: ans = subtract(z1, z2); break;
    case 3: ans = multiply(z1, z2); break;
    case 4: ans = divide(z1, z2); break;
    }

    std::cout << "\nAnswer: " << ans.toString() << "\n";
}