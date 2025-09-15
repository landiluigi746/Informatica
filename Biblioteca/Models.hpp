#pragma once

#include "List.hpp"

#include <functional>
#include <string>

namespace Biblioteca
{
    struct Book
    {
        int ID;
        int BorrowerID;
        std::string Title;
        std::string Author;
        int PublicationYear;
    };

    using Books = List<Book>;
    using BooksFilterFunc = std::function<bool(const Book&)>;
    using BooksCmpFunc = std::function<bool(const Book&, const Book&)>;

    struct User
    {
        int ID;
        std::string Username;
        std::string Password;
    };

    using Users = List<User>;
}
