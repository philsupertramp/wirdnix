#ifndef WIRDNIX_SHELL_H
#define WIRDNIX_SHELL_H

#include "olcPixelGameEngine.h"
#include "Engine.h"
#include <string>
#include <list>
#include <algorithm>

class Message
{
    static uint32_t _displayWidth;
    time_t _createdAt;

    uint32_t _scale;
    std::string _originalMessage;
    uint32_t _lines;
    uint32_t _messageWidth;
    std::string _message;
    olc::Sprite _messageSprite;
    olc::Pixel _color;
    float _age;
    olc::Pixel _backgroundColor;

    friend class Shell;
    // empty default constructor for Shell
    Message() {};

public:
    bool _messageUppercase = false;
    static const olc::Pixel BACKGROUND_COLOR;
    static const uint32_t PADDING = 5;
    static const float MAX_AGE;
    static const float FADE_AGE;

    Message(std::string const& message, olc::Pixel color = olc::WHITE, uint32_t scale = 2);

    void setColor(olc::Pixel const& newColor);
    void setBackground(olc::Pixel const& newColor);
    void setScale(uint32_t newScale);
    void initSprite();
    uint32_t getMessageHeight();
    static uint32_t getMessageWidth();
    std::string getMessageString();
    std::string generateMessageString(std::string const& message);
    void draw(uint32_t heightOffset, uint32_t widthOffset = 0);
    void increaseAge(float fElapsedTime);
    void toggleUppercase();
    float getAge() const;
    time_t getCreatedAt()const;
    olc::Pixel const& getColor() const;
    olc::Pixel const& getBackground() const;
};

class Shell
{
private:
    std::list<Message> messages;
    Message _inputMessage;
    std::string _inputString;
    bool _waitingForInput = false;

    // shell is a singleton
    Shell();

    static olc::Pixel shellBackgroundColor;

public:
    static const olc::Pixel SYSTEM_MESSAGE_COLOR;
    static const olc::Pixel USER_MESSAGE_COLOR;
    static const olc::Pixel SHELL_BACKGROUND_COLOR;

    static Shell& instance()
    {
        static Shell shell;
        return shell;
    }

    void draw(float fElapsedTime);
    void toggleWaiting();
    void setWaiting(bool = false);
    void addMessage(std::string const& message);
    void addUserMessage(std::string const& message);
    void addMessage(Message const& message);
    void sendUserMessage();
    Message& getInputMessage();
    bool isWaiting();
    void setInput(std::string const& input);
    std::string getInput();

};


#endif //WIRDNIX_SHELL_H
