#pragma once

namespace vulkan_level_20 {

	class PhysicalDevice: public node::ObjectWrap {
	public:
		static void Init(Isolate* isolate);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PhysicalDevice(const FunctionCallbackInfo<Value>& args);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void getQueueFamilyProperties(const FunctionCallbackInfo<Value>& args);
		static Persistent<Function> constructor;
		VkPhysicalDevice physicalDevice{ nullptr };
		Persistent<Object> instance;
		static void getMemoryProperties(const FunctionCallbackInfo<Value>& args);
		static void getWin32PresentationSupportKHR(const FunctionCallbackInfo<Value>& args);
	};

	class Instance: public node::ObjectWrap {
	public:
		static void Init(Isolate* isolate);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		Instance(const FunctionCallbackInfo<Value>& args);
		~Instance();
		static void New(const FunctionCallbackInfo<Value>& args);

		template<typename T> T Instance::getProcAddr(T &pProc, const char* pName);

		static void enumeratePhysicalDevices(const FunctionCallbackInfo<Value>& args);
		static Persistent<Function> constructor;
		VkInstance instance{ nullptr };
		/*
		//VK_KHR_surface
		VKAPI_ATTR void VKAPI_CALL vkDestroySurfaceKHR(
			VkInstance                                  instance,
			VkSurfaceKHR                                surface,
			const VkAllocationCallbacks*                pAllocator);

		VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceSupportKHR(
			VkPhysicalDevice                            physicalDevice,
			uint32_t                                    queueFamilyIndex,
			VkSurfaceKHR                                surface,
			VkBool32*                                   pSupported);

		VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
			VkPhysicalDevice                            physicalDevice,
			VkSurfaceKHR                                surface,
			VkSurfaceCapabilitiesKHR*                   pSurfaceCapabilities);

		VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceFormatsKHR(
			VkPhysicalDevice                            physicalDevice,
			VkSurfaceKHR                                surface,
			uint32_t*                                   pSurfaceFormatCount,
			VkSurfaceFormatKHR*                         pSurfaceFormats);

		VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModesKHR(
			VkPhysicalDevice                            physicalDevice,
			VkSurfaceKHR                                surface,
			uint32_t*                                   pPresentModeCount,
			VkPresentModeKHR*                           pPresentModes);

		//VK_KHR_win32_surface
		VKAPI_ATTR VkResult VKAPI_CALL vkCreateWin32SurfaceKHR(
			VkInstance                                  instance,
			const VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
			const VkAllocationCallbacks*                pAllocator,
			VkSurfaceKHR*                               pSurface);

		VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(
			VkPhysicalDevice                            physicalDevice,
			uint32_t                                    queueFamilyIndex);

		//VK_EXT_debug_report
		VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT(
			VkInstance                                  instance,
			const VkDebugReportCallbackCreateInfoEXT*   pCreateInfo,
			const VkAllocationCallbacks*                pAllocator,
			VkDebugReportCallbackEXT*                   pCallback);

		VKAPI_ATTR void VKAPI_CALL vkDestroyDebugReportCallbackEXT(
			VkInstance                                  instance,
			VkDebugReportCallbackEXT                    callback,
			const VkAllocationCallbacks*                pAllocator);

		VKAPI_ATTR void VKAPI_CALL vkDebugReportMessageEXT(
			VkInstance                                  instance,
			VkDebugReportFlagsEXT                       flags,
			VkDebugReportObjectTypeEXT                  objectType,
			uint64_t                                    object,
			size_t                                      location,
			int32_t                                     messageCode,
			const char*                                 pLayerPrefix,
			const char*                                 pMessage);
			*/
		PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR{ nullptr };
		PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR{ nullptr };

		PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT{ nullptr };
		PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT{ nullptr };
		PFN_vkDebugReportMessageEXT vkDebugReportMessageEXT{ nullptr };

		PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
		PFN_vkGetPhysicalDeviceSurfaceSupportKHR vkGetPhysicalDeviceSurfaceSupportKHR;
		PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR;
		PFN_vkGetPhysicalDeviceSurfaceFormatsKHR vkGetPhysicalDeviceSurfaceFormatsKHR;
		PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR;
		static VkBool32 cb_vkDebugReportCallbackEXT(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData);
	};

	void Init(Local<Object> exports);
}

