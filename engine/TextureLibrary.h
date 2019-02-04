#ifndef TEXTURELIBRARY_H
#define TEXTURELIBRARY_H

#include <map>
#include <set>
#include "olcPixelGameEngine.h"

class TextureLibrary
{
    static std::vector<std::pair<std::string, olc::Sprite*>> _lib;
    static size_t indexOf(std::string const& name);

    TextureLibrary();
    ~TextureLibrary();

public:
    TextureLibrary& instance()
    {
        static TextureLibrary t;
        return t;
    }

    void operator= (TextureLibrary) = delete;
    TextureLibrary(TextureLibrary const&)
    {
        if (_lib.size() > 0)
        {
            throw std::runtime_error("you shall not copy a TextureLibrary with stuff in it");
        }
    }

    static void add(std::string fileName);
    static void add(std::string name, olc::Sprite s);
    static olc::Sprite* get(std::string const& name);
    static olc::Sprite nothing(std::string const& name);

    static bool exists(std::string const& name);
};

#endif // TEXTURELIBRARY_H
