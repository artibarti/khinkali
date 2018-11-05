#ifndef GL_EXCEPTION_H
#define GL_EXCEPTION_H

#include <exception>
#include <iostream>

namespace khinkali {

    class glShaderNotLoadedForSceneException: public std::exception
    {
        virtual const char* what() const throw()
        {
            return "glShaderNotLoadedForSceneException";
        }
    };

    class glShaderLoadException: public std::exception
    {
        virtual const char* what() const throw()
        {
            return "glShaderLoadException";
        }
    };

    class glUnknownShaderTypeException: public std::exception
    {
        virtual const char* what() const throw()
        {
            return "glUnknownShaderTypeException";
        }
    };

    class glDuplicatedObjectNameException: public std::exception
    {
        virtual const char* what() const throw()
        {
            return "glDuplicatedObjectNameException";
        }
    };

    class glShaderCompileException: public std::exception
    {
        virtual const char* what() const throw()
        {
            return "glShaderCompileException";
        }
    };
}

#endif