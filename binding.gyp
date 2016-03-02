{ 
  "targets": [ 
    { 
      "target_name": "binding", 
      "sources": [
				"vulkan/dllmain.cpp",

				"vulkan/vulkan_level_10.cpp",
				"vulkan/vulkan_level_20.cpp",
				"vulkan/vulkan_level_20_Buffer.cpp",
				"vulkan/vulkan_level_20_BufferView.cpp",
				"vulkan/vulkan_level_20_CommandPool.cpp",
				"vulkan/vulkan_level_20_ComputePipeline.cpp",
				"vulkan/vulkan_level_20_DebugReportCallbackEXT.cpp",
				"vulkan/vulkan_level_20_DescriptorPool.cpp",
				"vulkan/vulkan_level_20_DescriptorSetLayout.cpp",
				"vulkan/vulkan_level_20_Device.cpp",
				"vulkan/vulkan_level_20_Event.cpp",
				"vulkan/vulkan_level_20_Fence.cpp",
				"vulkan/vulkan_level_20_Framebuffer.cpp",
				"vulkan/vulkan_level_20_GraphicsPipeline.cpp",
				"vulkan/vulkan_level_20_Image.cpp",
				"vulkan/vulkan_level_20_ImageView.cpp",
				"vulkan/vulkan_level_20_Instance.cpp",
				"vulkan/vulkan_level_20_PhysicalDevice.cpp",
				"vulkan/vulkan_level_20_PipelineCache.cpp",
				"vulkan/vulkan_level_20_PipelineLayout.cpp",
				"vulkan/vulkan_level_20_QueryPool.cpp",
				"vulkan/vulkan_level_20_RenderPass.cpp",
				"vulkan/vulkan_level_20_Sampler.cpp",
				"vulkan/vulkan_level_20_Semaphore.cpp",
				"vulkan/vulkan_level_20_ShaderModule.cpp",

				"vulkan/EternalStrings.h",

				"vulkan/vulkan_levels.h",
				"vulkan/vulkan_level_10.h",
				"vulkan/vulkan_level_20.h",
				"vulkan/vulkan_level_20_Buffer.h",
				"vulkan/vulkan_level_20_BufferView.h",
				"vulkan/vulkan_level_20_CommandPool.h",
				"vulkan/vulkan_level_20_ComputePipeline.h",
				"vulkan/vulkan_level_20_DebugReportCallbackEXT.h",
				"vulkan/vulkan_level_20_DescriptorPool.h",
				"vulkan/vulkan_level_20_DescriptorSetLayout.h",
				"vulkan/vulkan_level_20_Event.h",
				"vulkan/vulkan_level_20_Fence.h",
				"vulkan/vulkan_level_20_Framebuffer.h",
				"vulkan/vulkan_level_20_GraphicsPipeline.h",
				"vulkan/vulkan_level_20_Image.h",
				"vulkan/vulkan_level_20_ImageView.h",
				"vulkan/vulkan_level_20_PipelineCache.h",
				"vulkan/vulkan_level_20_PipelineLayout.h",
				"vulkan/vulkan_level_20_QueryPool.h",
				"vulkan/vulkan_level_20_RenderPass.h",
				"vulkan/vulkan_level_20_Sampler.h",
				"vulkan/vulkan_level_20_Semaphore.h",
				"vulkan/vulkan_level_20_ShaderModule.h",
				"vulkan/vulkan_pfn.h"],

			"library_dirs": ["lib"],
			"libraries": [
				"-lvulkan-1"],
			"include_dirs": ["include"],
			"defines": ["_WINDLL", "UNICODE", "_UNICODE"]
    }
  ]
}