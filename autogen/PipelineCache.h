#pragma once




namespace vulkan_autogen {
	class PipelineCache : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkPipelineCache vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreatePipelineCache vkCreatePipelineCache;
		PFN_vkDestroyPipelineCache vkDestroyPipelineCache;
		PipelineCache(const FunctionCallbackInfo<Value>& args);
		~PipelineCache();
	};
}


