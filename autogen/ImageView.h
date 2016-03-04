#pragma once




namespace vulkan_autogen {
	class ImageView : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkImageView vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateImageView vkCreateImageView;
		PFN_vkDestroyImageView vkDestroyImageView;
		ImageView(const FunctionCallbackInfo<Value>& args);
		~ImageView();
	};
}


