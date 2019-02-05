#ifndef WIRDNIX_SHELL_H
#define WIRDNIX_SHELL_H

#include "olcPixelGameEngine.h"
#include "Engine.h"
#include <string>

class Shell
{
private:
    Shell() = default;

public:
    static Shell& instance()
    {
        static Shell shell;
        return shell;
    }

    class Message
    {
        std::string _messageString;
        size_t _lines;
        olc::Sprite _messageSprite;
        olc::Pixel _color;
        uint32_t _scale;

    public:
        static const olc::Pixel BACKGROUND_COLOR;

        Message(std::string const& message_string, olc::Pixel color = olc::WHITE, uint32_t scale = 1)
            : _messageString(generateMessageString(message_string))
            , _messageSprite(uint32_t(Engine::ScreenWidth()/3 +2), uint32_t(_lines*10 +2))
            , _color(color)
            , _scale(scale)
        {
            initSprite();
        }

        void setColor(olc::Pixel const& newColor)
        {
            _color = newColor;
            initSprite();
        }

        void setScale(uint32_t newScale)
        {
            if (newScale == 0)
            {
                newScale = 1;
            }

            _scale = newScale;
            generateMessageString();
            initSprite();
        }

        void initSprite()
        {
            // reset to background color
            for(uint32_t i = 0; i < _messageSprite.width; i++)
            {
                for(uint32_t j = 0; j < _messageSprite.height; j ++)
                {
                    _messageSprite.SetPixel(i, j, BACKGROUND_COLOR);
                }
            }
            Engine::DrawString(_messageSprite, 1, 1, _messageString, _color, _scale);
        }

        std::string generateMessageString(std::string const& message)
        {
            _lines = size_t(std::count(message.begin(), message.end(), '\n')) +1;
            return message;
        }

        void draw()
        {
            Engine::instance().drawSpriteOnTop(&_messageSprite, 1, 1);
        }
    };
};


#endif //WIRDNIX_SHELL_H
