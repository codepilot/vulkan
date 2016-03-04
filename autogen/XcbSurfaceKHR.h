#pragma once

#ifdef VK_USE_PLATFORM_XCB_KHR


namespace vulkan_autogen {
	class XcbSurfaceKHR : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkSurfaceKHR vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_instance;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateXcbSurfaceKHR vkCreateXcbSurfaceKHR;
		PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
		XcbSurfaceKHR(const FunctionCallbackInfo<Value>& args);
		~XcbSurfaceKHR();
	};
}

#endif // VK_USE_PLATFORM_XCB_KHR
