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
        uint32_t _scale;
        size_t messageWidth;
        std::string _originalMessage;
        std::string _message;
        size_t _lines;
        olc::Sprite _messageSprite;
        olc::Pixel _color;

    public:
        static const olc::Pixel BACKGROUND_COLOR;
        static const uint32_t PADDING = 5;

        Message(std::string const& message, olc::Pixel color = olc::WHITE, uint32_t scale = 1)
            : _scale(scale)
            , _originalMessage(message)
            , _message(generateMessageString(_originalMessage))
            , _messageSprite(uint32_t(Engine::ScreenWidth() * 2 / 3 + 2 - (Engine::ScreenWidth() * 2 / 3 + 1)%(8*_scale)) + PADDING, uint32_t(_lines * 8 * _scale + 2) )
            , _color(color)
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
            generateMessageString(_originalMessage);
            initSprite();
        }

        void initSprite()
        {
            // reset to background color
            for (uint32_t i = 0; i < _messageSprite.width; i++) {
                for (uint32_t j = 0; j < _messageSprite.height; j++) {
                    _messageSprite.SetPixel(i, j, BACKGROUND_COLOR);
                }
            }
            Engine::DrawString(_messageSprite, 1, 1, _message, _color, _scale);
        }

        std::string generateMessageString(std::string const& message)
        {
            // 12 = 1.5(2/3 screen with) * 8(default font with)
            messageWidth = uint32_t(Engine::ScreenWidth()/ (12 * _scale) );
            _lines = 0;
            std::string newString;

            for(size_t start = 0; start < message.length(); start++)
            {
                std::string substr = message.substr(start, messageWidth);
                size_t current_newlines = size_t(std::count(substr.begin(), substr.end(), '\n'));
                size_t split_index = 0;
                if(current_newlines == 0)
                {
                    split_index = substr.find_last_of(' ');
                    if(split_index == std::string::npos)
                    {
                        split_index = messageWidth;
                    }
                    substr = substr.substr(0, split_index);
                    substr.append("\n");

                }
                newString.append(substr);
                _lines += 1;
                start += split_index;
            }
            if(_lines == 0){
                _lines = 1;
            }
            return newString;
        }

        void draw()
        {
            Engine::instance().drawSpriteOnTop(&_messageSprite, 1, 1);
        }
    };
};


#endif //WIRDNIX_SHELL_H
