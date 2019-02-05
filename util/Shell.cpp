#include "Shell.h"
#include "Engine.h"

const olc::Pixel Shell::Message::BACKGROUND_COLOR = olc::Pixel(0, 0, 0, 100);
const float Shell::Message::MAX_AGE = 10;
const float Shell::Message::FADE_AGE = MAX_AGE*2/3;

Shell::Message::Message(std::string const & message, olc::Pixel color, uint32_t scale)
    : _scale(scale)
    , _originalMessage(message)
    , _message(generateMessageString(_originalMessage))
    , _messageSprite(uint32_t(Engine::ScreenWidth() * 2 / 3 + 2 - (Engine::ScreenWidth() * 2 / 3 + 1) % (8 * _scale)) + PADDING, uint32_t(_lines * 8 * _scale + 2))
    , _color(color)
    , _age(0)
    , _backgroundColor(BACKGROUND_COLOR)
{
    initSprite();
}

void Shell::Message::initSprite()
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

std::string Shell::Message::generateMessageString(std::string const & message)
{
    // 12 = 1.5(2/3 screen with) * 8(default font with)
    messageWidth = uint32_t(Engine::ScreenWidth() / (12 * _scale));
    _lines = 0;
    std::string newString;

    for (size_t start = 0; start < message.length(); start++)
    {
        std::string substr = message.substr(start, messageWidth);
        size_t current_newlines = size_t(std::count(substr.begin(), substr.end(), '\n'));
        size_t split_index = 0;
        if (current_newlines == 0)
        {
            split_index = substr.find_last_of(' ');
            if (split_index == std::string::npos)
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
    if (_lines == 0) {
        _lines = 1;
    }
    return newString;
}

void Shell::Message::draw(uint32_t height)
{
    Engine::instance().drawSpriteOnTop(&_messageSprite, Message::PADDING, height);
}

void Shell::draw(float fElapsedTime)
{
    uint32_t height = Engine::ScreenHeight() - Message::PADDING -messages.front().getMessageHeight();
    for (auto& message : messages)
    {
        message.increaseAge(fElapsedTime);
        message.draw(height);
        height -= message.getMessageHeight() + Message::PADDING;

        if (message.getAge() >= Message::FADE_AGE)
        {
            olc::Pixel c = message.getColor();
            c.a -= /*(uint8_t)ceil((std::min(fElapsedTime, .99f)*c.a))+*/1;
            message.setColor(c);

            olc::Pixel b = message.getBackground();
            b.a = c.a / 10;
            message.setBackground(b);
        }
    }

    messages.remove_if([](Message const& message)
    {
        return /*message.getAge() >= Message::MAX_AGE ||*/ message.getColor().a < 10;
    });
}
