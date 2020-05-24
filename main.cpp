#include <iostream>
#include <vector>
#include "Hash.cpp"

using namespace std;

class Library
{
public:
    HashTable *books;

    Library(int size)
    {
        books = new HashTable(size);
    };
};

class User
{
    friend class Librarian;

    bool debt;
    Book onHandsBook;

public:
    User()
    {
        debt = false;
    };

    void ReturnBook(Library &lib)
    {
        if (debt == true)
        {
            debt = false;
            lib.books->Add(onHandsBook);
        };
    }
};

class Librarian : public User
{
    Library *lib;

    void Apologize()
    {
        cout << "OH NO!! NO SUCH BOOK!!" << endl;
    };

    void GetRidOf()
    {
        cout << "YO!! YOU ALREADY TOOK ONE!! You can only take one book." << endl;
    };

public:
    Librarian(Library *_lib) : User()
    {
        lib = _lib;
    };

    void GiveBookTo(Book &_book, User &user)
    {
        if (user.debt == true)
        {
            GetRidOf();
            return;
        }
        else
        {
            if (lib->books->Delete(_book))
            {
                user.debt = true;
                user.onHandsBook = _book;
            }
            else
            {
                Apologize();
                return;
            }
        }
    };
};

int main()
{
    Library lib(10);
    Book book;
    book.name = "Name";
    book.author = "Author";
    //cout << "5435";
    for (int i = 0; i < 10; i++)
    {
        lib.books->Add(book);
        book.name[0]++;
        book.author[0]++;
    }

    book.name = "Name";
    book.author = "Author";
    User user1;
    User user2;
    Librarian librarian(&lib);
    librarian.GiveBookTo(book, user1);

    librarian.GiveBookTo(book, user1);

    librarian.GiveBookTo(book, user2);

    user1.ReturnBook(lib);
    librarian.GiveBookTo(book, user2);


    return 0;
}
