#include <iostream>
#include <string>
#include <list>

class Memento
{
public:
    virtual std::string GetText() const = 0;
};

class ConcreteMemento : public Memento
{
private:
    std::string state;

public:
    ConcreteMemento(std::string state)
    {
        this->state = state;
    }

    std::string GetText() const override
    {
        return this->state;
    }
};

// Originator
class TextEditor
{
private:
    std::string state;

public:
    TextEditor(std::string state)
    {
        this->state = state;
    }

    std::string GetCurrentText() const
    {
        return this->state;
    }

    void SetNewText(std::string state)
    {
        this->state = state;
    }

    Memento *Save() // saves the current state inside a memento
    {
        return new ConcreteMemento(this->state);
    }

    void Restore(Memento *memento) // restores the TextEditor state from a memento object
    {
        this->state = memento->GetText();
    }
};

class History
{
private:
    TextEditor *text_editor;
    std::list<Memento *> mementos;

public:
    History(TextEditor *text_editor)
    {
        this->text_editor = text_editor;
    }

    void Backup()
    {
        std::cout << "Saving text editor text...\n";
        this->mementos.push_back(this->text_editor->Save());
        this->text_editor->SetNewText("");
    }

    void ShowHistory()
    {
        std::cout << "History:\n";
        for (auto memento : this->mementos)
        {
            std::cout << memento->GetText() << '\n';
        }
    }

    void Undo()
    {
        if (this->mementos.empty())
            return;

        Memento *memento = this->mementos.back();
        this->mementos.pop_back();

        std::cout << "Restoring state: " << memento->GetText() << '\n';

        this->text_editor->Restore(memento);
    }
};

int main()
{
    TextEditor *text_editor = new TextEditor("Hello world");

    History *history = new History(text_editor);
    history->Backup();

    text_editor->SetNewText("hello");
    history->Backup();

    text_editor->SetNewText("aabbccdd");
    history->Backup();

    text_editor->SetNewText("daniluk pls i want 3");
    history->Backup();

    std::cout << '\n';

    history->Undo();
    std::cout << "current state: " << text_editor->GetCurrentText() << '\n';

    history->Undo();
    std::cout << "current state: " << text_editor->GetCurrentText() << '\n';

    std::cout << '\n';

    history->ShowHistory();

    delete text_editor;

    return 0;
}