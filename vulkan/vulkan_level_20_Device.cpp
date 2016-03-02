#include "vulkan_levels.h"

namespace vulkan_level_20 {
	Persistent<Function> Device::constructor;

	void Device::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::Device"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		NODE_SET_PROTOTYPE_METHOD(tpl, "createBuffer", createBuffer);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createBufferView", createBufferView);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createCommandPool", createCommandPool);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createComputePipeline", createComputePipeline);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createComputePipelines", createComputePipelines);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createDescriptorPool", createDescriptorPool);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createDescriptorSetLayout", createDescriptorSetLayout);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createEvent", createEvent);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createFence", createFence);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createFramebuffer", createFramebuffer);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createGraphicsPipeline", createGraphicsPipeline);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createGraphicsPipelines", createGraphicsPipelines);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createImage", createImage);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createImageView", createImageView);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createPipelineCache", createPipelineCache);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createPipelineLayout", createPipelineLayout);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createQueryPool", createQueryPool);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createRenderPass", createRenderPass);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createSampler", createSampler);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createSemaphore", createSemaphore);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createShaderModule", createShaderModule);

		constructor.Reset(isolate, tpl->GetFunction());
	}

	void Device::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 2> argv{args[0], args[1]};
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	Device::Device(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());
		physicalDevice.Reset(isolate, args[0]->ToObject());

		device = double_to_ptr<VkDevice>(args[1]->NumberValue());
		setELitPtr(args.This(), device, device);

	}

	Device::~Device() {
		puts("Device::~Device()");
		vkDestroyDevice(device, nullptr);
	}

	void Device::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			// Invoked as constructor: `new MyObject(...)`
			Device* obj = new Device(args);
			args.GetReturnValue().Set(args.This());
			//args.This()->SetAccessor(getEternalLit(physicalDevices), physicalDevices_AccessorGetterCallback);
		} else {
			// Invoked as plain function `MyObject(...)`, turn into construct call.
			std::array<Local<Value>, 2> argv{ args[0], args[1] };
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}

	void Device::createBuffer(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Device* device = ObjectWrap::Unwrap<Device>(args.Holder());
		VkBufferCreateInfo createInfo{
			VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
			nullptr,
			0,
			4096ui64,
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			VK_SHARING_MODE_EXCLUSIVE,
			0,
			nullptr};

		VkBuffer buffer{ nullptr };
		const auto status = vkCreateBuffer(device->device, &createInfo, nullptr, &buffer);

		Local<Object> ret{ Object::New(isolate) };

		std::array<Local<Value>, 2> argv{ args.This(), Number::New(isolate, ptr_to_double(buffer)) };
		Local<Function> BufferConstructor = Local<Function>::New(isolate, Buffer::constructor);
		args.GetReturnValue().Set(BufferConstructor->NewInstance(SafeInt<int>(argv.size()), argv.data()));
	}


	void Device::createBufferView(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createCommandPool(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Device* device = ObjectWrap::Unwrap<Device>(args.Holder());
		VkCommandPoolCreateInfo createInfo{ VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO, nullptr, 0, 0};
		VkCommandPool commandPool{ nullptr };
		const auto status = vkCreateCommandPool(device->device, &createInfo, nullptr, &commandPool);

		Local<Object> ret{ Object::New(isolate) };

		std::array<Local<Value>, 2> argv{ args.This(), Number::New(isolate, ptr_to_double(commandPool)) };
		Local<Function> CommandPoolConstructor = Local<Function>::New(isolate, CommandPool::constructor);
		args.GetReturnValue().Set(CommandPoolConstructor->NewInstance(SafeInt<int>(argv.size()), argv.data()));
	}


	void Device::createComputePipeline(const FunctionCallbackInfo<Value>& args) {
	}

	void Device::createComputePipelines(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createDescriptorPool(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createDescriptorSetLayout(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createEvent(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createFence(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createFramebuffer(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createGraphicsPipeline(const FunctionCallbackInfo<Value>& args) {
	}

	void Device::createGraphicsPipelines(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createImage(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createImageView(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createPipelineCache(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createPipelineLayout(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createQueryPool(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createRenderPass(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createSampler(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createSemaphore(const FunctionCallbackInfo<Value>& args) {
	}


	void Device::createShaderModule(const FunctionCallbackInfo<Value>& args) {
	}


}