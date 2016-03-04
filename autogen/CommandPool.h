#pragma once




namespace vulkan_autogen {
	class CommandPool : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkCommandPool vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateCommandPool vkCreateCommandPool;
		PFN_vkDestroyCommandPool vkDestroyCommandPool;
		CommandPool(const FunctionCallbackInfo<Value>& args);
		~CommandPool();
	};
}


