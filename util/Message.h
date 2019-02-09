#ifndef WIRDNIX_MESSAGE_H
#define WIRDNIX_MESSAGE_H

#include "olcPixelGameEngine.h"
#include <string>
#include <list>
#include <algorithm>
#include "Shell.h"
#include <ctime>
#include "Engine.h"

class Message
{
    friend class Shell;

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

    // empty default constructor for Shell
    Message() = default;

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

#endif //WIRDNIX_MESSAGE_H
