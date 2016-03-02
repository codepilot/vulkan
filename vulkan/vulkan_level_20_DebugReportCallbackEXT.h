#pragma once

namespace vulkan_level_20 {

	class DebugReportCallbackEXT : public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkDebugReportCallbackEXT debugReportCallbackEXT{ nullptr };
		v8::UniquePersistent<Object> instance;
		v8::UniquePersistent<Function> callback;
		v8::UniquePersistent<Value> userData;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		static VkBool32 DebugReportCallbackEXT::cb_vkDebugReportCallbackEXT(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData);
		DebugReportCallbackEXT(const FunctionCallbackInfo<Value>& args);
		~DebugReportCallbackEXT();
	};

}