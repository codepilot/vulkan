#pragma once

namespace vulkan_level_20 {
	class Device: public node::ObjectWrap {
	public:
		static void Init(Isolate* isolate);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		Device(const FunctionCallbackInfo<Value>& args);
		~Device();
		static void New(const FunctionCallbackInfo<Value>& args);
		static Persistent<Function> constructor;
		VkDevice device{ nullptr };
		v8::UniquePersistent<Object> physicalDevice;
	};

	class PhysicalDevice: public node::ObjectWrap {
	public:
		static void Init(Isolate* isolate);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PhysicalDevice(const FunctionCallbackInfo<Value>& args);
		~PhysicalDevice();
		static void New(const FunctionCallbackInfo<Value>& args);
		static void getQueueFamilyProperties(const FunctionCallbackInfo<Value>& args);
		static void createDevice(const FunctionCallbackInfo<Value>& args);
		static Persistent<Function> constructor;
		static void getMemoryProperties(const FunctionCallbackInfo<Value>& args);
		static void getWin32PresentationSupportKHR(const FunctionCallbackInfo<Value>& args);
		VkPhysicalDevice physicalDevice{ nullptr };
		v8::UniquePersistent<Object> instance;
	};

	class Instance: public node::ObjectWrap {
	public:
		static void Init(Isolate* isolate);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		static void physicalDevices_AccessorGetterCallback(Local<String> property, const v8::PropertyCallbackInfo<Value>& info);
		static void physicalDevices_AccessorSetterCallback(Local<String> property, Local<Value> value, const v8::PropertyCallbackInfo<void>& info);

		Instance(const FunctionCallbackInfo<Value>& args);
		~Instance();
		static void New(const FunctionCallbackInfo<Value>& args);

		template<typename T> T Instance::getProcAddr(T &pProc, const char* pName);

		static VkBool32 cb_vkDebugReportCallbackEXT(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData);

		static Persistent<Function> constructor;
		VkInstance instance{ nullptr };
		static void physicalDevices_WeakCallbackInfo(const v8::WeakCallbackInfo<nullptr_t> &data);
		v8::UniquePersistent<Array> arrPhysicalDevices;

#define createPFN(funcName) PFN_##funcName funcName{ nullptr };
#include "vulkan_pfn.h"
#undef createPFN
	};

	void Init(Local<Object> exports);
}

