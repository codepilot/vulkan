#include "vulkan_levels.h"

namespace vulkan_level_20 {
	Persistent<Function> DescriptorSetLayout::constructor;

	void DescriptorSetLayout::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::DescriptorSetLayout"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Reset(isolate, tpl->GetFunction());
	}

	void DescriptorSetLayout::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 2> argv{ args[0], args[1] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	DescriptorSetLayout::DescriptorSetLayout(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());
		device.Reset(isolate, args[0]->ToObject());

		descriptorSetLayout = double_to_ptr<VkDescriptorSetLayout>(args[1]->NumberValue());
		setELitPtr(args.This(), descriptorSetLayout, descriptorSetLayout);

	}

	DescriptorSetLayout::~DescriptorSetLayout() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("DescriptorSetLayout::~DescriptorSetLayout()");
		Device *hDevice = ObjectWrap::Unwrap<Device>(device.Get(isolate));
		vkDestroyDescriptorSetLayout(hDevice->device, descriptorSetLayout, nullptr);
	}

	void DescriptorSetLayout::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			DescriptorSetLayout* obj = new DescriptorSetLayout(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 2> argv{ args[0], args[1] };
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}

}