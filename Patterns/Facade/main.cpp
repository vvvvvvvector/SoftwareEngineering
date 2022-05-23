#include <iostream>
#include <string>

class VideoFile
{
public:
    VideoFile()
    {
        std::cout << "creating a file...\n";
    }
};

// subsystem 1
class OggCompressionCodec
{
public:
    OggCompressionCodec()
    {
        std::cout << "destination ogg codec obj created!\n";
    }

    void GetCodec()
    {
        std::cout << "destination codec: ogg\n";
    }
};

// subsystem 2
class MPEG4CompressionCodec
{
public:
    MPEG4CompressionCodec()
    {
        std::cout << "destination mpeg4 codec obj created!\n";
    }

    void GetCodec()
    {
        std::cout << "destination codec: MPEG4\n";
    }
};

// subsystem 3
class CodecFactory
{
public:
    CodecFactory()
    {
        std::cout << "codec factory created!\n";
    }

    void ExtractFileCodec()
    {
        std::cout << "extracting a file source codec...\n";
    }
};

// subsystem 4
class BitrateReader
{
public:
    BitrateReader()
    {
        std::cout << "bitreader created!\n";
    }

    void Read()
    {
        std::cout << "writing a file to buffer...\n";
    }

    void Convert()
    {
        std::cout << "converting to destinaton codec...\n";
    }
};

// subsystem 5
class AudioMixer
{
public:
    AudioMixer()
    {
        std::cout << "audio mixer created!\n";
    }

    void Fix()
    {
        std::cout << "fixing the result file...\n";
    }
};

// VideoConverter == Facade
class VideoConverter
{
private:
    OggCompressionCodec *ogg_codec;
    MPEG4CompressionCodec *mpeg4_codec;
    CodecFactory *codec_factory;
    BitrateReader *bitrate_reader;
    AudioMixer *audio_mixer;

public:
    VideoConverter()
    {
        std::cout << "Facade initializes subsystems:\n";

        this->codec_factory = new CodecFactory();
        this->bitrate_reader = new BitrateReader();
        this->audio_mixer = new AudioMixer();
    }

    ~VideoConverter()
    {
        delete codec_factory;
        delete bitrate_reader;
        delete audio_mixer;

        if (ogg_codec != nullptr)
            delete ogg_codec;
        else
            delete mpeg4_codec;
    }

    void Convert(VideoFile *my_file, const std::string &dest_codec)
    {
        auto file = my_file;

        if (dest_codec == "ogg")
        {
            this->ogg_codec = new OggCompressionCodec();
            this->mpeg4_codec = nullptr;
        }
        else
        {
            this->mpeg4_codec = new MPEG4CompressionCodec();
            this->ogg_codec = nullptr;
        }

        std::cout << "Facade orders subsystems to perform the action:\n";

        this->codec_factory->ExtractFileCodec();
        this->bitrate_reader->Read();
        this->bitrate_reader->Convert();
        this->audio_mixer->Fix();

        std::cout << "Facade operation Convert returning a result!\n";
    }
};

int main()
{
    VideoFile *file = new VideoFile();

    VideoConverter *converter = new VideoConverter();

    converter->Convert(file, "mpeg4");

    delete file;
    delete converter;

    return 0;
}