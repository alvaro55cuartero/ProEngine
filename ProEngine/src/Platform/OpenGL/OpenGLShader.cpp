#include "Propch.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/gl.h"
#include <fstream>

namespace Pro
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		if (type == "compute")
			return GL_COMPUTE_SHADER;

		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		PRO_PROFILE_FUNCTION();

		std::string source = ReadFile(filepath);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_name = filepath.substr(lastSlash, count);
	}


	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		:m_name(name)
	{
		PRO_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}
	
	OpenGLShader::~OpenGLShader()
	{
		PRO_PROFILE_FUNCTION();

		glDeleteProgram(m_programID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		PRO_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
			else
			{
				std::cout << "Could not read from file " << filepath << "\n";
			}
		}
		else
		{
			std::cout << "Could not open file " << filepath << "\n";
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		PRO_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
			pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}


	void OpenGLShader::Bind() const 
	{
		PRO_PROFILE_FUNCTION();

		glUseProgram(m_programID);
	}

	void OpenGLShader::Unbind() const 
	{
		PRO_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		PRO_PROFILE_FUNCTION();

		m_programID = glCreateProgram();

		std::vector<GLenum> glShaderIDs;
		int glShaderIDIndex = 0;

		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;
			GLuint shaderID = CreateShader(type, source);
			glAttachShader(m_programID, shaderID);
			glShaderIDs.push_back(shaderID);
		}

		glLinkProgram(m_programID);

		GLint isLinked = 0;
		glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_programID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_programID);

			for (auto id : glShaderIDs)
				glDeleteShader(id);

			std::cout << infoLog.data();

			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader(m_programID, id);
			glDeleteShader(id);
		}
	}

	void OpenGLShader::SetInt(const std::string& name, const int& value)
	{
		PRO_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		PRO_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::SetFloat(const std::string& name, const float& value)
	{
		PRO_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::SetVec2(const std::string& name, const Vec2& value)
	{
		PRO_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}
	
	void OpenGLShader::SetVec3(const std::string& name, const Vec3& value)
	{
		PRO_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetVec4(const std::string& name, const Vec4& value)
	{
		PRO_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetMat3(const std::string& name, const Mat3& value)
	{
		PRO_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, &(value[0].x));
	}

	void OpenGLShader::SetMat4(const std::string& name, const Mat4& value)
	{
		PRO_PROFILE_FUNCTION();

		GLint location = glGetUniformLocation(m_programID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, &(value[0].x));
	}

	GLuint OpenGLShader::CreateShader(const GLuint type, const std::string& source) {
		PRO_PROFILE_FUNCTION();

		const char* shaderSrc = source.c_str();

		GLuint shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &shaderSrc, NULL);

		{
			PRO_PROFILE_SCOPE("Compile Shader");
			
			glCompileShader(shaderID);
		}

		{
			PRO_PROFILE_SCOPE("Fetch Shader Compilation Status");

			GLint isCompiled = 0;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);


				std::cout << infoLog.data();

				glDeleteShader(shaderID);
				return NULL;
			}
		}
		return shaderID;
	}
}