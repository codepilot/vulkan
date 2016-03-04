#pragma once




namespace vulkan_autogen {
	class ShaderModule : public node::ObjectWrap {
	public:
		static Eternal<Function> constructor;
		VkShaderModule vulkan_handle{ nullptr };
		
		v8::UniquePersistent<Object> parent_device;
		
		static void Init(Isolate* isolate);
		static void New(const FunctionCallbackInfo<Value>& args);
		static void NewInstance(const FunctionCallbackInfo<Value>& args);
		PFN_vkCreateShaderModule vkCreateShaderModule;
		PFN_vkDestroyShaderModule vkDestroyShaderModule;
		ShaderModule(const FunctionCallbackInfo<Value>& args);
		~ShaderModule();
	};
}


