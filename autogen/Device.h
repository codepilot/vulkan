#pragma once




namespace vulkan_autogen {
	class Device : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkDevice vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_instance;
		VkPhysicalDevice parent_physicalDevice;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateDevice vkCreateDevice;
		PFN_vkDestroyDevice vkDestroyDevice;
		Device(const FunctionCallbackInfo<Value>& args);
		~Device();
	};
}


