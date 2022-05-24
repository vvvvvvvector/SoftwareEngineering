#include <iostream>

class TBook
{
private:
    std::string bookTitle;
    std::string shelfMark;

public:
    TBook()
    {
        std::cout << "TBook constructor\n";
    }

    ~TBook()
    {
        std::cout << "TBook destructor\n";
    }

    void setTitle(const std::string &title)
    {
        this->bookTitle = title;
    }

    std::string getTitle() const
    {
        return this->bookTitle;
    }

    void setShelfMark(const std::string &shelfMark)
    {
        this->shelfMark = shelfMark;
    }

    std::string getShelfMark() const
    {
        return this->shelfMark;
    }
};

class TLibrary
{
private:
    TBook *book;
    std::string libraryName;

public:
    TLibrary(const std::string &libName)
    {
        this->libraryName = libName;
        std::cout << libName << '\n';
        this->book = new TBook();
    }

    ~TLibrary()
    {
        delete book;
    }

    void setData(std::string title, std::string shelfMark)
    {
        book->setTitle(title);
        book->setShelfMark(shelfMark);
    }

    void printData()
    {
        std::cout << book->getTitle() << '\t';
        std::cout << book->getShelfMark() << '\n';
    }
};

int main()
{
    std::cout << "Wywolanie konstruktora klasy TLibrary\n";
    TLibrary *library = new TLibrary("UMCS library");

    library->setData("Programowanie obiektowe", "sygnatura U 2031");
    library->printData();

    std::cout << "Wywolanie destruktora klasy TLibrary\n";
    delete library;

    return 0;
}