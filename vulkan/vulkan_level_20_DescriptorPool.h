#pragma once

namespace vulkan_level_20 {

	class DescriptorPool: public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkDescriptorPool descriptorPool{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		DescriptorPool(const FunctionCallbackInfo<Value>& args);
		~DescriptorPool();
	};

}