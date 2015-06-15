////////////////////////////////////////////////////////////////////////////
// Program.cpp -- generate switch statements to identify string
// Copyright (C) 2015 Katayama Hirofumi MZ.  All rights reserved.
////////////////////////////////////////////////////////////////////////////

#include "MakeSwitch.hpp"
#include <iostream>

////////////////////////////////////////////////////////////////////////////
// the main function

int main(int argc, char **argv) {
    using namespace katahiromz;

    // show usage when there is no argument
    if (argc <= 1) {
        std::string program = argv[0];
        auto i = program.find_last_of("\\/");
        if (i != std::string::npos) {
            program = program.substr(i + 1);
        }
        std::cout << "Usage: " << program << " string1 string2 ..." << std::endl;
        return 0;
    }

    // retrieve strings from command line
    std::vector<std::string> strings;
    strings.reserve(argc);
    for (int i = 1; i < argc; ++i) {
        strings.emplace_back(argv[i]);
    }

    // output a function
    std::cout << MakeIdentifyStringFunction(strings);

    return 0;
}

////////////////////////////////////////////////////////////////////////////
