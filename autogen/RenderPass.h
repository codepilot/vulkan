#pragma once




namespace vulkan_autogen {
	class RenderPass : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkRenderPass vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateRenderPass vkCreateRenderPass;
		PFN_vkDestroyRenderPass vkDestroyRenderPass;
		RenderPass(const FunctionCallbackInfo<Value>& args);
		~RenderPass();
	};
}


