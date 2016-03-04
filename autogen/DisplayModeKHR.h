#pragma once


#if 0 //VkDisplayModeKHR

namespace vulkan_autogen {
	class DisplayModeKHR : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkDisplayModeKHR vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		VkPhysicalDevice parent_physicalDevice;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateDisplayModeKHR vkCreateDisplayModeKHR;
		
		DisplayModeKHR(const FunctionCallbackInfo<Value>& args);
		~DisplayModeKHR();
	};
}


#endif //VkDisplayModeKHR