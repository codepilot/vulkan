#pragma once




namespace vulkan_autogen {
	class DescriptorPool : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkDescriptorPool vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateDescriptorPool vkCreateDescriptorPool;
		PFN_vkDestroyDescriptorPool vkDestroyDescriptorPool;
		DescriptorPool(const FunctionCallbackInfo<Value>& args);
		~DescriptorPool();
	};
}


