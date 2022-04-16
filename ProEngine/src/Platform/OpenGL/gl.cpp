#include "Propch.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Platform/OpenGL/gl.h"


#if defined(_WIN32) || defined(__CYGWIN__)

#include <windows.h>


#ifdef _MSC_VER
#ifdef __has_include
  #if __has_include(<winapifamily.h>)
    #define HAVE_WINAPIFAMILY 1
  #endif
#elif _MSC_VER >= 1700 && !_USING_V110_SDK71_
  #define HAVE_WINAPIFAMILY 1
#endif
#endif

#ifdef HAVE_WINAPIFAMILY
  #include <winapifamily.h>
#endif


#endif


//#define PRO_DEBUG_OPENGL
#ifdef PRO_DEBUG_OPENGL

#define DEF(name, type) \
    type gl_##name##_Native = NULL;\
    type gl_##name = NULL;

#define LOAD_NATIVE(name, type)\
    if(!(gl_##name##_Native = (type)load("gl"#name))) std::cout << "Error gl"#name" function could not be loaded\n";

#define LOAD(name, type)\
    if(!(gl_##name = (type)load("gl"#name))) std::cout << "Error";

#define LOAD0(name, type, ret)\
    LOAD_NATIVE(name, type)\
    gl_##name = []() -> ret {LOGI(__FILE__, __LINE__, "gl"#name) return gl_##name##_Native();};\
    

#define LOAD1(name, type, ret, arg1, name1)\
    LOAD_NATIVE(name, type)\
    gl_##name = [](arg1 name1) -> ret { LOG("gl"#name) return gl_##name##_Native(name1);};

#define LOAD2(name, type, ret, arg1, name1, arg2, name2)\
    LOAD_NATIVE(name, type)\
    gl_##name = [](arg1 name1, arg2 name2) -> ret { LOG("gl"#name) return gl_##name##_Native(name1, name2);};

#define LOAD3(name, type, ret, arg1, name1, arg2, name2, arg3, name3)\
    LOAD_NATIVE(name, type)\
    gl_##name = [](arg1 name1, arg2 name2, arg3 name3) -> ret { LOG("gl"#name) return gl_##name##_Native(name1, name2, name3);};

#define LOAD4(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4)\
    LOAD_NATIVE(name, type)\
    gl_##name = [](arg1 name1, arg2 name2, arg3 name3, arg4 name4) -> ret { LOG("gl"#name) return gl_##name##_Native(name1, name2, name3, name4);};

#define LOAD5(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4, arg5, name5)\
    LOAD_NATIVE(name, type)\
    gl_##name = [](arg1 name1, arg2 name2, arg3 name3, arg4 name4, arg5 name5) -> ret { LOG("gl"#name) return gl_##name##_Native(name1, name2, name3, name4, name5);};

#define LOAD6(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4, arg5, name5, arg6, name6)\
    LOAD_NATIVE(name, type)\
    gl_##name = [](arg1 name1, arg2 name2, arg3 name3, arg4 name4, arg5 name5, arg6 name6) -> ret { LOG("gl"#name) return gl_##name##_Native(name1, name2, name3, name4, name5, name6);};

#define LOAD7(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4, arg5, name5, arg6, name6, arg7, name7)\
    LOAD_NATIVE(name, type)\
    gl_##name = [](arg1 name1, arg2 name2, arg3 name3, arg4 name4, arg5 name5, arg6 name6, arg7 name7) -> ret { LOG("gl"#name) return gl_##name##_Native(name1, name2, name3, name4, name5, name6, name7);};

#define LOAD8(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4, arg5, name5, arg6, name6, arg7, name7, arg8, name8)\
    LOAD_NATIVE(name, type)\
    gl_##name = [](arg1 name1, arg2 name2, arg3 name3, arg4 name4, arg5 name5, arg6 name6, arg7 name7, arg8 name8) -> ret { LOG("gl"#name) return gl_##name##_Native(name1, name2, name3, name4, name5, name6, name7, name8);};

#define LOAD9(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4, arg5, name5, arg6, name6, arg7, name7, arg8, name8, arg9, name9)\
    LOAD_NATIVE(name, type)\
    gl_##name = [](arg1 name1, arg2 name2, arg3 name3, arg4 name4, arg5 name5, arg6 name6, arg7 name7, arg8 name8, arg9 name9) -> ret { LOG("gl"#name) return gl_##name##_Native(name1, name2, name3, name4, name5, name6, name7, name8, name9);};



#else

#define DEF(name, type) \
    type gl_##name = NULL;

#define LOAD(name, type)\
    if(!(gl_##name = (type)load("gl"#name))) std::cout << "Error gl"#name" function could not be loaded\n";

#define LOAD0(name, type, ret)\
    LOAD(name, type)

#define LOAD1(name, type, ret, arg1, name1)\
    LOAD(name, type)

#define LOAD2(name, type, ret, arg1, name1, arg2, name2)\
    LOAD(name, type)

#define LOAD3(name, type, ret, arg1, name1, arg2, name2, arg3, name3)\
    LOAD(name, type)

#define LOAD4(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4)\
    LOAD(name, type)

#define LOAD5(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4, arg5, name5)\
    LOAD(name, type)

#define LOAD6(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4, arg5, name5, arg6, name6)\
    LOAD(name, type)

#define LOAD7(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4, arg5, name5, arg6, name6, arg7, name7)\
    LOAD(name, type)

#define LOAD8(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4, arg5, name5, arg6, name6, arg7, name7, arg8, name8)\
    LOAD(name, type)

#define LOAD9(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4, arg5, name5, arg6, name6, arg7, name7, arg8, name8, arg9, name9)\
    LOAD(name, type)


#endif


DEF(Clear, PFNGLCLEARPROC)
DEF(ClearColor, PFNGLCLEARCOLORPROC)
DEF(GetString, PFNGLGETSTRINGPROC)
DEF(GenVertexArrays, PFNGLGENVERTEXARRAYSPROC)
DEF(BindVertexArray, PFNGLBINDVERTEXARRAYPROC)
DEF(GenBuffers, PFNGLGENBUFFERSPROC)
DEF(BindBuffer, PFNGLBINDBUFFERPROC)
DEF(BufferData, PFNGLBUFFERDATAPROC)
DEF(EnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC)
DEF(VertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC)
DEF(DrawArrays, PFNGLDRAWARRAYSPROC)
DEF(DisableVertexAttribArray, PFNGLDISABLEVERTEXATTRIBARRAYPROC)
DEF(CreateShader, PFNGLCREATESHADERPROC)
DEF(ShaderSource, PFNGLSHADERSOURCEPROC)
DEF(CompileShader, PFNGLCOMPILESHADERPROC)
DEF(CreateProgram, PFNGLCREATEPROGRAMPROC)
DEF(AttachShader, PFNGLATTACHSHADERPROC)
DEF(LinkProgram, PFNGLLINKPROGRAMPROC)
DEF(DetachShader, PFNGLDETACHSHADERPROC)
DEF(DeleteShader, PFNGLDELETESHADERPROC)
DEF(UseProgram, PFNGLUSEPROGRAMPROC)
DEF(DeleteProgram, PFNGLDELETEPROGRAMPROC)
DEF(GetShaderiv, PFNGLGETSHADERIVPROC)
DEF(GetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC)
DEF(GetProgramiv, PFNGLGETPROGRAMIVPROC)
DEF(GetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC)
DEF(DrawElements, PFNGLDRAWELEMENTSPROC)
DEF(GetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC)
DEF(UniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC)
DEF(UniformMatrix3fv, PFNGLUNIFORMMATRIX3FVPROC)
DEF(CreateTextures, PFNGLCREATETEXTURESPROC)
DEF(TextureStorage2D, PFNGLTEXTURESTORAGE2DPROC)
DEF(TextureParameteri, PFNGLTEXTUREPARAMETERIPROC)
DEF(TextureSubImage2D, PFNGLTEXTURESUBIMAGE2DPROC)
DEF(BindTextureUnit, PFNGLBINDTEXTUREUNITPROC)
DEF(Uniform1i, PFNGLUNIFORM1IPROC)
DEF(Enable, PFNGLENABLEPROC)
DEF(BlendFunc, PFNGLBLENDFUNCPROC)
DEF(Viewport, PFNGLVIEWPORTPROC)
DEF(Uniform2f, PFNGLUNIFORM2FPROC)
DEF(Uniform3f, PFNGLUNIFORM3FPROC)
DEF(Uniform4f, PFNGLUNIFORM4FPROC)
DEF(BindTexture, PFNGLBINDTEXTUREPROC)
DEF(BufferSubData, PFNGLBUFFERSUBDATAPROC)
DEF(Uniform1iv, PFNGLUNIFORM1IVPROC)
DEF(Uniform1f, PFNGLUNIFORM1FPROC)
DEF(GetIntegerv, PFNGLGETINTEGERVPROC)
DEF(ActiveTexture, PFNGLACTIVETEXTUREPROC)
DEF(IsEnabled, PFNGLISENABLEDPROC)
DEF(BlendEquation, PFNGLBLENDEQUATIONPROC)
DEF(Disable, PFNGLDISABLEPROC)
DEF(Scissor, PFNGLSCISSORPROC)
DEF(DeleteVertexArrays, PFNGLDELETEVERTEXARRAYSPROC)
DEF(BlendEquationSeparate, PFNGLBLENDEQUATIONSEPARATEPROC)
DEF(BlendFuncSeparate, PFNGLBLENDFUNCSEPARATEPROC)
DEF(GenTextures, PFNGLGENTEXTURESPROC)
DEF(TexParameteri, PFNGLTEXPARAMETERIPROC)
DEF(PixelStorei, PFNGLPIXELSTOREIPROC)
DEF(TexImage2D, PFNGLTEXIMAGE2DPROC)
DEF(DeleteTextures, PFNGLDELETETEXTURESPROC)
DEF(GetAttribLocation, PFNGLGETATTRIBLOCATIONPROC)
DEF(DeleteBuffers, PFNGLDELETEBUFFERSPROC)
DEF(GetError, PFNGLGETERRORPROC)
DEF(DebugMessageCallback, PFNGLDEBUGMESSAGECALLBACKPROC)
DEF(DebugMessageControl, PFNGLDEBUGMESSAGECONTROLPROC)
DEF(DispatchCompute, PFNGLDISPATCHCOMPUTEPROC);

static void load_GL(GLADloadproc load) {
    LOAD0(GetError, PFNGLGETERRORPROC, GLenum);


    LOAD1(Clear, PFNGLCLEARPROC, void, GLbitfield, mask);
    LOAD4(ClearColor, PFNGLCLEARCOLORPROC, void, GLfloat, red, GLfloat, green, GLfloat, blue, GLfloat, alpha);
    LOAD1(GetString, PFNGLGETSTRINGPROC, const GLubyte*, GLenum, name)
    LOAD2(GenVertexArrays, PFNGLGENVERTEXARRAYSPROC, void, GLsizei, n, GLuint*, arrays)
    LOAD1(BindVertexArray, PFNGLBINDVERTEXARRAYPROC, void, GLuint, array);
    LOAD2(GenBuffers, PFNGLGENBUFFERSPROC, void, GLsizei, n, GLuint*, buffers)
    LOAD2(BindBuffer, PFNGLBINDBUFFERPROC, void, GLenum, target, GLuint, buffer)
    LOAD4(BufferData, PFNGLBUFFERDATAPROC, void, GLenum, target, GLsizeiptr, size, const void*, data, GLenum, usage)
    LOAD1(EnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC, void, GLuint, index)
    LOAD6(VertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC, void, GLuint, index, GLint, size, GLenum, type, GLboolean, normalized, GLsizei, stride, const void*, pointer)
    LOAD3(DrawArrays, PFNGLDRAWARRAYSPROC, void, GLenum, mode, GLint, first, GLsizei, count)
    LOAD1(DisableVertexAttribArray, PFNGLDISABLEVERTEXATTRIBARRAYPROC, void, GLuint, index)
    LOAD1(CreateShader, PFNGLCREATESHADERPROC, GLuint, GLenum, type)
    LOAD4(ShaderSource, PFNGLSHADERSOURCEPROC, void, GLuint, shader, GLsizei, count, const GLchar* const*, string, const GLint*, length)
    LOAD1(CompileShader, PFNGLCOMPILESHADERPROC, void, GLuint, shader)
    LOAD0(CreateProgram, PFNGLCREATEPROGRAMPROC, GLuint)
    LOAD2(AttachShader, PFNGLATTACHSHADERPROC, void, GLuint, program, GLuint, shader)
    LOAD1(LinkProgram, PFNGLLINKPROGRAMPROC, void, GLuint, program)
    LOAD2(DetachShader, PFNGLDETACHSHADERPROC, void, GLuint, program, GLuint, shader)
    LOAD1(DeleteShader, PFNGLDELETESHADERPROC, void, GLuint, shader)
    LOAD1(UseProgram, PFNGLUSEPROGRAMPROC, void, GLuint, program)
    LOAD1(DeleteProgram, PFNGLDELETEPROGRAMPROC, void, GLuint, program)
    LOAD3(GetShaderiv, PFNGLGETSHADERIVPROC, void, GLuint, shader, GLenum, pname, GLint*, params)
    LOAD4(GetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC, void, GLuint, shader, GLsizei, bufSize, GLsizei*, length, GLchar*, infoLog)
    LOAD3(GetProgramiv, PFNGLGETPROGRAMIVPROC, void, GLuint, program, GLenum, pname, GLint*, params)    
    LOAD4(GetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC, void, GLuint, program, GLsizei, bufSize, GLsizei*, length, GLchar*, infoLog)
    LOAD4(DrawElements, PFNGLDRAWELEMENTSPROC, void, GLenum, mode, GLsizei, count, GLenum, type, const void*, indices)
    LOAD2(GetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC, GLint, GLuint, program, const GLchar*, name)
    LOAD4(UniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC, void, GLint, location, GLsizei, count, GLboolean, transpose, const GLfloat*, value)
    LOAD4(UniformMatrix3fv, PFNGLUNIFORMMATRIX3FVPROC, void, GLint, location, GLsizei, count, GLboolean, transpose, const GLfloat*, value)
    LOAD3(CreateTextures, PFNGLCREATETEXTURESPROC, void, GLenum, target, GLsizei, n, GLuint*, textures)
    LOAD5(TextureStorage2D, PFNGLTEXTURESTORAGE2DPROC, void, GLuint, texture, GLsizei, levels, GLenum, internalformat, GLsizei, width, GLsizei, height)
    LOAD3(TextureParameteri, PFNGLTEXTUREPARAMETERIPROC, void, GLuint, texture, GLenum, pname, GLint, param)
    LOAD9(TextureSubImage2D, PFNGLTEXTURESUBIMAGE2DPROC, void, GLuint, texture, GLint, level, GLint, xoffset, GLint, yoffset, GLsizei, width, GLsizei, height, GLenum, format, GLenum, type, const void*, pixels)
    LOAD2(BindTextureUnit, PFNGLBINDTEXTUREUNITPROC, void, GLuint, unit, GLuint, texture)
    LOAD2(Uniform1i, PFNGLUNIFORM1IPROC, void, GLint, location, GLint, v0)
    LOAD1(Enable, PFNGLENABLEPROC, void, GLenum, cap)
    LOAD2(BlendFunc, PFNGLBLENDFUNCPROC, void, GLenum, sfactor, GLenum, dfactor)
    LOAD4(Viewport, PFNGLVIEWPORTPROC, void, GLint, x, GLint, y, GLsizei, width, GLsizei, height)
    LOAD3(Uniform2f, PFNGLUNIFORM2FPROC, void, GLint, location, GLfloat, v0, GLfloat, v1)
    LOAD4(Uniform3f, PFNGLUNIFORM3FPROC, void, GLint, location, GLfloat, v0, GLfloat, v1, GLfloat, v2)
    LOAD5(Uniform4f, PFNGLUNIFORM4FPROC, void, GLint, location, GLfloat, v0, GLfloat, v1, GLfloat, v2, GLfloat, v3)
    LOAD2(BindTexture, PFNGLBINDTEXTUREPROC, void, GLenum, target, GLuint, texture)
    LOAD4(BufferSubData, PFNGLBUFFERSUBDATAPROC, void, GLenum, target, GLintptr, offset, GLsizeiptr, size, const void*, data)
    LOAD3(Uniform1iv, PFNGLUNIFORM1IVPROC, void, GLint, location, GLsizei, count, const GLint*, value)
    LOAD2(Uniform1f, PFNGLUNIFORM1FPROC, void, GLint, location, GLfloat, v0)
    LOAD2(GetIntegerv, PFNGLGETINTEGERVPROC, void, GLenum, pname, GLint*, data)
    LOAD1(ActiveTexture, PFNGLACTIVETEXTUREPROC, void, GLenum, texture)
    LOAD1(IsEnabled, PFNGLISENABLEDPROC, GLboolean, GLenum, cap)
    LOAD1(BlendEquation, PFNGLBLENDEQUATIONPROC, void, GLenum, mode)
    LOAD1(Disable, PFNGLDISABLEPROC, void, GLenum, cap)
    LOAD4(Scissor, PFNGLSCISSORPROC, void, GLint, x, GLint, y, GLsizei, width, GLsizei, height)
    LOAD2(DeleteVertexArrays, PFNGLDELETEVERTEXARRAYSPROC, void, GLsizei, n, const GLuint*, arrays)
    LOAD2(BlendEquationSeparate, PFNGLBLENDEQUATIONSEPARATEPROC, void, GLenum, modeRGB, GLenum, modeAlpha)
    LOAD4(BlendFuncSeparate, PFNGLBLENDFUNCSEPARATEPROC, void, GLenum, sfactorRGB, GLenum, dfactorRGB, GLenum, sfactorAlpha, GLenum, dfactorAlpha)
    LOAD2(GenTextures, PFNGLGENTEXTURESPROC, void, GLsizei, n, GLuint*, textures)
    LOAD3(TexParameteri, PFNGLTEXPARAMETERIPROC, void, GLenum, target, GLenum, pname, GLint, param)
    LOAD2(PixelStorei, PFNGLPIXELSTOREIPROC, void, GLenum, pname, GLint, param)
    LOAD9(TexImage2D, PFNGLTEXIMAGE2DPROC, void, GLenum, target, GLint, level, GLint, internalformat, GLsizei, width, GLsizei, height, GLint, border, GLenum, format, GLenum, type, const void*, pixels)
    LOAD2(DeleteTextures, PFNGLDELETETEXTURESPROC, void, GLsizei, n, const GLuint*, textures)
    LOAD2(GetAttribLocation, PFNGLGETATTRIBLOCATIONPROC, GLint, GLuint, program, const GLchar*, name)
    LOAD2(DeleteBuffers, PFNGLDELETEBUFFERSPROC, void, GLsizei, n, const GLuint*, buffers)
    LOAD2(DebugMessageCallback, PFNGLDEBUGMESSAGECALLBACKPROC, void, GLDEBUGPROC, callback, const void*, userParam)
    LOAD6(DebugMessageControl, PFNGLDEBUGMESSAGECONTROLPROC, void, GLenum, source, GLenum, type, GLenum, severity, GLsizei, count, const GLuint*, ids, GLboolean, enabled);
    LOAD3(DispatchCompute, PFNGLDISPATCHCOMPUTEPROC, void, GLuint, num_groups_x, GLuint, num_groups_y, GLuint, num_groups_z)
}

int gladLoadGLLoader(GLADloadproc load) {
	load_GL(load);
    
	return 0;
}



/*#include "Propch.h"
#include "gl.h"


namespace Pro
{
    void glLoadFunctions(loadproc load) 
    {    
        gl_GetString = (PFNGLGETSTRINGPROC)load("glGetString");
        gl_ClearColor = (PFNGLCLEARCOLORPROC)load("glClearColor");
        gl_Clear = (PFNGLCLEARPROC)load("glClear");
    }
}

*/