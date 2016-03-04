#pragma once




namespace vulkan_autogen {
	class Image : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkImage vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateImage vkCreateImage;
		PFN_vkDestroyImage vkDestroyImage;
		Image(const FunctionCallbackInfo<Value>& args);
		~Image();
	};
}


