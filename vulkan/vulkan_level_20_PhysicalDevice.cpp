#include "vulkan_levels.h"

namespace vulkan_level_20 {
	Persistent<Function> PhysicalDevice::constructor;

	void PhysicalDevice::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::PhyscalDevice"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		NODE_SET_PROTOTYPE_METHOD(tpl, "getQueueFamilyProperties", getQueueFamilyProperties);
		NODE_SET_PROTOTYPE_METHOD(tpl, "getWin32PresentationSupportKHR", getWin32PresentationSupportKHR);
		NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		
		constructor.Reset(isolate, tpl->GetFunction());
	}

	void PhysicalDevice::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 0> argv{};
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	};

	PhysicalDevice::PhysicalDevice(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());
		instance.Reset(isolate, args[0]->ToObject());
		physicalDevice = double_to_ptr<VkPhysicalDevice>(args[1]->NumberValue());
		setKeyPtr(args.This(), "physicalDevice", physicalDevice);

	}

	void PhysicalDevice::getMemoryProperties(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		auto physicalDevice = ObjectWrap::Unwrap<PhysicalDevice>(args.Holder());
		VkPhysicalDeviceMemoryProperties props{0};
		vkGetPhysicalDeviceMemoryProperties(physicalDevice->physicalDevice, &props);

		Local<Object> ret{ Object::New(isolate) };;
		Local<Array> memoryTypes{ Array::New(isolate, props.memoryTypeCount) };
		Local<Array> memoryHeaps{ Array::New(isolate, props.memoryHeapCount) };
		setKeyValue(ret, "memoryTypes", memoryTypes);
		setKeyValue(ret, "memoryHeaps", memoryHeaps);

		for (int32_t index{ 0 }; index < SafeInt<int32_t>(props.memoryTypeCount); index++) {
			Local<Object> nProps{ Object::New(isolate) };
			setKeyUint32(nProps, "propertyFlags", props.memoryTypes[index].propertyFlags);
			setKeyUint32(nProps, "heapIndex", props.memoryTypes[index].heapIndex);
			setIndexValue(memoryTypes, index, nProps);
		}

		for (int32_t index{ 0 }; index < SafeInt<int32_t>(props.memoryHeapCount); index++) {
			Local<Object> nProps{ Object::New(isolate) };
			setKeyValue(nProps, "size", Number::New(isolate, static_cast<double_t>(props.memoryHeaps[index].size)));
			setKeyUint32(nProps, "flags", props.memoryHeaps[index].flags);
			setIndexValue(memoryHeaps, index, nProps);
		}

		args.GetReturnValue().Set(ret);
	}

	void PhysicalDevice::getWin32PresentationSupportKHR(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		auto physicalDevice = ObjectWrap::Unwrap<PhysicalDevice>(args.Holder());
		args.GetReturnValue().Set(ObjectWrap::Unwrap<Instance>(Local<Object>::New(isolate, physicalDevice->instance))->vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice->physicalDevice, 0));
	}

	void PhysicalDevice::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			// Invoked as constructor: `new MyObject(...)`
			PhysicalDevice* obj = new PhysicalDevice(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			// Invoked as plain function `MyObject(...)`, turn into construct call.
			std::array<Local<Value>, 1> argv{ args[0] };
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}

	void PhysicalDevice::getQueueFamilyProperties(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		PhysicalDevice* physicalDevice = ObjectWrap::Unwrap<PhysicalDevice>(args.Holder());

		uint32_t pQueueFamilyPropertyCount{ 0 };
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice->physicalDevice, &pQueueFamilyPropertyCount, nullptr);

		std::vector<VkQueueFamilyProperties> pQueueFamilyProperties;
		pQueueFamilyProperties.resize(pQueueFamilyPropertyCount);

		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice->physicalDevice, &pQueueFamilyPropertyCount, pQueueFamilyProperties.data());
		Local<Array> aQueueFamilyProperties{ Array::New(isolate, pQueueFamilyPropertyCount) };
		for (int32_t index{ 0 }; index < SafeInt<int32_t>(pQueueFamilyPropertyCount); index++) {
			Local<Object> nProps{ Object::New(isolate) };
			setKeyUint32(nProps, "queueFlags", pQueueFamilyProperties[index].queueFlags);
			setKeyUint32(nProps, "queueCount", pQueueFamilyProperties[index].queueCount);
			setKeyUint32(nProps, "timestampValidBits", pQueueFamilyProperties[index].timestampValidBits);

			Local<Object> minImageTransferGranularity{ Object::New(isolate) };
			setKeyUint32(minImageTransferGranularity, "width", pQueueFamilyProperties[index].minImageTransferGranularity.width);
			setKeyUint32(minImageTransferGranularity, "height", pQueueFamilyProperties[index].minImageTransferGranularity.height);
			setKeyUint32(minImageTransferGranularity, "depth", pQueueFamilyProperties[index].minImageTransferGranularity.depth);
			setKeyValue(nProps, "minImageTransferGranularity", minImageTransferGranularity);

			setIndexValue(aQueueFamilyProperties, index, nProps);
		}

		args.GetReturnValue().Set(aQueueFamilyProperties);
	}

}