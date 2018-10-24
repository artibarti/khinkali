#ifndef GL_EXCEPTION_H
#define GL_EXCEPTION_H

#include <exception>
#include <iostream>

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

#endif