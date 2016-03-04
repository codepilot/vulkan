#pragma once




namespace vulkan_autogen {
	class Framebuffer : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkFramebuffer vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateFramebuffer vkCreateFramebuffer;
		PFN_vkDestroyFramebuffer vkDestroyFramebuffer;
		Framebuffer(const FunctionCallbackInfo<Value>& args);
		~Framebuffer();
	};
}


