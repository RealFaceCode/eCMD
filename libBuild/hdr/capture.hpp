#pragma once
#include <string>
#include <optional>

namespace ecmd
{
    /**
     * @brief Represents a capture object for input handling.
     */
    struct Capture
    {
        /**
         * @brief Clears the current line on the console.
         * @param offset The number of characters to offset the cursor position.
         */
        void clearLine(size_t offset = 0) const;

        /**
         * @brief Sets the cursor position on the console.
         * @param pos The new cursor position.
         */
        void setCursorPos(int pos) const;

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
         * @brief Retrieves the captured user input.
         * @return An optional string containing the captured user input, or std::nullopt if no input has been captured.
         */
        std::optional<std::string> getInput();

    private:
        std::string input;          ///< The captured user input.
        bool hasInputFlag = false;  ///< Flag indicating if user input has been captured.
        int cursorPos = 0;          ///< The current cursor position.
    };
}