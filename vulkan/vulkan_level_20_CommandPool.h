#pragma once

namespace vulkan_level_20 {
	class CommandPool : public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkCommandPool commandPool{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		CommandPool(const FunctionCallbackInfo<Value>& args);
		~CommandPool();
	};

}