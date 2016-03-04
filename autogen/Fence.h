#pragma once




namespace vulkan_autogen {
	class Fence : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkFence vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateFence vkCreateFence;
		PFN_vkDestroyFence vkDestroyFence;
		Fence(const FunctionCallbackInfo<Value>& args);
		~Fence();
	};
}


