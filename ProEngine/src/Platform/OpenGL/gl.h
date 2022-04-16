#pragma once



#ifndef __khrplatform_h_
#define __khrplatform_h_



#if defined(KHRONOS_STATIC)

#elif defined(_WIN32)
#   define KHRONOS_APICALL __declspec(dllimport)
#elif defined (__SYMBIAN32__)
#elif defined(__ANDROID__)
#else
#endif


#if defined(_WIN32) && !defined(_WIN32_WCE) && !defined(__SCITECH_SNAP__)

#   define KHRONOS_APIENTRY __stdcall
#else
#endif


#if defined (__ARMCC_2__)
#else
#define KHRONOS_APIATTRIBUTES
#endif


#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__) || defined(__SCO__) || defined(__USLC__)
#elif defined(__VMS ) || defined(__sgi)
#elif defined(_WIN32) && !defined(__SCITECH_SNAP__)

typedef __int32                 khronos_int32_t;
typedef unsigned __int32        khronos_uint32_t;
typedef __int64                 khronos_int64_t;
typedef unsigned __int64        khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1




#endif

typedef signed      char            khronos_int8_t;
typedef unsigned    char            khronos_uint8_t;
typedef signed      short int       khronos_int16_t;
typedef unsigned    short int       khronos_uint16_t;
typedef signed      long long int   khronos_intptr_t;
typedef unsigned    long long int   khronos_uintptr_t;
typedef signed      long long int   khronos_ssize_t;
typedef unsigned    long long int   khronos_usize_t;
typedef             float           khronos_float_t;




/*
 * Dummy value used to pad enum types to 32 bits.
 */
#ifndef KHRONOS_MAX_ENUM
#define KHRONOS_MAX_ENUM 0x7FFFFFFF
#endif



#endif 

#ifndef __glad_h_
#define __glad_h_

#ifdef __gl_h_
#error OpenGL header already included, remove this include, glad already provides it
#endif
#define __gl_h_

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#ifndef GLAPIENTRY
#define GLAPIENTRY APIENTRY
#endif

#ifdef __cplusplus
extern "C" {
#endif


typedef void* (* GLADloadproc)(const char *name);


#define GLAPI extern


GLAPI struct gladGLversionStruct GLVersion;

GLAPI int gladLoadGL(void);

GLAPI int gladLoadGLLoader(GLADloadproc);

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef khronos_int8_t GLbyte;
typedef khronos_uint8_t GLubyte;
typedef khronos_int16_t GLshort;
typedef khronos_uint16_t GLushort;
typedef int GLint;
typedef unsigned int GLuint;
typedef khronos_int32_t GLclampx;
typedef int GLsizei;
typedef khronos_float_t GLfloat;
typedef khronos_float_t GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void *GLeglClientBufferEXT;
typedef void *GLeglImageOES;
typedef char GLchar;
typedef char GLcharARB;
#ifdef __APPLE__
typedef void *GLhandleARB;
#else
typedef unsigned int GLhandleARB;
#endif
typedef khronos_uint16_t GLhalf;
typedef khronos_uint16_t GLhalfARB;
typedef khronos_int32_t GLfixed;
typedef khronos_intptr_t GLintptr;
typedef khronos_intptr_t GLintptrARB;
typedef khronos_ssize_t GLsizeiptr;
typedef khronos_ssize_t GLsizeiptrARB;
typedef khronos_int64_t GLint64;
typedef khronos_int64_t GLint64EXT;
typedef khronos_uint64_t GLuint64;
typedef khronos_uint64_t GLuint64EXT;









#define GL_FALSE 0
#define GL_TRUE 1
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_VERSION 0x1F02
#define GL_EXTENSIONS 0x1F03
#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_FLOAT 0x1406
#define GL_INT 0x1404
#define GL_BOOL 0x8B56
#define GL_TRIANGLES 0x0004
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_COMPILE_STATUS 0x8B81
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_LINK_STATUS 0x8B82
#define GL_UNSIGNED_INT 0x1405
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_TEXTURE_2D 0x0DE1
#define GL_RGB8 0x8051
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_NEAREST 0x2600
#define GL_LINEAR 0x2601
#define GL_RGB 0x1907
#define GL_UNSIGNED_BYTE 0x1401
#define GL_BLEND 0x0BE2
#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_RGBA8 0x8058
#define GL_RGBA 0x1908
#define GL_DEPTH_TEST 0x0B71
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_REPEAT 0x2901
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_ACTIVE_TEXTURE 0x84E0
#define GL_TEXTURE0 0x84C0
#define GL_CURRENT_PROGRAM 0x8B8D
#define GL_TEXTURE_BINDING_2D 0x8069
#define GL_ARRAY_BUFFER_BINDING 0x8894
#define GL_VERTEX_ARRAY_BINDING 0x85B5
#define GL_VIEWPORT 0x0BA2
#define GL_SCISSOR_BOX 0x0C10
#define GL_BLEND_DST_RGB 0x80C8
#define GL_BLEND_SRC_RGB 0x80C9
#define GL_BLEND_DST_ALPHA 0x80CA
#define GL_BLEND_SRC_ALPHA 0x80CB
#define GL_BLEND_EQUATION_RGB 0x8009
#define GL_BLEND_EQUATION_ALPHA 0x883D
#define GL_CULL_FACE 0x0B44
#define GL_SCISSOR_TEST 0x0C11
#define GL_FUNC_ADD 0x8006
#define GL_STREAM_DRAW 0x88E0
#define GL_UNSIGNED_SHORT 0x1403
#define GL_UNPACK_ROW_LENGTH 0x0CF2
#define GL_DEBUG_OUTPUT 0x92E0
#define GL_DEBUG_OUTPUT_SYNCHRONOUS 0x8242
#define GL_DONT_CARE 0x1100
#define GL_DEBUG_SEVERITY_NOTIFICATION 0x826B
#define GL_COMPUTE_SHADER 0x91B9






#define LOGI(file, line, x) std::cout << file << "("<< line << "): "<< x << "\n";
#define LOG(x) std::cout << x << "\n";

#define FUNC0(name, type, ret) \
typedef ret (*##type)(); \
GLAPI type gl_##name;

#define FUNC1(name, type, ret, arg1, name1) \
typedef ret (*##type)(##arg1 name1); \
GLAPI type gl_##name;

#define FUNC2(name, type, ret, arg1, name1, arg2, name2) \
typedef ret (*##type)(##arg1 name1, arg2 name2); \
GLAPI type gl_##name;

#define FUNC3(name, type, ret, arg1, name1, arg2, name2, arg3, name3) \
typedef ret (*##type)(##arg1 name1, arg2 name2, arg3 name3); \
GLAPI type gl_##name;

#define FUNC4(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4) \
typedef ret (*##type)(##arg1 name1, arg2 name2, arg3 name3, arg4 name4); \
GLAPI type gl_##name;

#define FUNC5(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4, arg5, name5) \
typedef ret (*##type)(##arg1 name1, arg2 name2, arg3 name3, arg4 name4, arg5 name5); \
GLAPI type gl_##name;

#define FUNC6(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4, arg5, name5, arg6, name6) \
typedef ret (*##type)(##arg1 name1, arg2 name2, arg3 name3, arg4 name4, arg5 name5, arg6 name6); \
GLAPI type gl_##name;

#define FUNC9(name, type, ret, arg1, name1, arg2, name2, arg3, name3, arg4, name4, arg5, name5, arg6, name6, arg7, name7, arg8, name8, arg9, name9) \
typedef ret (*##type)(##arg1 name1, arg2 name2, arg3 name3, arg4 name4, arg5 name5, arg6 name6, arg7 name7, arg8 name8, arg9 name9); \
GLAPI type gl_##name;


typedef void (* GLDEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);



FUNC1(Clear, PFNGLCLEARPROC, void, GLbitfield, mask)
#define glClear gl_Clear

FUNC4(ClearColor, PFNGLCLEARCOLORPROC, void, GLfloat, red, GLfloat, green, GLfloat, blue, GLfloat, alpha);
#define glClearColor gl_ClearColor

FUNC1(GetString, PFNGLGETSTRINGPROC, const GLubyte*, GLenum, name)
#define glGetString gl_GetString

FUNC2(GenVertexArrays, PFNGLGENVERTEXARRAYSPROC, void,  GLsizei, n, GLuint*, arrays)
#define glGenVertexArrays gl_GenVertexArrays

FUNC1(BindVertexArray, PFNGLBINDVERTEXARRAYPROC, void, GLuint, array)
#define glBindVertexArray gl_BindVertexArray

FUNC2(GenBuffers, PFNGLGENBUFFERSPROC, void, GLsizei, n, GLuint*, buffers)
#define glGenBuffers gl_GenBuffers

FUNC2(BindBuffer, PFNGLBINDBUFFERPROC, void, GLenum, target, GLuint, buffer)
#define glBindBuffer gl_BindBuffer

FUNC4(BufferData, PFNGLBUFFERDATAPROC, void, GLenum, target, GLsizeiptr, size, const void*, data, GLenum, usage)
#define glBufferData gl_BufferData

FUNC1(EnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC, void, GLuint, index)
#define glEnableVertexAttribArray gl_EnableVertexAttribArray

FUNC6(VertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC, void, GLuint, index, GLint, size, GLenum, type, GLboolean, normalized, GLsizei, stride, const void*, pointer)
#define glVertexAttribPointer gl_VertexAttribPointer

FUNC3(DrawArrays, PFNGLDRAWARRAYSPROC, void, GLenum, mode, GLint, first, GLsizei, count)
#define glDrawArrays gl_DrawArrays

FUNC1(DisableVertexAttribArray, PFNGLDISABLEVERTEXATTRIBARRAYPROC, void, GLuint, index)
#define glDisableVertexAttribArray gl_DisableVertexAttribArray

FUNC1(CreateShader, PFNGLCREATESHADERPROC, GLuint, GLenum, type)
#define glCreateShader gl_CreateShader

FUNC4(ShaderSource, PFNGLSHADERSOURCEPROC, void, GLuint, shader, GLsizei, count, const GLchar* const*, string, const GLint*, length)
#define glShaderSource gl_ShaderSource

FUNC1(CompileShader, PFNGLCOMPILESHADERPROC, void, GLuint, shader)
#define glCompileShader gl_CompileShader

FUNC0(CreateProgram, PFNGLCREATEPROGRAMPROC, GLuint)
#define glCreateProgram gl_CreateProgram

FUNC2(AttachShader, PFNGLATTACHSHADERPROC, void, GLuint, program, GLuint, shader)
#define glAttachShader gl_AttachShader

FUNC1(LinkProgram, PFNGLLINKPROGRAMPROC, void, GLuint, program)
#define glLinkProgram gl_LinkProgram

FUNC2(DetachShader, PFNGLDETACHSHADERPROC, void, GLuint, program, GLuint, shader)
#define glDetachShader gl_DetachShader

FUNC1(DeleteShader, PFNGLDELETESHADERPROC, void, GLuint, shader)
#define glDeleteShader gl_DeleteShader

FUNC1(UseProgram, PFNGLUSEPROGRAMPROC, void, GLuint, program)
#define glUseProgram gl_UseProgram

FUNC1(DeleteProgram, PFNGLDELETEPROGRAMPROC, void, GLuint, program)
#define glDeleteProgram gl_DeleteProgram

FUNC3(GetShaderiv, PFNGLGETSHADERIVPROC, void, GLuint, shader, GLenum, pname, GLint*, params)
#define glGetShaderiv gl_GetShaderiv

FUNC4(GetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC, void, GLuint, shader, GLsizei, bufSize, GLsizei*, length, GLchar*, infoLog)
#define glGetShaderInfoLog gl_GetShaderInfoLog

FUNC3(GetProgramiv, PFNGLGETPROGRAMIVPROC, void, GLuint, program, GLenum, pname, GLint*, params)
#define glGetProgramiv gl_GetProgramiv


FUNC4(GetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC, void, GLuint, program, GLsizei, bufSize, GLsizei*, length, GLchar*, infoLog)
#define glGetProgramInfoLog gl_GetProgramInfoLog

FUNC4(DrawElements, PFNGLDRAWELEMENTSPROC, void, GLenum, mode, GLsizei, count, GLenum, type, const void*, indices)
#define glDrawElements gl_DrawElements

FUNC2(GetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC, GLint, GLuint, program, const GLchar*, name)
#define glGetUniformLocation gl_GetUniformLocation

FUNC4(UniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC, void, GLint, location, GLsizei, count, GLboolean, transpose, const GLfloat*, value)
#define glUniformMatrix4fv gl_UniformMatrix4fv

FUNC4(UniformMatrix3fv, PFNGLUNIFORMMATRIX3FVPROC, void, GLint, location, GLsizei, count, GLboolean, transpose, const GLfloat*, value)
#define glUniformMatrix3fv gl_UniformMatrix3fv

FUNC3(CreateTextures, PFNGLCREATETEXTURESPROC, void, GLenum, target, GLsizei, n, GLuint*, textures)
#define glCreateTextures gl_CreateTextures

FUNC5(TextureStorage2D, PFNGLTEXTURESTORAGE2DPROC, void, GLuint, texture, GLsizei, levels, GLenum, internalformat, GLsizei, width, GLsizei, height)
#define glTextureStorage2D gl_TextureStorage2D

FUNC3(TextureParameteri, PFNGLTEXTUREPARAMETERIPROC, void, GLuint, texture, GLenum, pname, GLint, param)
#define glTextureParameteri gl_TextureParameteri

FUNC9(TextureSubImage2D, PFNGLTEXTURESUBIMAGE2DPROC, void, GLuint, texture, GLint, level, GLint, xoffset, GLint, yoffset, GLsizei, width, GLsizei, height, GLenum, format, GLenum, type, const void*, pixels)
#define glTextureSubImage2D gl_TextureSubImage2D

FUNC2(BindTextureUnit, PFNGLBINDTEXTUREUNITPROC, void, GLuint, unit, GLuint, texture)
#define glBindTextureUnit gl_BindTextureUnit

FUNC2(Uniform1i, PFNGLUNIFORM1IPROC, void, GLint, location, GLint, v0)
#define glUniform1i gl_Uniform1i

FUNC1(Enable, PFNGLENABLEPROC, void, GLenum, cap)
#define glEnable gl_Enable

FUNC2(BlendFunc, PFNGLBLENDFUNCPROC, void, GLenum, sfactor, GLenum, dfactor)
#define glBlendFunc gl_BlendFunc

FUNC4(Viewport, PFNGLVIEWPORTPROC, void, GLint, x, GLint, y, GLsizei, width, GLsizei, height)
#define glViewport gl_Viewport

FUNC3(Uniform2f, PFNGLUNIFORM2FPROC, void, GLint, location, GLfloat, v0, GLfloat, v1)
#define glUniform2f gl_Uniform2f

FUNC4(Uniform3f, PFNGLUNIFORM3FPROC, void, GLint, location, GLfloat, v0, GLfloat, v1, GLfloat, v2)
#define glUniform3f gl_Uniform3f

FUNC5(Uniform4f, PFNGLUNIFORM4FPROC, void, GLint, location, GLfloat, v0, GLfloat, v1, GLfloat, v2, GLfloat, v3)
#define glUniform4f gl_Uniform4f

FUNC2(BindTexture, PFNGLBINDTEXTUREPROC, void, GLenum, target, GLuint, texture)
#define glBindTexture gl_BindTexture

FUNC4(BufferSubData, PFNGLBUFFERSUBDATAPROC, void, GLenum, target, GLintptr, offset, GLsizeiptr, size, const void*, data)
#define glBufferSubData gl_BufferSubData

FUNC3(Uniform1iv, PFNGLUNIFORM1IVPROC, void, GLint, location, GLsizei, count, const GLint*, value)
#define glUniform1iv gl_Uniform1iv

FUNC2(Uniform1f, PFNGLUNIFORM1FPROC, void, GLint, location, GLfloat, v0)
#define glUniform1f gl_Uniform1f

FUNC2(GetIntegerv, PFNGLGETINTEGERVPROC, void, GLenum, pname, GLint*, data)
#define glGetIntegerv gl_GetIntegerv

FUNC1(ActiveTexture, PFNGLACTIVETEXTUREPROC, void, GLenum, texture)
#define glActiveTexture gl_ActiveTexture

FUNC1(IsEnabled, PFNGLISENABLEDPROC, GLboolean, GLenum, cap)
#define glIsEnabled gl_IsEnabled

FUNC1(BlendEquation, PFNGLBLENDEQUATIONPROC, void, GLenum, mode)
#define glBlendEquation gl_BlendEquation

FUNC1(Disable, PFNGLDISABLEPROC, void, GLenum, cap)
#define glDisable gl_Disable

FUNC4(Scissor, PFNGLSCISSORPROC, void, GLint, x, GLint, y, GLsizei, width, GLsizei, height)
#define glScissor gl_Scissor

FUNC2(DeleteVertexArrays, PFNGLDELETEVERTEXARRAYSPROC, void, GLsizei, n, const GLuint*, arrays)
#define glDeleteVertexArrays gl_DeleteVertexArrays

FUNC2(BlendEquationSeparate, PFNGLBLENDEQUATIONSEPARATEPROC, void, GLenum, modeRGB, GLenum, modeAlpha)
#define glBlendEquationSeparate gl_BlendEquationSeparate

FUNC4(BlendFuncSeparate, PFNGLBLENDFUNCSEPARATEPROC, void, GLenum, sfactorRGB, GLenum, dfactorRGB, GLenum, sfactorAlpha, GLenum, dfactorAlpha)
#define glBlendFuncSeparate gl_BlendFuncSeparate

FUNC2(GenTextures, PFNGLGENTEXTURESPROC, void, GLsizei, n, GLuint*, textures)
#define glGenTextures gl_GenTextures

FUNC3(TexParameteri, PFNGLTEXPARAMETERIPROC, void, GLenum, target, GLenum, pname, GLint, param)
#define glTexParameteri gl_TexParameteri

FUNC2(PixelStorei, PFNGLPIXELSTOREIPROC, void, GLenum, pname, GLint, param)
#define glPixelStorei gl_PixelStorei

FUNC9(TexImage2D, PFNGLTEXIMAGE2DPROC, void, GLenum, target, GLint, level, GLint, internalformat, GLsizei, width, GLsizei, height, GLint, border, GLenum, format, GLenum, type, const void*, pixels)
#define glTexImage2D gl_TexImage2D

FUNC2(DeleteTextures, PFNGLDELETETEXTURESPROC, void, GLsizei, n, const GLuint*, textures)
#define glDeleteTextures gl_DeleteTextures

FUNC2(GetAttribLocation, PFNGLGETATTRIBLOCATIONPROC, GLint, GLuint, program, const GLchar*, name)
#define glGetAttribLocation gl_GetAttribLocation

FUNC2(DeleteBuffers, PFNGLDELETEBUFFERSPROC, void, GLsizei, n, const GLuint*, buffers)
#define glDeleteBuffers gl_DeleteBuffers

FUNC0(GetError, PFNGLGETERRORPROC, GLenum)
#define glGetError gl_GetError

FUNC2(DebugMessageCallback, PFNGLDEBUGMESSAGECALLBACKPROC, void, GLDEBUGPROC, callback, const void*, userParam);
#define glDebugMessageCallback gl_DebugMessageCallback

FUNC6(DebugMessageControl, PFNGLDEBUGMESSAGECONTROLPROC, void, GLenum, source, GLenum, type, GLenum, severity, GLsizei, count, const GLuint*, ids, GLboolean, enabled);
#define glDebugMessageControl gl_DebugMessageControl

FUNC3(DispatchCompute, PFNGLDISPATCHCOMPUTEPROC, void, GLuint, num_groups_x, GLuint, num_groups_y, GLuint, num_groups_z)
#define glDispatchCompute gl_DispatchCompute




#ifdef __cplusplus
}
#endif

#endif
