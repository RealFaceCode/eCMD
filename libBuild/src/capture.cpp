#include "capture.hpp"
#include "key.hpp"
#include "util.hpp"

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

#include <iostream>

namespace ecmd
{
    void Capture::clearLine(size_t offset) const
    {
        std::cout << "\r" << std::string(input.size() + offset, ' ') << "\r";
        std::cout.flush();
    }

    void Capture::setCursorPos(int pos) const
    {
#ifdef _WIN32
        auto hStdout = ::GetStdHandle(STD_OUTPUT_HANDLE);
        if (hStdout == INVALID_HANDLE_VALUE)
            return;

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (!::GetConsoleScreenBufferInfo(hStdout, &csbi))
            return;

        csbi.dwCursorPosition.X = pos;
        csbi.dwCursorPosition.Y = csbi.dwCursorPosition.Y;
        ::SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
#else
        struct termios oldt;
        struct termios newt;
        int x;
        int y;

        ::tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);

        ::tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ::printf("\033[6n");
        ::fflush(stdout);
        ::scanf("\033[%d;%dR", &y, &x);
        ::tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        ::printf("\033[%d;%dH", y, pos + 1);
        ::fflush(stdout);
#endif
    }

    void Capture::captureInput()
    {
        KeyValue key;
        if (KBhit(key))
        {
            auto value = key.key.has_value();
            if(value)
            {
                auto keyValue = key.key.value();
                switch(keyValue)
                {
                    using enum Keys;
                    case ENTER:
                    {
                        std::cout << std::endl;
                        hasInputFlag = true;
                        cursorPos = 0;
                        setCursorPos(cursorPos);
                        return;
                    }
                    case BACKSPACE:
                    {
                        if(input.size() == 0 || cursorPos == 0)
                            return;

                        input.erase(cursorPos - 1, 1);
                        clearLine(1);
                        std::cout << input;
                        std::cout.flush();
                        cursorPos--;
                        setCursorPos(cursorPos);
                        return;
                    }
                    case ESCAPE:
                    {
                        return;
                    }
                    default:
                    {
                        input.reserve(input.size() + 1);
                        input.insert(cursorPos, 1, static_cast<int>(keyValue));
                        cursorPos++;
                        clearLine();
                        std::cout << input;
                        std::cout.flush();
                        setCursorPos(cursorPos);
                        return;
                    }
                }
            }

            value = key.funktionKey.has_value();
            if(value)
            {
                auto keyValue = key.funktionKey.value();
                switch(keyValue)
                {
                    using enum FunktionKeys;
                    case LEFT:
                    {
                        if(cursorPos == 0)
                            return;

                        cursorPos--;
                        setCursorPos(cursorPos);
                        return;
                    }
                    case RIGHT:
                    {
                        if(cursorPos == input.size())
                            return;

                        cursorPos++;
                        setCursorPos(cursorPos);
                        return;
                    }
                    default:
                    {
                        return;
                    }
                };
            }
        }
    }

    bool Capture::hasInput() const
    {
        return hasInputFlag;
    }

    std::optional<std::string> Capture::getInput()
    {
        if(hasInputFlag)
        {
            std::string out = input;
            input.clear();
            hasInputFlag = false;
            return out;
        }
        return std::nullopt;
    }
} // namespace ecmd