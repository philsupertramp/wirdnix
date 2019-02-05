#include "Shell.h"
#include "Engine.h"

const olc::Pixel Shell::Message::BACKGROUND_COLOR = olc::Pixel(0, 0, 0, 100);
const olc::Pixel Shell::SHELL_BACKGROUND_COLOR = olc::Pixel(0, 0, 0, 150);
const olc::Pixel Shell::SYSTEM_MESSAGE_COLOR = olc::WHITE;
const olc::Pixel Shell::USER_MESSAGE_COLOR = olc::BLUE;
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
    time_t now = time(0);
    tm* local_now = localtime(&now);
    local_now->tm_sec += 20;
    _createdAt = time_t (local_now);
}

void Shell::Message::setColor(olc::Pixel const & newColor)
{
    _color = newColor;
    initSprite();
}

void Shell::Message::setBackground(olc::Pixel const & newColor)
{
    _backgroundColor = newColor;
    initSprite(); //TODO dirty flag
}

void Shell::Message::setScale(uint32_t newScale)
{
    if (newScale == 0)
    {
        newScale = 1;
    }

    _scale = newScale;
    generateMessageString(_originalMessage);
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

uint32_t Shell::Message::getMessageHeight()
{
    return _messageSprite.height;
}
uint32_t Shell::Message::getMessageWidth()
{
    return _messageSprite.width;
}

std::string Shell::Message::generateMessageString(std::string const & message)
{
    // 12 = 1.5(2/3 screen with) * 8(default font with)
    messageWidth = uint32_t(Engine::ScreenWidth() / (12 * _scale));
    _lines = 0;
    std::string newString;
    if(message.length() <= messageWidth){
        newString = message;
        _lines += 1;
        return newString;
    }
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

void Shell::Message::increaseAge(float fElapsedTime)
{
    _age += fElapsedTime;
}

float Shell::Message::getAge() const
{
    return _age;
}

olc::Pixel const & Shell::Message::getColor() const
{
    return _color;
}

olc::Pixel const & Shell::Message::getBackground() const
{
    return _backgroundColor;
}

std::string Shell::Message::getMessageString()
{
    return _originalMessage;
}

time_t Shell::Message::getCreatedAt()const {
    return _createdAt;
}

void Shell::Message::toggleUppercase(){
    _messageUppercase = !_messageUppercase;
}
void Shell::draw(float fElapsedTime)
{
    uint32_t height = Engine::ScreenHeight() - Message::PADDING -messages.front().getMessageHeight();
    uint32_t shell_height = Message::PADDING;

    if(_waitingForInput){
        Message input(_input);
        if(messages.front().getMessageString() != input.getMessageString() || messages.empty())
        {
            if(!messages.empty()) {
                messages.pop_front();
            }
            messages.push_front(input);
            shell_height += input.getMessageHeight();
        }
    }

    for (auto& n : messages)
    {
        shell_height += n.getMessageHeight() + Message::PADDING;
    }
    setHeight(shell_height);
    Engine::instance().fillRectOnTop(SHELL_BACKGROUND_COLOR, 0, Engine::ScreenHeight() - getHeight(), messages.front().getMessageWidth() + 2*Message::PADDING, getHeight());
    for (auto& message : messages)
    {
        message.increaseAge(fElapsedTime);
        message.draw(height);
        height -= message.getMessageHeight() + Message::PADDING;
    }

    messages.remove_if([](Message const& message)
    {
        return message.getAge() >= Message::MAX_AGE || message.getCreatedAt() < time(nullptr);
    });
}

void Shell::addMessage(std::string const & message)
{
    Message newMessage(message);
    addMessage(newMessage);
}
void Shell::addUserMessage(std::string const & message)
{
    Message newMessage(message);
    newMessage.setColor(USER_MESSAGE_COLOR);
    addMessage(newMessage);
    _input = "";
}

void Shell::addMessage(Message const & message)
{
    messages.push_front(message);
}

void Shell::setHeight(uint32_t const& height)
{
    _height = height;
}

uint32_t Shell::getHeight()
{
    return _height;
}

void Shell::toggleWaiting()
{
    _waitingForInput = !_waitingForInput;
}

void Shell::sendUserMessage()
{
    if(_waitingForInput){
        addUserMessage(_input);
    }
}
bool Shell::isWaiting()
{
    return _waitingForInput;
}

void Shell::setInput(std::string const& input)
{
    _input = input;
}

std::string Shell::getInput()
{
    return _input;
}

Shell::Message& Shell::getActiveMessage()
{
    return messages.front();
}
