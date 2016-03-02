#pragma once

namespace vulkan_level_20 {

	class ImageView: public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkImageView imageView{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		ImageView(const FunctionCallbackInfo<Value>& args);
		~ImageView();
	};

}