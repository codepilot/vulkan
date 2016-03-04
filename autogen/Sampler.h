#pragma once




namespace vulkan_autogen {
	class Sampler : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkSampler vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateSampler vkCreateSampler;
		PFN_vkDestroySampler vkDestroySampler;
		Sampler(const FunctionCallbackInfo<Value>& args);
		~Sampler();
	};
}


