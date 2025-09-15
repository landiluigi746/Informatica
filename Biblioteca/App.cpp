#include "App.hpp"
#include "Utils.hpp"

namespace Biblioteca
{
    App::App() : m_CurrentUser(nullptr) {}

    void App::Run()
    {
        int choice;

        do {
            Utils::ClearScreen();

            std::cout << "----------------------------------------------------\n"
                      << "|                                                  |\n"
                      << "|                    Biblioteca                    |\n"
                      << "|                                                  |\n"
                      << "----------------------------------------------------\n\n";

            std::cout << "Menu:\n"
                      << "1. Add a new book\n"
                      << "2. View all books\n"
                      << "0. Exit\n\n";

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
    }
}
