#pragma once




namespace vulkan_autogen {
	class PipelineLayout : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkPipelineLayout vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreatePipelineLayout vkCreatePipelineLayout;
		PFN_vkDestroyPipelineLayout vkDestroyPipelineLayout;
		PipelineLayout(const FunctionCallbackInfo<Value>& args);
		~PipelineLayout();
	};
}


