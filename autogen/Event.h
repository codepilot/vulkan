#pragma once




namespace vulkan_autogen {
	class Event : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkEvent vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateEvent vkCreateEvent;
		PFN_vkDestroyEvent vkDestroyEvent;
		Event(const FunctionCallbackInfo<Value>& args);
		~Event();
	};
}


