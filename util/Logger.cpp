#include "Logger.h"
#include <exception>
#include <ctime>

Logger::Logger()
{
    std::time_t result = std::time(nullptr);
    std::string fileName = "Log" + std::to_string(result) + ".log";

    _fout.open(fileName);

    if (!_fout.is_open())
    {
        _fout.clear();
        _fout.open(fileName, std::ios::out); //Create file.
        _fout.close();
        _fout.open(fileName);
        if(!_fout.is_open())
        {
            throw std::runtime_error("can't log");
        }
    }

    if (_fout.bad())
    {
        throw std::runtime_error("can't log");
    }
}

Logger::~Logger()
{
    if (_fout.is_open() && !_fout.bad())
    {
        _fout.close();
    }
    else
    {
        throw std::runtime_error("can't close log!");
    }
}

void Logger::Log(std::string const& str /* = "" */)
{
    static Logger l;
    l._fout << str << std::endl;
}
