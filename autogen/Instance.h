#pragma once




namespace vulkan_autogen {
	class Instance : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkInstance vulkan_handle{ nullptr };
		
		
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		
		
		Instance(const FunctionCallbackInfo<Value>& args);
		~Instance();
	};
}


