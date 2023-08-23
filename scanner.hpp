/*

MIT License

Copyright (c) 2023 sean butler

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#pragma once

// --------------------------------------------------

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// --------------------------------------------------

namespace scanner 
{

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
