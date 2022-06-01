#include <iostream>
#include <list>
#include <ctime>

class INumbersGenerator {
public:
    virtual ~INumbersGenerator(){}
    virtual void Generate(int size) = 0;
    virtual void Traverse() = 0;
};

class IntegersGenerator : public INumbersGenerator {
private:
     std::list<int> numbers;
public:
    void Generate(int size) override {
        for (int i = 0; i < size; i++) {
            numbers.push_back(rand() % 101);
        }
    }
    void Traverse() override {
        for (auto i = this->numbers.begin(); i != this->numbers.end(); i++) {
            std::cout << (*i) << ' ';
        }
        std::cout << '\n';
    }
};

class DoublesGenerator : public INumbersGenerator {
private:
     std::list<double> numbers;
public:
    void Generate(int size) override {
        for (int i = 0; i < size; i++) {
            numbers.push_back(-5 + ((double)rand() / RAND_MAX) * (5 - (-5)));
        }
    }
    void Traverse() override {
        for (auto i = this->numbers.begin(); i != this->numbers.end(); i++) {
            std::cout << (*i) << ' ';
        }
        std::cout << '\n';
    }
};

class Context {
private:
    INumbersGenerator *generator;
public:
    void Generate(int size) {
        this->generator->Generate(size);
        this->generator->Traverse();
    }
    
    void ChangeGenerator(INumbersGenerator *generator) {
        this->generator = generator;
    }
};

int main() {
    srand(time(nullptr));
    
    Context *context = new Context();
    
    context->ChangeGenerator(new IntegersGenerator());
    context->Generate(10);
    
    context->ChangeGenerator(new DoublesGenerator());
    context->Generate(10);
    
    delete context;

    return 0;
}