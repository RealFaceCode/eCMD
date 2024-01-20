#pragma once

#include <string>
#include <optional>
#include <queue>

#include "capture.hpp"

namespace ecmd
{
    struct CommandPromt
    {
        CommandPromt();

        CommandPromt(int argc, const char** argv, bool voidFirstArg = false);

        CommandPromt(const CommandPromt&) = default;
        CommandPromt& operator=(const CommandPromt&) = default;
        CommandPromt(CommandPromt&&) = default;
        CommandPromt& operator=(CommandPromt&&) = default;

        std::optional<std::string> next();

        ~CommandPromt();

        void captureInput();

        bool hasInput() const;

        bool check();

        size_t argsLeft();

        bool compare(std::string_view str, size_t argsLeft, bool ignore = false);

        bool compare(std::string_view str);

        std::string_view lastArg() const;

    private:
        std::queue<std::string> args;
        Capture capture;
        bool captureMode;
        std::string last;
        bool looped = false;
    };
}