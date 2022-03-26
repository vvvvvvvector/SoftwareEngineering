#include <iostream>
#include <cstring>

class TStudent
{
private:
    char i[51];
    friend class TFriendStudent;

public:
    TStudent()
    {
        strcpy(i, "Janek Kowalski");
    }
};

class TFriendStudent
{
public:
    void addFriend(const char *x) // return strncat(student.i, x, 19) ???
    {
        TStudent student;
        strncat(student.i, x, 19);
        std::cout << student.i << '\n';
    }
};

int main()
{
    TFriendStudent friendStudent;

    friendStudent.addFriend(" i Bartek Jankowski");

    return 0;
}