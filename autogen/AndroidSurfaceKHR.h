#pragma once

#ifdef VK_USE_PLATFORM_ANDROID_KHR


namespace vulkan_autogen {
	class AndroidSurfaceKHR : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkSurfaceKHR vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_instance;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR;
		PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
		AndroidSurfaceKHR(const FunctionCallbackInfo<Value>& args);
		~AndroidSurfaceKHR();
	};
}

#endif // VK_USE_PLATFORM_ANDROID_KHR
