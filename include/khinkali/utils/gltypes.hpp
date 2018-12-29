#ifndef GL_TYPES_H
#define GL_TYPES_H

namespace khinkali
{    
    enum GLDrawableType 
    {
        GL_DRAWABLE_TYPE_TRIANGLE,
        GL_DRAWABLE_TYPE_RECTANGLE,
        GL_DRAWABLE_TYPE_CUBE        
    };

    enum GLEventType
    {
        GL_ACTION_TYPE_KEY_EVENT,
        GL_ACTION_TYPE_MOUSE_EVENT,
        GL_ACTION_TYPE_HIT_EVENT
    };
};

#endif