#pragma once

#ifdef VK_USE_PLATFORM_XLIB_KHR


namespace vulkan_autogen {
	class XlibSurfaceKHR : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkSurfaceKHR vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_instance;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateXlibSurfaceKHR vkCreateXlibSurfaceKHR;
		PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
		XlibSurfaceKHR(const FunctionCallbackInfo<Value>& args);
		~XlibSurfaceKHR();
	};
}

#endif // VK_USE_PLATFORM_XLIB_KHR
