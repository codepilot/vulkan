#include "vulkan_levels.h"

namespace vulkan_level_10 {

	void wrap_vkCreateInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		VkInstanceCreateInfo info{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0, nullptr, 0, nullptr, 0, nullptr };
		VkInstance pInstance{ nullptr };
		const auto status = vkCreateInstance(&info, nullptr, &pInstance);
		Local<Object> ret{ Object::New(isolate) };
		setELitInt32(ret, status, status);
		printf("instance: %I64u (0x%I64x)\n", (int64_t)pInstance, (int64_t)pInstance);
		setELitPtr(ret, instance, pInstance);
		args.GetReturnValue().Set(ret);
		return;
	}

	
	void wrap_vkDestroyDevice(const FunctionCallbackInfo<Value>& args) {
		VkDevice device{ double_to_ptr<VkDevice>(args[0]->NumberValue()) };
		vkDestroyDevice(device, nullptr);
		return;
	}

	void wrap_vkDestroyInstance(const FunctionCallbackInfo<Value>& args) {
		VkInstance pInstance{ double_to_ptr<VkInstance>(args[0]->NumberValue()) };
		vkDestroyInstance(pInstance, nullptr);
		return;
	}

	void wrap_vkEnumeratePhysicalDevices(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		VkInstance pInstance{ double_to_ptr<VkInstance>(args[0]->NumberValue()) };

		uint32_t pPhysicalDeviceCount{ 0 };
		{
			const auto status = vkEnumeratePhysicalDevices(pInstance, &pPhysicalDeviceCount, nullptr);
		}

		std::vector<VkPhysicalDevice> pPhysicalDevices;
		pPhysicalDevices.resize(pPhysicalDeviceCount, nullptr);

		const auto status = vkEnumeratePhysicalDevices(pInstance, &pPhysicalDeviceCount, pPhysicalDevices.data());

		Local<Array> aPhysicalDevices{ Array::New(isolate, pPhysicalDeviceCount) };
		for (int32_t index{ 0 }; index < SafeInt<int32_t>(pPhysicalDeviceCount); index++) {
			setIndexPtr(aPhysicalDevices, index, pPhysicalDevices[index]);
		}

		Local<Object> ret{ Object::New(isolate) };
		setELitInt32(ret, status, status);
		printf("instance: %I64u (0x%I64x)\n", (int64_t)pInstance, (int64_t)pInstance);
		setELitValue(ret, physicalDevices, aPhysicalDevices);
		args.GetReturnValue().Set(ret);
	}

	void wrap_vkGetPhysicalDeviceQueueFamilyProperties(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		VkPhysicalDevice physicalDevice{ double_to_ptr<VkPhysicalDevice>(args[0]->NumberValue()) };

		uint32_t pQueueFamilyPropertyCount{ 0 };
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &pQueueFamilyPropertyCount, nullptr);

		std::vector<VkQueueFamilyProperties> pQueueFamilyProperties;
		pQueueFamilyProperties.resize(pQueueFamilyPropertyCount);

		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &pQueueFamilyPropertyCount, pQueueFamilyProperties.data());
		Local<Array> aQueueFamilyProperties{ Array::New(isolate, pQueueFamilyPropertyCount) };
		for (int32_t index{ 0 }; index < SafeInt<int32_t>(pQueueFamilyPropertyCount); index++) {
			Local<Object> nProps{ Object::New(isolate) };
			setELitUint32(nProps, queueFlags, pQueueFamilyProperties[index].queueFlags);
			setELitUint32(nProps, queueCount, pQueueFamilyProperties[index].queueCount);
			setELitUint32(nProps, timestampValidBits, pQueueFamilyProperties[index].timestampValidBits);

			Local<Object> minImageTransferGranularity{ Object::New(isolate) };
			setELitUint32(minImageTransferGranularity, width, pQueueFamilyProperties[index].minImageTransferGranularity.width);
			setELitUint32(minImageTransferGranularity, height, pQueueFamilyProperties[index].minImageTransferGranularity.height);
			setELitUint32(minImageTransferGranularity, depth, pQueueFamilyProperties[index].minImageTransferGranularity.depth);
			setELitValue(nProps, minImageTransferGranularity, minImageTransferGranularity);

			setIndexValue(aQueueFamilyProperties, index, nProps);
		}

		args.GetReturnValue().Set(aQueueFamilyProperties);
	}

	std::vector<float_t> getArgAsVectorOfFloats(const Local<Array>& arr) {
		std::vector<float_t> ret;
		const uint32_t len = arr->Length();
		ret.resize(len);
		for (uint32_t index{ 0 }; index < len; index++) {
			ret[index] = static_cast<float_t>(arr->Get(index)->NumberValue());
		}
		return ret;
	}

	void wrap_vkCreateDevice(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		
		std::vector<float_t> pQueuePriorities = getArgAsVectorOfFloats(get_args_n_Elit_as_Array(1, queuePriorities));
		std::array<VkDeviceQueueCreateInfo, 1> queueCreateInfo{
			{
				VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
				nullptr,
				0,
				get_args_n_Elit_as_Uint32(1, queueFamilyIndex),
				get_args_n_Elit_as_Uint32(1, queueCount),
				pQueuePriorities.data()
			}
		};

		VkPhysicalDeviceFeatures deviceFeatures{ 0 };
		VkDeviceCreateInfo info{
			VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			nullptr,
			0,
			SafeInt<uint32_t>(queueCreateInfo.size()),
			queueCreateInfo.data(),
			0,
			nullptr,
			0,
			nullptr,
			&deviceFeatures};

		VkPhysicalDevice physicalDevice{ double_to_ptr<VkPhysicalDevice>(args[0]->NumberValue()) };

		VkDevice device{ nullptr };
		const auto status = vkCreateDevice(physicalDevice, &info, nullptr, &device);

		Local<Object> ret{ Object::New(isolate) };
		setELitInt32(ret, status, status);
		printf("device: %I64u (0x%I64x)\n", (int64_t)device, (int64_t)device);
		setELitPtr(ret, device, device);
		args.GetReturnValue().Set(ret);
	}

	void wrap_vkGetDeviceQueue(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		VkDevice device{ double_to_ptr<VkDevice>(args[0]->NumberValue()) };
		uint32_t queueFamilyIndex{ args[1]->Uint32Value() };
		uint32_t queueIndex{ args[2]->Uint32Value() };
		VkQueue pQueue{ nullptr };

		vkGetDeviceQueue(device, queueFamilyIndex, queueIndex, &pQueue);

		printf("queue: %I64u (0x%I64x)\n", (int64_t)pQueue, (int64_t)pQueue);
		
		args.GetReturnValue().Set(ptr_to_double(pQueue));
	}

	
	void wrap_vkDeviceWaitIdle(const FunctionCallbackInfo<Value>& args) {
		VkDevice device{ double_to_ptr<VkDevice>(args[0]->NumberValue()) };
		const auto status = vkDeviceWaitIdle(device);

		args.GetReturnValue().Set(status);
	}

	void wrap_vkQueueWaitIdle(const FunctionCallbackInfo<Value>& args) {
		VkQueue queue{ double_to_ptr<VkQueue>(args[0]->NumberValue()) };
		const auto status = vkQueueWaitIdle(queue);

		args.GetReturnValue().Set(status);
	}

	void Init(Local<Object> exports) {
		NODE_SET_METHOD(exports, "vkCreateInstance", wrap_vkCreateInstance);
		NODE_SET_METHOD(exports, "vkDestroyInstance", wrap_vkDestroyInstance);
		NODE_SET_METHOD(exports, "vkEnumeratePhysicalDevices", wrap_vkEnumeratePhysicalDevices);
		NODE_SET_METHOD(exports, "vkGetPhysicalDeviceQueueFamilyProperties", wrap_vkGetPhysicalDeviceQueueFamilyProperties);
		NODE_SET_METHOD(exports, "vkCreateDevice", wrap_vkCreateDevice);
		NODE_SET_METHOD(exports, "vkDestroyDevice", wrap_vkDestroyDevice);
		NODE_SET_METHOD(exports, "vkGetDeviceQueue", wrap_vkGetDeviceQueue);
		NODE_SET_METHOD(exports, "vkDeviceWaitIdle", wrap_vkDeviceWaitIdle);
		NODE_SET_METHOD(exports, "vkQueueWaitIdle", wrap_vkQueueWaitIdle);
		
	}
}