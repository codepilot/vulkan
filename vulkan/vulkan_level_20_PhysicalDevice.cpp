#include "vulkan_levels.h"

namespace vulkan_level_20 {
	Persistent<Function> PhysicalDevice::constructor;

	void PhysicalDevice::Init(Isolate* isolate) {
		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::PhyscalDevice"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		NODE_SET_PROTOTYPE_METHOD(tpl, "getQueueFamilyProperties", getQueueFamilyProperties);
		NODE_SET_PROTOTYPE_METHOD(tpl, "getWin32PresentationSupportKHR", getWin32PresentationSupportKHR);
		NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);
		NODE_SET_PROTOTYPE_METHOD(tpl, "createDevice", createDevice);
		
		constructor.Reset(isolate, tpl->GetFunction());
	}

	void PhysicalDevice::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::array<Local<Value>, 0> argv{};
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

		args.GetReturnValue().Set(instance);
	};

	PhysicalDevice::PhysicalDevice(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		Wrap(args.This());
		instance.Reset(isolate, args[0]->ToObject());
		physicalDevice = double_to_ptr<VkPhysicalDevice>(args[1]->NumberValue());
		setELitPtr(args.This(), physicalDevice, physicalDevice);

		VkPhysicalDeviceProperties pProperties{ 0 };
		vkGetPhysicalDeviceProperties(physicalDevice, &pProperties);
		Local<Object> properties{ Object::New(isolate) };

		setELitValue(args.This(), properties, properties);

		setELitUint32(properties, apiVersion, pProperties.apiVersion);
		setELitUint32(properties, driverVersion, pProperties.driverVersion);
		setELitUint32(properties, vendorID, pProperties.vendorID);
		setELitUint32(properties, deviceID, pProperties.deviceID);
		setELitInt32(properties, deviceType, pProperties.deviceType);
		setELitValue(properties, deviceName, String::NewFromUtf8(isolate, pProperties.deviceName));

		Local<v8::ArrayBuffer> ab_pipelineCacheUUID{ v8::ArrayBuffer::New(isolate, 16) };
		Local<v8::Uint8Array> pipelineCacheUUID{ v8::Uint8Array::New(ab_pipelineCacheUUID, 0, 16) };
		setELitValue(properties, pipelineCacheUUID, pipelineCacheUUID);
		for (int i = 0; i < ARRAYSIZE(pProperties.pipelineCacheUUID); i++) {
			setIndexUint32(pipelineCacheUUID, i, pProperties.pipelineCacheUUID[i]);
		}

		Local<Object> limits{ Object::New(isolate) };
		setELitValue(properties, limits, limits);

		setELitUint32(limits, maxImageDimension1D, pProperties.limits.maxImageDimension1D);
		setELitUint32(limits, maxImageDimension2D, pProperties.limits.maxImageDimension2D);
		setELitUint32(limits, maxImageDimension3D, pProperties.limits.maxImageDimension3D);
		setELitUint32(limits, maxImageDimensionCube, pProperties.limits.maxImageDimensionCube);
		setELitUint32(limits, maxImageArrayLayers, pProperties.limits.maxImageArrayLayers);
		setELitUint32(limits, maxTexelBufferElements, pProperties.limits.maxTexelBufferElements);
		setELitUint32(limits, maxUniformBufferRange, pProperties.limits.maxUniformBufferRange);
		setELitUint32(limits, maxStorageBufferRange, pProperties.limits.maxStorageBufferRange);
		setELitUint32(limits, maxPushConstantsSize, pProperties.limits.maxPushConstantsSize);
		setELitUint32(limits, maxMemoryAllocationCount, pProperties.limits.maxMemoryAllocationCount);
		setELitUint32(limits, maxSamplerAllocationCount, pProperties.limits.maxSamplerAllocationCount);
		setELitFloat64(limits, bufferImageGranularity, static_cast<double_t>(pProperties.limits.bufferImageGranularity));
		setELitFloat64(limits, sparseAddressSpaceSize, static_cast<double_t>(pProperties.limits.sparseAddressSpaceSize));
		setELitUint32(limits, maxBoundDescriptorSets, pProperties.limits.maxBoundDescriptorSets);
		setELitUint32(limits, maxPerStageDescriptorSamplers, pProperties.limits.maxPerStageDescriptorSamplers);
		setELitUint32(limits, maxPerStageDescriptorUniformBuffers, pProperties.limits.maxPerStageDescriptorUniformBuffers);
		setELitUint32(limits, maxPerStageDescriptorStorageBuffers, pProperties.limits.maxPerStageDescriptorStorageBuffers);
		setELitUint32(limits, maxPerStageDescriptorSampledImages, pProperties.limits.maxPerStageDescriptorSampledImages);
		setELitUint32(limits, maxPerStageDescriptorStorageImages, pProperties.limits.maxPerStageDescriptorStorageImages);
		setELitUint32(limits, maxPerStageDescriptorInputAttachments, pProperties.limits.maxPerStageDescriptorInputAttachments);
		setELitUint32(limits, maxPerStageResources, pProperties.limits.maxPerStageResources);
		setELitUint32(limits, maxDescriptorSetSamplers, pProperties.limits.maxDescriptorSetSamplers);
		setELitUint32(limits, maxDescriptorSetUniformBuffers, pProperties.limits.maxDescriptorSetUniformBuffers);
		setELitUint32(limits, maxDescriptorSetUniformBuffersDynamic, pProperties.limits.maxDescriptorSetUniformBuffersDynamic);
		setELitUint32(limits, maxDescriptorSetStorageBuffers, pProperties.limits.maxDescriptorSetStorageBuffers);
		setELitUint32(limits, maxDescriptorSetStorageBuffersDynamic, pProperties.limits.maxDescriptorSetStorageBuffersDynamic);
		setELitUint32(limits, maxDescriptorSetSampledImages, pProperties.limits.maxDescriptorSetSampledImages);
		setELitUint32(limits, maxDescriptorSetStorageImages, pProperties.limits.maxDescriptorSetStorageImages);
		setELitUint32(limits, maxDescriptorSetInputAttachments, pProperties.limits.maxDescriptorSetInputAttachments);
		setELitUint32(limits, maxVertexInputAttributes, pProperties.limits.maxVertexInputAttributes);
		setELitUint32(limits, maxVertexInputBindings, pProperties.limits.maxVertexInputBindings);
		setELitUint32(limits, maxVertexInputAttributeOffset, pProperties.limits.maxVertexInputAttributeOffset);
		setELitUint32(limits, maxVertexInputBindingStride, pProperties.limits.maxVertexInputBindingStride);
		setELitUint32(limits, maxVertexOutputComponents, pProperties.limits.maxVertexOutputComponents);
		setELitUint32(limits, maxTessellationGenerationLevel, pProperties.limits.maxTessellationGenerationLevel);
		setELitUint32(limits, maxTessellationPatchSize, pProperties.limits.maxTessellationPatchSize);
		setELitUint32(limits, maxTessellationControlPerVertexInputComponents, pProperties.limits.maxTessellationControlPerVertexInputComponents);
		setELitUint32(limits, maxTessellationControlPerVertexOutputComponents, pProperties.limits.maxTessellationControlPerVertexOutputComponents);
		setELitUint32(limits, maxTessellationControlPerPatchOutputComponents, pProperties.limits.maxTessellationControlPerPatchOutputComponents);
		setELitUint32(limits, maxTessellationControlTotalOutputComponents, pProperties.limits.maxTessellationControlTotalOutputComponents);
		setELitUint32(limits, maxTessellationEvaluationInputComponents, pProperties.limits.maxTessellationEvaluationInputComponents);
		setELitUint32(limits, maxTessellationEvaluationOutputComponents, pProperties.limits.maxTessellationEvaluationOutputComponents);
		setELitUint32(limits, maxGeometryShaderInvocations, pProperties.limits.maxGeometryShaderInvocations);
		setELitUint32(limits, maxGeometryInputComponents, pProperties.limits.maxGeometryInputComponents);
		setELitUint32(limits, maxGeometryOutputComponents, pProperties.limits.maxGeometryOutputComponents);
		setELitUint32(limits, maxGeometryOutputVertices, pProperties.limits.maxGeometryOutputVertices);
		setELitUint32(limits, maxGeometryTotalOutputComponents, pProperties.limits.maxGeometryTotalOutputComponents);
		setELitUint32(limits, maxFragmentInputComponents, pProperties.limits.maxFragmentInputComponents);
		setELitUint32(limits, maxFragmentOutputAttachments, pProperties.limits.maxFragmentOutputAttachments);
		setELitUint32(limits, maxFragmentDualSrcAttachments, pProperties.limits.maxFragmentDualSrcAttachments);
		setELitUint32(limits, maxFragmentCombinedOutputResources, pProperties.limits.maxFragmentCombinedOutputResources);
		setELitUint32(limits, maxComputeSharedMemorySize, pProperties.limits.maxComputeSharedMemorySize);

		Local<v8::ArrayBuffer> ab_maxComputeWorkGroupCount{ v8::ArrayBuffer::New(isolate, 12) };
		Local<v8::Uint32Array> maxComputeWorkGroupCount{ v8::Uint32Array::New(ab_maxComputeWorkGroupCount, 0, 3)};
		setELitValue(limits, maxComputeWorkGroupCount, maxComputeWorkGroupCount);
		setIndexUint32(maxComputeWorkGroupCount, 0, pProperties.limits.maxComputeWorkGroupCount[0]);
		setIndexUint32(maxComputeWorkGroupCount, 1, pProperties.limits.maxComputeWorkGroupCount[1]);
		setIndexUint32(maxComputeWorkGroupCount, 2, pProperties.limits.maxComputeWorkGroupCount[2]);

		setELitUint32(limits, maxComputeWorkGroupInvocations, pProperties.limits.maxComputeWorkGroupInvocations);

		Local<v8::ArrayBuffer> ab_maxComputeWorkGroupSize{ v8::ArrayBuffer::New(isolate, 12) };
		Local<v8::Uint32Array> maxComputeWorkGroupSize{ v8::Uint32Array::New(ab_maxComputeWorkGroupSize, 0, 3) };
		setELitValue(limits, maxComputeWorkGroupSize, maxComputeWorkGroupSize);
		setIndexUint32(maxComputeWorkGroupSize, 0, pProperties.limits.maxComputeWorkGroupSize[0]);
		setIndexUint32(maxComputeWorkGroupSize, 1, pProperties.limits.maxComputeWorkGroupSize[1]);
		setIndexUint32(maxComputeWorkGroupSize, 2, pProperties.limits.maxComputeWorkGroupSize[2]);



		setELitUint32(limits, subPixelPrecisionBits, pProperties.limits.subPixelPrecisionBits);
		setELitUint32(limits, subTexelPrecisionBits, pProperties.limits.subTexelPrecisionBits);
		setELitUint32(limits, mipmapPrecisionBits, pProperties.limits.mipmapPrecisionBits);
		setELitUint32(limits, maxDrawIndexedIndexValue, pProperties.limits.maxDrawIndexedIndexValue);
		setELitUint32(limits, maxDrawIndirectCount, pProperties.limits.maxDrawIndirectCount);
		setELitFloat64(limits, maxSamplerLodBias, pProperties.limits.maxSamplerLodBias);
		setELitFloat64(limits, maxSamplerAnisotropy, pProperties.limits.maxSamplerAnisotropy);
		setELitUint32(limits, maxViewports, pProperties.limits.maxViewports);

		Local<v8::ArrayBuffer> ab_maxViewportDimensions{ v8::ArrayBuffer::New(isolate, 8) };
		Local<v8::Uint32Array> maxViewportDimensions{ v8::Uint32Array::New(ab_maxViewportDimensions, 0, 2) };
		setELitValue(limits, maxViewportDimensions, maxViewportDimensions);
		setIndexUint32(maxViewportDimensions, 0, pProperties.limits.maxViewportDimensions[0]);
		setIndexUint32(maxViewportDimensions, 1, pProperties.limits.maxViewportDimensions[1]);

		Local<v8::ArrayBuffer> ab_viewportBoundsRange{ v8::ArrayBuffer::New(isolate, 8) };
		Local<v8::Float32Array> viewportBoundsRange{ v8::Float32Array::New(ab_viewportBoundsRange, 0, 2) };
		setELitValue(limits, viewportBoundsRange, viewportBoundsRange);
		setIndexFloat64(viewportBoundsRange, 0, pProperties.limits.viewportBoundsRange[0]);
		setIndexFloat64(viewportBoundsRange, 1, pProperties.limits.viewportBoundsRange[1]);

		setELitUint32(limits, viewportSubPixelBits, pProperties.limits.viewportSubPixelBits);
		setELitFloat64(limits, minMemoryMapAlignment, static_cast<double_t>(pProperties.limits.minMemoryMapAlignment));
		setELitFloat64(limits, minTexelBufferOffsetAlignment, static_cast<double_t>(pProperties.limits.minTexelBufferOffsetAlignment));
		setELitFloat64(limits, minUniformBufferOffsetAlignment, static_cast<double_t>(pProperties.limits.minUniformBufferOffsetAlignment));
		setELitFloat64(limits, minStorageBufferOffsetAlignment, static_cast<double_t>(pProperties.limits.minStorageBufferOffsetAlignment));
		setELitInt32(limits, minTexelOffset, pProperties.limits.minTexelOffset);
		setELitUint32(limits, maxTexelOffset, pProperties.limits.maxTexelOffset);
		setELitInt32(limits, minTexelGatherOffset, pProperties.limits.minTexelGatherOffset);
		setELitUint32(limits, maxTexelGatherOffset, pProperties.limits.maxTexelGatherOffset);
		setELitFloat64(limits, minInterpolationOffset, pProperties.limits.minInterpolationOffset);
		setELitFloat64(limits, maxInterpolationOffset, pProperties.limits.maxInterpolationOffset);
		setELitUint32(limits, subPixelInterpolationOffsetBits, pProperties.limits.subPixelInterpolationOffsetBits);
		setELitUint32(limits, maxFramebufferWidth, pProperties.limits.maxFramebufferWidth);
		setELitUint32(limits, maxFramebufferHeight, pProperties.limits.maxFramebufferHeight);
		setELitUint32(limits, maxFramebufferLayers, pProperties.limits.maxFramebufferLayers);
		setELitUint32(limits, framebufferColorSampleCounts, pProperties.limits.framebufferColorSampleCounts);
		setELitUint32(limits, framebufferDepthSampleCounts, pProperties.limits.framebufferDepthSampleCounts);
		setELitUint32(limits, framebufferStencilSampleCounts, pProperties.limits.framebufferStencilSampleCounts);
		setELitUint32(limits, framebufferNoAttachmentsSampleCounts, pProperties.limits.framebufferNoAttachmentsSampleCounts);
		setELitUint32(limits, maxColorAttachments, pProperties.limits.maxColorAttachments);
		setELitUint32(limits, sampledImageColorSampleCounts, pProperties.limits.sampledImageColorSampleCounts);
		setELitUint32(limits, sampledImageIntegerSampleCounts, pProperties.limits.sampledImageIntegerSampleCounts);
		setELitUint32(limits, sampledImageDepthSampleCounts, pProperties.limits.sampledImageDepthSampleCounts);
		setELitUint32(limits, sampledImageStencilSampleCounts, pProperties.limits.sampledImageStencilSampleCounts);
		setELitUint32(limits, storageImageSampleCounts, pProperties.limits.storageImageSampleCounts);
		setELitUint32(limits, maxSampleMaskWords, pProperties.limits.maxSampleMaskWords);
		setELitUint32(limits, timestampComputeAndGraphics, pProperties.limits.timestampComputeAndGraphics);
		setELitFloat64(limits, timestampPeriod, pProperties.limits.timestampPeriod);
		setELitUint32(limits, maxClipDistances, pProperties.limits.maxClipDistances);
		setELitUint32(limits, maxCullDistances, pProperties.limits.maxCullDistances);
		setELitUint32(limits, maxCombinedClipAndCullDistances, pProperties.limits.maxCombinedClipAndCullDistances);
		setELitUint32(limits, discreteQueuePriorities, pProperties.limits.discreteQueuePriorities);

		Local<v8::ArrayBuffer> ab_pointSizeRange{ v8::ArrayBuffer::New(isolate, 8) };
		Local<v8::Float32Array> pointSizeRange{ v8::Float32Array::New(ab_pointSizeRange, 0, 2) };
		setELitValue(limits, pointSizeRange, pointSizeRange);
		setIndexFloat64(pointSizeRange, 0, pProperties.limits.pointSizeRange[0]);
		setIndexFloat64(pointSizeRange, 1, pProperties.limits.pointSizeRange[1]);

		Local<v8::ArrayBuffer> ab_lineWidthRange{ v8::ArrayBuffer::New(isolate, 8) };
		Local<v8::Float32Array> lineWidthRange{ v8::Float32Array::New(ab_lineWidthRange, 0, 2) };
		setELitValue(limits, lineWidthRange, lineWidthRange);
		setIndexFloat64(lineWidthRange, 0, pProperties.limits.lineWidthRange[0]);
		setIndexFloat64(lineWidthRange, 1, pProperties.limits.lineWidthRange[1]);

		setELitFloat64(limits, pointSizeGranularity, pProperties.limits.pointSizeGranularity);
		setELitFloat64(limits, lineWidthGranularity, pProperties.limits.lineWidthGranularity);
		setELitUint32(limits, strictLines, pProperties.limits.strictLines);
		setELitUint32(limits, standardSampleLocations, pProperties.limits.standardSampleLocations);
		setELitFloat64(limits, optimalBufferCopyOffsetAlignment, static_cast<double_t>(pProperties.limits.optimalBufferCopyOffsetAlignment));
		setELitFloat64(limits, optimalBufferCopyRowPitchAlignment, static_cast<double_t>(pProperties.limits.optimalBufferCopyRowPitchAlignment));
		setELitFloat64(limits, nonCoherentAtomSize, static_cast<double_t>(pProperties.limits.nonCoherentAtomSize));


		Local<Object> sparseProperties{ Object::New(isolate) };
		setELitValue(properties, sparseProperties, sparseProperties);

		setELitUint32(sparseProperties, residencyStandard2DBlockShape, pProperties.sparseProperties.residencyStandard2DBlockShape);
		setELitUint32(sparseProperties, residencyStandard2DMultisampleBlockShape, pProperties.sparseProperties.residencyStandard2DMultisampleBlockShape);
		setELitUint32(sparseProperties, residencyStandard3DBlockShape, pProperties.sparseProperties.residencyStandard3DBlockShape);
		setELitUint32(sparseProperties, residencyAlignedMipSize, pProperties.sparseProperties.residencyAlignedMipSize);
		setELitUint32(sparseProperties, residencyNonResidentStrict, pProperties.sparseProperties.residencyNonResidentStrict);


		uint32_t pQueueFamilyPropertyCount{ 0 };
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &pQueueFamilyPropertyCount, nullptr);

		std::vector<VkQueueFamilyProperties> pQueueFamilyProperties;
		pQueueFamilyProperties.resize(pQueueFamilyPropertyCount);

		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &pQueueFamilyPropertyCount, pQueueFamilyProperties.data());
		Local<Array> aQueueFamilyProperties{ Array::New(isolate, pQueueFamilyPropertyCount) };
		for (int32_t index{ 0 }; index < SafeInt<int32_t>(pQueueFamilyPropertyCount); index++) {
			Local<Object> nProps{ Object::New(isolate) };
			setELitUint32(nProps, queueFlags, pQueueFamilyProperties[index].queueFlags);
			setELitUint32(nProps, queueCount, pQueueFamilyProperties[index].queueCount);
			setELitUint32(nProps, timestampValidBits, pQueueFamilyProperties[index].timestampValidBits);

			Local<Object> minImageTransferGranularity{ Object::New(isolate) };
			setELitUint32(minImageTransferGranularity, width, pQueueFamilyProperties[index].minImageTransferGranularity.width);
			setELitUint32(minImageTransferGranularity, height, pQueueFamilyProperties[index].minImageTransferGranularity.height);
			setELitUint32(minImageTransferGranularity, depth, pQueueFamilyProperties[index].minImageTransferGranularity.depth);
			setELitValue(nProps, minImageTransferGranularity, minImageTransferGranularity);

			setIndexValue(aQueueFamilyProperties, index, nProps);
		}

		setELitValue(args.This(), queueFamilyProperties, aQueueFamilyProperties);







		VkPhysicalDeviceMemoryProperties props{ 0 };
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &props);

		Local<Object> memoryProperties{ Object::New(isolate) };;
		Local<Array> memoryTypes{ Array::New(isolate, props.memoryTypeCount) };
		Local<Array> memoryHeaps{ Array::New(isolate, props.memoryHeapCount) };
		setELitValue(memoryProperties, memoryTypes, memoryTypes);
		setELitValue(memoryProperties, memoryHeaps, memoryHeaps);

		for (int32_t index{ 0 }; index < SafeInt<int32_t>(props.memoryTypeCount); index++) {
			Local<Object> nProps{ Object::New(isolate) };
			setELitUint32(nProps, propertyFlags, props.memoryTypes[index].propertyFlags);
			setELitUint32(nProps, heapIndex, props.memoryTypes[index].heapIndex);
			setIndexValue(memoryTypes, index, nProps);
		}

		for (int32_t index{ 0 }; index < SafeInt<int32_t>(props.memoryHeapCount); index++) {
			Local<Object> nProps{ Object::New(isolate) };
			setELitValue(nProps, size, Number::New(isolate, static_cast<double_t>(props.memoryHeaps[index].size)));
			setELitUint32(nProps, flags, props.memoryHeaps[index].flags);
			setIndexValue(memoryHeaps, index, nProps);
		}

		setELitValue(args.This(), memoryProperties, memoryProperties);


		VkPhysicalDeviceFeatures pdfeatures{ 0 };
		vkGetPhysicalDeviceFeatures(physicalDevice, &pdfeatures);
		Local<Object> features{ Object::New(isolate) };
		setELitValue(args.This(), features, features);

		setELitUint32(features, robustBufferAccess, pdfeatures.robustBufferAccess);
		setELitUint32(features, fullDrawIndexUint32, pdfeatures.fullDrawIndexUint32);
		setELitUint32(features, imageCubeArray, pdfeatures.imageCubeArray);
		setELitUint32(features, independentBlend, pdfeatures.independentBlend);
		setELitUint32(features, geometryShader, pdfeatures.geometryShader);
		setELitUint32(features, tessellationShader, pdfeatures.tessellationShader);
		setELitUint32(features, sampleRateShading, pdfeatures.sampleRateShading);
		setELitUint32(features, dualSrcBlend, pdfeatures.dualSrcBlend);
		setELitUint32(features, logicOp, pdfeatures.logicOp);
		setELitUint32(features, multiDrawIndirect, pdfeatures.multiDrawIndirect);
		setELitUint32(features, drawIndirectFirstInstance, pdfeatures.drawIndirectFirstInstance);
		setELitUint32(features, depthClamp, pdfeatures.depthClamp);
		setELitUint32(features, depthBiasClamp, pdfeatures.depthBiasClamp);
		setELitUint32(features, fillModeNonSolid, pdfeatures.fillModeNonSolid);
		setELitUint32(features, depthBounds, pdfeatures.depthBounds);
		setELitUint32(features, wideLines, pdfeatures.wideLines);
		setELitUint32(features, largePoints, pdfeatures.largePoints);
		setELitUint32(features, alphaToOne, pdfeatures.alphaToOne);
		setELitUint32(features, multiViewport, pdfeatures.multiViewport);
		setELitUint32(features, samplerAnisotropy, pdfeatures.samplerAnisotropy);
		setELitUint32(features, textureCompressionETC2, pdfeatures.textureCompressionETC2);
		setELitUint32(features, textureCompressionASTC_LDR, pdfeatures.textureCompressionASTC_LDR);
		setELitUint32(features, textureCompressionBC, pdfeatures.textureCompressionBC);
		setELitUint32(features, occlusionQueryPrecise, pdfeatures.occlusionQueryPrecise);
		setELitUint32(features, pipelineStatisticsQuery, pdfeatures.pipelineStatisticsQuery);
		setELitUint32(features, vertexPipelineStoresAndAtomics, pdfeatures.vertexPipelineStoresAndAtomics);
		setELitUint32(features, fragmentStoresAndAtomics, pdfeatures.fragmentStoresAndAtomics);
		setELitUint32(features, shaderTessellationAndGeometryPointSize, pdfeatures.shaderTessellationAndGeometryPointSize);
		setELitUint32(features, shaderImageGatherExtended, pdfeatures.shaderImageGatherExtended);
		setELitUint32(features, shaderStorageImageExtendedFormats, pdfeatures.shaderStorageImageExtendedFormats);
		setELitUint32(features, shaderStorageImageMultisample, pdfeatures.shaderStorageImageMultisample);
		setELitUint32(features, shaderStorageImageReadWithoutFormat, pdfeatures.shaderStorageImageReadWithoutFormat);
		setELitUint32(features, shaderStorageImageWriteWithoutFormat, pdfeatures.shaderStorageImageWriteWithoutFormat);
		setELitUint32(features, shaderUniformBufferArrayDynamicIndexing, pdfeatures.shaderUniformBufferArrayDynamicIndexing);
		setELitUint32(features, shaderSampledImageArrayDynamicIndexing, pdfeatures.shaderSampledImageArrayDynamicIndexing);
		setELitUint32(features, shaderStorageBufferArrayDynamicIndexing, pdfeatures.shaderStorageBufferArrayDynamicIndexing);
		setELitUint32(features, shaderStorageImageArrayDynamicIndexing, pdfeatures.shaderStorageImageArrayDynamicIndexing);
		setELitUint32(features, shaderClipDistance, pdfeatures.shaderClipDistance);
		setELitUint32(features, shaderCullDistance, pdfeatures.shaderCullDistance);
		setELitUint32(features, shaderFloat64, pdfeatures.shaderFloat64);
		setELitUint32(features, shaderInt64, pdfeatures.shaderInt64);
		setELitUint32(features, shaderInt16, pdfeatures.shaderInt16);
		setELitUint32(features, shaderResourceResidency, pdfeatures.shaderResourceResidency);
		setELitUint32(features, shaderResourceMinLod, pdfeatures.shaderResourceMinLod);
		setELitUint32(features, sparseBinding, pdfeatures.sparseBinding);
		setELitUint32(features, sparseResidencyBuffer, pdfeatures.sparseResidencyBuffer);
		setELitUint32(features, sparseResidencyImage2D, pdfeatures.sparseResidencyImage2D);
		setELitUint32(features, sparseResidencyImage3D, pdfeatures.sparseResidencyImage3D);
		setELitUint32(features, sparseResidency2Samples, pdfeatures.sparseResidency2Samples);
		setELitUint32(features, sparseResidency4Samples, pdfeatures.sparseResidency4Samples);
		setELitUint32(features, sparseResidency8Samples, pdfeatures.sparseResidency8Samples);
		setELitUint32(features, sparseResidency16Samples, pdfeatures.sparseResidency16Samples);
		setELitUint32(features, sparseResidencyAliased, pdfeatures.sparseResidencyAliased);
		setELitUint32(features, variableMultisampleRate, pdfeatures.variableMultisampleRate);
		setELitUint32(features, inheritedQueries, pdfeatures.inheritedQueries);
	}

	PhysicalDevice::~PhysicalDevice() {
		puts("PhysicalDevice::~PhysicalDevice()");
	}

	std::vector<float_t> getArgAsVectorOfFloats(const Local<Array>& arr) {
		std::vector<float_t> ret;
		const uint32_t len = arr->Length();
		ret.resize(len);
		for (uint32_t index{ 0 }; index < len; index++) {
			ret[index] = static_cast<float_t>(arr->Get(index)->NumberValue());
		}
		return ret;
	}

	void PhysicalDevice::createDevice(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		std::vector<float_t> pQueuePriorities = getArgAsVectorOfFloats(get_args_n_Elit_as_Array(0, queuePriorities));
		std::array<VkDeviceQueueCreateInfo, 1> queueCreateInfo{
			{
				VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
				nullptr,
			0,
			get_args_n_Elit_as_Uint32(0, queueFamilyIndex),
			get_args_n_Elit_as_Uint32(0, queueCount),
			pQueuePriorities.data()
			}
		};

		VkPhysicalDeviceFeatures deviceFeatures{ 0 };
		VkDeviceCreateInfo info{
			VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			nullptr,
			0,
			SafeInt<uint32_t>(queueCreateInfo.size()),
			queueCreateInfo.data(),
			0,
			nullptr,
			0,
			nullptr,
			&deviceFeatures };

		auto physicalDevice = ObjectWrap::Unwrap<PhysicalDevice>(args.Holder());

		VkDevice device{ nullptr };
		const auto status = vkCreateDevice(physicalDevice->physicalDevice, &info, nullptr, &device);

		Local<Object> ret{ Object::New(isolate) };
	//setELitInt32(ret, status, status);
	//printf("device: %I64u (0x%I64x)\n", (int64_t)device, (int64_t)device);
	//setELitPtr(ret, device, device);
	//args.GetReturnValue().Set(ret);

		std::array<Local<Value>, 2> argv{ args.This(), Number::New(isolate, ptr_to_double(device)) };
		Local<Function> DeviceConstructor = Local<Function>::New(isolate, Device::constructor);
		Local<Object> Device = DeviceConstructor->NewInstance(SafeInt<int>(argv.size()), argv.data());
		args.GetReturnValue().Set(Device);
	}

	void PhysicalDevice::getMemoryProperties(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		auto physicalDevice = ObjectWrap::Unwrap<PhysicalDevice>(args.Holder());
		VkPhysicalDeviceMemoryProperties props{0};
		vkGetPhysicalDeviceMemoryProperties(physicalDevice->physicalDevice, &props);

		Local<Object> ret{ Object::New(isolate) };;
		Local<Array> memoryTypes{ Array::New(isolate, props.memoryTypeCount) };
		Local<Array> memoryHeaps{ Array::New(isolate, props.memoryHeapCount) };
		setELitValue(ret, memoryTypes, memoryTypes);
		setELitValue(ret, memoryHeaps, memoryHeaps);

		for (int32_t index{ 0 }; index < SafeInt<int32_t>(props.memoryTypeCount); index++) {
			Local<Object> nProps{ Object::New(isolate) };
			setELitUint32(nProps, propertyFlags, props.memoryTypes[index].propertyFlags);
			setELitUint32(nProps, heapIndex, props.memoryTypes[index].heapIndex);
			setIndexValue(memoryTypes, index, nProps);
		}

		for (int32_t index{ 0 }; index < SafeInt<int32_t>(props.memoryHeapCount); index++) {
			Local<Object> nProps{ Object::New(isolate) };
			setELitValue(nProps, size, Number::New(isolate, static_cast<double_t>(props.memoryHeaps[index].size)));
			setELitUint32(nProps, flags, props.memoryHeaps[index].flags);
			setIndexValue(memoryHeaps, index, nProps);
		}

		args.GetReturnValue().Set(ret);
	}

	void PhysicalDevice::getWin32PresentationSupportKHR(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		auto physicalDevice = ObjectWrap::Unwrap<PhysicalDevice>(args.Holder());
		args.GetReturnValue().Set(ObjectWrap::Unwrap<Instance>(Local<Object>::New(isolate, physicalDevice->instance))->vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice->physicalDevice, 0));
	}

	void PhysicalDevice::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		HandleScope handle_scope(isolate);

		if (args.IsConstructCall()) {
			// Invoked as constructor: `new MyObject(...)`
			PhysicalDevice* obj = new PhysicalDevice(args);
			args.GetReturnValue().Set(args.This());
		}
		else {
			// Invoked as plain function `MyObject(...)`, turn into construct call.
			std::array<Local<Value>, 1> argv{ args[0] };
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
		}
	}

	void PhysicalDevice::getQueueFamilyProperties(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();
		PhysicalDevice* physicalDevice = ObjectWrap::Unwrap<PhysicalDevice>(args.Holder());

		uint32_t pQueueFamilyPropertyCount{ 0 };
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice->physicalDevice, &pQueueFamilyPropertyCount, nullptr);

		std::vector<VkQueueFamilyProperties> pQueueFamilyProperties;
		pQueueFamilyProperties.resize(pQueueFamilyPropertyCount);

		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice->physicalDevice, &pQueueFamilyPropertyCount, pQueueFamilyProperties.data());
		Local<Array> aQueueFamilyProperties{ Array::New(isolate, pQueueFamilyPropertyCount) };
		for (int32_t index{ 0 }; index < SafeInt<int32_t>(pQueueFamilyPropertyCount); index++) {
			Local<Object> nProps{ Object::New(isolate) };
			setELitUint32(nProps, queueFlags, pQueueFamilyProperties[index].queueFlags);
			setELitUint32(nProps, queueCount, pQueueFamilyProperties[index].queueCount);
			setELitUint32(nProps, timestampValidBits, pQueueFamilyProperties[index].timestampValidBits);

			Local<Object> minImageTransferGranularity{ Object::New(isolate) };
			setELitUint32(minImageTransferGranularity, width, pQueueFamilyProperties[index].minImageTransferGranularity.width);
			setELitUint32(minImageTransferGranularity, height, pQueueFamilyProperties[index].minImageTransferGranularity.height);
			setELitUint32(minImageTransferGranularity, depth, pQueueFamilyProperties[index].minImageTransferGranularity.depth);
			setELitValue(nProps, minImageTransferGranularity, minImageTransferGranularity);

			setIndexValue(aQueueFamilyProperties, index, nProps);
		}

		args.GetReturnValue().Set(aQueueFamilyProperties);
	}

}