#include "vulkan_levels.h"

namespace vulkan_level_20 {
	Persistent<Function> Instance::constructor;
	
	void Instance::physicalDevices_AccessorGetterCallback(Local<String> property, const v8::PropertyCallbackInfo<Value>& info) {
		Isolate* isolate = info.GetIsolate();
		HandleScope handle_scope(isolate);

		Instance* instance = ObjectWrap::Unwrap<Instance>(info.Holder());
		info.GetReturnValue().Set(instance->arrPhysicalDevices.Get(isolate));
	}

	void Instance::physicalDevices_AccessorSetterCallback(Local<String> property, Local<Value> value, const v8::PropertyCallbackInfo<void>& info) {

	}

	void Instance::Init(Isolate* isolate) {
		// Prepare constructor template
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::Instance"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

	//tpl->SetNativeDataProperty(getEternalLit(physicalDevices), physicalDevices_AccessorGetterCallback);
		
		NODE_SET_PROTOTYPE_METHOD(tpl, "createDebugReportCallbackEXT", createDebugReportCallbackEXT);
			// Prototype
		//NODE_SET_PROTOTYPE_METHOD(tpl, "enumeratePhysicalDevices", enumeratePhysicalDevices);
		//NODE_SET_PROTOTYPE_METHOD(tpl, "getBytesReceived", wrap_getBytesReceived);
		//NODE_SET_PROTOTYPE_METHOD(tpl, "getLengthReceived", wrap_getLengthReceived);
		//NODE_SET_PROTOTYPE_METHOD(tpl, "getBuffer", wrap_getBuffer);
		//NODE_SET_PROTOTYPE_METHOD(tpl, "getBufferReceived", wrap_getBufferReceived);
	//es_status.Set(isolate, String::NewFromTwoByte(isolate, ptr_to_ptr<const wchar_t *, const uint16_t *>(L"status"), v8::String::kInternalizedString));
	//es_instance.Set(isolate, String::NewFromTwoByte(isolate, ptr_to_ptr<const wchar_t *, const uint16_t *>(L"instance"), v8::String::kInternalizedString));

	
		constructor.Reset(isolate, tpl->GetFunction());
	}

	void Instance::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 0> argv{};
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	};

	auto jsArray_to_string_array(const Local<Array> arr) {
		std::tuple<std::vector<std::string>, std::vector<const char *>> ret;

		const auto arrLength = arr->Length();
		std::get<0>(ret).reserve(arrLength);
		std::get<1>(ret).reserve(arrLength);

		for (uint32_t index{ 0 }; index < arrLength; index++) {
			String::Utf8Value valN{ arr->Get(index)->ToString() };
			std::get<0>(ret).push_back(*valN);
			std::get<1>(ret).push_back(std::get<0>(ret)[index].c_str());
		}
		return ret;
	}

	Instance::Instance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		VkInstanceCreateInfo info{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0, nullptr, 0, nullptr, 0, nullptr };

		decltype(jsArray_to_string_array(get_args_n_Elit_as_Array(0, layers))) layers;
		decltype(jsArray_to_string_array(get_args_n_Elit_as_Array(0, extensions))) extensions;

		if (args.Length() > 0 && args[0]->IsObject()) {
			if (args[0]->ToObject()->HasOwnProperty(getEternalLit(layers))) {
				layers = jsArray_to_string_array(get_args_n_Elit_as_Array(0, layers));
				info.ppEnabledLayerNames = std::get<1>(layers).data();
				info.enabledLayerCount = SafeInt<uint32_t>(std::get<1>(layers).size());
			}

			if (args[0]->ToObject()->HasOwnProperty(getEternalLit(extensions))) {
				extensions = jsArray_to_string_array(get_args_n_Elit_as_Array(0, extensions));
				info.ppEnabledExtensionNames = std::get<1>(extensions).data();
				info.enabledExtensionCount = SafeInt<uint32_t>(std::get<1>(extensions).size());
			}
		}

		const auto status = vkCreateInstance(&info, nullptr, &instance);
		setELitInt32(args.This(), status, status);

		printf("instance: %I64u (0x%I64x)\n", (int64_t)instance, (int64_t)instance);
		setELitPtr(args.This(), instance, instance);

		{
#define createPFN(funcName) {getProcAddr(funcName, #funcName); setELitPtr(args.This(), funcName, funcName); }
#include "vulkan_pfn.h"
#undef createPFN
		}

		Wrap(args.This());

	//VkDebugReportCallbackEXT callback{ nullptr };
	//{
	//	VkDebugReportCallbackCreateInfoEXT info{ VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT, nullptr, VK_DEBUG_REPORT_INFORMATION_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_DEBUG_BIT_EXT,  Instance::cb_vkDebugReportCallbackEXT};
	//	vkCreateDebugReportCallbackEXT(instance, &info, nullptr, &callback);
	//}
	//vkDebugReportMessageEXT(instance, VK_DEBUG_REPORT_INFORMATION_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT, 0, 0, 0, "test", "test2");

	//const auto desktopSupport = vkGetPhysicalDeviceWin32PresentationSupportKHR()
		/*
		VkSurfaceKHR surface{ nullptr };
		{
			HMODULE hModule;
			GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, nullptr, &hModule);
			VkWin32SurfaceCreateInfoKHR info{ VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR, nullptr, 0, hModule, GetDesktopWindow()};
			const auto status = vkCreateWin32SurfaceKHR(instance, &info, nullptr, &surface);
		}
		*/

		uint32_t pPhysicalDeviceCount{ 0 };
		{
			const auto status = vkEnumeratePhysicalDevices(instance, &pPhysicalDeviceCount, nullptr);
		}

		std::vector<VkPhysicalDevice> pPhysicalDevices;
		pPhysicalDevices.resize(pPhysicalDeviceCount, nullptr);

		{
			const auto status = vkEnumeratePhysicalDevices(instance, &pPhysicalDeviceCount, pPhysicalDevices.data());
		}

		Local<Array> aPhysicalDevices{ Array::New(isolate, pPhysicalDeviceCount) };
		Local<Function> PhysicalDeviceConstructor = Local<Function>::New(isolate, PhysicalDevice::constructor);

		for (int32_t index{ 0 }; index < SafeInt<int32_t>(pPhysicalDeviceCount); index++) {
			std::array<Local<Value>, 2> argv{ args.This(), Number::New(isolate, ptr_to_double(pPhysicalDevices[index])) };
			Local<Object> physicalDevice = PhysicalDeviceConstructor->NewInstance(SafeInt<int>(argv.size()), argv.data());
			setIndexValue(aPhysicalDevices, index, physicalDevice);
		}

		arrPhysicalDevices.Reset(isolate, aPhysicalDevices);
		arrPhysicalDevices.SetWeak<nullptr_t>(nullptr, physicalDevices_WeakCallbackInfo, v8::WeakCallbackType::kParameter);
		args.This()->SetAccessor(getEternalLit(physicalDevices), physicalDevices_AccessorGetterCallback);
	}

	void Instance::physicalDevices_WeakCallbackInfo(const v8::WeakCallbackInfo<nullptr_t> &data) {

	}

	Instance::~Instance() {
		puts("Instance::~Instance()");
		vkDestroyInstance(instance, nullptr);
	}

	void Instance::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			// Invoked as constructor: `new MyObject(...)`
			Instance* obj = new Instance(args);
			args.GetReturnValue().Set(args.This());
		//args.This()->SetAccessor(getEternalLit(physicalDevices), physicalDevices_AccessorGetterCallback);
		}
		else {
			// Invoked as plain function `MyObject(...)`, turn into construct call.
			std::array<Local<Value>, 1> argv{ args[0] };
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}

	template<typename T> T Instance::getProcAddr(T &pProc, const char* pName) {
		return pProc = reinterpret_cast<T>(vkGetInstanceProcAddr(instance, pName));
	}

	void Instance::createDebugReportCallbackEXT(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Instance* instance = ObjectWrap::Unwrap<Instance>(args.Holder());

		if (args.Length() > 0 && args[0]->IsObject()) {
			std::array<Local<Value>, 2> argv{ args.This(), args[0] };
			Local<Function> DebugReportCallbackEXTConstructor = Local<Function>::New(isolate, DebugReportCallbackEXT::constructor);
			Local<Object> obj_debugReportCallbackEXT = DebugReportCallbackEXTConstructor->NewInstance(SafeInt<int>(argv.size()), argv.data());
			args.GetReturnValue().Set(obj_debugReportCallbackEXT);
		} else {
			std::array<Local<Value>, 1> argv{ args.This() };
			Local<Function> DebugReportCallbackEXTConstructor = Local<Function>::New(isolate, DebugReportCallbackEXT::constructor);
			Local<Object> obj_debugReportCallbackEXT = DebugReportCallbackEXTConstructor->NewInstance(SafeInt<int>(argv.size()), argv.data());
			args.GetReturnValue().Set(obj_debugReportCallbackEXT);
		}



	}

}