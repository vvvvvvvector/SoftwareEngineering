#include <iostream>
#include <list>
#include <string>

// for instance webpage component 🤔
class Component
{
public:
    virtual ~Component() {}
    virtual std::string GetHTML() = 0;
};

// Leaf
class ListItem : public Component
{
private:
    std::string text;

public:
    ListItem(std::string text)
    {
        this->text = text;
    }

    std::string GetHTML() override
    {
        return this->text;
    }
};

// Composite
class UnorderedList : public Component
{
private:
    std::string title;
    std::list<Component *> components;

public:
    UnorderedList(std::string title, std::list<Component *> components)
    {
        this->title = title;
        this->components = components;
    }

    std::string GetHTML() override
    {
        std::string result = "";

        result += "<ul>\n";

        result += "<h2> " + this->title + " </h2>\n";

        for (auto i = this->components.begin(); i != this->components.end(); i++)
        {
            result += "<li> " + (*i)->GetHTML() + " </li>\n";
        }

        result += "</ul>\n";

        return result;
    }
};

int main()
{
    std::list<Component *> list_items = {
        new ListItem("(Main-list) item 1"),
        new ListItem("(Main-list) item 2"),
        new UnorderedList("nested-list[3]",
                          {new ListItem("(nested-list[3]) item 1"),
                           new ListItem("(nested-list[3]) item 2"),
                           new ListItem("(nested-list[3]) item 3")}),
        new ListItem("(Main-list) item 4")};

    UnorderedList *ul = new UnorderedList("Main-list", list_items);

    std::cout << ul->GetHTML();

    delete ul;

    return 0;
}