#include "Utils.hpp"

#include <cctype>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <limits>

namespace Utils
{
    void ClearScreen()
    {
        std::cout << std::flush;
        std::system("cls || clear");
    }

    void Pause()
    {
        std::cout << "Press any button to continue..." << std::flush;
        std::system("read -n 1 > /dev/null || pause > nul");
    }

    void ClearInputBuffer()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    bool StringContainsInsensitive(std::string a, std::string b)
    {
        for(char& c: a)
            c = std::tolower(c);

        for(char& c: b)
            c = std::tolower(c);

        return a.find(b) != std::string::npos;
    }
}
