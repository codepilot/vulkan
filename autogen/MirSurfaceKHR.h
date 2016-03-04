#pragma once

#ifdef VK_USE_PLATFORM_MIR_KHR


namespace vulkan_autogen {
	class MirSurfaceKHR : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkSurfaceKHR vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_instance;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateMirSurfaceKHR vkCreateMirSurfaceKHR;
		PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
		MirSurfaceKHR(const FunctionCallbackInfo<Value>& args);
		~MirSurfaceKHR();
	};
}

#endif // VK_USE_PLATFORM_MIR_KHR
