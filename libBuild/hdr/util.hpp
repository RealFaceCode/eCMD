#pragma once

namespace ecmd
{
    struct KeyValue;

    /**
     * @brief Checks if a key has been pressed.
     * @param key The key to check.
     * @return True if a key was been pressed, false otherwise.
     */
    bool KBhit(KeyValue& key);
}