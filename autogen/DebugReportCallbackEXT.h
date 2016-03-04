#pragma once




namespace vulkan_autogen {
	class DebugReportCallbackEXT : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkDebugReportCallbackEXT vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_instance;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateDebugReportCallbackEXT vkCreateDebugReportCallbackEXT;
		PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT;
		DebugReportCallbackEXT(const FunctionCallbackInfo<Value>& args);
		~DebugReportCallbackEXT();
	};
}


