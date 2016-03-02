#pragma once

namespace vulkan_level_20 {

	class Sampler: public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkSampler sampler{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		Sampler(const FunctionCallbackInfo<Value>& args);
		~Sampler();
	};

}