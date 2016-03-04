#include "vulkan_autogen.h"

#ifdef VK_USE_PLATFORM_WIN32_KHR


namespace vulkan_autogen {
	Eternal<Function> Win32SurfaceKHR::constructor;

	void Win32SurfaceKHR::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::Win32SurfaceKHR"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Set(isolate, tpl->GetFunction());
	}

	void Win32SurfaceKHR::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 1> argv{ args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	Win32SurfaceKHR::Win32SurfaceKHR(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());

		parent_instance.Reset(isolate, getELitObjectFromArgN(0, parent_instance));
		
		vkCreateWin32SurfaceKHR = reinterpret_cast<PFN_vkCreateWin32SurfaceKHR>(vkGetInstanceProcAddr(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle,"vkCreateWin32SurfaceKHR"));
		vkDestroySurfaceKHR = reinterpret_cast<PFN_vkDestroySurfaceKHR>(vkGetInstanceProcAddr(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle,"vkDestroySurfaceKHR"));
	
				VkWin32SurfaceCreateInfoKHR pCreateInfo;
		memset(&pCreateInfo, 0, sizeof(VkWin32SurfaceCreateInfoKHR));
		pCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		vkCreateWin32SurfaceKHR(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle, &pCreateInfo, nullptr, &vulkan_handle);

		setELitPtr(args.This(), vulkan_handle, vulkan_handle);

	}

	Win32SurfaceKHR::~Win32SurfaceKHR() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("Win32SurfaceKHR::~Win32SurfaceKHR()");

		vkDestroySurfaceKHR(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle, vulkan_handle, nullptr);
		
	}

	void Win32SurfaceKHR::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			Win32SurfaceKHR* obj = new Win32SurfaceKHR(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 1> argv{ args[0] };
			Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}
}

#endif // VK_USE_PLATFORM_WIN32_KHR
