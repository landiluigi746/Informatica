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
        Books m_Books;
        Users m_Users;
        User* m_CurrentUser;
    };
}
