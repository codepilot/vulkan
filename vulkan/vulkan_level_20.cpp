#include "vulkan_levels.h"

namespace vulkan_level_20 {
	void Init(Local<Object> exports) {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		Instance::Init(isolate);
		PhysicalDevice::Init(isolate);
		Device::Init(isolate);

		Buffer::Init(isolate);
		BufferView::Init(isolate);
		CommandPool::Init(isolate);
		ComputePipeline::Init(isolate);
		DescriptorPool::Init(isolate);
		DescriptorSetLayout::Init(isolate);
		Event::Init(isolate);
		Fence::Init(isolate);
		Framebuffer::Init(isolate);
		GraphicsPipeline::Init(isolate);
		Image::Init(isolate);
		ImageView::Init(isolate);
		PipelineCache::Init(isolate);
		PipelineLayout::Init(isolate);
		QueryPool::Init(isolate);
		RenderPass::Init(isolate);
		Sampler::Init(isolate);
		Semaphore::Init(isolate);
		ShaderModule::Init(isolate);

		DebugReportCallbackEXT::Init(isolate);
		exports->Set(String::NewFromUtf8(isolate, "Instance"), Local<Function>::New(isolate, Instance::constructor));
	}
}