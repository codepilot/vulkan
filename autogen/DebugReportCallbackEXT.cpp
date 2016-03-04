#include "vulkan_autogen.h"




namespace vulkan_autogen {
	Eternal<Function> DebugReportCallbackEXT::constructor;

	void DebugReportCallbackEXT::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::DebugReportCallbackEXT"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Set(isolate, tpl->GetFunction());
	}

	void DebugReportCallbackEXT::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 1> argv{ args[0] };
		Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	DebugReportCallbackEXT::DebugReportCallbackEXT(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());

		parent_instance.Reset(isolate, getELitObjectFromArgN(0, parent_instance));
		
		vkCreateDebugReportCallbackEXT = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(vkGetInstanceProcAddr(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle,"vkCreateDebugReportCallbackEXT"));
		vkDestroyDebugReportCallbackEXT = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(vkGetInstanceProcAddr(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle,"vkDestroyDebugReportCallbackEXT"));
	
				VkDebugReportCallbackCreateInfoEXT pCreateInfo;
		memset(&pCreateInfo, 0, sizeof(VkDebugReportCallbackCreateInfoEXT));
		pCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		vkCreateDebugReportCallbackEXT(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle, &pCreateInfo, nullptr, &vulkan_handle);

		setELitPtr(args.This(), vulkan_handle, vulkan_handle);

	}

	DebugReportCallbackEXT::~DebugReportCallbackEXT() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("DebugReportCallbackEXT::~DebugReportCallbackEXT()");

		vkDestroyDebugReportCallbackEXT(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle, vulkan_handle, nullptr);
		
	}

	void DebugReportCallbackEXT::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			DebugReportCallbackEXT* obj = new DebugReportCallbackEXT(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 1> argv{ args[0] };
			Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}
}


