#pragma once




namespace vulkan_autogen {
	class DisplayPlaneSurfaceKHR : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkSurfaceKHR vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_instance;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateDisplayPlaneSurfaceKHR vkCreateDisplayPlaneSurfaceKHR;
		PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
		DisplayPlaneSurfaceKHR(const FunctionCallbackInfo<Value>& args);
		~DisplayPlaneSurfaceKHR();
	};
}


