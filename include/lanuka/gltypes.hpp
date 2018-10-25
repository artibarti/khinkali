#ifndef GL_TYPES_H
#define GL_TYPES_H

namespace Lanuka
{
    enum GLWindowType { GL_WINDOW_2D, GL_WINDOW_3D };

    enum GLTransformationType 
    { 
        GL_SHIFT_2D, GL_ROTATE_2D, GL_MIRROR_2D, GL_SCALE_2D,
        GL_SHIFT_3D, GL_ROTATE_3D, GL_MIRROR_3D, GL_SCALE_3D
    };

    enum GLShapeType 
    { 
        GL_RECTANGLE, 
        GL_TRIANGLE, 
        GL_CIRCLE 
    };
    
    enum GLShaderType 
    { 
        GL_SHADER_TYPE_VERTEX, 
        GL_SHADER_TYPE_FRAGMENT 
    };    

};

#endif