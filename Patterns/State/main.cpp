#include <iostream>

class State;

class PowerSupply
{
private:
    State *state;

public:
    PowerSupply();

    void SetState(State *state)
    {
        this->state = state;
    }

    void On();

    void Off();
};

class State
{
public:
    virtual void On(PowerSupply *power_supply)
    {
        std::cout << "already in on state\n";
    }
    virtual void Off(PowerSupply *power_supply)
    {
        std::cout << "already in off state\n";
    }
};

void PowerSupply::On()
{
    this->state->On(this);
}

void PowerSupply::Off()
{
    this->state->Off(this);
}

class StateOff : public State
{
public:
    StateOff()
    {
        std::cout << "supply off\n";
    }

    void On(PowerSupply *power_supply);
};

class StateOn : public State
{
public:
    StateOn()
    {
        std::cout << "supply on\n";
    }

    void Off(PowerSupply *power_supply)
    {
        power_supply->SetState(new StateOff());
        delete this;
    }
};

void StateOff::On(PowerSupply *power_supply)
{
    power_supply->SetState(new StateOn());
    delete this;
}

PowerSupply::PowerSupply()
{
    this->state = new StateOff();
}

int main()
{
    PowerSupply *power_supply = new PowerSupply();

    power_supply->On();
    power_supply->On();
    power_supply->Off();
    power_supply->Off();

    delete power_supply;

    return 0;
}