#pragma once




namespace vulkan_autogen {
	class Buffer : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkBuffer vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateBuffer vkCreateBuffer;
		PFN_vkDestroyBuffer vkDestroyBuffer;
		Buffer(const FunctionCallbackInfo<Value>& args);
		~Buffer();
	};
}


