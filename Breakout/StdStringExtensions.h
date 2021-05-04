#pragma once

#include <algorithm> 
#include <cctype>
#include <locale>

// trim from start (in place)
static inline void LTrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
}

// trim from end (in place)
static inline void RTrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

// trim from both ends (in place)
static inline void Trim(std::string& s) {
    LTrim(s);
    RTrim(s);
}

