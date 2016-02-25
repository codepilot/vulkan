#pragma once

namespace vulkan_level_20 {

	class PhysicalDevice: public node::ObjectWrap {
	public:
		static void Init(Isolate* isolate);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PhysicalDevice(const FunctionCallbackInfo<Value>& args);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void getQueueFamilyProperties(const FunctionCallbackInfo<Value>& args);
		static Persistent<Function> constructor;
		VkPhysicalDevice physicalDevice{ nullptr };
		Persistent<Object> instance;
		static void getMemoryProperties(const FunctionCallbackInfo<Value>& args);
		static void getWin32PresentationSupportKHR(const FunctionCallbackInfo<Value>& args);
	};

	class Instance: public node::ObjectWrap {
	public:
		static void Init(Isolate* isolate);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		Instance(const FunctionCallbackInfo<Value>& args);
		~Instance();
		static void New(const FunctionCallbackInfo<Value>& args);

		template<typename T> T Instance::getProcAddr(T &pProc, const char* pName);

		static void enumeratePhysicalDevices(const FunctionCallbackInfo<Value>& args);
		static VkBool32 cb_vkDebugReportCallbackEXT(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData);

		static Persistent<Function> constructor;
		VkInstance instance{ nullptr };

#define createPFN(funcName) PFN_##funcName funcName{ nullptr };
#include "vulkan_pfn.h"
#undef createPFN
	};

	void Init(Local<Object> exports);
}

