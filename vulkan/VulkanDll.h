#pragma once

#include "vulkan_levels.h"
namespace VulkanDll {
	class VulkanDll : public node::ObjectWrap {
	public:
		static void Init(Isolate* isolate);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		VulkanDll();
		VulkanDll(const FunctionCallbackInfo<Value>& args);
		~VulkanDll();
		static void New(const FunctionCallbackInfo<Value>& args);

		template<typename T> void VulkanDll::getProcAddr(T &pProc, const char* pName);

		static Persistent<Function> constructor;
		HMODULE hDll{ nullptr };
		PFN_vkGetInstanceProcAddr vkGetInstanceProcAddr{ nullptr };
	};

	void Init(Local<Object> exports);
}