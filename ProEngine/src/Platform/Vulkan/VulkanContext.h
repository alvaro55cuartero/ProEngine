#pragma once

#include "ProEngine/Renderer/GraphicsContext.h"
#include "Platform/Windows/WindowsWindow.h"
#include "vulkan/vulkan.h"
#include <map>

namespace Pro {

	class VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(WindowsWindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;

		void Destroy();

		void CreateInstance();
		void SetupDebugMessenger();
		void PickPhysicalDevice();
		void CreateLogicalDevice();

	private:
		WindowsWindow* m_window;
		VkInstance instance;
		VkDebugUtilsMessengerEXT debugMessenger;
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device;
	};


}