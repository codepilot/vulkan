#pragma once

namespace vulkan_level_20 {

	class GraphicsPipeline: public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkPipeline graphicsPipeline{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		GraphicsPipeline(const FunctionCallbackInfo<Value>& args);
		~GraphicsPipeline();
	};

}