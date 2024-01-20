#include "util.hpp"
#include "key.hpp"

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
    bool KBhit(KeyValue& key)
    {
    #ifdef _WIN32
        auto hStdin = ::GetStdHandle(STD_INPUT_HANDLE);
        if (hStdin == INVALID_HANDLE_VALUE)
            return false;

        DWORD keysWaiting = 0;
        if (!::GetNumberOfConsoleInputEvents(hStdin, &keysWaiting))
            return false;

        if (keysWaiting == 0)
            return false;

        INPUT_RECORD input;
        DWORD eventsRead = 0;
        if (!::ReadConsoleInput(hStdin, &input, 1, &eventsRead))
            return false;

        if (eventsRead == 0)
            return false;

        if (input.EventType != KEY_EVENT)
            return false;

        if (!input.Event.KeyEvent.bKeyDown && input.Event.KeyEvent.wVirtualKeyCode != VK_MODIFIER_KEYS)
            return false;

        int value = input.Event.KeyEvent.uChar.AsciiChar;
        if(value == 0)
        {
            key.key = std::nullopt;
            key.funktionKey = static_cast<FunktionKeys>(input.Event.KeyEvent.wVirtualKeyCode);
        }
        else
        {
            key.key = static_cast<Keys>(value);
            key.funktionKey = std::nullopt;
        }

        return true;
    #else
        int value = 0;
        auto readBytes = ::read(STDIN_FILENO, &value, 1);
        if(readBytes == 0)
            return false;

        if(value == 27)
        {
            if(readBytes = ::read(STDIN_FILENO, &value, 1); readBytes == 0)
                return false;
            if(value == 91)
            {
                if(readBytes = ::read(STDIN_FILENO, &value, 1); readBytes == 0)
                    return false;

                key.key = std::nullopt;
                key.funktionKey = static_cast<FunktionKeys>(value);
            }
            else
            {
                key.key = static_cast<Keys>(value);
                key.funktionKey = std::nullopt;
            }
        }
        else
        {
            key.key = static_cast<Keys>(value);
            key.funktionKey = std::nullopt;
        }

        return true;
    #endif
    }
}