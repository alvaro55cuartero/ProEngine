#pragma once
#include "ProEngine/Math/Mat4.h"
#include "ProEngine/Scene/SceneCamera.h"
#include "ProEngine/Math/Quaternion.h"
#include "ProEngine/ECS/ScriptableEntity.h"
#include "ProEngine/Core/Timestep.h"
#include "ProEngine/Renderer/Sprite/Sprite.h"
#include "ProEngine/Physics/AABB.h"
#include "ProEngine/Renderer/Cameras/PixelPerfectCamera.h"

#include "../vendor/box2d/include/box2d/box2d.h"
#include "../vendor/json/single_include/nlohmann/json.hpp"

namespace Pro
{
	class Component {
	};

	class TagComponent : public Component
	{
	public:
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string & tag)
			: Tag(tag) {}

		nlohmann::json Serialize()
		{
			return Tag;
		}


		void Deserialize(nlohmann::json json)
		{
			Tag = json.get<std::string>();
		}

	};

	class TransformComponent : public Component
	{
	public:
		Vec3 Translation = { 0.0f, 0.0f, 0.0f };
		Vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		Vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Vec3& translation)
			: Translation(translation) {}

		Mat4 GetTransform() const
		{
			Mat4 rotation = Quaternion(Rotation).ToMat4();
			Mat4 translation = Math::translate(Mat4(1.0f), Translation);
			Mat4 scale = Math::scale(Mat4(1.0f), Scale);

			return translation * rotation * scale;
		}

		nlohmann::json Serialize()
		{
			return nlohmann::json({
				{"Position", {
					{"x", Translation.x},
					{"y", Translation.y},
					{"z", Translation.z}
				}},
				{"Rotation", {
					{"x", Rotation.x},
					{"y", Rotation.y},
					{"z", Rotation.z}
				}},
				{"Scale", {
					{"x", Scale.x},
					{"y", Scale.y},
					{"z", Scale.z}
				}}
			});
		}

		void Deserialize(nlohmann::json json)
		{
			Translation = { json["Position"]["x"].get<float>(),		json["Position"]["y"].get<float>(),		json["Position"]["z"].get<float>() };
			Rotation = { json["Rotation"]["x"].get<float>(),		json["Rotation"]["y"].get<float>(),		json["Rotation"]["z"].get<float>() };
			Scale = { json["Scale"]["x"].get<float>(),				json["Scale"]["y"].get<float>(),		json["Scale"]["z"].get<float>() };

		}
	};

	class SpriteComponent : public Component
	{
	public:
		SpriteComponent() = default;

		SpriteComponent(const Vec4& color, std::string spriteSheet, std::string sprite)
			: Color(color), SpriteSheet(spriteSheet), Sprite(sprite)
		{}

		nlohmann::json Serialize()
		{
			return { 
				{
					"Color",{
						{"x", Color.x},
						{"y", Color.y},
						{"z", Color.z},
						{"w", Color.w}
					}
				},
				{
					"Sprite", Sprite
				},
				{
					"SpriteSheet", SpriteSheet
				}
			};
		}

		void Deserialize(nlohmann::json json)
		{
			Color.x = json["Color"]["x"].get<float>();
			Color.y = json["Color"]["y"].get<float>(); 
			Color.z = json["Color"]["z"].get<float>();
			Color.w = json["Color"]["w"].get<float>();
			
			Sprite = json["Sprite"].get<std::string>();
			SpriteSheet = json["SpriteSheet"].get<std::string>();
		}
		
	public:
		Vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		std::string Sprite;
		std::string SpriteSheet;

	};

	struct CameraComponent : public Component
	{
		Camera* Camera;
		bool Primary = true;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;

		nlohmann::json Serialize()
		{
			nlohmann::json json;
			json["Primary"] = Primary;
			json["CameraType"] = "PixelPerfect";

			return json;
		}

		void Deserialize(nlohmann::json json)
		{
 			Primary = json["Primary"];

			std::string type = json["CameraType"].get<std::string>();
			
			if (type == "Perspective")
			{

			}
			else if (type == "PixePerfect")
			{
				Camera = new Pro::PixelPerfectCamera(1280.0f, 720.0f);
			}



			//Camera.SetProjectionType(json["CameraType"] ==  "Perspective" ? SceneCamera::ProjectionType::Perspective : SceneCamera::ProjectionType::Orthographic);
			//Camera.SetViewportSize(1080, 720);

		}
	};

	struct NativeScriptComponent : public Component
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};

	struct MeshComponent : public Component
	{
		std::vector<float> vertices;
		std::vector<uint32_t> indices;

		MeshComponent() = default;

	};

	struct GUIComponent : public Component
	{

		bool visible = true;

		GUIComponent() = default;

	};

	struct BoxCollider2DComponent
	{
		bool isStatic = true;
		Physics::AABB AABB;
		Vec2 velocity;

		BoxCollider2DComponent() {};

		Physics::AABB GetAABB(Vec2 position, Vec2 scale)
		{
			return Physics::AABB(position, scale);
		}

		nlohmann::json Serialize()
		{
			nlohmann::json json;
			json["AABB"] = {};
			json["AABB"]["Position"]["X"] = AABB.Position.x;
			json["AABB"]["Position"]["Y"] = AABB.Position.y;
			json["AABB"]["Scale"]["X"] = AABB.Scale.x;
			json["AABB"]["Scale"]["Y"] = AABB.Scale.y;

			return json;
		}

		void Deserialize(nlohmann::json json)
		{
			Vec2 position = { json["AABB"]["Position"]["X"].get<float>(), json["AABB"]["Position"]["Y"].get<float>() };
			Vec2 scale = { json["AABB"]["Scale"]["X"].get<float>(), json["AABB"]["Scale"]["Y"].get<float>() };

			AABB = Physics::AABB(position, scale);
		}

	};

	struct TextComponent
	{
		TextComponent(std::string text, Pro::Vec4 color)
			: Text(text), Color(color)
		{};

		std::string Text;
		Pro::Vec4 Color;
	};

}