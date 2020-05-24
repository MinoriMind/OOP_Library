using namespace std;

enum Statuses
{
    EMPTY,
    IS,
    DELETED
};

class Book
{
public:
    string author;
    string name;
};

class HashTable
{
    unsigned int max;
    unsigned int currentnum;
    Book* books;
    Statuses* status;

    unsigned int HashFunction(string &str)
    {
        unsigned int result = 0;
        for(int i = 0; i < str.size(); i++)
        {
            result += str[i];
        }
        return (result % max);
    };

    unsigned int HashFunction2(unsigned int hash)
    {
        return ((hash + 1) % max);
    };


    int InSearch(Book inBook) //>=0 if success - -1 if not
    {
        unsigned int index = HashFunction(inBook.name);
        unsigned int previndex;

        if (index == 0)
        {
            previndex = max - 1;
        }
        else
        {
            previndex = index - 1;
        }

        while ((status[index] == IS) || (status[index] == DELETED))
        {
            if ((inBook.author == books[index].author) && (inBook.name == books[index].name) && (status[index] == IS))
            {
                return index;
            };

            if (index == previndex)
            {
                return -1;
            };

            index = HashFunction2(index);
        };
        return -1;
    };


    int SameCodeSearch(Book inBook) //>=0 if success - -1 if not
    {
        unsigned int index = HashFunction(inBook.name);
        unsigned int previndex;

        if (index == 0)
        {
            previndex = max - 1;
        }
        else
        {
            previndex = index - 1;
        }

        while ((status[index] == IS) || (status[index] == DELETED))
        {
            if ((inBook.name == books[index].name) && (status[index] == IS))
            {
                return index;
            };

            if (index == previndex)
            {
                return -1;
            };

            index = HashFunction2(index);
        };
        return -1;
    };


public:


    HashTable(unsigned int _max)
    {
        max = _max;
        currentnum = 0;
        books = new Book[max];
        status = new Statuses[max];

        for (int p = 0; p < max; p++)
        {
            status[p] = EMPTY;
        }
    };

    HashTable()
    {
    };

        ~HashTable()
    {
        delete[] books;
        delete[] status;
    };


    void PrintAllHashTable()
    {
        for (int p = 0; p < max; p++)
        {
            cout << "Author: " << books[p].author << " ";
            cout << "Name: " << books[p].name << " ";
            cout << "Status: " << status[p] << endl;
            cout << endl;
        }
    };


    void PrintHashTable()
    {
        for (int p = 0; p < max; p++)
        {
            if (status[p] == IS)
            {
                cout << "Index: " << p << " ";
                cout << "Author: " << books[p].author << " ";
                cout << "Name: " << books[p].name << " ";
                cout << "Status: " << status[p] << " ";
                cout << endl;
            }
        }
    };


    bool Add(Book inBook) //true if added - false if not
    {
        if (max != currentnum)
        {
            if (SameCodeSearch(inBook) == -1)
            {
                int index = HashFunction(inBook.name);

                while (status[index] == IS)
                {
                    if (inBook.name == books[index].name)
                    {
                        return false;
                    }

                    index = HashFunction2(index);
                }
                status[index] = IS;
                books[index].name = inBook.name;
                books[index].author = inBook.author;
                currentnum++;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        return true;
    };


    bool Delete(Book inBook) //true if deleted, false if not
    {
        if (currentnum != 0)
        {
            int index = InSearch(inBook);
            if (index != -1)
            {
                status[index] = DELETED;
                currentnum--;
                return true;
            }
            else
            {
                return false;
            };
        }
        else
        {
            return false;
        };
    };


    Book DeleteAndReturn(Book inBook) //index if deleted, empty inBook.name if not
    {
        if (currentnum != 0)
        {
            int index = InSearch(inBook);
            if (index != -1)
            {
                status[index] = DELETED;
                currentnum--;
                return books[index];
            }
            else
            {
                inBook.name = "";
                return inBook;
            }
        }
    };


    bool Search(Book inBook) //true if success - false if not
    {
        int res = InSearch(inBook);
        if (res != -1)
        {
            return true;
        }
        else
        {
            return false;
        }
    };
};
