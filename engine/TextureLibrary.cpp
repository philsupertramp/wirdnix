#include "TextureLibrary.h"
#include "Engine.h"


std::vector<std::pair<std::string, olc::Sprite*>> TextureLibrary::_lib;

TextureLibrary::TextureLibrary()
{ }

TextureLibrary::~TextureLibrary()
{
    // clean the mess up
    for (size_t i = 0; i < _lib.size(); i++)
    {
        if (_lib[i].second != nullptr)
        {
            delete _lib[i].second;
            _lib[i].second = nullptr;
        }
    }
}

void clean(std::string& s)
{
    size_t lastB = s.find_last_of('/');
    if (lastB != std::string::npos)
    {
        s.erase(0, lastB+1);
//      std::cout << s << std::endl;
    }

    size_t lastP = s.find_last_of('.');
    if (lastP != std::string::npos)
    {
        s.erase(lastP);
//      std::cout << s << std::endl;
    }
}

size_t TextureLibrary::indexOf(std::string const& name)
{
    for (size_t i = 0; i < _lib.size(); i++)
    {
        if (_lib.at(i).first == name)
        {
            return i;
        }
    }
    return std::string::npos;
}

void TextureLibrary::add(std::string fileName)
{
    std::string cleanedName = fileName;
    clean(cleanedName);

    if (indexOf(cleanedName) == std::string::npos)
    {
        olc::Sprite* s = new olc::Sprite(fileName);
        //TODO check if file actually loaded
        _lib.push_back( std::make_pair(cleanedName, s) );
    }
}

void TextureLibrary::add(std::string name, olc::Sprite s)
{
    clean(name);

    if (indexOf(name) == std::string::npos)
    {
        olc::Sprite* p = new olc::Sprite(s);
        _lib.push_back( std::make_pair(name, p) );
    }
}

olc::Sprite* TextureLibrary::get(std::string const& name)
{
    size_t index = indexOf(name);
    if (index != std::string::npos)
    {
        return _lib.at(index).second;
    }
    else
    {
        nothing(name);
        return get(name);
    }
}

olc::Sprite TextureLibrary::nothing(std::string const& name)
{
    int offSet = 5;
    olc::Sprite s(300-offSet, 300-offSet);

    olc::Pixel color[2];
    color[0] = olc::Pixel(50, 50, 50, 255);
    color[1] = olc::Pixel(50,  0, 50, 255);

    int squareLength = (s.width + s.height)/4;
    while (--squareLength > 11)
    {
        if (squareLength % s.width == 0 && squareLength % s.height == 0)
        {
            break;
        }
    }

    // construct errorSprite
    for (uint32_t i = 0; i < s.height; i += squareLength)
    {
        // such that each row starts with a different color
        int colToChoose = i / squareLength % 2;
        for (uint32_t j = 0; j < s.width; j += squareLength)
        {
            Engine::FillRect(s, i, j, std::min(s.width, i + squareLength), std::min(s.height, j + squareLength), color[colToChoose]);
            colToChoose++;
            colToChoose %= 2;
        }
    }

    auto exn = "\"" + name + "\", ";
    for (uint32_t i = 0; i < s.height; i += 20)
    {
        Engine::DrawString(s, 1, i, "Texture Not Found!", olc::YELLOW);
        Engine::DrawString(s, 1, i + 10, exn + exn + exn, olc::MAGENTA);
    }

    // mirror
    for (uint32_t i = 0; i < (s.height+1)/2; ++i)
    {
        for (uint32_t j = 0; j < (s.width+1)/2; ++j)
        {
            olc::Pixel const& p = s.GetPixel(i, j);
            s.SetPixel(s.height - i,s.width - j,p);
            s.SetPixel(s.height - i,          j,p);
            s.SetPixel(           i,s.width - j,p);
        }
    }

    add(name, s);

    return s;
}

bool TextureLibrary::exists(std::string const& name)
{
    return indexOf(name) != std::string::npos;
}
