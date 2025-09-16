#include "Models.hpp"
#include <cctype>


namespace Biblioteca
{
    bool User::ValidateUsername() const noexcept
    {
        if(Username.empty())
            return false;

        for(char c : Username)
            if(!std::isalnum(c))
                return false;

        return true;
    }

    bool User::ValidatePassword() const noexcept
    {
        if(Password.empty())
            return false;

        for(char c : Password)
            if(!(std::isalnum(c) || c == '*' || c == '_' || c == '-'))
                return false;

        return true;
    }
}
