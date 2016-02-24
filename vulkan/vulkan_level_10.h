#pragma once

namespace vulkan_level_10 {
	using v8::FunctionCallbackInfo;
	using v8::Value;
	using v8::Local;
	using v8::Object;

	void wrap_vkCreateInstance(const FunctionCallbackInfo<Value>& args);
	void wrap_vkDestroyInstance(const FunctionCallbackInfo<Value>& args);
	void Init(Local<Object> exports);
}