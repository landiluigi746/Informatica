#pragma once

#include <string>

namespace Utils
{
    void ClearScreen();
    void Pause();
    void ClearInputBuffer();
    bool StringContainsInsensitive(std::string a, std::string b);
    std::string HashString(const std::string& s);
}
