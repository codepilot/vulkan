#include "vulkan_autogen.h"


#if 0 //VkDisplayModeKHR

namespace vulkan_autogen {
	Eternal<Function> DisplayModeKHR::constructor;

	void DisplayModeKHR::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::DisplayModeKHR"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Set(isolate, tpl->GetFunction());
	}

	void DisplayModeKHR::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 1> argv{ args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	DisplayModeKHR::DisplayModeKHR(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());

		parent_device.Reset(isolate, getELitObjectFromArgN(0, parent_device));
		parent_physicalDevice = double_to_ptr<decltype(parent_physicalDevice)>(getELitValueFromArgN(0, parent_device)->NumberValue());
		
		vkCreateDisplayModeKHR = reinterpret_cast<PFN_vkCreateDisplayModeKHR>(vkGetDeviceProcAddr(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle,"vkCreateDisplayModeKHR"));
		
	
				VkDisplayModeCreateInfoKHR pCreateInfo;
		memset(&pCreateInfo, 0, sizeof(VkDisplayModeCreateInfoKHR));
		pCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		vkCreateDisplayModeKHR(parent_physicalDevice, VkDisplayKHR, &pCreateInfo, nullptr, &vulkan_handle);

		setELitPtr(args.This(), vulkan_handle, vulkan_handle);

	}

	DisplayModeKHR::~DisplayModeKHR() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("DisplayModeKHR::~DisplayModeKHR()");

		//NO_DESTROY ();
		
	}

	void DisplayModeKHR::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			DisplayModeKHR* obj = new DisplayModeKHR(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 1> argv{ args[0] };
			Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}
}


#endif //VkDisplayModeKHR