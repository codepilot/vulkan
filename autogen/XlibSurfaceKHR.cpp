#include "vulkan_autogen.h"

#ifdef VK_USE_PLATFORM_XLIB_KHR


namespace vulkan_autogen {
	Eternal<Function> XlibSurfaceKHR::constructor;

	void XlibSurfaceKHR::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::XlibSurfaceKHR"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Set(isolate, tpl->GetFunction());
	}

	void XlibSurfaceKHR::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 1> argv{ args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	XlibSurfaceKHR::XlibSurfaceKHR(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());

		parent_instance.Reset(isolate, getELitObjectFromArgN(0, parent_instance));
		
		vkCreateXlibSurfaceKHR = reinterpret_cast<PFN_vkCreateXlibSurfaceKHR>(vkGetInstanceProcAddr(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle,"vkCreateXlibSurfaceKHR"));
		vkDestroySurfaceKHR = reinterpret_cast<PFN_vkDestroySurfaceKHR>(vkGetInstanceProcAddr(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle,"vkDestroySurfaceKHR"));
	
				VkXlibSurfaceCreateInfoKHR pCreateInfo;
		memset(&pCreateInfo, 0, sizeof(VkXlibSurfaceCreateInfoKHR));
		pCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		vkCreateXlibSurfaceKHR(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle, &pCreateInfo, nullptr, &vulkan_handle);

		setELitPtr(args.This(), vulkan_handle, vulkan_handle);

	}

	XlibSurfaceKHR::~XlibSurfaceKHR() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("XlibSurfaceKHR::~XlibSurfaceKHR()");

		vkDestroySurfaceKHR(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle, vulkan_handle, nullptr);
		
	}

	void XlibSurfaceKHR::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			XlibSurfaceKHR* obj = new XlibSurfaceKHR(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 1> argv{ args[0] };
			Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}
}

#endif // VK_USE_PLATFORM_XLIB_KHR
