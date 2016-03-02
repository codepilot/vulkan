#pragma once

namespace vulkan_level_20 {

	class ComputePipeline : public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkPipeline computePipeline{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		ComputePipeline(const FunctionCallbackInfo<Value>& args);
		~ComputePipeline();
	};

}