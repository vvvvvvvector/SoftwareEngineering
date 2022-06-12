#include <iostream>
#include <string>
#include <list>

class Drawer;
class Popup;

class ComponentVisitor
{
public:
    virtual ~ComponentVisitor() {}
    virtual void VisitDrawer(const Drawer *drawer) const = 0;
    virtual void VisitPopup(const Popup *popup) const = 0;
};

class ReactComponent
{
public:
    virtual ~ReactComponent() {}
    virtual std::string GetHTML() const = 0;
    virtual void Render() const = 0;
    virtual void Accept(ComponentVisitor *visitor) const = 0;
};

class Drawer : public ReactComponent
{
public:
    std::string GetHTML() const override
    {
        return "DRAWER HTML HERE";
    }

    void Render() const override
    {
        std::cout << "Rendering drawer\n";
    }

    void Accept(ComponentVisitor *visitor) const override
    {
        visitor->VisitDrawer(this);
    }
};

class Popup : public ReactComponent
{
public:
    std::string GetHTML() const override
    {
        return "POPUP HTML HERE";
    }

    void Render() const override
    {
        std::cout << "Rendering popup\n";
    }

    void Accept(ComponentVisitor *visitor) const override
    {
        visitor->VisitPopup(this);
    }
};

class DoAnotherMagicWithHTMLVisitor : public ComponentVisitor
{
public:
    void VisitDrawer(const Drawer *drawer) const override
    {
        std::cout << "MAGIC(" << drawer->GetHTML() << ")...\n";
    }

    void VisitPopup(const Popup *popup) const override
    {
        std::cout << "MAGIC(" << popup->GetHTML() << ")...\n";
    }
};

class HTMLExportVisitor : public ComponentVisitor
{
public:
    void VisitDrawer(const Drawer *drawer) const override
    {
        std::cout << "Exporting(" << drawer->GetHTML() << ")...\n";
    }

    void VisitPopup(const Popup *popup) const override
    {
        std::cout << "Exporting(" << popup->GetHTML() << ")...\n";
    }
};

int main()
{
    std::list<const ReactComponent *> components;

    components.push_back(new Drawer);
    components.push_back(new Popup);

    HTMLExportVisitor *html_visitor = new HTMLExportVisitor();
    DoAnotherMagicWithHTMLVisitor *magic_visitor = new DoAnotherMagicWithHTMLVisitor();

    std::cout << "html visitor:\n";

    for (auto c : components)
        c->Accept(html_visitor);

    std::cout << "\nmagic visitor:\n";

    for (auto c : components)
        c->Accept(magic_visitor);

    delete html_visitor;
    delete magic_visitor;

    return 0;
}