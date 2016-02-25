"use strict";

const vulkan = new require("./build/Release/binding.node");

for (const k in vulkan) {
	exports[k] = vulkan[k];
}