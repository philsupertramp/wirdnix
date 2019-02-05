#ifndef WIRDNIX_SHELL_H
#define WIRDNIX_SHELL_H

#include "olcPixelGameEngine.h"
#include "Engine.h"
#include <string>
#include <list>
#include <algorithm>

class Shell
{
public:
    class Message;

private:
    std::list<Message> messages;
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
        float _age;

    public:
        olc::Pixel _backgroundColor;
        static const olc::Pixel Shell::Message::BACKGROUND_COLOR;
        static const uint32_t PADDING = 5;
        static const float MAX_AGE;
        static const float FADE_AGE;

        Message(std::string const& message, olc::Pixel color = olc::WHITE, uint32_t scale = 1);

        void setColor(olc::Pixel const& newColor)
        {
            _color = newColor;
            initSprite();
        }

        void setBackground(olc::Pixel const& newColor)
        {
            _backgroundColor = newColor;
            initSprite(); //TODO dirty flag
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

        void initSprite();

        uint32_t getMessageHeight()
        {
            return _messageSprite.height;
        }

        std::string generateMessageString(std::string const& message);

        void draw(uint32_t height);

        void increaseAge(float fElapsedTime)
        {
            _age += fElapsedTime;
        }

        float getAge() const
        {
            return _age;
        }

        olc::Pixel const& getColor() const
        {
            return _color;
        }

        olc::Pixel const& getBackground() const
        {
            return _backgroundColor;
        }
    };

    void draw(float fElapsedTime);

    void addMessage(std::string const& message)
    {
        Message newMessage(message);
        addMessage(newMessage);
    }

    void addMessage(Message const& message)
    {
        messages.push_front(message);
    }
};


#endif //WIRDNIX_SHELL_H
