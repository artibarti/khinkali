#ifndef GL_EVENT_HANDLER_H
#define GL_EVENT_HANDLER_H

#include "utils/gltypes.hpp"
#include <map>

namespace khinkali
{    
    template<typename T>
    class GLEventHandler
    {
        public:
            void addCallback(GLEventType eventType, void(*callback)(T*));

        private:
            std::map<GLEventType, void(*)(T*)> callbacks;
    };

    template<typename T>
    void GLEventHandler<T>::addCallback(GLEventType eventType, void(*callback)(T*))
    {
        this->callbacks[eventType] = callback;
    }
};

#endif