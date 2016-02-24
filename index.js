"use strict";

if (false) {
	//don't really want to dynamically load the dll, static is better for now
	const vulkanNode = require(process.argv[2]);
	console.log('vulkanNode', vulkanNode);

	{
		const VulkanDll = new vulkanNode.VulkanDll('C:\\VulkanSDK\\1.0.3.1\\Demos\\x64\\Debug\\vulkan-1.dll');
	//const VulkanDll = new vulkanNode.VulkanDll('C:\\VulkanSDK\\1.0.3.1\\Source\\lib\\vulkan-1.dll');//no good
		console.log('VulkanDll', VulkanDll);
	}

	{
		const VulkanDll = new vulkanNode.VulkanDll();
		console.log('VulkanDll', VulkanDll);
	}
}

if(false) {
	const vulkan_level_10 = require(process.argv[2]).level_10;
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

if (true) {
	const vulkan_level_20 = require(process.argv[2]).level_20;
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