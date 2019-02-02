#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <string>

class Logger
{
    Logger();
    ~Logger();
    std::fstream _fout;

public:

    static void Log(std::string const& str = "");
};

#endif // LOGGER_H
