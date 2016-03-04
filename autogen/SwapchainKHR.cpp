#include "vulkan_autogen.h"




namespace vulkan_autogen {
	Eternal<Function> SwapchainKHR::constructor;

	void SwapchainKHR::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::SwapchainKHR"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Set(isolate, tpl->GetFunction());
	}

	void SwapchainKHR::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 1> argv{ args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	SwapchainKHR::SwapchainKHR(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());

		parent_device.Reset(isolate, getELitObjectFromArgN(0, parent_device));
		
		vkCreateSwapchainKHR = reinterpret_cast<PFN_vkCreateSwapchainKHR>(vkGetDeviceProcAddr(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle,"vkCreateSwapchainKHR"));
		vkDestroySwapchainKHR = reinterpret_cast<PFN_vkDestroySwapchainKHR>(vkGetDeviceProcAddr(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle,"vkDestroySwapchainKHR"));
	
				VkSwapchainCreateInfoKHR pCreateInfo;
		memset(&pCreateInfo, 0, sizeof(VkSwapchainCreateInfoKHR));
		pCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		vkCreateSwapchainKHR(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle, &pCreateInfo, nullptr, &vulkan_handle);

		setELitPtr(args.This(), vulkan_handle, vulkan_handle);

	}

	SwapchainKHR::~SwapchainKHR() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("SwapchainKHR::~SwapchainKHR()");

		vkDestroySwapchainKHR(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle, vulkan_handle, nullptr);
		
	}

	void SwapchainKHR::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			SwapchainKHR* obj = new SwapchainKHR(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 1> argv{ args[0] };
			Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}
}


