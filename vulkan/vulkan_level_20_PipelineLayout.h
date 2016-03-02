#pragma once

namespace vulkan_level_20 {

	class PipelineLayout: public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkPipelineLayout pipelineLayout{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PipelineLayout(const FunctionCallbackInfo<Value>& args);
		~PipelineLayout();
	};

}