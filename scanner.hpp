//
// scanner.hpp
//

// --------------------------------------------------

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// --------------------------------------------------

namespace scanner {

    std::string load_file_to_string(const std::string &filename)
    {
        std::ifstream t(filename);
        std::string text((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        t.close();
        return text;
    }

    std::vector<std::string> split(const std::string & str,
                                    const std::string & delimiter = "\n")
    {
        std::vector<std::string> strings;

        std::string::size_type pos = 0;
        std::string::size_type prev = 0;
        while ((pos = str.find(delimiter, prev)) != std::string::npos)
        {
            strings.push_back(str.substr(prev, pos - prev));
            prev = pos + delimiter.size();
        }

        // To get the last substring (or only, if delimiter is not found)
        strings.push_back(str.substr(prev));

        return strings;
    }

}

// --------------------------------------------------
