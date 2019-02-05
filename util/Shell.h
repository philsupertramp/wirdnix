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
        size_t scale;
        std::string messageString;
        size_t newLines;
        size_t messageWidth;
        olc::Sprite messageSprite;

    public:
        static const olc::Pixel BACKGROUND_COLOR;

        Message(std::string const& message_string, olc::Pixel color = olc::WHITE, size_t const& scale = 1)
                : scale(scale)
                , messageString(generate_message_string(message_string))
                , messageSprite(uint32_t(Engine::ScreenWidth()/3), uint32_t(newLines*10))
        {
            for(uint32_t i = 0; i < messageSprite.width; i++)
            {
                for(uint32_t j = 0; j < messageSprite.height; j ++)
                {
                    messageSprite.SetPixel(i, j, BACKGROUND_COLOR);
                }
            }
            Engine::DrawString(messageSprite, 2, 2, messageString, color);
        }

        std::string generate_message_string(std::string const& message)
        {
            // 24 = 3(1/3 screen with) * 8(default font with)
            messageWidth = uint32_t(Engine::ScreenWidth()/ (24 * scale) );
            newLines = 1;
            std::string newString;
            size_t end = messageWidth - 1;

            for(size_t start = 0; start < message.length(); start++)
            {
                std::string substr = message.substr(start, end);
                size_t current_newlines = size_t(std::count(substr.begin(), substr.end(), '\n'));
                size_t split_index = 0;
                if(current_newlines == 0)
                {
                    split_index = substr.find_last_of(' ');
                    if(split_index == std::string::npos)
                    {
                        split_index = messageWidth - 1;
                    }
                    else
                    {
                        substr = substr.substr(0, split_index);
                        substr.append("\n");
                    }
                }
                newString.append(substr);
                newLines += 1;
                start += split_index;
                end = start + messageWidth - 1;
                if(end >= message.length())
                {
                    end = message.length();
                }
            }
            return newString;
        }

        void draw()
        {
            Engine::instance().drawSpriteOnTop(&messageSprite);
        }
    };
};


#endif //WIRDNIX_SHELL_H
