#include "vulkan_levels.h"

namespace vulkan_level_20 {
	Persistent<Function> Instance::constructor;
	

	void Instance::Init(Isolate* isolate) {
		// Prepare constructor template
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::Instance"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		// Prototype
		NODE_SET_PROTOTYPE_METHOD(tpl, "enumeratePhysicalDevices", enumeratePhysicalDevices);
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

	Instance::Instance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		VkInstanceCreateInfo info{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0, nullptr, 0, nullptr, 0, nullptr };

		std::vector<std::string> vsEnabledExtensionNames{ "VK_KHR_surface", "VK_KHR_win32_surface", "VK_EXT_debug_report" };
		std::vector<std::string> vsEnabledLayerNames{
			"VK_LAYER_GOOGLE_unique_objects",//	wrap all Vulkan objects in a unique pointer at create time and unwrap them at use time
			"VK_LAYER_LUNARG_api_dump",//	print API calls and their parameters and values
			"VK_LAYER_LUNARG_device_limits",//	validate that app properly queries features and obeys feature limitations
			"VK_LAYER_LUNARG_draw_state",//	validate the descriptor set, pipeline state, and dynamic state; validate the interfaces between SPIR - V modules and the graphics pipeline
			"VK_LAYER_LUNARG_image",//	validate texture formats and render target formats
			"VK_LAYER_LUNARG_mem_tracker",//	track and validate GPU memory and its binding to objects and command buffers
			"VK_LAYER_LUNARG_object_tracker",//	track all Vulkan objects and flag invalid objects and object memory leaks
			"VK_LAYER_LUNARG_param_checker",//	validate API parameter values
			"VK_LAYER_LUNARG_swapchain",//	validate the use of the WSI "swapchain" extensions
			"VK_LAYER_LUNARG_threading"//	check validity of multi - threaded API usage
		};

		std::vector<const char *> vpEnabledExtensionNames{};
		std::vector<const char *> vpEnabledLayerNames{};
		for (const auto &nExt: vsEnabledExtensionNames) { vpEnabledExtensionNames.push_back(nExt.c_str()); }
		for (const auto &nLayer: vsEnabledLayerNames) { vpEnabledLayerNames.push_back(nLayer.c_str()); }

		info.ppEnabledExtensionNames = vpEnabledExtensionNames.data();
		info.ppEnabledLayerNames = vpEnabledLayerNames.data();

		info.enabledExtensionCount = SafeInt<uint32_t>(vpEnabledExtensionNames.size());
		info.enabledLayerCount = SafeInt<uint32_t>(vpEnabledLayerNames.size());

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

		VkDebugReportCallbackEXT callback{ nullptr };
		{
			VkDebugReportCallbackCreateInfoEXT info{ VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT, nullptr, VK_DEBUG_REPORT_INFORMATION_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT | VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_DEBUG_BIT_EXT,  Instance::cb_vkDebugReportCallbackEXT};
			vkCreateDebugReportCallbackEXT(instance, &info, nullptr, &callback);
		}
	//vkDebugReportMessageEXT(instance, VK_DEBUG_REPORT_INFORMATION_BIT_EXT, VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT, 0, 0, 0, "test", "test2");

	//const auto desktopSupport = vkGetPhysicalDeviceWin32PresentationSupportKHR()

		VkSurfaceKHR surface{ nullptr };
		{
			HMODULE hModule;
			GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, nullptr, &hModule);
			VkWin32SurfaceCreateInfoKHR info{ VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR, nullptr, 0, hModule, GetDesktopWindow()};
			const auto status = vkCreateWin32SurfaceKHR(instance, &info, nullptr, &surface);
		}
	}
	VkBool32 Instance::cb_vkDebugReportCallbackEXT(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage, void* pUserData) {
		printf("vkDebugReportCallbackEXT(%u, %u, %I64u, %I64u, %d, %s, %s, %p)\n", flags, objectType, object, location, messageCode, pLayerPrefix, pMessage, pUserData);
		return 1;
	}

	Instance::~Instance() {
		vkDestroyInstance(instance, nullptr);
	}

	void Instance::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			// Invoked as constructor: `new MyObject(...)`
			Instance* obj = new Instance(args);
			args.GetReturnValue().Set(args.This());
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

	void Instance::enumeratePhysicalDevices(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Instance* instance = ObjectWrap::Unwrap<Instance>(args.Holder());

		uint32_t pPhysicalDeviceCount{ 0 };
		{
			const auto status = vkEnumeratePhysicalDevices(instance->instance, &pPhysicalDeviceCount, nullptr);
		}

		std::vector<VkPhysicalDevice> pPhysicalDevices;
		pPhysicalDevices.resize(pPhysicalDeviceCount, nullptr);

		const auto status = vkEnumeratePhysicalDevices(instance->instance, &pPhysicalDeviceCount, pPhysicalDevices.data());

		Local<Array> aPhysicalDevices{ Array::New(isolate, pPhysicalDeviceCount) };
		Local<Function> PhysicalDeviceConstructor = Local<Function>::New(isolate, PhysicalDevice::constructor);

		for (int32_t index{ 0 }; index < SafeInt<int32_t>(pPhysicalDeviceCount); index++) {
			std::array<Local<Value>, 2> argv{ args.Holder(), Number::New(isolate, ptr_to_double(pPhysicalDevices[index])) };
			Local<Object> physicalDevice = PhysicalDeviceConstructor->NewInstance(SafeInt<int>(argv.size()), argv.data());

			setIndexValue(aPhysicalDevices, index, physicalDevice);
		}

		args.GetReturnValue().Set(aPhysicalDevices);
	}

}