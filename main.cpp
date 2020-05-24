#include <iostream>
#include <vector>

using namespace std;

enum BookState
{
    IS,
    TAKEN
};

class Book
{
public:
    string author;
    string name;
    BookState bookState;
};

class Library
{
public:
    vector<Book> books;

};

class User
{
    friend class Librarian;

    bool debt;
    Book onHandsBook;
    int takenBookIndex;

public:
    User()
    {
        debt = false;
    };

    int AskBook(Library &lib, Book &_book)
    {
        for (int i = 0; i < lib.books.size(); i++)
        {
            if ((lib.books[i].name == _book.name) &&
                (lib.books[i].author == _book.author) &&
                (lib.books[i].bookState == IS))
            {
                takenBookIndex = i;
                return i;
            }
        }
        return -1;
    };

    void ReturnBook(Library &lib, Book &_book)
    {
        debt = false;
        lib.books[takenBookIndex].bookState = IS;
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
            int index = AskBook(*lib, _book);
            if (index != -1)
            {
                lib->books[index].bookState = TAKEN;
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
    Library library;
    Book book;
    book.name = "Name";
    book.author = "Author";

    for (int i = 0; i <= 10; i++)
    {
        book.bookState = IS;
        library.books.push_back(book);
        book.name[0]++;
        book.author[0]++;
    }

    book.name = "Name";
    book.author = "Author";
    User user1;
    User user2;

    Librarian librarian(&library);

    librarian.GiveBookTo(book, user1);
    librarian.GiveBookTo(book, user1);

    librarian.GiveBookTo(book, user2);

    //user1.ReturnBook(library, book);
    //librarian.GiveBookTo(book, user2);


    return 0;
}