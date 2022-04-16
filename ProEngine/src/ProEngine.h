#pragma once



#include "ProEngine/Core/Application.h"
#include "ProEngine/Core/Timestep.h"
#include "ProEngine/Core/KeyCodes.h"
#include "ProEngine/Core/Layer.h"
#include "ProEngine/Core/Base.h"


//Events

#include "ProEngine/Events/Event.h"
#include "ProEngine/Events/ApplicationEvent.h"
#include "ProEngine/Events/KeyEvents.h"
#include "ProEngine/Events/MouseEvent.h"

//Math

#include "ProEngine/Math/Math.h"
#include "ProEngine/Math/Transform.h"
#include "ProEngine/Math/Intersections.h"

// Renderer

#include "ProEngine/Renderer/Cameras/FlyingCameraController.h"
#include "ProEngine/Renderer/Cameras/OrthographicCameraController.h"
#include "ProEngine/Renderer/Cameras/PerspectiveCamera.h"
#include "ProEngine/Renderer/Cameras/OrthographicCamera.h"
#include "ProEngine/Renderer/Cameras/PixelPerfectCamera.h"

#include "ProEngine/Renderer/Sprite/SpriteLibrary.h"
#include "ProEngine/Renderer/Sprite/SpriteSheet.h"
#include "ProEngine/Renderer/Sprite/Sprite.h"

#include "ProEngine/Renderer/RenderCommand.h"
#include "ProEngine/Renderer/VertexBuffer.h"
#include "ProEngine/Renderer/VertexArray.h"
#include "ProEngine/Renderer/RendererGUI.h"
#include "ProEngine/Renderer/Renderer2D.h"
#include "ProEngine/Renderer/Renderer.h"
#include "ProEngine/Renderer/Texture.h"
#include "ProEngine/Renderer/Shader.h"
#include "ProEngine/Renderer/Mesh.h"

#include "ProEngine/Debug/Instrumentor.h"


//#include "ProEngine/ECS/ScriptableEntity.h"
//#include "ProEngine/ECS/Component.h"


// File Managing

#include "ProEngine/File/File.h"
#include "ProEngine/Font/Font.h"
#include "ProEngine/File/FBX/FBX.h"


// ECS
#include "ProEngine/ECS/Registry/Registry.h"
#include "ProEngine/ECS/Entity/Entity.h"
//#include "ProEngine/ECS/System.h"

#include "ProEngine/Scene/Scene.h"

// GUI


//Physics
#include "../vendor/box2d/include/box2d/box2d.h"
#include "ProEngine/Physics/Physics2D.h"
#include "ProEngine/Physics/AABB.h"
#include "ProEngine/Physics/Tests.h"


//Containers

#include "ProEngine/Containers/SparseSet.h"
#include "ProEngine/Containers/SparseMap.h"
#include "ProEngine/Containers/TypeStorage.h"

//Json

#include "../vendor/json/single_include/nlohmann/json.hpp"


//Hashing

#include "ProEngine/Hash/CRC/CRC32.h"