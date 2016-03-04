#pragma once




namespace vulkan_autogen {
	class Semaphore : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkSemaphore vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateSemaphore vkCreateSemaphore;
		PFN_vkDestroySemaphore vkDestroySemaphore;
		Semaphore(const FunctionCallbackInfo<Value>& args);
		~Semaphore();
	};
}


