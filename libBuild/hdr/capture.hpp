#pragma once
#include <string>
#include <optional>

namespace ecmd
{
    struct Capture
    {
        void clearLine(size_t offset = 0) const;
        void setCursorPos(int pos) const;
        void captureInput();
        bool hasInput() const;
        std::optional<std::string> getInput();

    private:
        std::string input;
        bool hasInputFlag = false;
        int cursorPos = 0;
    };
}