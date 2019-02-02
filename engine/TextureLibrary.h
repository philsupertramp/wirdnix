#ifndef TEXTURELIBRARY_H
#define TEXTURELIBRARY_H

#include <map>
#include <set>
#include "olcPixelGameEngine.h"

class TextureLibrary
{
    std::vector<std::pair<std::string, olc::Sprite*>> _lib;
    size_t indexOf(std::string const& name);

public:
    TextureLibrary();
    ~TextureLibrary();

    void operator= (TextureLibrary) = delete;
    TextureLibrary(TextureLibrary const&)
    {
        if (_lib.size() > 0)
            throw std::runtime_error("you shall not copy a TextureLibrary with stuff in it");
    }

    void add(std::string fileName);
    void add(std::string name, olc::Sprite s);
    olc::Sprite* get(std::string name);
    olc::Sprite nothing(std::string const& name);
};

#endif // TEXTURELIBRARY_H
