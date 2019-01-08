#ifndef GL_EVENT_HPP
#define GL_EVENT_HPP

#include "../drawables/gldrawable.hpp"

namespace khinkali 
{
    class GLEvent
    {
        public:
            GLEvent();
            GLEvent(bool (*trigger)());

        private:
            bool (*trigger)() = nullptr;
            void (*callback)(GLDrawable*) = nullptr;
    };
};

#endif