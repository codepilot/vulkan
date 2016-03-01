"use strict";

function test_vulkan_level_20() {
		const vulkan_level_20 = require("./index.js").level_20;

		const inst = new vulkan_level_20.Instance({
			"layers": [
				"VK_LAYER_GOOGLE_unique_objects",// wrap all Vulkan objects in a unique pointer at create time and unwrap them at use time
				"VK_LAYER_LUNARG_api_dump",      // print API calls and their parameters and values
				"VK_LAYER_LUNARG_device_limits", // validate that app properly queries features and obeys feature limitations
				"VK_LAYER_LUNARG_draw_state",    // validate the descriptor set, pipeline state, and dynamic state; validate the interfaces between SPIR - V modules and the graphics pipeline
				"VK_LAYER_LUNARG_image",         // validate texture formats and render target formats
				"VK_LAYER_LUNARG_mem_tracker",   // track and validate GPU memory and its binding to objects and command buffers
				"VK_LAYER_LUNARG_object_tracker",// track all Vulkan objects and flag invalid objects and object memory leaks
				"VK_LAYER_LUNARG_param_checker", // validate API parameter values
				"VK_LAYER_LUNARG_swapchain",     // validate the use of the WSI "swapchain" extensions
				"VK_LAYER_LUNARG_threading"      // check validity of multi - threaded API usage
			],
			"extensions": [
				"VK_KHR_surface",
				"VK_KHR_win32_surface",
				"VK_EXT_debug_report"
			]
		});
		console.dir(inst, { showHidden: true, depth: null, colors: true });
		//console.dir(inst.physicalDevices, { showHidden: true, depth: null, colors: true });
		//console.dir(Object.getPrototypeOf(inst), { showHidden: true, depth: null, colors: true });
		//console.dir(Object.getPrototypeOf(inst).physicalDevices, { showHidden: true, depth: null, colors: true });
		console.log(JSON.stringify(inst, null, 2));

		const deviceCreateInfo = {
			queueCreateInfo: [{
				queueFamilyIndex: 0,
				queueCount: inst.physicalDevices[0].queueFamilyProperties[0].queueCount,
				queuePriorities: Array(inst.physicalDevices[0].queueFamilyProperties[0].queueCount).fill(0)
			}],
			layers: [
				"VK_LAYER_GOOGLE_unique_objects",// wrap all Vulkan objects in a unique pointer at create time and unwrap them at use time
				"VK_LAYER_LUNARG_api_dump",      // print API calls and their parameters and values
				"VK_LAYER_LUNARG_device_limits", // validate that app properly queries features and obeys feature limitations
				"VK_LAYER_LUNARG_draw_state",    // validate the descriptor set, pipeline state, and dynamic state; validate the interfaces between SPIR - V modules and the graphics pipeline
				"VK_LAYER_LUNARG_image",         // validate texture formats and render target formats
				"VK_LAYER_LUNARG_mem_tracker",   // track and validate GPU memory and its binding to objects and command buffers
				"VK_LAYER_LUNARG_object_tracker",// track all Vulkan objects and flag invalid objects and object memory leaks
				"VK_LAYER_LUNARG_param_checker", // validate API parameter values
				"VK_LAYER_LUNARG_swapchain",     // validate the use of the WSI "swapchain" extensions
				"VK_LAYER_LUNARG_threading"      // check validity of multi - threaded API usage
			],
			extensions: [
				'VK_KHR_swapchain',
				'VK_NV_glsl_shader'
			],
			features: inst.physicalDevices[0].features
		};


		console.log('deviceCreateInfo');
		console.log(JSON.stringify(deviceCreateInfo, null, 2));

		console.log('createDevice');
		const device = inst.physicalDevices[0].createDevice(deviceCreateInfo);
		console.dir(device, { showHidden: true, depth: null, colors: true });


	}

test_vulkan_level_20();
setInterval(function () { global.gc(); }, 1000);

if (false) {
	//don't really want to dynamically load the dll, static is better for now
	const vulkanNode = require("./index.js");
	console.log('vulkanNode', vulkanNode);

	{
		const VulkanDll = new vulkanNode.VulkanDll('C:\\VulkanSDK\\1.0.3.1\\Demos\\x64\\Debug\\vulkan-1.dll');
		//const VulkanDll = new vulkanNode.VulkanDll('C:\\VulkanSDK\\1.0.3.1\\Source\\lib\\vulkan-1.dll');//no good
		console.log('VulkanDll', VulkanDll);
	}

	{
	//const VulkanDll = new vulkanNode.VulkanDll();
	//console.log('VulkanDll', VulkanDll);
	}
}

if (false) {
	const vulkan_level_10 = require("./index.js").level_10;
	console.log('vulkan_level_10', vulkan_level_10);

	const createInstanceResult = vulkan_level_10.vkCreateInstance();
	console.log('createInstanceResult', createInstanceResult);

	const physicalDevices = vulkan_level_10.vkEnumeratePhysicalDevices(createInstanceResult.instance);
	console.log('physicalDevices ', physicalDevices);


	const queueFamilyProperties = physicalDevices.physicalDevices.map(function (v, i, a) {
		return vulkan_level_10.vkGetPhysicalDeviceQueueFamilyProperties(v);
	});

	console.log('queueFamilyProperties');
	console.log(JSON.stringify(queueFamilyProperties, null, 2));

	const queueCreateInfo = {
		queueFamilyIndex: 0,
		queueCount: queueFamilyProperties[0][0].queueCount,
		queuePriorities: Array(queueFamilyProperties[0][0].queueCount).fill(0)
	};

	console.log('queueCreateInfo');
	console.log(JSON.stringify(queueCreateInfo, null, 2));

	const device = vulkan_level_10.vkCreateDevice(physicalDevices.physicalDevices[0], queueCreateInfo);
	console.log('device', device);

	const queue = vulkan_level_10.vkGetDeviceQueue(device.device, 0, 0);
	console.log('queue', queue);


	{
		const deviceWaitStatus = vulkan_level_10.vkDeviceWaitIdle(device.device);
		console.log('deviceWaitStatus', deviceWaitStatus);
	}

	{
		const queueWaitStatus = vulkan_level_10.vkQueueWaitIdle(queue);
		console.log('queueWaitStatus', queueWaitStatus);
	}

	vulkan_level_10.vkDestroyDevice(device.device);

	vulkan_level_10.vkDestroyInstance(createInstanceResult.instance);
}

if (false) {
	const vulkan_level_20 = require("./index.js").level_20;
	console.log('vulkan_level_20', vulkan_level_20);

	const instance = new vulkan_level_20.Instance();
	console.log('instance', instance);
	instance.enumeratePhysicalDevices().forEach(function (v, i, a) {
		console.log('physicalDevice[' + i + ']', v);
		console.log('v.getQueueFamilyProperties()', v.getQueueFamilyProperties());
		console.log('v.getWin32PresentationSupportKHR()', v.getWin32PresentationSupportKHR());
		console.log('v.getMemoryProperties()', v.getMemoryProperties());
	});
}