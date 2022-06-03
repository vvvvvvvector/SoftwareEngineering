#include <iostream>
#include <string>
#include <unordered_map>

enum Config
{
    CONFIG_MACOS = 0,
    CONFIG_WINDOWS,
    CONFIG_LINUX
};

class ICloneableConfig
{
public:
    virtual ~ICloneableConfig() {}
    virtual ICloneableConfig *Clone() const = 0;
    virtual void ShowConfig() = 0;
    virtual void ChangeConfig(const std::string &new_config) = 0;
};

class MacConfig : public ICloneableConfig
{
private:
    std::string config_description;

public:
    ICloneableConfig *Clone() const override
    {
        return new MacConfig(*this);
    }

    MacConfig(const std::string &config_description)
    {
        this->config_description = config_description;
    }

    void ShowConfig() override
    {
        std::cout << this->config_description << '\n';
    }

    void ChangeConfig(const std::string &new_config) override
    {
        this->config_description = new_config;
    }
};

class WindowsConfig : public ICloneableConfig
{
private:
    std::string config_description;

public:
    ICloneableConfig *Clone() const override
    {
        return new WindowsConfig(*this);
    }

    WindowsConfig(const std::string &config_description)
    {
        this->config_description = config_description;
    }

    void ShowConfig() override
    {
        std::cout << this->config_description << '\n';
    }

    void ChangeConfig(const std::string &new_config) override
    {
        this->config_description = new_config;
    }
};

class LinuxConfig : public ICloneableConfig
{
private:
    std::string config_description;

public:
    ICloneableConfig *Clone() const override
    {
        return new LinuxConfig(*this);
    }

    LinuxConfig(const std::string &config_description)
    {
        this->config_description = config_description;
    }

    void ShowConfig() override
    {
        std::cout << this->config_description << '\n';
    }

    void ChangeConfig(const std::string &new_config) override
    {
        this->config_description = new_config;
    }
};

class ConfigFactory
{
private:
    std::unordered_map<Config, ICloneableConfig *, std::hash<int>> os_configurations;

public:
    ConfigFactory()
    {
        os_configurations[Config::CONFIG_MACOS] = new MacConfig("my standard macos config");
        os_configurations[Config::CONFIG_WINDOWS] = new WindowsConfig("my standard windows config");
        os_configurations[Config::CONFIG_LINUX] = new LinuxConfig("my standard linux config");
    }

    ~ConfigFactory()
    {
        delete os_configurations[Config::CONFIG_MACOS];
        delete os_configurations[Config::CONFIG_WINDOWS];
        delete os_configurations[Config::CONFIG_LINUX];
    }

    ICloneableConfig *CreatePrototype(Config config)
    {
        return os_configurations[config]->Clone();
    }
};

int main()
{
    ConfigFactory *config_factory = new ConfigFactory();

    ICloneableConfig *mac_conf = config_factory->CreatePrototype(Config::CONFIG_MACOS);

    mac_conf->ShowConfig();
    mac_conf->ChangeConfig("changed config mac_conf");
    mac_conf->ShowConfig();

    ICloneableConfig *mac_conf_1 = config_factory->CreatePrototype(Config::CONFIG_MACOS);
    mac_conf_1->ShowConfig();

    delete config_factory;

    delete mac_conf;
    delete mac_conf_1;

    return 0;
}