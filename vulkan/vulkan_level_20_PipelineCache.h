#pragma once

namespace vulkan_level_20 {

	class PipelineCache: public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkPipelineCache pipelineCache{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PipelineCache(const FunctionCallbackInfo<Value>& args);
		~PipelineCache();
	};

}