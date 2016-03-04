#pragma once




namespace vulkan_autogen {
	class QueryPool : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkQueryPool vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateQueryPool vkCreateQueryPool;
		PFN_vkDestroyQueryPool vkDestroyQueryPool;
		QueryPool(const FunctionCallbackInfo<Value>& args);
		~QueryPool();
	};
}


