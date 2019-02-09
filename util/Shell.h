#ifndef WIRDNIX_SHELL_H
#define WIRDNIX_SHELL_H

#include "olcPixelGameEngine.h"
#include <string>
#include <list>
#include <algorithm>
#include "Message.h"
#include "Engine.h"

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
