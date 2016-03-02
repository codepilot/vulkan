#pragma once

namespace vulkan_level_20 {

	class DescriptorSetLayout: public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkDescriptorSetLayout descriptorSetLayout{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		DescriptorSetLayout(const FunctionCallbackInfo<Value>& args);
		~DescriptorSetLayout();
	};

}