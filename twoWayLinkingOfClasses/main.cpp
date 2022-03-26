#include <iostream>

class TStudent;

class TBook
{
private:
    TStudent *student;

public:
    void setStudent(TStudent *newStudent);

    const TStudent *getStudent() const; // const dont allow to modify objects on which they are called
};

class TStudent
{
private:
    TBook *book;

public:
    void setBook(TBook *newBook);

    const TBook *getBook() const; // const dont allow to modify objects on which they are called
};

int main()
{

    return 0;
}