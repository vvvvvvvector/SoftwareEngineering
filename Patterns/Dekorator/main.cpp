#include <iostream>
#include <string>

// Interface; component
class INotifier
{
public:
    virtual ~INotifier() {}
    virtual std::string send() const = 0;
};

// Core functionality; concrete component
class CoreNotifier : public INotifier
{
public:
    std::string send() const override
    {
        return "core_notifier";
    }
};

// Optional wrapper; abstract class
class Wrapper : public INotifier
{
private:
    INotifier *wrapper;

public:
    Wrapper(INotifier *wrapper)
    {
        this->wrapper = wrapper;
    }

    std::string send() const override
    {
        return this->wrapper->send();
    }
};

// concrete wrapper 1
class EmailNotifier : public Wrapper
{
public:
    EmailNotifier(INotifier *notifier) : Wrapper(notifier) {}

    std::string send() const override
    {
        return "email_notifier(" + Wrapper::send() + ")";
    }
};

// concrete wrapper 2
class PhoneNotifier : public Wrapper
{
public:
    PhoneNotifier(INotifier *notifier) : Wrapper(notifier) {}

    std::string send() const override
    {
        return "phone_notifier(" + Wrapper::send() + ")";
    }
};

int main()
{
    // decorators can decorate another decorators, not only components
    INotifier *notifier = new PhoneNotifier(new EmailNotifier(new CoreNotifier()));

    std::cout << "decorated component:\n"
              << notifier->send() << '\n';

    delete notifier;

    return 0;
}