#pragma once

namespace vulkan_level_20 {

	class Framebuffer: public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkFramebuffer framebuffer{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		Framebuffer(const FunctionCallbackInfo<Value>& args);
		~Framebuffer();
	};

}