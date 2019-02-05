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
    std::uint32_t _height;
    std::string _input = "";
    bool _waitingForInput;
    Shell() = default;

public:
    static const olc::Pixel SHELL_BACKGROUND_COLOR;
    static const olc::Pixel SYSTEM_MESSAGE_COLOR;
    static const olc::Pixel USER_MESSAGE_COLOR;
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
        time_t _createdAt;

    public:
        bool _messageUppercase = false;
        olc::Pixel _backgroundColor;
        static const olc::Pixel BACKGROUND_COLOR;
        static const uint32_t PADDING = 5;
        static const float MAX_AGE;
        static const float FADE_AGE;

        Message(std::string const& message, olc::Pixel color = olc::WHITE, uint32_t scale = 1);

        void setColor(olc::Pixel const& newColor);
        void setBackground(olc::Pixel const& newColor);
        void setScale(uint32_t newScale);
        void initSprite();
        uint32_t getMessageHeight();
        uint32_t getMessageWidth();
        std::string getMessageString();
        std::string generateMessageString(std::string const& message);
        void draw(uint32_t height);
        void increaseAge(float fElapsedTime);
        void toggleUppercase();
        float getAge() const;
        time_t getCreatedAt()const;
        olc::Pixel const& getColor() const;
        olc::Pixel const& getBackground() const;
    };

    void draw(float fElapsedTime);
    void toggleWaiting();
    void addMessage(std::string const& message);
    void addUserMessage(std::string const& message);
    void addMessage(Message const& message);
    void setHeight(uint32_t const& height);
    void sendUserMessage();
    Message& getActiveMessage();
    uint32_t getHeight();
    bool isWaiting();
    void setInput(std::string const& input);
    std::string getInput();

};


#endif //WIRDNIX_SHELL_H
