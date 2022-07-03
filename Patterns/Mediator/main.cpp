#include <iostream>
#include <list>
#include <string>
#include <algorithm>

class Customer;

class Mediator
{
public:
    virtual ~Mediator() {}
    virtual void Order(Customer *customer, const std::string &name, const std::string &info) = 0;
};

class Customer
{
private:
    std::string name;
    Mediator *mediator;

public:
    Customer(const std::string &name, Mediator *mediator)
    {
        this->name = name;
        this->mediator = mediator;
    }

    std::string GetName() const
    {
        return this->name;
    }

    void MakeAutoOrder(const std::string &name, const std::string &info)
    {
        mediator->Order(this, name, info);
    }
};

class AutoDealer : public Mediator
{
private:
    std::list<Customer *> customers;

public:
    void Order(Customer *customer, const std::string &name, const std::string &info) override
    {
        std::string customer_name = customer->GetName();

        std::cout << "new order, complicated order logic...\ncustomer_name: " << customer_name << '\n';
        std::cout << "order auto name: " << name << '\n';
        std::cout << "additional info: " << info << '\n';

        auto found = (std::find(this->customers.begin(), this->customers.end(), customer) != this->customers.end());

        if (!found)
            this->customers.push_back(customer);
    }

    void ShowCustomersList()
    {
        std::cout << "customers list:\n";
        for (auto customer : customers)
        {
            std::cout << customer->GetName() << "\n";
        }
    }
};

int main()
{
    AutoDealer *auto_dealer = new AutoDealer();

    Customer *customer_1 = new Customer("name_1", auto_dealer);
    Customer *customer_2 = new Customer("name_2", auto_dealer);

    customer_1->MakeAutoOrder("auto_1", "info_1");

    std::cout << '\n';

    customer_1->MakeAutoOrder("auto_3", "info_3");

    std::cout << '\n';

    customer_2->MakeAutoOrder("auto_2", "info_2");

    std::cout << '\n';

    auto_dealer->ShowCustomersList();

    delete auto_dealer;
    delete customer_1;
    delete customer_2;

    return 0;
}