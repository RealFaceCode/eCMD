#pragma once

#include <string>
#include <optional>
#include <queue>

#include "capture.hpp"

namespace ecmd
{
    /**
     * @brief Represents a command prompt object for input handling.
     */
    struct CommandPromt
    {
        /**
         * @brief Constructs a new CommandPromt object.
         */
        CommandPromt();

        /**
         * @brief Constructs a new CommandPromt object.
         * @param argc The number of arguments.
         * @param argv The arguments.
         * @param voidFirstArg Flag indicating if the first argument should be voided.
         */
        CommandPromt(int argc, const char** argv, bool voidFirstArg = false);

        /**
         * @brief Constructs a new CommandPromt object.
         * @param other The CommandPromt object to copy.
         */
        CommandPromt(const CommandPromt&) = default;

        /**
         * @brief Assigns a CommandPromt object.
         * @param other The CommandPromt object to assign.
         * @return A reference to this CommandPromt object.
         */
        CommandPromt& operator=(const CommandPromt&) = default;

        /**
         * @brief Constructs a new CommandPromt object.
         * @param other The CommandPromt object to move.
         */
        CommandPromt(CommandPromt&&) = default;

        /**
         * @brief Assigns a CommandPromt object.
         * @param other The CommandPromt object to move.
         * @return A reference to this CommandPromt object.
         */
        CommandPromt& operator=(CommandPromt&&) = default;

        /**
         * @brief Retrieves the next argument.
         * @return An optional string containing the next argument, or std::nullopt if no arguments are left.
         */
        std::optional<std::string> next();

        /**
         * @brief Destroys the CommandPromt object.
         */
        ~CommandPromt();

        /**
         * @brief Captures user input from the console.
         */
        void captureInput();

        /**
         * @brief Checks if user input has been captured.
         * @return True if user input has been captured, false otherwise.
         */
        bool hasInput() const;

        /**
         * @brief Checks if the command prompt is in capture mode.
         * @return True if the command prompt is ready.
         */
        bool check();

        /**
         * @brief Checks if the command prompt has arguments left.
         * @return size_t The number of arguments left.
         */
        size_t argsLeft();

        /**
         * @brief Compares the next argument with a string.
         * @param str The string to compare with.
         * @param argsLeft The number of arguments left.
         * @param ignore Flag indicating if the case should be ignored.
         * @return True if the next argument matches the string, false otherwise.
         */
        bool compare(std::string_view str, size_t argsLeft, bool ignore = false);

        /**
         * @brief Compares the next argument with a string.
         * @param str The string to compare with.
         * @param ignore Flag indicating if the case should be ignored.
         * @return True if the next argument matches the string, false otherwise.
         */
        bool compare(std::string_view str);

        /**
         * @brief Retrieves the last command.
         * @return A string containing the last command.
         */
        std::string_view lastCommand() const;

    private:
        std::queue<std::string> args;   ///< The arguments.
        Capture capture;                ///< The capture object.
        bool captureMode;               ///< Flag indicating if the command prompt is in capture mode.
        std::string last;               ///< The last command.
        bool looped = false;            ///< Flag indicating if the command prompt has looped.
    };
}