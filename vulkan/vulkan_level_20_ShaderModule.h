#pragma once

namespace vulkan_level_20 {

	class ShaderModule: public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkShaderModule shaderModule{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		ShaderModule(const FunctionCallbackInfo<Value>& args);
		~ShaderModule();
	};

}