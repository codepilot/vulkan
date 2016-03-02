#pragma once

namespace vulkan_level_20 {

	class Fence: public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkFence fence{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		Fence(const FunctionCallbackInfo<Value>& args);
		~Fence();
	};

}