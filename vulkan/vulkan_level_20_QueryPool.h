#pragma once

namespace vulkan_level_20 {

	class QueryPool: public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkQueryPool queryPool{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		QueryPool(const FunctionCallbackInfo<Value>& args);
		~QueryPool();
	};

}