#pragma once




namespace vulkan_autogen {
	class GraphicsPipeline : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkPipeline vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateGraphicsPipelines vkCreateGraphicsPipelines;
		PFN_vkDestroyPipeline vkDestroyPipeline;
		GraphicsPipeline(const FunctionCallbackInfo<Value>& args);
		~GraphicsPipeline();
	};
}


