#include <iostream>
#include <string>

// abstract product 1
class Button
{
public:
    virtual ~Button() {}
    virtual void GetButton() = 0;
};

// abstract product 2
class Checkbox
{
public:
    virtual ~Checkbox() {}
    virtual void GetCheckbox() = 0;
};

// concrete product 1.1(Button mac)
class MacButton : public Button
{
public:
    void GetButton() override
    {
        std::cout << "I am a macos button!\n";
    }
};

// concrete product 1.2(Checkbox mac)
class MacCheckbox : public Checkbox
{
public:
    void GetCheckbox() override
    {
        std::cout << "I am a macos checkbox!\n";
    }
};

// concrete product 2.1(Button windows)
class WindowsButton : public Button
{
public:
    void GetButton() override
    {
        std::cout << "I am a windows button!\n";
    }
};

// concrete product 2.2(Checkbox windows)
class WindowsCheckbox : public Checkbox
{
public:
    void GetCheckbox() override
    {
        std::cout << "I am a windows checkbox!\n";
    }
};

// concrete product 3.1(Button Linux)
class LinuxButton : public Button
{
public:
    void GetButton() override
    {
        std::cout << "I am a linux button!\n";
    }
};

// concrete product 3.2(Checkbox Linux)
class LinuxCheckbox : public Checkbox
{
public:
    void GetCheckbox() override
    {
        std::cout << "I am a linux checkbox!\n";
    }
};

// abstract factory
class GUIFactory
{
public:
    virtual ~GUIFactory() {}
    virtual Button *CreateButton() const = 0;
    virtual Checkbox *CreateCheckbox() const = 0;
};

// concrete factory 1
class MacGUIFactory : public GUIFactory
{
public:
    Button *CreateButton() const override
    {
        return new MacButton();
    }

    Checkbox *CreateCheckbox() const override
    {
        return new MacCheckbox();
    }
};

// concrete factory 2
class WindowsGUIFactory : public GUIFactory
{
public:
    Button *CreateButton() const override
    {
        return new WindowsButton();
    }

    Checkbox *CreateCheckbox() const override
    {
        return new WindowsCheckbox();
    }
};

// concrete factory 3
class LinuxGUIFactory : public GUIFactory
{
public:
    Button *CreateButton() const override
    {
        return new LinuxButton();
    }

    Checkbox *CreateCheckbox() const override
    {
        return new LinuxCheckbox();
    }
};

void CreateUI(const GUIFactory &);

int main()
{
    std::string option = "macos";

    GUIFactory *factory = nullptr;

    if (option == "macos")
        factory = new MacGUIFactory();
    else if (option == "windows")
        factory = new WindowsGUIFactory();
    else if (option == "linux")
        factory = new LinuxGUIFactory();

    if (factory != nullptr)
    {
        CreateUI(*factory);
        delete factory;
    }

    return 0;
}

void CreateUI(const GUIFactory &factory)
{
    Button *button = factory.CreateButton();
    Checkbox *checkbox = factory.CreateCheckbox();

    button->GetButton();
    checkbox->GetCheckbox();

    delete button;
    delete checkbox;
}
