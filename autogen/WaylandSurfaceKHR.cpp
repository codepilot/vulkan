#include "vulkan_autogen.h"

#ifdef VK_USE_PLATFORM_WAYLAND_KHR


namespace vulkan_autogen {
	Eternal<Function> WaylandSurfaceKHR::constructor;

	void WaylandSurfaceKHR::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::WaylandSurfaceKHR"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Set(isolate, tpl->GetFunction());
	}

	void WaylandSurfaceKHR::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 1> argv{ args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	WaylandSurfaceKHR::WaylandSurfaceKHR(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());

		parent_instance.Reset(isolate, getELitObjectFromArgN(0, parent_instance));
		
		vkCreateWaylandSurfaceKHR = reinterpret_cast<PFN_vkCreateWaylandSurfaceKHR>(vkGetInstanceProcAddr(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle,"vkCreateWaylandSurfaceKHR"));
		vkDestroySurfaceKHR = reinterpret_cast<PFN_vkDestroySurfaceKHR>(vkGetInstanceProcAddr(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle,"vkDestroySurfaceKHR"));
	
				VkWaylandSurfaceCreateInfoKHR pCreateInfo;
		memset(&pCreateInfo, 0, sizeof(VkWaylandSurfaceCreateInfoKHR));
		pCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		vkCreateWaylandSurfaceKHR(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle, &pCreateInfo, nullptr, &vulkan_handle);

		setELitPtr(args.This(), vulkan_handle, vulkan_handle);

	}

	WaylandSurfaceKHR::~WaylandSurfaceKHR() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("WaylandSurfaceKHR::~WaylandSurfaceKHR()");

		vkDestroySurfaceKHR(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle, vulkan_handle, nullptr);
		
	}

	void WaylandSurfaceKHR::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			WaylandSurfaceKHR* obj = new WaylandSurfaceKHR(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 1> argv{ args[0] };
			Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}
}

#endif // VK_USE_PLATFORM_WAYLAND_KHR
