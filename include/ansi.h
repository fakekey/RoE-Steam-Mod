#pragma once

#include <iostream>

namespace ansi {
    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits> &reset(std::basic_ostream<CharT, Traits> &os)
    {
        return os << "\033[0m";
    }

    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits> &foreground_black(std::basic_ostream<CharT, Traits> &os)
    {
        return os << "\033[30m";
    }

    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits> &foreground_red(std::basic_ostream<CharT, Traits> &os)
    {
        return os << "\033[31m";
    }

    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits> &foreground_green(std::basic_ostream<CharT, Traits> &os)
    {
        return os << "\033[32m";
    }

    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits> &foreground_yellow(std::basic_ostream<CharT, Traits> &os)
    {
        return os << "\033[33m";
    }

    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits> &foreground_blue(std::basic_ostream<CharT, Traits> &os)
    {
        return os << "\033[34m";
    }

    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits> &foreground_magenta(std::basic_ostream<CharT, Traits> &os)
    {
        return os << "\033[35m";
    }

    template <class CharT, class Traits>
    constexpr std::basic_ostream<CharT, Traits> &foreground_cyan(std::basic_ostream<CharT, Traits> &os)
    {
        return os << "\033[36m";
    }
} // namespace ansi