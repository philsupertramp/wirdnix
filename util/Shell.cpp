#define __STDC_WANT_LIB_EXT1__ 1
#include "Shell.h"
#include "Message.h"
#include "Engine.h"
#include <time.h>

olc::Pixel Shell::shellBackgroundColor = olc::Pixel(0, 0, 0, 100);
const olc::Pixel Shell::SYSTEM_MESSAGE_COLOR = olc::Pixel(255,200,200,255);
const olc::Pixel Shell::USER_MESSAGE_COLOR = olc::Pixel(255,255,255,255);
const olc::Pixel Shell::SHELL_BACKGROUND_COLOR = Shell::shellBackgroundColor;

// shell is a singleton
Shell::Shell()
{ }

void Shell::draw(float fElapsedTime)
{
    uint32_t nextMessageHeight = Engine::ScreenHeight() - Message::PADDING;

    bool noMessages = messages.empty();

    uint32_t shellHeight = Message::PADDING;

    if (_waitingForInput)
    {
        nextMessageHeight -= _inputMessage.getMessageHeight() + Message::PADDING;
        auto a = olc::Pixel(100, 0, 0, 100);
        Engine::instance().fillRectOnTop(a,Message::PADDING,Engine::ScreenHeight() - shellHeight - _inputMessage.getMessageHeight()-Message::PADDING, _inputMessage.getMessageWidth() + 2 * Message::PADDING, _inputMessage.getMessageHeight() + 2 * Message::PADDING );
    }

    for (auto& n : messages)
    {
        shellHeight += n.getMessageHeight() + Message::PADDING;
    }

    if(!noMessages)
    {
        uint32_t backgroundWidth = Message::getMessageWidth() + 2 * Message::PADDING;
        uint32_t backgroundHeight = shellHeight;
        uint32_t backgroundPosX = Message::PADDING;
        uint32_t backgroundPosY = Engine::ScreenHeight() - shellHeight - Message::PADDING;

        if (_waitingForInput)
        {
            backgroundPosY -= _inputMessage.getMessageHeight() + Message::PADDING;
        }

        Engine::instance().fillRectOnTop(shellBackgroundColor, backgroundPosX, backgroundPosY, backgroundWidth, backgroundHeight);
    }

    if(_waitingForInput)
    {
        _inputMessage.draw(Engine::ScreenHeight() - _inputMessage.getMessageHeight() - Message::PADDING, Message::PADDING);
        std::cout << messages.size() << " -" << _inputString << std::endl;
    }

    for (auto& message : messages)
    {
        message.increaseAge(fElapsedTime);
        nextMessageHeight -= message.getMessageHeight() + Message::PADDING;
        message.draw(nextMessageHeight, Message::PADDING);
    }

    messages.remove_if([](Message const& message)
    {
        return false;
        return message.getAge() >= Message::MAX_AGE || message.getCreatedAt() < time(NULL);
    });
}


void Shell::addMessage(std::string const& message)
{
    Message newMessage(message);
    addMessage(newMessage);
}


void Shell::addUserMessage(std::string const& message)
{
    Message inputMessage(_inputString = message);
    _inputMessage = inputMessage;
    _inputMessage.setColor(USER_MESSAGE_COLOR);
    _inputMessage.setBackground(SHELL_BACKGROUND_COLOR);
}

void Shell::addMessage(Message const& message)
{
    messages.push_front(message);
}


void Shell::toggleWaiting()
{
    _waitingForInput = !_waitingForInput;
    if (!_waitingForInput)
    {
        _inputString.clear();
    }
}

void Shell::setWaiting(bool isWaiting /* = false */)
{
    _waitingForInput = isWaiting;
    if (!_waitingForInput)
    {
        _inputString.clear();
    }
}

void Shell::sendUserMessage()
{
    if(_waitingForInput)
    {
        _inputMessage.setScale(2);
        _inputMessage.setColor(olc::Pixel(255, 255, 255, 255));
        _inputMessage.setBackground(Message::BACKGROUND_COLOR);
        addMessage(_inputMessage);
        addUserMessage("");
    }
}
bool Shell::isWaiting()
{
    return _waitingForInput;
}

void Shell::setInput(std::string const& input)
{
    addUserMessage(_inputString = input);
}

std::string Shell::getInput()
{
    return _inputString;
}

Message& Shell::getInputMessage()
{
    return _inputMessage;
}
