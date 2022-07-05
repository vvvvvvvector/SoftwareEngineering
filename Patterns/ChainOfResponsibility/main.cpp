#include <iostream>
#include <string>

class Numbers
{
private:
    int x;
    int y;
    std::string operation;

public:
    Numbers(int x, int y, std::string operation)
    {
        this->x = x;
        this->y = y;
        this->operation = operation;
    }

    int GetX() const
    {
        return this->x;
    }

    int GetY() const
    {
        return this->y;
    }

    std::string GetOperation() const
    {
        return this->operation;
    }
};

class IChain
{
public:
    virtual ~IChain() {}
    virtual void SetNext(IChain *next) = 0;
    virtual void Calculate(Numbers *request) = 0; // handle
};

class AddNumbers : public IChain
{
private:
    IChain *nextInChain;

public:
    void SetNext(IChain *next) override
    {
        this->nextInChain = next;
    }

    void Calculate(Numbers *request) override
    {
        if (request->GetOperation() == "add")
        {
            int x = request->GetX();
            int y = request->GetY();

            printf("%d + %d = %d\n", x, y, x + y);
        }
        else
        {
            this->nextInChain->Calculate(request);
        }
    }
};

class SubstractNumbers : public IChain
{
private:
    IChain *nextInChain;

public:
    void SetNext(IChain *next) override
    {
        this->nextInChain = next;
    }

    void Calculate(Numbers *request) override
    {
        if (request->GetOperation() == "sub")
        {
            int x = request->GetX();
            int y = request->GetY();

            printf("%d - %d = %d\n", x, y, x - y);
        }
        else
        {
            this->nextInChain->Calculate(request);
        }
    }
};

class MultiplyNumbers : public IChain
{
private:
    IChain *nextInChain;

public:
    void SetNext(IChain *next) override
    {
        this->nextInChain = next;
    }

    void Calculate(Numbers *request) override
    {
        if (request->GetOperation() == "mult")
        {
            int x = request->GetX();
            int y = request->GetY();

            printf("%d * %d = %d\n", x, y, x * y);
        }
        else
        {
            this->nextInChain->Calculate(request);
        }
    }
};

class DivideNumbers : public IChain
{
private:
    IChain *nextInChain;

public:
    void SetNext(IChain *next) override
    {
        this->nextInChain = next;
    }

    void Calculate(Numbers *request) override
    {
        if (request->GetOperation() == "div")
        {
            int x = request->GetX();
            int y = request->GetY();

            if (y != 0)
                printf("%d / %d = %d\n", x, y, x / y);
            else
                printf("y = 0!!!\n");
        }
        else
        {
            printf("Only works for add, sub, mult and div.\n");
        }
    }
};

int main()
{
    IChain *chain_1 = new AddNumbers();
    IChain *chain_2 = new SubstractNumbers();
    IChain *chain_3 = new MultiplyNumbers();
    IChain *chain_4 = new DivideNumbers();

    Numbers *request = new Numbers(5, 7, "mult");

    chain_1->SetNext(chain_2);
    chain_2->SetNext(chain_3);
    chain_3->SetNext(chain_4);

    chain_1->Calculate(request);

    delete chain_1;
    delete chain_2;
    delete chain_3;
    delete chain_4;

    delete request;

    return 0;
}