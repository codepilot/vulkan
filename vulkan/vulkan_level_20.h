#pragma once

#include <node_object_wrap.h>
#include <vulkan\vulkan.h>
#include <array>
#include <vector>
#include <safeint.h>

namespace vulkan_level_20 {
	#include "vulkan_levels.h"

	class PhysicalDevice: public node::ObjectWrap {
	public:
		static void Init(Isolate* isolate) {
			Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
			tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::PhyscalDevice"));
			tpl->InstanceTemplate()->SetInternalFieldCount(1);

			NODE_SET_PROTOTYPE_METHOD(tpl, "getQueueFamilyProperties", getQueueFamilyProperties);

			constructor.Reset(isolate, tpl->GetFunction());
		}
		static void NewInstance(const FunctionCallbackInfo<Value>& args) {
			Isolate* isolate = args.GetIsolate();
			HandleScope handle_scope(isolate);

			std::array<Local<Value>, 0> argv{};
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

			args.GetReturnValue().Set(instance);
		};
	private:
		PhysicalDevice(const FunctionCallbackInfo<Value>& args) {
			Isolate* isolate = args.GetIsolate();
			HandleScope handle_scope(isolate);

			Wrap(args.This());
			physicalDevice = double_to_ptr<VkPhysicalDevice>(args[0]->NumberValue());
			setKeyPtr(args.This(), "physicalDevice", physicalDevice);
		}
	public:
		static void New(const FunctionCallbackInfo<Value>& args) {
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

		static void getQueueFamilyProperties(const FunctionCallbackInfo<Value>& args) {
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

		static Persistent<Function> constructor;
		VkPhysicalDevice physicalDevice{ nullptr };
	};

	class Instance: public node::ObjectWrap {
	public:
		static void Init(Isolate* isolate) {
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
			constructor.Reset(isolate, tpl->GetFunction());
		}
		static void NewInstance(const FunctionCallbackInfo<Value>& args) {
			Isolate* isolate = args.GetIsolate();
			HandleScope handle_scope(isolate);

			std::array<Local<Value>, 0> argv{ };
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

			args.GetReturnValue().Set(instance);
		};
	private:
		Instance(const FunctionCallbackInfo<Value>& args) {
			Isolate* isolate = args.GetIsolate();
			HandleScope handle_scope(isolate);

			VkInstanceCreateInfo info{ VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0, nullptr, 0, nullptr, 0, nullptr };
			const auto status = vkCreateInstance(&info, nullptr, &instance);
			setKeyInt32(args.This(), "status", status);
			printf("instance: %I64u (0x%I64x)\n", (int64_t)instance, (int64_t)instance);
			setKeyPtr(args.This(), "instance", instance);
			Wrap(args.This());
		}
		~Instance() {
			vkDestroyInstance(instance, nullptr);
		}
	public:
		static void New(const FunctionCallbackInfo<Value>& args) {
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

		PFN_vkVoidFunction getProcAddr(const char* pName) {
			return vkGetInstanceProcAddr(instance, pName);
		}

		static void enumeratePhysicalDevices(const FunctionCallbackInfo<Value>& args) {
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
				std::array<Local<Value>, 1> argv{ Number::New(isolate, ptr_to_double(pPhysicalDevices[index])) };
				Local<Object> physicalDevice = PhysicalDeviceConstructor->NewInstance(SafeInt<int>(argv.size()), argv.data());

				setIndexValue(aPhysicalDevices, index, physicalDevice);
			}

			args.GetReturnValue().Set(aPhysicalDevices);
		}
	public:
		static Persistent<Function> constructor;
		VkInstance instance{ nullptr };
	};

	void wrap_vkCreateInstance(const FunctionCallbackInfo<Value>& args);
	void wrap_vkDestroyInstance(const FunctionCallbackInfo<Value>& args);
	void Init(Local<Object> exports);

	Persistent<Function> vulkan_level_20::Instance::constructor;
	Persistent<Function> vulkan_level_20::PhysicalDevice::constructor;
	
	static void Init(Local<Object> exports) {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		Instance::Init(isolate);
		PhysicalDevice::Init(isolate);

		exports->Set(String::NewFromUtf8(isolate, "Instance"), Local<Function>::New(isolate, Instance::constructor));
	}

}

