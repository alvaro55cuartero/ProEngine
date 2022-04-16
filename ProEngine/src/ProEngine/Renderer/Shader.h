#pragma once
#include "ProEngine/Math/Math.h"
#include <unordered_map>
#include <string>


namespace Pro
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, const int& value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;

		virtual void SetFloat(const std::string& name, const float& value) = 0;

		virtual void SetVec2(const std::string& name, const Vec2& value) = 0;
		virtual void SetVec3(const std::string& name, const Vec3& value) = 0;
		virtual void SetVec4(const std::string& name, const Vec4& value) = 0;

		virtual void SetMat3(const std::string& name, const Mat3& value) = 0;
		virtual void SetMat4(const std::string& name, const Mat4& value) = 0;

		virtual const std::string& GetName() const = 0;

		virtual const uint32_t& GetNativeID() const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_shaders;
	};
}

