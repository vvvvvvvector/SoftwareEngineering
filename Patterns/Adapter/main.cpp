#include <iostream>
#include <string>

class ISender
{
public:
    virtual ~ISender() {}
    virtual void Send(const std::string &message) = 0;
};

class ClientSender
{
private:
    // nothing
public:
    void SendMessageFromClient(const std::string &message)
    {
        std::cout << "Message from client: " << message << '\n';
    }
};

class ClientAdapter : ISender
{
private:
    ClientSender client;

public:
    void Send(const std::string &message) override
    {
        client.SendMessageFromClient(message);
    }
};

class ServerSender
{
private:
    // nothing
public:
    void SendMessageFromServer(const std::string &message)
    {
        std::cout << "Message from server: " << message << '\n';
    }
};

class ServerAdapter : ISender
{
private:
    ServerSender server;

public:
    void Send(const std::string &message) override
    {
        server.SendMessageFromServer(message);
    }
};

int main()
{
    ServerAdapter *server_adapter = new ServerAdapter();

    server_adapter->Send("hello world from server!");

    ClientAdapter *client_adapter = new ClientAdapter();

    client_adapter->Send("hello world from client!");

    delete server_adapter;
    delete client_adapter;

    return 0;
}