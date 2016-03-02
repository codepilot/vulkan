#include "vulkan_levels.h"

namespace vulkan_level_20 {
	Persistent<Function> QueryPool::constructor;

	void QueryPool::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::QueryPool"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Reset(isolate, tpl->GetFunction());
	}

	void QueryPool::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 2> argv{ args[0], args[1] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	QueryPool::QueryPool(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());
		device.Reset(isolate, args[0]->ToObject());

		queryPool = double_to_ptr<VkQueryPool>(args[1]->NumberValue());
		setELitPtr(args.This(), queryPool, queryPool);

	}

	QueryPool::~QueryPool() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("QueryPool::~QueryPool()");
		Device *hDevice = ObjectWrap::Unwrap<Device>(device.Get(isolate));
		vkDestroyQueryPool(hDevice->device, queryPool, nullptr);
	}

	void QueryPool::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			QueryPool* obj = new QueryPool(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 2> argv{ args[0], args[1] };
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}

}