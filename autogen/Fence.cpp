#include "vulkan_autogen.h"




namespace vulkan_autogen {
	Eternal<Function> Fence::constructor;

	void Fence::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::Fence"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Set(isolate, tpl->GetFunction());
	}

	void Fence::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 1> argv{ args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	Fence::Fence(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());

		parent_device.Reset(isolate, getELitObjectFromArgN(0, parent_device));
		
		vkCreateFence = reinterpret_cast<PFN_vkCreateFence>(vkGetDeviceProcAddr(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle,"vkCreateFence"));
		vkDestroyFence = reinterpret_cast<PFN_vkDestroyFence>(vkGetDeviceProcAddr(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle,"vkDestroyFence"));
	
				VkFenceCreateInfo pCreateInfo;
		memset(&pCreateInfo, 0, sizeof(VkFenceCreateInfo));
		pCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		vkCreateFence(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle, &pCreateInfo, nullptr, &vulkan_handle);

		setELitPtr(args.This(), vulkan_handle, vulkan_handle);

	}

	Fence::~Fence() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("Fence::~Fence()");

		vkDestroyFence(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle, vulkan_handle, nullptr);
		
	}

	void Fence::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			Fence* obj = new Fence(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 1> argv{ args[0] };
			Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}
}


