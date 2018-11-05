#ifndef GL_UTILS_H
#define GL_UTILS_H

#include <string>
#include <sstream>
#include <fstream>

namespace khinkali
{
    std::string loadShaderFromFile(const std::string& filename)
    {
        std::string result;

        std::ifstream fs(filename);
        if (fs.good())
        {
            std::stringstream is;
            is << fs.rdbuf();
            result = is.str();
        }

        return result;
    }
}

#endif