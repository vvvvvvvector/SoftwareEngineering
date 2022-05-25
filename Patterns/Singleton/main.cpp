#include <iostream>
#include <list>

class Database
{
private:
    static Database *instance;

    std::list<int> data;

    Database() {}

public:
    Database(Database &other) = delete; // singletons should not be cloneable

    void operator=(const Database &) = delete; // singletons should not be assignable.

    static Database *getDatabase();

    // ------- business logic -------
    void addData(int data)
    {
        this->data.push_back(data);
    }

    void traverseDatabaseData()
    {
        for (auto i = this->data.begin(); i != data.end(); i++)
        {
            std::cout << (*i) << ' ';
        }
        std::cout << '\n';
    }
};

Database *Database::instance = nullptr;

Database *Database::getDatabase()
{
    if (instance == nullptr)
    {
        instance = new Database();
        std::cout << "Now you are connected to a database!\n";
    }
    return instance;
}

int main()
{
    Database *db_first_inst = Database::getDatabase();

    db_first_inst->addData(10);
    db_first_inst->addData(20);
    db_first_inst->addData(30);
    db_first_inst->addData(40);

    db_first_inst->traverseDatabaseData();

    Database *db_second_inst = Database::getDatabase();

    db_second_inst->addData(100);

    db_first_inst->traverseDatabaseData();

    if (db_first_inst == db_second_inst)
        std::cout << "Singleton works, both variables contain the same instance.\n";

    delete db_first_inst;

    return 0;
}