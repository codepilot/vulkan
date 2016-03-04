#include "vulkan_autogen.h"




namespace vulkan_autogen {
	Eternal<Function> SharedSwapchainKHR::constructor;

	void SharedSwapchainKHR::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::SharedSwapchainKHR"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Set(isolate, tpl->GetFunction());
	}

	void SharedSwapchainKHR::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 1> argv{ args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	SharedSwapchainKHR::SharedSwapchainKHR(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());

		parent_device.Reset(isolate, getELitObjectFromArgN(0, parent_device));
		
		vkCreateSharedSwapchainsKHR = reinterpret_cast<PFN_vkCreateSharedSwapchainsKHR>(vkGetDeviceProcAddr(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle,"vkCreateSharedSwapchainsKHR"));
		vkDestroySwapchainKHR = reinterpret_cast<PFN_vkDestroySwapchainKHR>(vkGetDeviceProcAddr(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle,"vkDestroySwapchainKHR"));
	
				VkSwapchainCreateInfoKHR pCreateInfos;
		memset(&pCreateInfos, 0, sizeof(VkSwapchainCreateInfoKHR));
		pCreateInfos.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		vkCreateSharedSwapchainsKHR(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle, 1, &pCreateInfos, nullptr, &vulkan_handle);

		setELitPtr(args.This(), vulkan_handle, vulkan_handle);

	}

	SharedSwapchainKHR::~SharedSwapchainKHR() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("SharedSwapchainKHR::~SharedSwapchainKHR()");

		vkDestroySwapchainKHR(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle, vulkan_handle, nullptr);
		
	}

	void SharedSwapchainKHR::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			SharedSwapchainKHR* obj = new SharedSwapchainKHR(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 1> argv{ args[0] };
			Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}
}


