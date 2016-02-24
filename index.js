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

	console.log('queueFamilyProperties', queueFamilyProperties);

	vulkan_level_10.vkDestroyInstance(createInstanceResult.instance);
}