#include "Utils.hpp"

#include <iostream>

int main()
{
    int choice;

    do {
        Utils::ClearScreen();

        std::cout << "----------------------------------------------------\n";
        std::cout << "|                                                  |\n";
        std::cout << "|                    Biblioteca                    |\n";
        std::cout << "|                                                  |\n";
        std::cout << "----------------------------------------------------\n\n";

        std::cout << "Menu:\n\n";

        std::cout << "1. Add a new book\n";
        std::cout << "2. View all books\n";
        std::cout << "0. Exit\n\n";

        std::cout << "Enter a choice: ";
        std::cin >> choice;

        Utils::ClearInputBuffer();
        Utils::ClearScreen();

        switch(choice)
        {
            case 1:
            case 2:
                std::cout << "To be implemented!\n";
                Utils::Pause();
                break;
            case 0:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice!\n";
                Utils::Pause();
                break;
        }
    } while(choice != 0);

    return 0;
}
