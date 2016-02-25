"use strict";

try {
	const vulkan = new require("./build/Debug/binding.node");

	for (const k in vulkan) {
		exports[k] = vulkan[k];
	}
} catch(err) {
	console.log(err);

	const vulkan = new require("./build/Release/binding.node");

	for (const k in vulkan) {
		exports[k] = vulkan[k];
	}
}