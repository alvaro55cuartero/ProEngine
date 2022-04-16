#pragma once
#include "ProEngine/Renderer/Shader.h"
#include "ProEngine/Math/Math.h"

#include "Platform/OpenGL/gl.h"

typedef unsigned int GLenum;

namespace Pro 
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, const int& value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		
		virtual void SetFloat(const std::string& name, const float& value) override;

		virtual void SetVec2(const std::string& name, const Vec2& value) override;
		virtual void SetVec3(const std::string& name, const Vec3& value) override;
		virtual void SetVec4(const std::string& name, const Vec4& value) override;

		virtual void SetMat3(const std::string& name, const Mat3& value) override;
		virtual void SetMat4(const std::string& name, const Mat4& value) override;

		virtual const std::string& GetName() const override { return m_name; }
		virtual const uint32_t& GetNativeID() const override { return m_programID; };

	
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		GLuint CreateShader(const GLuint type, const std::string& source);
	
	private:
		std::string m_name;
		uint32_t m_programID;
	};
}

