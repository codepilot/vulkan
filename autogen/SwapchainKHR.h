#pragma once




namespace vulkan_autogen {
	class SwapchainKHR : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkSwapchainKHR vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateSwapchainKHR vkCreateSwapchainKHR;
		PFN_vkDestroySwapchainKHR vkDestroySwapchainKHR;
		SwapchainKHR(const FunctionCallbackInfo<Value>& args);
		~SwapchainKHR();
	};
}


