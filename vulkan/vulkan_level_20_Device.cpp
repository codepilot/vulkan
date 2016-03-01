#include "vulkan_levels.h"

namespace vulkan_level_20 {
	Persistent<Function> Device::constructor;

	void Device::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::Device"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

	//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Reset(isolate, tpl->GetFunction());
	}

	void Device::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 2> argv{args[0], args[1]};
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	Device::Device(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());
		physicalDevice.Reset(isolate, args[0]->ToObject());

		device = double_to_ptr<VkDevice>(args[1]->NumberValue());
		setELitPtr(args.This(), device, device);

	}

	Device::~Device() {
		puts("Device::~Device()");
		vkDestroyDevice(device, nullptr);
	}

	void Device::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			// Invoked as constructor: `new MyObject(...)`
			Device* obj = new Device(args);
			args.GetReturnValue().Set(args.This());
			//args.This()->SetAccessor(getEternalLit(physicalDevices), physicalDevices_AccessorGetterCallback);
		}
		else {
			// Invoked as plain function `MyObject(...)`, turn into construct call.
			std::array<Local<Value>, 2> argv{ args[0], args[1] };
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}

	}
}