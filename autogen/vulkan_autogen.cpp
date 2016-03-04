#include "vulkan_autogen.h"

namespace vulkan_autogen {
	void Init(Local<Object> exports) {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		Instance::Init(isolate);
		Device::Init(isolate);
		Fence::Init(isolate);
		Semaphore::Init(isolate);
		Event::Init(isolate);
		QueryPool::Init(isolate);
		Buffer::Init(isolate);
		BufferView::Init(isolate);
		Image::Init(isolate);
		ImageView::Init(isolate);
		ShaderModule::Init(isolate);
		PipelineCache::Init(isolate);
		GraphicsPipeline::Init(isolate);
		ComputePipeline::Init(isolate);
		PipelineLayout::Init(isolate);
		Sampler::Init(isolate);
		DescriptorSetLayout::Init(isolate);
		DescriptorPool::Init(isolate);
		Framebuffer::Init(isolate);
		RenderPass::Init(isolate);
		CommandPool::Init(isolate);

#ifdef VK_USE_PLATFORM_ANDROID_KHR
		AndroidSurfaceKHR::Init(isolate);
#endif // VK_USE_PLATFORM_ANDROID_KHR


#if 0 // VkDisplayModeKHR
		DisplayModeKHR::Init(isolate);
#endif // VkDisplayModeKHR

		DisplayPlaneSurfaceKHR::Init(isolate);
		SharedSwapchainKHR::Init(isolate);

#ifdef VK_USE_PLATFORM_MIR_KHR
		MirSurfaceKHR::Init(isolate);
#endif // VK_USE_PLATFORM_MIR_KHR

		SwapchainKHR::Init(isolate);

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
		WaylandSurfaceKHR::Init(isolate);
#endif // VK_USE_PLATFORM_WAYLAND_KHR


#ifdef VK_USE_PLATFORM_WIN32_KHR
		Win32SurfaceKHR::Init(isolate);
#endif // VK_USE_PLATFORM_WIN32_KHR


#ifdef VK_USE_PLATFORM_XLIB_KHR
		XlibSurfaceKHR::Init(isolate);
#endif // VK_USE_PLATFORM_XLIB_KHR


#ifdef VK_USE_PLATFORM_XCB_KHR
		XcbSurfaceKHR::Init(isolate);
#endif // VK_USE_PLATFORM_XCB_KHR

		DebugReportCallbackEXT::Init(isolate);
		Instance::Init(isolate);
		exports->Set(String::NewFromUtf8(isolate, "Instance"), Local<Function>::New(isolate, Instance::constructor.Get(isolate)));
	}
}