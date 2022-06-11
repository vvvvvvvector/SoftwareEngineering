#include <iostream>
#include <string>

class Song
{
private:
    std::string song_name;
    std::string song_artist;
    std::string song_text;
    std::string song_cover;
    int song_duration;

public:
    Song(const std::string &name, const std::string &artist, const std::string &text, const std::string &cover, int duration)
    {
        this->song_name = name;
        this->song_artist = artist;
        this->song_text = text;
        this->song_cover = cover;
        this->song_duration = duration;
    }

    std::string GetName() const
    {
        return this->song_name;
    }

    std::string GetArtist() const
    {
        return this->song_artist;
    }

    std::string GetText() const
    {
        return this->song_text;
    }

    std::string GetCover() const
    {
        return this->song_cover;
    }

    int GetDuration() const
    {
        return this->song_duration;
    }
};

// Implementation
class IResource
{
public:
    virtual ~IResource() {}
    virtual std::string Title() = 0;
    virtual std::string Description() = 0;
};

// ConcreteImplementation
class SongResource : public IResource
{
private:
    Song *song;

public:
    SongResource(Song *s) : song(s)
    {
    }

    std::string Title() override
    {
        return "Artist: " + song->GetArtist() + "\n" +
               "Song name: " + song->GetName() + "\n" +
               "Song cover: " + song->GetCover();
    }

    std::string Description() override
    {
        return "Song text: " + song->GetText() + "\n" +
               "Song duration: " + std::to_string(song->GetDuration());
    }
};

// abstraction
class ComponentView
{
protected:
    IResource *resource;

public:
    ComponentView(IResource *res) : resource(res)
    {
    }

    virtual ~ComponentView() {}

    virtual void ShowComponent() = 0;
};

// concreate abstraction 1
class RowComponent : public ComponentView
{
public:
    RowComponent(IResource *resource) : ComponentView(resource)
    {
    }

    void ShowComponent() override
    {
        std::cout << "I'm a row component!\n"
                  << this->resource->Title() + '\n';
    }
};

// concreate abstraction 2
class FullComponent : public ComponentView
{
public:
    FullComponent(IResource *resource) : ComponentView(resource)
    {
    }

    void ShowComponent() override
    {
        std::cout << "I'm a full component!\n"
                  << this->resource->Title() << '\n'
                  << this->resource->Description() << '\n';
    }
};

int main()
{
    Song *song = new Song("Control me", "Lil Gotit", "control me song text", "control me song cover image url", 180);

    IResource *resource = new SongResource(song);

    ComponentView *row = new RowComponent(resource);
    ComponentView *full = new FullComponent(resource);

    row->ShowComponent();

    std::cout << '\n';

    full->ShowComponent();

    delete song;
    delete resource;
    delete row;
    delete full;

    return 0;
}