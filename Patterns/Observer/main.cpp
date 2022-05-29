#include <iostream>
#include <list>
#include <ctime>

class IObserver
{
public:
    virtual ~IObserver(){};
    virtual void Update() = 0;
};

class IObservable
{
public:
    virtual ~IObservable(){};
    virtual void Subscribe(IObserver *observer) = 0;
    virtual void Unsubscribe(IObserver *observer) = 0;
    virtual void Notify() = 0;
};

class WeatherStation : public IObservable
{
private:
    int data;
    std::list<IObserver *> subscribers;

public:
    virtual ~WeatherStation()
    {
        std::cout << "Weather station was deleted.\n";
    }

    void Subscribe(IObserver *observer) override
    {
        this->subscribers.push_back(observer);
    }

    void Unsubscribe(IObserver *observer) override
    {
        subscribers.remove(observer);
    }

    void Notify() override
    {
        std::list<IObserver *>::iterator it = this->subscribers.begin();
        for (auto i = it; i != this->subscribers.end(); i++)
        {
            (*i)->Update();
        }
    }

    void MeasureData()
    {
        this->data = rand() & 101;
        Notify();
    }

    int getData() const
    {
        return this->data;
    }
};

class PhoneDisplay : public IObserver
{
private:
    int data;
    WeatherStation &station;

public:
    virtual ~PhoneDisplay()
    {
        std::cout << "Goodbye, Phone Display was an observer\n";
    }

    PhoneDisplay(WeatherStation &station) : station(station)
    {
        station.Subscribe(this);
        std::cout << "Now Phone Display is the Observer\n";
    }

    void Update() override
    {
        this->data = this->station.getData();
        std::cout << "Phone display data was updated: " << this->data << '\n';
    }
};

class PCDisplay : public IObserver
{
private:
    int data;
    WeatherStation &station;

public:
    virtual ~PCDisplay()
    {
        std::cout << "Goodbye, PC Display was an observer\n";
    }

    PCDisplay(WeatherStation &station) : station(station)
    {
        station.Subscribe(this);
        std::cout << "Now PC Display is the Observer\n";
    }

    void Update() override
    {
        this->data = this->station.getData();
        std::cout << "PC display data was updated: " << this->data << '\n';
    }
};

class ArduinoLCD : public IObserver
{
private:
    int data;
    WeatherStation &station;

public:
    virtual ~ArduinoLCD()
    {
        std::cout << "Goodbye, Arduino LCD was an observer\n";
    }

    ArduinoLCD(WeatherStation &station) : station(station)
    {
        station.Subscribe(this);
        std::cout << "Now ArduinoLCD Display is the Observer\n";
    }

    void Update() override
    {
        this->data = this->station.getData();
        std::cout << "Arduino lcd display data was updated: " << this->data << '\n';
    }
};

int main()
{
    srand(time(nullptr));

    WeatherStation *station = new WeatherStation();

    PCDisplay *pc_display = new PCDisplay(*station);
    PhoneDisplay *phone_display = new PhoneDisplay(*station);
    ArduinoLCD *arduino_lcd = new ArduinoLCD(*station);

    station->MeasureData();

    station->Unsubscribe(phone_display);

    station->MeasureData();

    delete station;
    delete pc_display;
    delete phone_display;
    delete arduino_lcd;

    return 0;
}