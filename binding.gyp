{ 
  "targets": [ 
    { 
      "target_name": "binding", 
      "sources": [
				"vulkan/vulkan_levels.h",
				"vulkan/vulkan_level_10.h",
				"vulkan/vulkan_level_20.h",
				"vulkan/dllmain.cpp",
				"vulkan/vulkan_level_10.cpp",
				"vulkan/vulkan_level_20.cpp",
				"vulkan/vulkan_level_20_Instance.cpp",
				"vulkan/vulkan_level_20_PhysicalDevice.cpp"],
			"library_dirs": ["lib"],
			"libraries": [
				"-lvulkan-1"],
			"include_dirs": ["include"],
			"defines": ["_WINDLL", "UNICODE", "_UNICODE"]
    }
  ]
}