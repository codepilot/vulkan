#include "vulkan_levels.h"

namespace vulkan_level_20 {
	Persistent<Function> CommandPool::constructor;

	void CommandPool::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::CommandPool"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Reset(isolate, tpl->GetFunction());
	}

	void CommandPool::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 2> argv{ args[0], args[1] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	CommandPool::CommandPool(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());
		device.Reset(isolate, args[0]->ToObject());

		commandPool = double_to_ptr<VkCommandPool>(args[1]->NumberValue());
		setELitPtr(args.This(), commandPool, commandPool);

	}

	CommandPool::~CommandPool() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("CommandPool::~CommandPool()");
		Device *hDevice = ObjectWrap::Unwrap<Device>(device.Get(isolate));
		vkDestroyCommandPool(hDevice->device, commandPool, nullptr);
	}

	void CommandPool::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			CommandPool* obj = new CommandPool(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 2> argv{ args[0], args[1] };
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}

}