#include <iostream>

class UserBuilder
{
public:
    virtual ~UserBuilder() {}
    virtual void Reset() = 0;
    virtual void SetFirstName(const std::string &first_name) = 0;
    virtual void SetLastName(const std::string &last_name) = 0;
    virtual void SetEmail(const std::string &email) = 0;
    virtual void SetPhoneNumber(const std::string &phone_number) = 0;
    virtual void SetDateOfBirth(const std::string &date_of_birth) = 0;
    virtual void SetUsername(const std::string &username) = 0;
    virtual void SetPassword(const std::string &password) = 0;
};

class InstagramUser
{
private:
    std::string user_information;

public:
    void ConstructInstagramUser(std::string some_information)
    {
        this->user_information += some_information;
    }

    void ShowUserInfo()
    {
        std::cout << this->user_information << '\n';
    }
};

class InstagramUserBuilder : public UserBuilder
{
private:
    InstagramUser *user;

public:
    ~InstagramUserBuilder()
    {
        delete user;
    }

    void Reset() override
    {
        this->user = new InstagramUser();
        this->user->ConstructInstagramUser("Instagram user:");
    }

    InstagramUserBuilder()
    {
        this->Reset();
    }

    void SetFirstName(const std::string &first_name) override
    {
        this->user->ConstructInstagramUser("\nmy first name: " + first_name);
    }

    void SetLastName(const std::string &last_name) override
    {
        this->user->ConstructInstagramUser("\nmy last name: " + last_name);
    }

    void SetEmail(const std::string &email) override
    {
        this->user->ConstructInstagramUser("\nmy email: " + email);
    }

    void SetPhoneNumber(const std::string &phone_number) override
    {
        this->user->ConstructInstagramUser("\nmy phone: " + phone_number);
    }

    void SetDateOfBirth(const std::string &date_of_birth) override
    {
        this->user->ConstructInstagramUser("\nmy date of birth: " + date_of_birth);
    }

    void SetUsername(const std::string &username) override
    {
        this->user->ConstructInstagramUser("\nmy username: " + username);
    }

    void SetPassword(const std::string &password) override
    {
        this->user->ConstructInstagramUser("\nmy password: " + password);
    }

    InstagramUser *GetUser()
    {
        InstagramUser *result = this->user;
        this->Reset();
        return result;
    }
};

int main()
{
    InstagramUserBuilder *builder = new InstagramUserBuilder();

    builder->SetFirstName("Viktar");
    builder->SetLastName("VScoder");
    builder->SetEmail("viktorzhdanovich@gmail.com");
    builder->SetUsername("vvvvvector");
    builder->SetPassword("1234567890");

    InstagramUser *user_1 = builder->GetUser();
    user_1->ShowUserInfo();

    std::cout << "\n";

    builder->SetFirstName("Pavel");
    builder->SetLastName("VisualStudio");
    builder->SetEmail("i_hate_visual_studio@gmail.com");

    InstagramUser *user_2 = builder->GetUser();
    user_2->ShowUserInfo();

    delete builder;
    delete user_1;
    delete user_2;

    return 0;
}