#pragma once

namespace vulkan_level_20 {

	class Event: public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkEvent event{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		Event(const FunctionCallbackInfo<Value>& args);
		~Event();
	};

}