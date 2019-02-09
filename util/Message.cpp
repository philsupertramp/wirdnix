#define __STDC_WANT_LIB_EXT1__ 1
#include "Message.h"
#include "Engine.h"
#include <time.h>
#include "olcPixelGameEngine.h"

const olc::Pixel Message::BACKGROUND_COLOR = olc::Pixel(0, 0, 0, 100);
const float Message::MAX_AGE = 10;
const float Message::FADE_AGE = MAX_AGE*2/3;

uint32_t Message::_displayWidth(Engine::ScreenWidth() * 2 / 3 + 2 + Message::PADDING);

Message::Message(std::string const& message, olc::Pixel color, uint32_t scale)
    : _scale(scale)
    , _originalMessage(message)
 //   , _lines(1)
    , _messageWidth(Engine::ScreenWidth() / (12 * _scale))
    , _message(generateMessageString(_originalMessage))
    // recalculate _displayWidth, as initialization of static member is too early
    , _messageSprite(_displayWidth = Engine::ScreenWidth() * 2 / 3 + 2 + Message::PADDING, _lines * 8 * _scale + 2)
    , _color(color)
    , _age(0)
    , _backgroundColor(BACKGROUND_COLOR)
    // 12 = 1.5(2/3 screen with) * 8(default font with)
{
#ifdef __STDC_LIB_EXT1__
    initSprite();
    time_t t = time(NULL);
    struct tm buf;
    localtime_s(&buf, &t);
    buf.tm_sec += 20;
    _createdAt = mktime(&buf);
#endif
}

void Message::setColor(olc::Pixel const & newColor)
{
    _color = newColor;
    initSprite();
}

void Message::setBackground(olc::Pixel const & newColor)
{
    _backgroundColor = newColor;
    initSprite(); //TODO dirty flag
}

void Message::setScale(uint32_t newScale)
{
    if (newScale == 0)
    {
        newScale = 1;
    }

    _scale = newScale;
    generateMessageString(_originalMessage);
    initSprite();
}

void Message::initSprite()
{
    // reset to background color
    for (uint32_t i = 0; i < _messageSprite.width; i++)
    {
        for (uint32_t j = 0; j < _messageSprite.height; j++)
        {
            _messageSprite.SetPixel(i, j, _backgroundColor);
        }
    }
    Engine::DrawString(_messageSprite, 1, 1, _message, _color, _scale);
}

uint32_t Message::getMessageHeight()
{
    return _messageSprite.height;
}
uint32_t Message::getMessageWidth()
{
    return _displayWidth;
}

std::string Message::generateMessageString(std::string const& message)
{
    //// 12 = 1.5(2/3 screen with) * 8(default font with)
    //_messageWidth = uint32_t(Engine::ScreenWidth() / (12 * _scale));
    _lines = 0;
    std::string newString;

    if(message.length() <= _messageWidth)
    {
        newString = message;
        _lines += 1;
        return newString;
    }

    for (size_t start = 0; start < message.length(); start++)
    {
        std::string substr = message.substr(start, _messageWidth);
        size_t current_newlines = size_t(std::count(substr.begin(), substr.end(), '\n'));
        size_t split_index = 0;
        if (current_newlines == 0)
        {
            split_index = substr.find_last_of(' ');
            if (split_index == std::string::npos)
            {
                split_index = _messageWidth;
            }
            substr = substr.substr(0, split_index);
            substr.append("\n");

        }
        newString.append(substr);
        _lines += 1;
        start += split_index;
    }

    if (_lines == 0)
    {
        _lines = 1;
    }
    return newString;
}

void Message::draw(uint32_t heightOffset, uint32_t widthOffset /* = 0 */)
{
    Engine::instance().drawSpriteOnTop(&_messageSprite, widthOffset + Message::PADDING, heightOffset);
}

void Message::increaseAge(float fElapsedTime)
{
    _age += fElapsedTime;
}

float Message::getAge() const
{
    return _age;
}

olc::Pixel const & Message::getColor() const
{
    return _color;
}

olc::Pixel const & Message::getBackground() const
{
    return _backgroundColor;
}

std::string Message::getMessageString()
{
    return _originalMessage;
}

time_t Message::getCreatedAt() const
{
    return _createdAt;
}

void Message::toggleUppercase()
{
    _messageUppercase = !_messageUppercase;
}
