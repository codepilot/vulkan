"use strict";

{
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