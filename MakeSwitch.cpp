////////////////////////////////////////////////////////////////////////////
// MakeSwitch.cpp -- generate switch statements to identify string
// Copyright (C) 2015 Katayama Hirofumi MZ.  All rights reserved.
////////////////////////////////////////////////////////////////////////////

#include "MakeSwitch.hpp"
#include <unordered_set>

namespace katahiromz
{

////////////////////////////////////////////////////////////////////////////
// configration

// tab width
static const int c_tab_width = 4;
//static const int c_tab_width = 8;
//static const int c_tab_width = -1;

////////////////////////////////////////////////////////////////////////////

// make indent
std::string MakeIndent(int indent_level) {
    if (c_tab_width == -1) {
        return std::string(indent_level, '\t');
    } else {
        return std::string(c_tab_width * indent_level, ' ');
    }
}

// make switch statements to identify the string
std::string MakeSwitch(
    const std::vector<std::string>& strings,
    const std::string& matched/* = ""*/,
    int switch_level/* = 0*/, int indent_level/* = 1*/)
{
    std::string ret = MakeIndent(indent_level);
    ret += "switch (s[" + std::to_string(switch_level) + "])\n";
    ret += MakeIndent(indent_level) + "{\n";

    int i = 0, index = -1;
    std::unordered_set<char> chars;
    for (auto& str : strings) {
        if (str.find(matched) == 0) {
            char ch = str[matched.size()];
            if (ch) {
                chars.emplace(ch);
            } else {
                index = i;
            }
        }
        ++i;
    }

    for (auto ch : chars) {
        ret += MakeIndent(indent_level) + "case '";
        ret += ch;
        ret += "':\n";

        std::string new_matched = matched;
        new_matched += ch;
        for (size_t i = 0; i < strings.size(); ++i) {
            if (strings[i].find(new_matched) == 0) {
                ret += MakeSwitch(strings, new_matched,
                    switch_level + 1, indent_level + 1);
                break;
            }
        }
    }

    if (index != -1) {
        ret += MakeIndent(indent_level) + "case 0:\n";
        ret += MakeIndent(indent_level + 1) +
               "return " + std::to_string(index) + ";\n";
    }

    ret += MakeIndent(indent_level) + "default:\n";
    ret += MakeIndent(indent_level + 1) + "return -1;\n";

    ret += MakeIndent(indent_level) + "}\n";
    return ret;
}

// make a function code to identify the string
std::string MakeIdentifyStringFunction(
    const std::vector<std::string>& strings,
    const std::string& func_name/* = "identify_string"*/)
{
    std::string ret = "int " + func_name + "(const char *s)\n";
    ret += "{\n";
    ret += MakeSwitch(strings);
    ret += "}\n";
    return ret;
}

////////////////////////////////////////////////////////////////////////////

} // namespace katahiromz

////////////////////////////////////////////////////////////////////////////
