////////////////////////////////////////////////////////////////////////////
// MakeSwitch.hpp -- generate switch statements to identify string
// Copyright (C) 2015 Katayama Hirofumi MZ.  All rights reserved.
////////////////////////////////////////////////////////////////////////////

#ifndef MAKESWITCH_HPP_
#define MAKESWITCH_HPP_ 1

#include <vector>
#include <string>

////////////////////////////////////////////////////////////////////////////

namespace katahiromz
{
    // make indent
    std::string MakeIndent(int indent_level);

    // make switch statements to identify the string
    std::string MakeSwitch(
        const std::vector<std::string>& strings,
        const std::string& matched = "",
        int switch_level = 0, int indent_level = 1);

    // make a function code to identify the string
    std::string MakeIdentifyStringFunction(
        const std::vector<std::string>& strings,
        const std::string& func_name = "identify_string");
} // namespace katahiromz

////////////////////////////////////////////////////////////////////////////

#endif  // ndef MAKESWITCH_HPP_
