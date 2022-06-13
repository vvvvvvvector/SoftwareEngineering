#include <iostream>
#include <string>

class IConverter
{
public:
    virtual ~IConverter() {}
    virtual std::string Convert(const std::string &video) = 0;
};

class VideoConverter : public IConverter
{
public:
    std::string Convert(const std::string &video) override
    {
        std::cout << "Converting...\n";
        return "Converted(" + video + ")";
    }
};

class VideoConverterProxy : public IConverter
{
private:
    VideoConverter *converter_ = nullptr;
    std::string cached_video = "";

public:
    ~VideoConverterProxy()
    {
        delete converter_;
    }

    VideoConverterProxy(VideoConverter *converter) : converter_(new VideoConverter(*converter))
    {
    }

    std::string Convert(const std::string &video) override
    {
        if (this->cached_video == "Cached(Converted(" + video + "))")
            return this->cached_video;

        std::string converted_video = converter_->Convert(video);
        this->cached_video = "Cached(" + converted_video + ")";

        return converted_video;
    }
};

int main()
{
    VideoConverter *converter = new VideoConverter;

    std::cout << converter->Convert("HelloWorld.mov") << '\n';
    std::cout << converter->Convert("HelloWorld.mov") << '\n';
    std::cout << converter->Convert("HelloWorld.mov") << '\n';

    std::cout << '\n';

    VideoConverterProxy *proxy = new VideoConverterProxy(converter);

    std::cout << proxy->Convert("MyVideo.mov") << '\n';
    std::cout << proxy->Convert("MyVideo.mov") << '\n';
    std::cout << proxy->Convert("MyVideo.mov") << '\n';

    std::cout << '\n';

    std::cout << proxy->Convert("MyNewVideo.mov") << '\n';
    std::cout << proxy->Convert("MyNewVideo.mov") << '\n';
    std::cout << proxy->Convert("MyNewVideo.mov") << '\n';

    delete converter;
    delete proxy;

    return 0;
}