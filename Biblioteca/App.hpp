#pragma once

#include "Models.hpp"

namespace Biblioteca
{
    class App
    {
    public:
        App();
        void Run();

    private:
        void RegisterBook();
        void ListBooks();
        void RegisterUser();
        void LoginUser();
        void LogoutUser();
        void PrintBooks(const BooksFilterFunc& func);
        BooksFilterFunc SearchBooks();
        BooksCmpFunc SortBooks();

    private:
        Books m_Books;
        Users m_Users;
        User* m_CurrentUser;
    };
}
