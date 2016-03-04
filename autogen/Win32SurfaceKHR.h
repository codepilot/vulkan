#pragma once

#ifdef VK_USE_PLATFORM_WIN32_KHR


namespace vulkan_autogen {
	class Win32SurfaceKHR : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkSurfaceKHR vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_instance;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateWin32SurfaceKHR vkCreateWin32SurfaceKHR;
		PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
		Win32SurfaceKHR(const FunctionCallbackInfo<Value>& args);
		~Win32SurfaceKHR();
	};
}

#endif // VK_USE_PLATFORM_WIN32_KHR
