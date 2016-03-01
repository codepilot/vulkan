#include "vulkan_levels.h"

namespace vulkan_level_20 {
	void Init(Local<Object> exports) {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		Instance::Init(isolate);
		PhysicalDevice::Init(isolate);
		Device::Init(isolate);

		exports->Set(String::NewFromUtf8(isolate, "Instance"), Local<Function>::New(isolate, Instance::constructor));
	}
}