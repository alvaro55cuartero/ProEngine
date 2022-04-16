#pragma once
#include "ProEngine.h"
#include <algorithm>

class PlayerController : public Pro::ScriptableEntity
{
public:
	virtual void OnCreate() override
	{
		auto& translation = GetComponent<Pro::TransformComponent>().Translation;
		translation.y = 500;
	}

	virtual void OnDestroy() override
	{
	}

	virtual void OnUpdate(Pro::Timestep delta) override
	{
		Pro::Registry* reg = GetRegistry();

		Pro::TransformComponent* cameraTransform = nullptr;
		Pro::CameraComponent* camera = nullptr;
		{
			auto view = reg->GetView<Pro::TransformComponent, Pro::CameraComponent>();
			for (auto entity: view)
			{
				camera = &reg->Get<Pro::CameraComponent>(entity);
				if (camera->Primary)
				{
					cameraTransform = &reg->Get<Pro::TransformComponent>(entity);
				}
			}
		}


		downCollision = false;
		int vel = 0;
		Pro::BoxCollider2DComponent playerCollider = GetComponent<Pro::BoxCollider2DComponent>();
		auto& translation = GetComponent<Pro::TransformComponent>().Translation;
		auto& scale = GetComponent<Pro::TransformComponent>().Scale;
		{
			auto view = reg->GetView<Pro::BoxCollider2DComponent, Pro::TagComponent>();

			for (auto entity : view)
			{
				auto tag = reg->Get<Pro::TagComponent>(entity);
				auto collider = reg->Get<Pro::BoxCollider2DComponent>(entity);

				if (tag.Tag == "Player") continue;

				velocity.y += -gravity * delta;



				
				if (Pro::Physics::TestYGrid(translation, velocity.y, collider.AABB) || Pro::Physics::TestYGrid(translation + Pro::Vec2(scale.x, 0), velocity.y, collider.AABB))
				{
					vel = translation.y - collider.AABB.Max.y + 1;

					downCollision = true;
				}
			}
		}

		if (downCollision)
		{
			isGrounded = true;
			velocity.y = velocity.y > 0 ? vel : -vel;
		}



		auto input = Pro::Application::Get().GetWindow().GetInput();

		if (isGrounded && !jumpRelease && input->IsKeyPressedImpl(Pro::Key::Space))
		{
			jumpRelease = true;
			velocity.y += jumpSpeed;
		}
		
		if (!input->IsKeyPressedImpl(Pro::Key::Space))
		{
			jumpRelease = false;
		}


		//if (isGrounded && jumpRelease)
		//{
		//	velocity.y += jumpSpeed;
		//	std::cout << "jump\n";
		//}

		
		if (input->IsKeyPressedImpl(Pro::Key::A))
			translation.x -= speed * delta;
		if (input->IsKeyPressedImpl(Pro::Key::D))
			translation.x += speed * delta;
			
		translation.y += velocity.y;
		
		if (translation.y != std::floor(translation.y))
		{
			translation.y = std::floor(translation.y);
		}

		if (translation.y < -1000)
		{
			translation.y = 700;
			velocity.y = 0;
		}

		camera->Camera->SetPosition(translation - Pro::Vec2(1280 / 2, 720 / 2));
	}


private:

	bool downCollision = false;

	Pro::Vec2 velocity = {};
	bool isGrounded = false;
	bool jumpRelease = false;

	float speed = 200.0f;
	float gravity = 40;
	float jumpSpeed = 12;

};

