#include "Models.hpp"
#include "Date.hpp"

#include <cctype>

namespace Biblioteca
{
    bool Book::ValidateTitle() const noexcept
    {
        return (!Title.empty());
    }

    bool Book::ValidateAuthor() const noexcept
    {
        return (!Author.empty());
    }

    bool Book::ValidatePublicationYear() const noexcept
    {
        return PublicationYear >= Book::MIN_PUBLICATION_YEAR && PublicationYear <= Date::Now().Year();
    }

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
