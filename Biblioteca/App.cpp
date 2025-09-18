#include "App.hpp"
#include "Models.hpp"
#include "Utils.hpp"
#include <string>

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

            std::cout << "Menu:\n\n"
                      << "1. Add a new book\n"
                      << "2. View all books\n";

            if(!m_CurrentUser)
            {
                std::cout << "3. Register\n"
                          << "4. Login\n";
            }
            else
                std::cout << "3. Logout\n";

            std::cout << "0. Exit\n\n";

            if(m_CurrentUser)
                std::cout << "You are currently logged as " << m_CurrentUser->Username << "\n\n";
            else
                std::cout << "You are not logged at the moment\n\n";

            std::cout << "Users registered: " << m_Users.Size() << "\n";
            std::cout << "Books registered: " << m_Books.Size() << "\n\n";

            std::cout << "Enter an option: ";
            std::cin >> choice;

            Utils::ClearInputBuffer();
            Utils::ClearScreen();

            switch(choice)
            {
                case 1:
                    RegisterBook();
                    break;
                case 2:
                    ListBooks();
                    break;
                case 3:
                    (!m_CurrentUser) ? RegisterUser() : LogoutUser();
                    break;
                case 4:
                    if (!m_CurrentUser)
                    {
                        LoginUser();
                        ListExpiredLoans();
                    }
                    else
                    {
                        std::cout << "Invalid choice!\n";
                        Utils::Pause();
                    }
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

    void App::RegisterBook()
    {
        Book newBook;
        bool alreadyPresent;

        std::cout << "-------------------------------\n"
                  << "|      Book registration      |\n"
                  << "-------------------------------\n\n";

        do {
            do {
                std::cout << "Enter the title of the book: ";
                std::getline(std::cin, newBook.Title);
            } while(!newBook.ValidateTitle());

            do {
                std::cout << "Enter the author of the book: ";
                std::getline(std::cin, newBook.Author);
            } while(!newBook.ValidateAuthor());

            alreadyPresent = m_Books.Search([](const Book& a, const Book& b) {
                return a.Title == b.Title && a.Author == b.Author;
            }, newBook);

            if(alreadyPresent)
                std::cout << "A book with the same title and author already exists\n";
        } while(alreadyPresent);

        do {
            std::cout << "Enter the publication year of the book: ";
            std::cin >> newBook.PublicationYear;
            Utils::ClearInputBuffer();
        } while(!newBook.ValidatePublicationYear());

        newBook.ID = m_Books.Size() + 1;
        newBook.BorrowerID = -1;

        m_Books.PushFront(std::move(newBook));
        std::cout << "Book registered successfully\n";

        Utils::Pause();
    }

    void App::ListBooks()
    {
        if(m_Books.Empty())
        {
            std::cout << "The catalogue is empty\n";
            Utils::Pause();
            return;
        }

        int choice;
        BooksFilterFunc filterFunc = [](const Book&){ return true; };
        BooksCmpFunc cmpFunc;

        do {
            Utils::ClearScreen();

            std::cout << "-----------------------\n"
                      << "|      Catalogue      |\n"
                      << "-----------------------\n\n";

            if(cmpFunc)
                m_Books.Sort(cmpFunc);

            PrintBooks(filterFunc);

            std::cout << "Available options:\n"
                      << "1. Search for books\n"
                      << "2. Order books\n"
                      << "3. Show only available books\n"
                      << "4. Show only borrowed books\n"
                      << "5. Show all books\n"
                      << "6. Remove a book\n";

            if(m_CurrentUser)
            {
                std::cout << "7. Borrow a book\n"
                          << "8. See borrowed books\n"
                          << "9. Return a book\n";
            }

            std::cout << "0. Go back to menu\n\n";

            std::cout << "Enter an option: ";
            std::cin >> choice;
            Utils::ClearInputBuffer();

            switch(choice)
            {
                case 1:
                    filterFunc = SearchBooks();
                    break;
                case 2:
                    cmpFunc = SortBooks();
                    filterFunc = [](const Book&){ return true; };
                    break;
                case 3:
                    filterFunc = [](const Book& book) {
                        return book.BorrowerID < 0;
                    };
                    break;
                case 4:
                    filterFunc = [](const Book& book) {
                        return book.BorrowerID > 0;
                    };
                    break;
                case 5:
                    filterFunc = [](const Book&){ return true; };
                    break;
                case 6:
                    RemoveBook();
                    break;
                case 7:
                    if(m_CurrentUser)
                        BorrowBook();
                    else
                    {
                        Utils::ClearScreen();
                        std::cout << "Invalid choice!\n";
                        Utils::Pause();
                    }
                    break;
                case 8:
                    if(m_CurrentUser)
                    {
                        filterFunc = [this](const Book& book) {
                            return book.BorrowerID == m_CurrentUser->ID;
                        };
                    }
                    else
                    {
                        Utils::ClearScreen();
                        std::cout << "Invalid choice!\n";
                        Utils::Pause();
                    }
                    break;
                case 9:
                    if(m_CurrentUser)
                        ReturnBook();
                    else
                    {
                        Utils::ClearScreen();
                        std::cout << "Invalid choice!\n";
                        Utils::Pause();
                    }
                    break;
                case 0:
                    break;
                default:
                    Utils::ClearScreen();
                    std::cout << "Invalid choice!\n";
                    Utils::Pause();
                    break;
            }
        } while(choice != 0);
    }

    void App::BorrowBook()
    {
        Book bookToBorrow;

        do {
            std::cout << "Enter the ID of the book to borrow: ";
            std::cin >> bookToBorrow.ID;
        } while(bookToBorrow.ID <= 0);

        Book* selectedBook = m_Books.Search([](const Book& a, const Book& b) {
            return a.ID == b.ID;
        }, bookToBorrow);

        if(!selectedBook)
        {
            std::cout << "Requested book was not found\n";
            Utils::Pause();
            return;
        }

        if(selectedBook->BorrowerID > 0)
        {
            std::cout << "You can't borrow this book, it is already borrowed\n";
            Utils::Pause();
            return;
        }

        int day, month, year;
        bool validDate;
        std::cout << "Enter the due date to return the book:\n";

        do {
            std::cout << "Day: ";
            std::cin >> day;
            Utils::ClearInputBuffer();

            std::cout << "Month: ";
            std::cin >> month;
            Utils::ClearInputBuffer();

            std::cout << "Year: ";
            std::cin >> year;
            Utils::ClearInputBuffer();

            Date tempDate{day, month, year};
            validDate = Date::IsValid(day, month, year) && tempDate > Date::CurrentDate();

            if(!validDate)
                std::cout << "Invalid date\n";
        } while(!validDate);

        selectedBook->BorrowerID = m_CurrentUser->ID;
        selectedBook->LoanDate = Date::CurrentDate();
        selectedBook->DueDate = Date{day, month, year};

        std::cout << "Book " << selectedBook->Title
                  << " by " << selectedBook->Author
                  << " borrowed successfully\n";
        Utils::Pause();
    }

    void App::ReturnBook()
    {
        Book bookToReturn;

        do {
            std::cout << "Enter the ID of the book to return: ";
            std::cin >> bookToReturn.ID;
        } while(bookToReturn.ID <= 0);

        Book* selectedBook = m_Books.Search([](const Book& a, const Book& b) {
            return a.ID == b.ID;
        }, bookToReturn);

        if(!selectedBook)
        {
            std::cout << "Requested book was not found\n";
            Utils::Pause();
            return;
        }

        if(selectedBook->BorrowerID != m_CurrentUser->ID)
        {
            std::cout << "You can't return this book, you haven't borrowed it\n";
            Utils::Pause();
            return;
        }

        selectedBook->BorrowerID = -1;

        std::cout << "Book " << selectedBook->Title
                  << " by " << selectedBook->Author
                  << " returned successfully\n";
        Utils::Pause();
    }

    void App::ListExpiredLoans()
    {
        size_t count = 0;

        Utils::ClearScreen();
        std::cout << "-------------------------------\n"
                  << "|    Expired loans notice     |\n"
                  << "-------------------------------\n\n";

        m_Books.ForEach([&count, this](Book& book) {
            if(book.BorrowerID == m_CurrentUser->ID && book.DueDate < Date::CurrentDate())
            {
                std::cout << "The book " << book.Title
                          << " by " << book.Author
                          << " that you loaned on " << book.LoanDate.ToString()
                          << " was due to return on " << book.DueDate.ToString() << "\n\n";

                char choice;

                do {
                    std::cout << "Do you want to return it (y -> yes, n -> no)? ";
                    std::cin >> choice;
                    Utils::ClearInputBuffer();
                    choice = tolower(choice);
                } while(choice != 'y' && choice != 'n');

                if(choice == 'y')
                {
                    book.BorrowerID = -1;
                    std::cout << "Book returned successfully\n\n";
                }
                else
                    std::cout << "Make sure to return it as soon as possible\n\n";

                ++count;
            }
        });


        if (count > 0)
            Utils::Pause();
    }

    void App::RemoveBook()
    {
        Book bookToRemove;

        do {
            std::cout << "Enter the ID of the book to remove: ";
            std::cin >> bookToRemove.ID;
        } while(bookToRemove.ID <= 0);

        bool bookRemoved = m_Books.Erase([](const Book& a, const Book& b) {
            return a.ID == b.ID;
        }, bookToRemove);

        if(!bookRemoved)
        {
            std::cout << "Requested book was not found\n";
            Utils::Pause();
            return;
        }

        std::cout << "Book removed successfully\n";
        Utils::Pause();
    }

    void App::RegisterUser()
    {
        User newUser;
        bool alreadyPresent;

        std::cout << "-------------------------------\n"
                  << "|      User registration      |\n"
                  << "-------------------------------\n\n";

        do {
            std::cout << "Enter username (only letters and numbers): ";
            std::getline(std::cin, newUser.Username);

            alreadyPresent = m_Users.Search([](const User& a, const User& b) {
                return a.Username == b.Username;
            }, newUser);

            if(alreadyPresent)
                std::cout << "Username already present\n";
        } while(!newUser.ValidateUsername() || alreadyPresent);

        do {
            std::cout << "Enter password (only letters, numbers and symbols (*, _, -)): ";
            std::getline(std::cin, newUser.Password);
        } while(!newUser.ValidatePassword());

        newUser.Password = Utils::HashString(newUser.Password);

        newUser.ID = m_Users.Size() + 1;
        m_Users.PushFront(std::move(newUser));
        m_CurrentUser = &m_Users.Front();

        std::cout << "Registered and logged in successfully!\n";
        Utils::Pause();
    }

    void App::LoginUser()
    {
        User user;

        std::cout << "------------------------\n"
                  << "|      User login      |\n"
                  << "------------------------\n\n";

        do {
            std::cout << "Enter username: ";
            std::getline(std::cin, user.Username);
        } while(user.Username.empty());

        do {
            std::cout << "Enter password: ";
            std::getline(std::cin, user.Password);
        } while(user.Password.empty());

        user.Password = Utils::HashString(user.Password);

        User* savedUser = m_Users.Search([](const User& a, const User& b) {
            return (a.Username == b.Username && a.Password == b.Password);
        }, user);

        if(savedUser)
        {
            std::cout << "Logged in successfully as " << user.Username << "\n";
            m_CurrentUser = savedUser;
        }
        else
            std::cout << "Wrong credentials\n";

        Utils::Pause();
    }

    void App::LogoutUser()
    {
        m_CurrentUser = nullptr;
    }

    void App::PrintBooks(const BooksFilterFunc& func)
    {
        size_t count = 0;

        m_Books.ForEach([&func, &count, this](const Book& book) {
            if(!func(book))
                return;

            std::cout << "ID: " << book.ID << "\n"
                      << "Title: " << book.Title << "\n"
                      << "Author: " << book.Author << "\n"
                      << "Publication Year: " << book.PublicationYear << "\n";

            if(book.BorrowerID > 0)
            {
                User* borrower = m_Users.Search([](const User& a, const User& b) {
                    return a.ID == b.ID;
                }, User{book.BorrowerID, "", ""});

                if(!borrower)
                {
                    std::cout << "Borrower couldn't be found\n";
                    return;
                }

                std::cout << "Borrowed by: " << (borrower->ID == m_CurrentUser->ID ? "You" : borrower->Username) << "\n";

                if(borrower->ID == m_CurrentUser->ID)
                {
                    std::cout << "Loaned on: " << book.LoanDate.ToString() << "\n";
                    std::cout << "Return due on: " << book.DueDate.ToString() << "\n";
                    if(book.DueDate < Date::CurrentDate())
                        std::cout << "You're late! You should return it!\n";
                }
            }

            std::cout << "\n";
            ++count;
        });

        if(count == 0)
            std::cout << "No books were found with the current filter\n\n";
    }

    BooksFilterFunc App::SearchBooks()
    {
        int choice;
        int yearQuery;
        std::string searchQuery;

        do {
            Utils::ClearScreen();

            std::cout << "What do you want to search by?\n"
                      << "1. Title\n"
                      << "2. Author\n"
                      << "3. Publication Year\n\n";

            std::cout << "Enter a choice: ";
            std::cin >> choice;
            Utils::ClearInputBuffer();
            Utils::ClearScreen();

            switch(choice)
            {
                case 1:
                    std::cout << "Enter the title you want to search for: ";
                    std::getline(std::cin, searchQuery);

                    return [searchQuery](const Book& book) {
                        return Utils::StringContainsInsensitive(book.Title, searchQuery);
                    };
                case 2:
                    std::cout << "Enter the author you want to search books of: ";
                    std::getline(std::cin, searchQuery);

                    return [searchQuery](const Book& book) {
                        return Utils::StringContainsInsensitive(book.Author, searchQuery);
                    };
                case 3:
                    std::cout << "Enter the year you want to search books in: ";
                    std::cin >> yearQuery;
                    Utils::ClearInputBuffer();

                    return [yearQuery](const Book& book) {
                        return book.PublicationYear == yearQuery;
                    };
                default:
                    std::cout << "Invalid choice!";
            }
        } while(choice < 1 || choice > 3);

        return [](const Book&) { return true; };
    }

    BooksCmpFunc App::SortBooks()
    {
        int choice;

        do {
            Utils::ClearScreen();

            std::cout << "What do you want to order by?\n"
                      << "1. Title\n"
                      << "2. Author\n"
                      << "3. Publication Year\n\n";

            std::cout << "Enter a choice: ";
            std::cin >> choice;
            Utils::ClearInputBuffer();
            Utils::ClearScreen();

            switch(choice)
            {
                case 1:
                    return [](const Book& a, const Book& b) {
                        return a.Title < b.Title;
                    };
                case 2:
                    return [](const Book& a, const Book& b) {
                        return a.Author < b.Author;
                    };
                case 3:
                    return [](const Book& a, const Book& b) {
                        return a.PublicationYear < b.PublicationYear;
                    };
                default:
                    std::cout << "Invalid choice!";
            }
        } while(choice < 1 || choice > 3);

        return [](const Book&, const Book&) { return false; };
    }
}
