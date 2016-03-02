#pragma once

namespace vulkan_level_20 {

	class Image: public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkImage image{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		Image(const FunctionCallbackInfo<Value>& args);
		~Image();
	};

}