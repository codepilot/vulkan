#include "vulkan_levels.h"

namespace vulkan_level_20 {
	Persistent<Function> DebugReportCallbackEXT::constructor;

	void DebugReportCallbackEXT::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::DebugReportCallbackEXT"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Reset(isolate, tpl->GetFunction());
	}

	void DebugReportCallbackEXT::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 2> argv{ args[0], args[1] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	VkBool32 DebugReportCallbackEXT::cb_vkDebugReportCallbackEXT(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData) {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		printf("vkDebugReportCallbackEXT(%u, %u, %I64u, %I64u, %d, %s, %s, %p)\n", flags, objectType, object, location, messageCode, pLayerPrefix, pMessage, pUserData);
		auto thisPtr = reinterpret_cast<DebugReportCallbackEXT *>(pUserData);
		if (!thisPtr->callback.IsEmpty()) {
			std::array<Local<Value>, 8> argv{
				Uint32::NewFromUnsigned(isolate, flags),
				Uint32::NewFromUnsigned(isolate, objectType),
				Number::New(isolate, static_cast<double_t>(object)),
				Number::New(isolate, static_cast<double_t>(location)),
				Int32::New(isolate, messageCode),
				String::NewFromUtf8(isolate, pLayerPrefix),
				String::NewFromUtf8(isolate, pMessage),
				thisPtr->userData.Get(isolate)
			};
			thisPtr->callback.Get(isolate)->Call(v8::Null(isolate), SafeInt<int>(argv.size()), argv.data());
		}
		return 1;
	}


	DebugReportCallbackEXT::DebugReportCallbackEXT(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());
		instance.Reset(isolate, args[0]->ToObject());



		VkDebugReportCallbackCreateInfoEXT createInfo{
			VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT,
			nullptr,
			VK_DEBUG_REPORT_INFORMATION_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_DEBUG_BIT_EXT,
			DebugReportCallbackEXT::cb_vkDebugReportCallbackEXT,
			this
		};

		if (args.Length() >= 1 && args[1]->IsObject()) {
			if (args[1]->ToObject()->HasOwnProperty(getEternalLit(flags))) {
				createInfo.flags = get_args_n_Elit_as_Uint32(1, flags);
			}
		}

		if (args.Length() >= 1 && args[1]->IsObject()) {
			if (args[1]->ToObject()->HasOwnProperty(getEternalLit(pfnCallback)) && getELitValueFromArgN(1, pfnCallback)->IsFunction()) {
				callback.Reset(isolate, Local<Function>::Cast(getELitValueFromArgN(1, pfnCallback)));
			}

			if (args[1]->ToObject()->HasOwnProperty(getEternalLit(pUserData))) {
				userData.Reset(isolate, getELitValueFromArgN(1, pUserData));
			}
		}

		Instance* pInstance = ObjectWrap::Unwrap<Instance>(args[0]->ToObject());
		const auto status = pInstance->vkCreateDebugReportCallbackEXT(pInstance->instance, &createInfo, nullptr, &debugReportCallbackEXT);

		setELitPtr(args.This(), debugReportCallbackEXT, debugReportCallbackEXT);

	}

	DebugReportCallbackEXT::~DebugReportCallbackEXT() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("DebugReportCallbackEXT::~DebugReportCallbackEXT()");
		Instance *hInstance = ObjectWrap::Unwrap<Instance>(instance.Get(isolate));
		hInstance->vkDestroyDebugReportCallbackEXT(hInstance->instance, debugReportCallbackEXT, nullptr);
	}

	void DebugReportCallbackEXT::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			DebugReportCallbackEXT* obj = new DebugReportCallbackEXT(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 2> argv{ args[0], args[1] };
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}

}