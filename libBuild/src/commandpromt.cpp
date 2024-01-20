#include "commandpromt.hpp"

#ifdef _WIN32
#include <Windows.h>
#define VK_MODIFIER_KEYS 0x10
#else
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#define VK_MODIFIER_KEYS 0
#endif

namespace ecmd
{
    CommandPromt::CommandPromt()
    {
#ifdef _WIN32
        DWORD mode;
        HANDLE hstdin = ::GetStdHandle(STD_INPUT_HANDLE);
        ::GetConsoleMode(hstdin, &mode);
        ::SetConsoleMode(hstdin, mode & (~ENABLE_ECHO_INPUT));
#elif __linux__
        struct termios oldt;
        struct termios newt;
        ::tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        ::tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif
    }

    CommandPromt::CommandPromt(int argc, const char** argv, bool voidFirstArg)
    : CommandPromt()
    {
        std::vector<std::string> argSpan = {argv, argv + argc};
        if (args.size() <= 1)
        {
            captureMode = true;
            return;
        }
        else
            captureMode = false;
        for (auto arg : argSpan)
            args.emplace(arg);

        if(voidFirstArg)
            args.pop();
    }

    std::optional<std::string> CommandPromt::next()
    {
        if (args.empty())
            return std::nullopt;

        auto arg = args.front();
        args.pop();
        return arg;
    }

    CommandPromt::~CommandPromt()
    {
#ifdef _WIN32
        DWORD mode;
        HANDLE hstdin = ::GetStdHandle(STD_INPUT_HANDLE);
        ::GetConsoleMode(hstdin, &mode);
        ::SetConsoleMode(hstdin, mode | ENABLE_ECHO_INPUT);
#elif __linux__
        struct termios oldt;
        ::tcgetattr(STDIN_FILENO, &oldt);
        oldt.c_lflag |= ICANON | ECHO;
        ::tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    }

    void CommandPromt::captureInput()
    {
        if(captureMode)
            capture.captureInput();
    }

    bool CommandPromt::hasInput() const
    {
        return !args.empty();
    }

    bool CommandPromt::check()
    {
        captureInput();

        if(!captureMode)
            return true;

        if(!capture.hasInput())
            return false;

        auto input = capture.getInput();
        if(!input.has_value())
            return false;

        auto& str = input.value();
        auto pos = str.find_first_of(' ');

        while( pos != std::string::npos)
        {
            auto in = str.substr(0, pos);
            args.push(in);
            str = str.substr(pos + 1);
            pos = str.find_first_of(' ');
        }

        args.push(str);
        return true;
    }

    size_t CommandPromt::argsLeft()
    {
        if(looped)
        {
            looped = false;
            while(!args.empty())
                args.pop();

            return 0;
        }

        looped = true;
        return args.size();
    }

    bool CommandPromt::compare(std::string_view str, size_t argsLeft, bool ignore)
    {
        if(args.empty())
            return false;

        const auto& arg = args.front();
        last = arg;

        bool shouldIgnore = (ignore ? false : (argsLeft != args.size() - 1));
        if(shouldIgnore)
            return false;

        if(arg != str)
            return false;

        args.pop();
        return true;
    }

    bool CommandPromt::compare(std::string_view str)
    {
        return compare(str, 0, true);
    }

    std::string_view CommandPromt::lastCommand() const
    {
        return last;
    }
} // namespace ecmd