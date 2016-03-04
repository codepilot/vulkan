#pragma once




namespace vulkan_autogen {
	class BufferView : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkBufferView vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateBufferView vkCreateBufferView;
		PFN_vkDestroyBufferView vkDestroyBufferView;
		BufferView(const FunctionCallbackInfo<Value>& args);
		~BufferView();
	};
}


