#include "vulkan_autogen.h"




namespace vulkan_autogen {
	Eternal<Function> Framebuffer::constructor;

	void Framebuffer::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::Framebuffer"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Set(isolate, tpl->GetFunction());
	}

	void Framebuffer::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 1> argv{ args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	Framebuffer::Framebuffer(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());

		parent_device.Reset(isolate, getELitObjectFromArgN(0, parent_device));
		
		vkCreateFramebuffer = reinterpret_cast<PFN_vkCreateFramebuffer>(vkGetDeviceProcAddr(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle,"vkCreateFramebuffer"));
		vkDestroyFramebuffer = reinterpret_cast<PFN_vkDestroyFramebuffer>(vkGetDeviceProcAddr(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle,"vkDestroyFramebuffer"));
	
				VkFramebufferCreateInfo pCreateInfo;
		memset(&pCreateInfo, 0, sizeof(VkFramebufferCreateInfo));
		pCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		vkCreateFramebuffer(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle, &pCreateInfo, nullptr, &vulkan_handle);

		setELitPtr(args.This(), vulkan_handle, vulkan_handle);

	}

	Framebuffer::~Framebuffer() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("Framebuffer::~Framebuffer()");

		vkDestroyFramebuffer(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle, vulkan_handle, nullptr);
		
	}

	void Framebuffer::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			Framebuffer* obj = new Framebuffer(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 1> argv{ args[0] };
			Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}
}


