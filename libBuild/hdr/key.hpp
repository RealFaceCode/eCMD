#pragma once

#include <optional>

namespace ecmd
{
    enum class Keys : int
    {
        a = 97, A = 65,
        b = 98, B = 66,
        c = 99, C = 67,
        d = 100, D = 68,
        e = 101, E = 69,
        f = 102, F = 70,
        g = 103, G = 71,
        h = 104, H = 72,
        i = 105, I = 73,
        j = 106, J = 74,
        k = 107, K = 75,
        l = 108, L = 76,
        m = 109, M = 77,
        n = 110, N = 78,
        o = 111, O = 79,
        p = 112, P = 80,
        q = 113, Q = 81,
        r = 114, R = 82,
        s = 115, S = 83,
        t = 116, T = 84,
        u = 117, U = 85,
        v = 118, V = 86,
        w = 119, W = 87,
        x = 120, X = 88,
        y = 121, Y = 89,
        z = 122, Z = 90,
        _0 = 48, _1 = 49, _2 = 50, _3 = 51, _4 = 52, _5 = 53, _6 = 54, _7 = 55, _8 = 56, _9 = 57, 
        hash_symbol = 35, dollar_symbol = 36, percent_symbol = 37, ampersand_symbol = 38, quotation_mark = 34, apostrophe = 39,
        left_parenthesis = 40, right_parenthesis = 41, asterisk = 42, plus_sign = 43, comma = 44, minus_sign = 45, period = 46,
        slash = 47, colon = 58, semicolon = 59, less_than_sign = 60, equal_sign = 61, greater_than_sign = 62, question_mark = 63,
        at_sign = 64, left_square_bracket = 91, backslash = 92, right_square_bracket = 93, circumflex = 94, underscore = 95, grave_accent = 96,
        left_curly_bracket = 123, vertical_bar = 124, right_curly_bracket = 125, tilde = 126,
        NP_0 = 96, NP_1 = 97, NP_2 = 98, NP_3 = 99, NP_4 = 100, NP_5 = 101, NP_6 = 102, NP_7 = 103, NP_8 = 104, NP_9 = 105,
        SPACE = 32, ESCAPE = 27, TAB = 9,
    #ifdef _WIN32
        ENTER = 13,
        BACKSPACE = 8,
    #elif __linux__
        ENTER = 10,
        BACKSPACE = 127,
    #endif
    };

    enum class FunktionKeys : int
    {
        F1 = 112, F2 = 113, F3 = 114, F4 = 115, F5 = 116, F6 = 117, F7 = 118, F8 = 119, F9 = 120, F10 = 121, F11 = 122, F12 = 123,
        POS = 36, END = 35, PAGE_UP = 33, PAGE_DOWN = 34, INSERT = 45, DEL = 46,
        CAPS_LOCK = 20, SHIFT = 16, CTRL = 17, ALT = 18,

    #ifdef _WIN32
        LEFT = 37, UP = 38, RIGHT = 39, DOWN = 40,
    #elif __linux__
        LEFT = 68, UP = 65, RIGHT = 67, DOWN = 66,
    #endif
    };

    struct KeyValue
    {
        std::optional<Keys> key;
        std::optional<FunktionKeys> funktionKey;
    };
}