#include "vulkan_levels.h"

namespace vulkan_level_20 {
	Persistent<Function> DescriptorPool::constructor;

	void DescriptorPool::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::DescriptorPool"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Reset(isolate, tpl->GetFunction());
	}

	void DescriptorPool::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 2> argv{ args[0], args[1] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	DescriptorPool::DescriptorPool(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());
		device.Reset(isolate, args[0]->ToObject());

		descriptorPool = double_to_ptr<VkDescriptorPool>(args[1]->NumberValue());
		setELitPtr(args.This(), descriptorPool, descriptorPool);

	}

	DescriptorPool::~DescriptorPool() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("DescriptorPool::~DescriptorPool()");
		Device *hDevice = ObjectWrap::Unwrap<Device>(device.Get(isolate));
		vkDestroyDescriptorPool(hDevice->device, descriptorPool, nullptr);
	}

	void DescriptorPool::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			DescriptorPool* obj = new DescriptorPool(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 2> argv{ args[0], args[1] };
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}

}