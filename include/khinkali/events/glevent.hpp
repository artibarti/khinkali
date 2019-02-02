#ifndef GL_EVENT_HPP
#define GL_EVENT_HPP

#include "../drawables/gldrawable.hpp"

namespace khinkali 
{
    class GLScene;

    class GLEvent
    {
        public:

            GLEvent(bool (*trigger)(GLScene*, GLDrawable*), void (*callback)(GLDrawable*));
            bool (*trigger)(GLScene*, GLDrawable*) = nullptr;
            void (*callback)(GLDrawable*) = nullptr;
    };

    GLEvent::GLEvent(bool (*trigger)(GLScene*, GLDrawable*), void (*callback)(GLDrawable*))
    {
        this -> trigger = trigger;
        this -> callback =callback;
    }

};

#endif