#ifndef GL_TYPES_H
#define GL_TYPES_H

namespace khinkali
{
    enum GLWindowType { GL_WINDOW_2D, GL_WINDOW_3D };

    enum GLTransformationType 
    { 
        GL_SHIFT_2D, GL_ROTATE_2D, GL_MIRROR_2D, GL_SCALE_2D,
        GL_SHIFT_3D, GL_ROTATE_3D, GL_MIRROR_3D, GL_SCALE_3D
    };
    
    enum GLShaderType 
    { 
        GL_SHADER_TYPE_VERTEX, 
        GL_SHADER_TYPE_FRAGMENT 
    };    

    enum GLDrawableType 
    {
        GL_DRAWABLE_TYPE_TRIANGLE,
        GL_DRAWABLE_TYPE_RECTANGLE,
        GL_DRAWABLE_TYPE_CUBE        
    };
};

#endif