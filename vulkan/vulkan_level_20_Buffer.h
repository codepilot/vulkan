#pragma once

namespace vulkan_level_20 {

	class Buffer : public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkBuffer buffer{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		Buffer(const FunctionCallbackInfo<Value>& args);
		~Buffer();
	};

}