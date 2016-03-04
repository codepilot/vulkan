#pragma once




namespace vulkan_autogen {
	class DescriptorSetLayout : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkDescriptorSetLayout vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateDescriptorSetLayout vkCreateDescriptorSetLayout;
		PFN_vkDestroyDescriptorSetLayout vkDestroyDescriptorSetLayout;
		DescriptorSetLayout(const FunctionCallbackInfo<Value>& args);
		~DescriptorSetLayout();
	};
}


