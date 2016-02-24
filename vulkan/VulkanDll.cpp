#include "VulkanDll.h"

namespace VulkanDll {
	void Init(Local<Object> exports) {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		VulkanDll::Init(isolate);

		exports->Set(String::NewFromUtf8(isolate, "VulkanDll"), Local<Function>::New(isolate, VulkanDll::constructor));
	}

	Persistent<Function> VulkanDll::constructor;

	void VulkanDll::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::VulkanDll"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		constructor.Reset(isolate, tpl->GetFunction());
	}
	void VulkanDll::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.Length() == 1 && args[0]->IsString()) {
			std::array<Local<Value>, 1> argv{ args[0] };
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

			args.GetReturnValue().Set(instance);
		}
		else {
			std::array<Local<Value>, 0> argv{};
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

			args.GetReturnValue().Set(instance);
		}

	}

	VulkanDll::VulkanDll() {
		hDll = LoadLibraryExW(L"vulkan-1.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	}

	VulkanDll::VulkanDll(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.Length() == 1 && args[0]->IsString()) {
			String::Value svDllPath{ args[0] };
			PTCHAR ptDllPath{ reinterpret_cast<const PTCHAR>(*svDllPath) };
			hDll = LoadLibraryExW(ptDllPath, nullptr, 0);
		}
		else {
			hDll = LoadLibraryExW(L"vulkan-1.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
		}
		getProcAddr(vkGetInstanceProcAddr, "vkGetInstanceProcAddr");
		setKeyPtr(args.This(), "hDll", hDll);
		setKeyPtr(args.This(), "vkGetInstanceProcAddr", vkGetInstanceProcAddr);
		Wrap(args.This());
	}

	VulkanDll::~VulkanDll() {
		FreeLibrary(hDll);
	}

	void VulkanDll::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			// Invoked as constructor: `new MyObject(...)`
			VulkanDll* obj = new VulkanDll(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			if (args.Length() == 1 && args[0]->IsString()) {
				std::array<Local<Value>, 1> argv{ args[0] };
				args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
			}
			else {
				std::array<Local<Value>, 0> argv{};
				args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
			}
		}
	}

	template<typename T> void VulkanDll::getProcAddr(T &pProc, const char* pName) {
		pProc = reinterpret_cast<T>(GetProcAddress(hDll, pName));
	}
}