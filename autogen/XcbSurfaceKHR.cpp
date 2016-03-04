#include "vulkan_autogen.h"

#ifdef VK_USE_PLATFORM_XCB_KHR


namespace vulkan_autogen {
	Eternal<Function> XcbSurfaceKHR::constructor;

	void XcbSurfaceKHR::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::XcbSurfaceKHR"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Set(isolate, tpl->GetFunction());
	}

	void XcbSurfaceKHR::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 1> argv{ args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	XcbSurfaceKHR::XcbSurfaceKHR(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());

		parent_instance.Reset(isolate, getELitObjectFromArgN(0, parent_instance));
		
		vkCreateXcbSurfaceKHR = reinterpret_cast<PFN_vkCreateXcbSurfaceKHR>(vkGetInstanceProcAddr(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle,"vkCreateXcbSurfaceKHR"));
		vkDestroySurfaceKHR = reinterpret_cast<PFN_vkDestroySurfaceKHR>(vkGetInstanceProcAddr(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle,"vkDestroySurfaceKHR"));
	
				VkXcbSurfaceCreateInfoKHR pCreateInfo;
		memset(&pCreateInfo, 0, sizeof(VkXcbSurfaceCreateInfoKHR));
		pCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		vkCreateXcbSurfaceKHR(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle, &pCreateInfo, nullptr, &vulkan_handle);

		setELitPtr(args.This(), vulkan_handle, vulkan_handle);

	}

	XcbSurfaceKHR::~XcbSurfaceKHR() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("XcbSurfaceKHR::~XcbSurfaceKHR()");

		vkDestroySurfaceKHR(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle, vulkan_handle, nullptr);
		
	}

	void XcbSurfaceKHR::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			XcbSurfaceKHR* obj = new XcbSurfaceKHR(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 1> argv{ args[0] };
			Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}
}

#endif // VK_USE_PLATFORM_XCB_KHR
