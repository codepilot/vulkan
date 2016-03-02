#pragma once

namespace vulkan_level_20 {

}


#include "vulkan_level_20_Buffer.h"
#include "vulkan_level_20_BufferView.h"
#include "vulkan_level_20_CommandPool.h"
#include "vulkan_level_20_ComputePipeline.h"
#include "vulkan_level_20_DescriptorPool.h"
#include "vulkan_level_20_DescriptorSetLayout.h"
#include "vulkan_level_20_Event.h"
#include "vulkan_level_20_Fence.h"
#include "vulkan_level_20_Framebuffer.h"
#include "vulkan_level_20_GraphicsPipeline.h"
#include "vulkan_level_20_Image.h"
#include "vulkan_level_20_ImageView.h"
#include "vulkan_level_20_PipelineCache.h"
#include "vulkan_level_20_PipelineLayout.h"
#include "vulkan_level_20_QueryPool.h"
#include "vulkan_level_20_RenderPass.h"
#include "vulkan_level_20_Sampler.h"
#include "vulkan_level_20_Semaphore.h"
#include "vulkan_level_20_ShaderModule.h"

#include "vulkan_level_20_DebugReportCallbackEXT.h"


namespace vulkan_level_20 {

	class Device: public node::ObjectWrap {
	public:
		static Persistent<Function> constructor;
		VkDevice device{ nullptr };
		v8::UniquePersistent<Object> physicalDevice;
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		Device(const FunctionCallbackInfo<Value>& args);
		~Device();

		static void createBuffer(const FunctionCallbackInfo<Value>& args);
		static void createBufferView(const FunctionCallbackInfo<Value>& args);
		static void createCommandPool(const FunctionCallbackInfo<Value>& args);
		static void createComputePipeline(const FunctionCallbackInfo<Value>& args);
		static void createComputePipelines(const FunctionCallbackInfo<Value>& args);
		static void createDescriptorPool(const FunctionCallbackInfo<Value>& args);
		static void createDescriptorSetLayout(const FunctionCallbackInfo<Value>& args);
		static void createEvent(const FunctionCallbackInfo<Value>& args);
		static void createFence(const FunctionCallbackInfo<Value>& args);
		static void createFramebuffer(const FunctionCallbackInfo<Value>& args);
		static void createGraphicsPipeline(const FunctionCallbackInfo<Value>& args);
		static void createGraphicsPipelines(const FunctionCallbackInfo<Value>& args);
		static void createImage(const FunctionCallbackInfo<Value>& args);
		static void createImageView(const FunctionCallbackInfo<Value>& args);
		static void createPipelineCache(const FunctionCallbackInfo<Value>& args);
		static void createPipelineLayout(const FunctionCallbackInfo<Value>& args);
		static void createQueryPool(const FunctionCallbackInfo<Value>& args);
		static void createRenderPass(const FunctionCallbackInfo<Value>& args);
		static void createSampler(const FunctionCallbackInfo<Value>& args);
		static void createSemaphore(const FunctionCallbackInfo<Value>& args);
		static void createShaderModule(const FunctionCallbackInfo<Value>& args);
	};

	class PhysicalDevice: public node::ObjectWrap {
	public:
		static void Init(Isolate* isolate);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PhysicalDevice(const FunctionCallbackInfo<Value>& args);
		~PhysicalDevice();
		static void New(const FunctionCallbackInfo<Value>& args);
		static void createDevice(const FunctionCallbackInfo<Value>& args);
		static Persistent<Function> constructor;
		Local<Object> PhysicalDevice::getProperties();
		Local<Object> PhysicalDevice::getQueueFamilyProperties();
		Local<Object> PhysicalDevice::getMemoryProperties();
		Local<Object> PhysicalDevice::getFeatures();
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

		static Persistent<Function> constructor;
		VkInstance instance{ nullptr };
		static void physicalDevices_WeakCallbackInfo(const v8::WeakCallbackInfo<nullptr_t> &data);
		v8::UniquePersistent<Array> arrPhysicalDevices;

#define createPFN(funcName) PFN_##funcName funcName{ nullptr };
#include "vulkan_pfn.h"
#undef createPFN

		static void createDebugReportCallbackEXT(const FunctionCallbackInfo<Value>& args);
	};

	void Init(Local<Object> exports);
}

