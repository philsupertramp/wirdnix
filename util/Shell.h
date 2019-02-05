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
        std::string messageString;
        size_t new_lines = 0;
        olc::Sprite messageSprite;
    public:
        static const olc::Pixel BACKGROUND_COLOR;

        Message(std::string const& message_string, olc::Pixel color = olc::WHITE)
                : messageString(generate_message_string(message_string))
                , messageSprite(uint32_t(new_lines*10), uint32_t(Engine::ScreenWidth()/3))
        {
            for(uint32_t i = 0; i < messageSprite.width; i++)
            {
                for(uint32_t j = 0; j < messageSprite.height; j ++)
                {
                    messageSprite.SetPixel(i, j, BACKGROUND_COLOR);
                }
            }
            Engine::DrawString(messageSprite, 0, 0, messageString, color);
        }

        std::string generate_message_string(std::string const& message)
        {
            new_lines = size_t(std::count(message.begin(), message.end(), '\n'));
            return message;
        }

        void draw()
        {
            Engine::instance().drawSpriteOnTop(&messageSprite);
        }
    };
};


#endif //WIRDNIX_SHELL_H
