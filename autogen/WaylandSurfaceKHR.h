#pragma once

#ifdef VK_USE_PLATFORM_WAYLAND_KHR


namespace vulkan_autogen {
	class WaylandSurfaceKHR : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkSurfaceKHR vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_instance;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR;
		PFN_vkDestroySurfaceKHR vkDestroySurfaceKHR;
		WaylandSurfaceKHR(const FunctionCallbackInfo<Value>& args);
		~WaylandSurfaceKHR();
	};
}

#endif // VK_USE_PLATFORM_WAYLAND_KHR
