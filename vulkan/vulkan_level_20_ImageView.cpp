#include "vulkan_levels.h"

namespace vulkan_level_20 {
	Persistent<Function> ImageView::constructor;

	void ImageView::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::ImageView"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

		constructor.Reset(isolate, tpl->GetFunction());
	}

	void ImageView::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 2> argv{ args[0], args[1] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	}

	ImageView::ImageView(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());
		device.Reset(isolate, args[0]->ToObject());

		imageView = double_to_ptr<VkImageView>(args[1]->NumberValue());
		setELitPtr(args.This(), imageView, imageView);

	}

	ImageView::~ImageView() {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		puts("ImageView::~ImageView()");
		Device *hDevice = ObjectWrap::Unwrap<Device>(device.Get(isolate));
		vkDestroyImageView(hDevice->device, imageView, nullptr);
	}

	void ImageView::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			ImageView* obj = new ImageView(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			std::array<Local<Value>, 2> argv{ args[0], args[1] };
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}

}