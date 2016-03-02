#pragma once

namespace vulkan_level_20 {

	class BufferView : public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkBufferView bufferView{ nullptr };
		v8::UniquePersistent<Object> device;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		BufferView(const FunctionCallbackInfo<Value>& args);
		~BufferView();
	};

}