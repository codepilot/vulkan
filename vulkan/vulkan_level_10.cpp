#include <stdexcept>
#include <vector>
#include <array>
#include <safeint.h>
#include <node.h>
#include <node_buffer.h>
#include <node_object_wrap.h>
#include <uv.h>
#include <fcntl.h>

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
//#include <windows.h>

#define VK_USE_PLATFORM_WIN32_KHR 1
#include <vulkan/vulkan.h>

#pragma comment(lib, "node.lib")
#pragma comment (lib,"vulkan-1.lib")

namespace vulkan_level_10 {
	using v8::Int32;
	using v8::Uint32;
	using v8::HandleScope;
	using v8::Array;
	using v8::Exception;
	using v8::FunctionCallbackInfo;
	using v8::Persistent;

	using v8::FunctionTemplate;
	using v8::Function;
	using v8::Isolate;
	using v8::Local;
	using v8::Number;
	using v8::Object;
	using v8::String;
	using v8::Value;

	using msl::utilities::SafeInt;


	template <typename T> double ptr_to_double(T ptr) { return static_cast<double>(reinterpret_cast<int64_t>(ptr)); }
	template <typename T> T double_to_ptr(double dbl) { return reinterpret_cast<T>(static_cast<int64_t>(dbl)); }

#define lit2b(lit) String::NewFromTwoByte(isolate, reinterpret_cast<const uint16_t *>(TEXT(#lit)))
#define str2b(str) String::NewFromTwoByte(isolate, reinterpret_cast<const uint16_t *>(TEXT(str)))
#define setKeyValue(dst, key, val) { dst->Set(str2b(key), val); };
#define setKeyInt32(dst, key, val) { setKeyValue(dst, key, Int32::New(isolate, val)); };
#define setKeyUint32(dst, key, val) { setKeyValue(dst, key, Uint32::New(isolate, val)); };
#define setKeyPtr(dst, key, val) { setKeyValue(dst, key, Number::New(isolate, ptr_to_double(val))); };

#define setIndexValue(dst, key, val) { dst->Set(index, val); };
#define setIndexPtr(dst, index, val) { setIndexValue(dst, key, Number::New(isolate, ptr_to_double(val))); };

	void wrap_vkCreateInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();

		VkInstanceCreateInfo info{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0, nullptr, 0, nullptr, 0, nullptr };
		VkInstance pInstance{ nullptr };
		const auto status = vkCreateInstance(&info, nullptr, &pInstance);
		Local<Object> ret{ Object::New(isolate) };
		setKeyInt32(ret, "status", status);
		printf("instance: %I64u (0x%I64x)\n", (int64_t)pInstance, (int64_t)pInstance);
		setKeyPtr(ret, "instance", pInstance);
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
		setKeyInt32(ret, "status", status);
		printf("instance: %I64u (0x%I64x)\n", (int64_t)pInstance, (int64_t)pInstance);
		setKeyValue(ret, "physicalDevices", aPhysicalDevices);
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
		
		std::vector<float_t> pQueuePriorities = getArgAsVectorOfFloats(Local<Array>::Cast(args[1]->ToObject()->Get(lit2b(queuePriorities))));
		std::array<VkDeviceQueueCreateInfo, 1> queueCreateInfo{
			{
				VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
				nullptr,
				0,
				args[1]->ToObject()->Get(lit2b(queueFamilyIndex))->Uint32Value(),
				args[1]->ToObject()->Get(lit2b(queueCount))->Uint32Value(),
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
		setKeyInt32(ret, "status", status);
		printf("device: %I64u (0x%I64x)\n", (int64_t)device, (int64_t)device);
		setKeyPtr(ret, "device", device);
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