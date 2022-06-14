#include <iostream>
#include <list>

class TV
{
public:
    void ChannelForward()
    {
        std::cout << "channel forward\n";
    }

    void ChannelBack()
    {
        std::cout << "channel back\n";
    }

    void Mute()
    {
        std::cout << "TV was muted\n";
    }

    void Unmute()
    {
        std::cout << "TV was unmuted\n";
    }

    void VolumeUp()
    {
        std::cout << "volume up\n";
    }

    void VolumeDown()
    {
        std::cout << "volume down\n";
    }
};

class ICommand
{
public:
    virtual ~ICommand() {}
    virtual void Execute() = 0;
    virtual void Unexecute() = 0;
};

class RemoteForwardButtonCommand : public ICommand
{
private:
    TV *tv;

public:
    RemoteForwardButtonCommand(TV *tv)
    {
        this->tv = tv;
    }

    void Execute() override
    {
        this->tv->ChannelForward();
    }

    void Unexecute() override
    {
        this->tv->ChannelBack();
    }
};

class RemoteBackButtonCommand : public ICommand
{
private:
    TV *tv;

public:
    RemoteBackButtonCommand(TV *tv)
    {
        this->tv = tv;
    }

    void Execute() override
    {
        this->tv->ChannelBack();
    }

    void Unexecute() override
    {
        this->tv->ChannelForward();
    }
};

class RemoteMuteButtonCommand : public ICommand
{
private:
    TV *tv;

public:
    RemoteMuteButtonCommand(TV *tv)
    {
        this->tv = tv;
    }

    void Execute() override
    {
        this->tv->Mute();
    }

    void Unexecute() override
    {
        this->tv->Unmute();
    }
};

class RemoteUnmuteButtonCommand : public ICommand
{
private:
    TV *tv;

public:
    RemoteUnmuteButtonCommand(TV *tv)
    {
        this->tv = tv;
    }

    void Execute() override
    {
        this->tv->Unmute();
    }

    void Unexecute() override
    {
        this->tv->Mute();
    }
};

class RemoteVolumeUpCommand : public ICommand
{
private:
    TV *tv;

public:
    RemoteVolumeUpCommand(TV *tv)
    {
        this->tv = tv;
    }

    void Execute() override
    {
        this->tv->VolumeUp();
    }

    void Unexecute() override
    {
        this->tv->VolumeDown();
    }
};

class RemoteVolumeDownCommand : public ICommand
{
private:
    TV *tv;

public:
    RemoteVolumeDownCommand(TV *tv)
    {
        this->tv = tv;
    }

    void Execute() override
    {
        this->tv->VolumeDown();
    }

    void Unexecute() override
    {
        this->tv->VolumeUp();
    }
};

class CommandHistory
{
private:
    std::list<ICommand *> executedCommands;

public:
    void Push(ICommand *command)
    {
        executedCommands.push_back(command);
    }

    ICommand *Pop()
    {
        ICommand *command = executedCommands.back();
        executedCommands.pop_back();
        return command;
    }
};

class RemoteController
{
private:
    ICommand *forward;
    ICommand *back;
    ICommand *mute;
    ICommand *unmute;
    ICommand *up;
    ICommand *down;
    CommandHistory *history;

public:
    RemoteController(RemoteForwardButtonCommand *forward, RemoteBackButtonCommand *back, RemoteMuteButtonCommand *mute, RemoteUnmuteButtonCommand *unmute, RemoteVolumeUpCommand *up, RemoteVolumeDownCommand *down)
    {
        this->forward = forward;
        this->back = back;
        this->mute = mute;
        this->unmute = unmute;
        this->up = up;
        this->down = down;
        this->history = new CommandHistory();
    }

    void Undo()
    {
        ICommand *command = history->Pop();
        command->Unexecute();
    }

    void Forward()
    {
        history->Push(this->forward);
        this->forward->Execute();
    }

    void Back()
    {
        history->Push(this->back);
        this->back->Execute();
    }

    void Mute()
    {
        history->Push(this->mute);
        this->mute->Execute();
    }

    void Unmute()
    {
        history->Push(this->unmute);
        this->unmute->Execute();
    }

    void VolumeUp()
    {
        history->Push(this->up);
        this->up->Execute();
    }

    void VolumeDown()
    {
        history->Push(this->down);
        this->down->Execute();
    }
};

int main()
{
    TV *tv = new TV();

    RemoteForwardButtonCommand *forward = new RemoteForwardButtonCommand(tv);
    RemoteBackButtonCommand *back = new RemoteBackButtonCommand(tv);
    RemoteMuteButtonCommand *mute = new RemoteMuteButtonCommand(tv);
    RemoteUnmuteButtonCommand *unmute = new RemoteUnmuteButtonCommand(tv);
    RemoteVolumeUpCommand *up = new RemoteVolumeUpCommand(tv);
    RemoteVolumeDownCommand *down = new RemoteVolumeDownCommand(tv);

    RemoteController *controller = new RemoteController(forward, back, mute, unmute, up, down);

    controller->Forward();
    controller->VolumeUp();
    controller->Mute();

    std::cout << '\n';

    controller->Undo();
    controller->Undo();
    controller->Undo();

    delete tv;
    delete forward;
    delete back;
    delete mute;
    delete unmute;
    delete up;
    delete down;
    delete controller;

    return 0;
}