"use strict";

fs = require 'fs'
util = require 'util'

inspectObj = {showHidden: true, depth: null, colors: true}

console.inspect = (item)-> console.dir item, inspectObj

vk = JSON.parse(fs.readFileSync('vk.xml.json', 'utf-8'))

handle_childNodes_nodeName = (parentNode, objHandlers)->
	parentNode.childNodes?.forEach (v2, i2, a2)->
		return if typeof v2 is 'string'
		return if v2.hasOwnProperty 'comment'

		if typeof objHandlers[v2?.nodeName] is 'function'
			objHandlers[v2?.nodeName] v2
		else
			console.log typeof v2, v2?.nodeName, v2

allEnums = Object.create null

getAttributeFromNode = (node, attribute)->
	for attr in node?.attributes
		return attr.value if attr.name is attribute

	#console.log node, attribute
	#throw ''
	return

getNodesByName = (node, nodeName)->
	ret = []
	node.childNodes?.forEach (v, i, a)->
		return if typeof v is 'string'
		return if v.hasOwnProperty 'comment'

		ret.push v if v?.nodeName is nodeName

	return ret
	
getNodesByPath = (parentNode, nodePath)->
	ret = []

	rp = (node, curPath)->
		if curPath is nodePath then ret.push node #else console.log curPath

		node.childNodes?.forEach (v, i, a)->
			#return if typeof v is 'string'
			if [curPath, 'text()'].join('/') is nodePath
				ret.push v
			else if v.hasOwnProperty 'comment'
				return
			else
				rp v, [curPath, v?.nodeName].join('/')

	
	rp(parentNode, '')
	return ret

getNodeText = (node)->
	ret = []
	for kid in node?.childNodes
		if typeof kid is 'string'
			ret.push kid
		else
			ret.push getNodeText kid

	return ret.join('')

managedObjects = {}
vulkanObjects = {}
vulkanCommands = {}
vulkanCommandParams = {}

renameManageObjects =
	ComputePipelines: 'ComputePipeline'
	GraphicsPipelines: 'GraphicsPipeline'
	SharedSwapchainsKHR: 'SharedSwapchainKHR'

regex_vkCreate = /^vkCreate([A-Z].*)$/
regex_vkDestroy = /^vkDestroy([A-Z].*)$/

path_handlers =
	'/registry/commands/command': (node, curPath)->
		#console.log curPath, getNodesByName(getNodesByName(node, 'proto')[0], 'name')
		protoName = getNodesByPath(node, '/proto/name/text()').join('')
		
		vulkanCommands[protoName] = node
		vulkanCommandParams[protoName] = getNodesByPath(node, '/param/type/text()')
		
		switch
			when regex_vkCreate.test protoName
				mo_name = regex_vkCreate.exec(protoName)[1]
				mo_name = renameManageObjects[mo_name] ? mo_name

				vulkanHandleType = getNodesByPath(node, '/param/type/text()').pop()

				managedObjects[mo_name] = Object.create(null) unless managedObjects.hasOwnProperty mo_name
				managedObjects[mo_name].create = node
				managedObjects[mo_name].vulkanHandleType = vulkanHandleType

				vulkanObjects[vulkanHandleType] = Object.create(null) unless vulkanObjects.hasOwnProperty vulkanHandleType
				vulkanObjects[vulkanHandleType].create = node

			when regex_vkDestroy.test protoName
				destroyParams = getNodesByPath(node, '/param/type/text()')
				destroyParams.pop()
				vulkanHandleType = destroyParams.pop()

				mo_name = regex_vkDestroy.exec(protoName)[1]
				mo_name = renameManageObjects[mo_name] ? mo_name

				managedObjects[mo_name] = Object.create(null) unless managedObjects.hasOwnProperty mo_name
				managedObjects[mo_name].destroy = node
				managedObjects[mo_name].vulkanHandleType = vulkanHandleType

				vulkanObjects[vulkanHandleType] = Object.create(null) unless vulkanObjects.hasOwnProperty vulkanHandleType
				vulkanObjects[vulkanHandleType].destroy = node

			#else
			#	console.log protoName, getNodesByPath(node, '/param/type/text()')

	#'/registry/commands/command/proto/name': (node, curPath)-> console.log curPath, getNodeText node
	#'/registry/tags/tag': (node, curPath)-> console.log curPath, node
	#'/registry/vendorids/vendorid': (node, curPath)-> console.log curPath, node
	#'/registry/enums': (node, curPath)-> console.log curPath, node
	'/registry/enums/enum': (node, curPath)->
		if getAttributeFromNode(node, 'value')?
			allEnums[getAttributeFromNode(node, 'name')] = getAttributeFromNode(node, 'value')
		else if getAttributeFromNode(node, 'bitpos')?
			allEnums[getAttributeFromNode(node, 'name')] = '1 << ' + getAttributeFromNode(node, 'bitpos')
		else
			throw JSON.strinify node

recurse_path = (node, curPath)->
	if typeof path_handlers[curPath] is 'function'
		path_handlers[curPath] node, curPath
	#else console.log curPath

	#node.attributes?.forEach (v, i, a)->
	#	recurse_path v, [curPath, v?.name].join('@')

	node.childNodes?.forEach (v, i, a)->
		return if typeof v is 'string'
		return if v.hasOwnProperty 'comment'

		recurse_path v, [curPath, v?.nodeName].join('/')

buildManagedObjects = ->
	vulkan_autogen_cpp = fs.createWriteStream './vulkan_autogen.cpp'
	
	vulkan_autogen_cpp.write """
		#include "vulkan_autogen.h"

		namespace vulkan_autogen {
			void Init(Local<Object> exports) {
				Isolate* isolate = Isolate::GetCurrent();
				HandleScope handle_scope(isolate);


		"""

	autogenHeader = []
	autogenHeader.push """
		#pragma once

		#include <stdexcept>
		#include <vector>
		#include <array>
		#include <safeint.h>
		#include <node.h>
		#include <node_buffer.h>
		#include <node_object_wrap.h>
		#include <uv.h>
		#include <fcntl.h>

		#include <SDKDDKVer.h>
		#define WIN32_LEAN_AND_MEAN
		//#include <windows.h>

		#define VK_USE_PLATFORM_WIN32_KHR 1
		#include <vulkan/vulkan.h>

		using v8::Int32;
		using v8::Uint32;
		using v8::HandleScope;
		using v8::Array;
		using v8::Exception;
		using v8::FunctionCallbackInfo;
		using v8::Persistent;
		using v8::Eternal;

		using v8::FunctionTemplate;
		using v8::Function;
		using v8::Isolate;
		using v8::Local;
		using v8::Number;
		using v8::Object;
		using v8::String;
		using v8::Value;

		using msl::utilities::SafeInt;
		
		template <typename T> double ptr_to_double(T ptr) { return static_cast<double>(reinterpret_cast<int64_t>(ptr)); }
		template <typename T> T double_to_ptr(double dbl) { return reinterpret_cast<T>(static_cast<int64_t>(dbl)); }
		template <typename SrcType, typename DstType> DstType ptr_to_ptr(SrcType srcPtr) { return reinterpret_cast<DstType>(srcPtr); }

		//#define lit2b(lit) String::NewFromTwoByte(isolate, ptr_to_ptr<const wchar_t *, const uint16_t *>(L#lit))
		//#define str2b(str) String::NewFromTwoByte(isolate, ptr_to_ptr<const wchar_t *, const uint16_t *>(L##str))
		//#define setKeyValue(dst, key, val) { dst->Set(str2b(key), val); };
		//#define setKeyInt32(dst, key, val) { setKeyValue(dst, key, Int32::New(isolate, val)); };
		//#define setKeyUint32(dst, key, val) { setKeyValue(dst, key, Uint32::New(isolate, val)); };
		//#define setKeyPtr(dst, key, val) { setKeyValue(dst, key, Number::New(isolate, ptr_to_double(val))); };

		#define setIndexValue(dst, index, val) { dst->Set(index, val); };
		#define setIndexInt32(dst, index, val) { setIndexValue(dst, index, Int32::New(isolate, val)); };
		#define setIndexUint32(dst, index, val) { setIndexValue(dst, index, Uint32::New(isolate, val)); };
		#define setIndexFloat64(dst, index, val) { setIndexValue(dst, index, Number::New(isolate, val)); };
		#define setIndexPtr(dst, index, val) { setIndexValue(dst, index, Number::New(isolate, ptr_to_double(val))); };

		//#define setEternalLit(lit) { EternalStrings::es_##lit.Set(isolate, String::NewFromTwoByte(isolate, ptr_to_ptr<const wchar_t *, const uint16_t *>(L#lit), v8::String::kInternalizedString)); }
		#define getEternalLit(lit) EternalStrings::es_##lit.Get(isolate)

		#define getELitValue(src, eLit) src->Get(getEternalLit(eLit))
		#define getELitValueFromObject(src, eLit) src->ToObject()->Get(getEternalLit(eLit))
		#define getELitValueFromArgN(argN, eLit) args[argN]->ToObject()->Get(getEternalLit(eLit))
		#define getELitObjectFromArgN(argN, eLit) args[argN]->ToObject()->Get(getEternalLit(eLit))->ToObject()

		#define get_args_n_Elit_as_Array(argN, eLit) Local<Array>::Cast(args[argN]->ToObject()->Get(getEternalLit(eLit)))
		#define get_args_n_Elit_as_Uint32(argN, eLit) args[argN]->ToObject()->Get(getEternalLit(eLit))->Uint32Value()

		#define setELitValue(dst, eLit, val) { dst->Set(getEternalLit(eLit), val); };
		#define setELitInt32(dst, eLit, val) { setELitValue(dst, eLit, Int32::New(isolate, val)); };
		#define setELitUint32(dst, eLit, val) { setELitValue(dst, eLit, Uint32::New(isolate, val)); };
		#define setELitFloat64(dst, eLit, val) { setELitValue(dst, eLit, Number::New(isolate, val)); };
		#define setELitPtr(dst, eLit, val) { setELitValue(dst, eLit, Number::New(isolate, ptr_to_double(val))); };


		namespace EternalStrings {
		#define createELit(eLit) extern v8::Eternal<v8::String> es_##eLit;
		#include "../vulkan/EternalStrings.h"
		#undef createELit
		
		}
		#include "./Instance.h"
		#include "./Device.h"
		#include "./PipelineCache.h"
		"""

	for k, v of managedObjects
		switch v.vulkanHandleType
			when 'VkInstance' then continue
			when 'VkDevice', 'VkSurfaceKHR', 'VkDebugReportCallbackEXT'
				v.gpa = 'vkGetInstanceProcAddr(ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle,'
			else
				v.gpa = 'vkGetDeviceProcAddr(ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle,'

	for k, v of managedObjects
		continue unless v.create?
		
		createParams = getNodesByPath(v.create, '/param/type/text()')
		createParamNames = getNodesByPath(v.create, '/param/name/text()')
		#console.log 'v.vulkanHandleType', v.vulkanHandleType
		#console.log 'vulkanObjects[v.vulkanHandleType].destroy', vulkanObjects[v.vulkanHandleType].destroy
		destroyParams = if vulkanObjects[v.vulkanHandleType].destroy? then getNodesByPath(vulkanObjects[v.vulkanHandleType].destroy, '/param/type/text()') else []
	
		
		
		if v.create?
			v.createProc = getNodesByPath(v.create, '/proto/name/text()').join('')

		if vulkanObjects[v.vulkanHandleType].destroy?
			v.destroyProc = getNodesByPath(vulkanObjects[v.vulkanHandleType].destroy, '/proto/name/text()').join('')
		
		createInfos = []
		parentHandleDefinitions = {}
		parentHandleValues = {}
		parentHandleSetups = {}
		ObjectValues = (obj)-> Object.keys(obj).map (k)-> obj[k]

		switch v.vulkanHandleType
			when 'VkInstance' then
			when 'VkDevice', 'VkSurfaceKHR', 'VkDebugReportCallbackEXT'
				parentHandleDefinitions['VkInstance'] = 'v8::UniquePersistent<Object> parent_instance;'
				parentHandleValues['VkInstance'] = 'ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle'
				parentHandleSetups['VkInstance'] = 'parent_instance.Reset(isolate, getELitObjectFromArgN(0, parent_instance));'

			else
				parentHandleDefinitions['VkDevice'] = 'v8::UniquePersistent<Object> parent_device;'
				parentHandleValues['VkDevice'] = 'ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle'
				parentHandleSetups['VkDevice'] = 'parent_device.Reset(isolate, getELitObjectFromArgN(0, parent_device));'
		
		if v.vulkanHandleType is 'VkDevice'
			parentHandleDefinitions['VkInstance'] = 'v8::UniquePersistent<Object> parent_instance;'
			parentHandleValues['VkInstance'] = 'ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle'
		
		createArgs = createParams.map (cp, ci)->
			if v.vulkanHandleType is cp then return '&vulkan_handle'
			if /CreateInfo/.test cp
				createInfos.push '\t\t' + cp + ' ' + createParamNames[ci] + ';\n\t\t' + 'memset(&' + createParamNames[ci] + ', 0, sizeof(' + cp + '));\n\t\t' + createParamNames[ci] + '.sType = ' + createInfoType_to_structureType(cp) + ';'
				return '&' + createParamNames[ci]
			
			switch cp
				when 'VkInstance'
					parentHandleDefinitions[cp] = 'v8::UniquePersistent<Object> parent_instance;'
					parentHandleValues[cp] = 'ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle'
					parentHandleSetups[cp] = 'parent_instance.Reset(isolate, getELitObjectFromArgN(0, parent_instance));'
					return 'ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle'

				when 'VkDevice'
					parentHandleDefinitions[cp] = 'v8::UniquePersistent<Object> parent_device;'
					parentHandleValues[cp] = 'ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle'
					parentHandleSetups[cp] = 'parent_device.Reset(isolate, getELitObjectFromArgN(0, parent_device));'
					return 'ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle'

				when 'VkPhysicalDevice'
					parentHandleDefinitions[cp] = 'VkPhysicalDevice parent_physicalDevice;'
					parentHandleValues[cp] = 'parent_physicalDevice'
					parentHandleSetups[cp] = 'parent_physicalDevice = double_to_ptr<decltype(parent_physicalDevice)>(getELitValueFromArgN(0, parent_device)->NumberValue());'
					return 'parent_physicalDevice'

				when 'VkAllocationCallbacks'
					return 'nullptr'
					
				when 'VkPipelineCache'
					return 'nullptr'
					
				when 'uint32_t'
					return '1'

				else return cp
				
		destroyArgs = destroyParams.map (cp)->
			if v.vulkanHandleType is cp then return 'vulkan_handle'
			switch cp
				when 'VkInstance' then return 'ObjectWrap::Unwrap<Instance>(parent_instance.Get(isolate))->vulkan_handle'
				when 'VkDevice' then return 'ObjectWrap::Unwrap<Device>(parent_device.Get(isolate))->vulkan_handle'
				when 'VkAllocationCallbacks' then return 'nullptr'
				else return cp

		autogenHeader.push("#include \"./#{k}.h\"")

		fs.writeFileSync """./#{k}.h""",
			"""#pragma once

			#{if v.createProc? and protectedCommands[v.createProc]? then '#ifdef ' + protectedCommands[v.createProc] else ''}
			#{if v.vulkanHandleType is 'VkDisplayModeKHR' then '#if 0 //VkDisplayModeKHR' else ''}

			namespace vulkan_autogen {
				class #{k} : public node::ObjectWrap {
				public:
					static Eternal<Function> constructor;
					#{ v.vulkanHandleType } vulkan_handle{ nullptr };
					
					#{ObjectValues(parentHandleDefinitions).join('\n\t\t')}
					
					static void Init(Isolate* isolate);
					static void New(const FunctionCallbackInfo<Value>& args);
					static void NewInstance(const FunctionCallbackInfo<Value>& args);
					#{if v.gpa? and v.createProc? then 'PFN_' + v.createProc + ' ' + v.createProc + ';' else ''}
					#{if v.gpa? and v.destroyProc? then 'PFN_' + v.destroyProc + ' ' + v.destroyProc + ';' else ''}
					#{k}(const FunctionCallbackInfo<Value>& args);
					~#{k}();
				};
			}

			#{if v.createProc? and protectedCommands[v.createProc]? then '#endif // ' + protectedCommands[v.createProc] else ''}
			#{if v.vulkanHandleType is 'VkDisplayModeKHR' then '#endif //VkDisplayModeKHR' else ''}
			"""

		if v.createProc? and protectedCommands[v.createProc]?
			vulkan_autogen_cpp.write '\n#ifdef ' + protectedCommands[v.createProc] + '\n'
		else if v.vulkanHandleType is 'VkDisplayModeKHR'
			vulkan_autogen_cpp.write '\n#if 0 // ' + v.vulkanHandleType + '\n'

		vulkan_autogen_cpp.write "\t\t#{k}::Init(isolate);\n"

		if v.createProc? and protectedCommands[v.createProc]?
			vulkan_autogen_cpp.write '#endif // ' + protectedCommands[v.createProc] + '\n\n'
		else if v.vulkanHandleType is 'VkDisplayModeKHR'
			vulkan_autogen_cpp.write '#endif // ' + v.vulkanHandleType + '\n\n'

		fs.writeFileSync """./#{k}.cpp""",
			"""#include "vulkan_autogen.h"

				#{if v.createProc? and protectedCommands[v.createProc]? then '#ifdef ' + protectedCommands[v.createProc] else ''}
				#{if v.vulkanHandleType is 'VkDisplayModeKHR' then '#if 0 //VkDisplayModeKHR' else ''}

				namespace vulkan_autogen {
					Eternal<Function> #{k}::constructor;

					void #{k}::Init(Isolate* isolate) {
						Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
						tpl->SetClassName(String::NewFromUtf8(isolate, "Vulkan::#{k}"));
						tpl->InstanceTemplate()->SetInternalFieldCount(1);

						//NODE_SET_PROTOTYPE_METHOD(tpl, "getMemoryProperties", getMemoryProperties);

						constructor.Set(isolate, tpl->GetFunction());
					}

					void #{k}::NewInstance(const FunctionCallbackInfo<Value>& args) {
						Isolate* isolate = args.GetIsolate();
						HandleScope handle_scope(isolate);

						std::array<Local<Value>, 1> argv{ args[0] };
						Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
						Local<Object> instance = cons->NewInstance(SafeInt<int>(argv.size()), argv.data());

						args.GetReturnValue().Set(instance);
					}

					#{k}::#{k}(const FunctionCallbackInfo<Value>& args) {
						Isolate* isolate = args.GetIsolate();
						HandleScope handle_scope(isolate);

						Wrap(args.This());

						#{ObjectValues(parentHandleSetups).join('\n\t\t')}
						
						#{if v.gpa? and v.createProc? then v.createProc + ' = reinterpret_cast<PFN_' + v.createProc + '>(' + v.gpa + '"' + v.createProc + '"));' else ''}
						#{if v.gpa? and v.destroyProc? then v.destroyProc + ' = reinterpret_cast<PFN_' + v.destroyProc + '>(' + v.gpa + '"' + v.destroyProc + '"));' else ''}
					
						#{createInfos.join('')}
						#{if v.create? then v.createProc else '//NO_CREATE'}(#{createArgs.join(', ')});

						setELitPtr(args.This(), vulkan_handle, vulkan_handle);

					}

					#{k}::~#{k}() {
						Isolate* isolate = Isolate::GetCurrent();
						HandleScope handle_scope(isolate);

						puts("#{k}::~#{k}()");

						#{if destroyArgs.length is 0 then '//NO_DESTROY ' else ''}#{if vulkanObjects[v.vulkanHandleType].destroy? then v.destroyProc else ''}(#{destroyArgs.join(', ')});
						
					}

					void #{k}::New(const FunctionCallbackInfo<Value>& args) {
						Isolate* isolate = args.GetIsolate();
						HandleScope handle_scope(isolate);

						if (args.IsConstructCall()) {
							#{k}* obj = new #{k}(args);
							args.GetReturnValue().Set(args.This());
						}
						else {
							std::array<Local<Value>, 1> argv{ args[0] };
							Local<Function> cons = Local<Function>::New(isolate, constructor.Get(isolate));
							args.GetReturnValue().Set(cons->NewInstance(SafeInt<int>(argv.size()), argv.data()));
						}
					}
				}
				
				#{if v.createProc? and protectedCommands[v.createProc]? then '#endif // ' + protectedCommands[v.createProc] else ''}
				#{if v.vulkanHandleType is 'VkDisplayModeKHR' then '#endif //VkDisplayModeKHR' else ''}
				"""

	fs.writeFileSync './vulkan_autogen.h', autogenHeader.join('\n')

	vulkan_autogen_cpp.write """
				Instance::Init(isolate);
				exports->Set(String::NewFromUtf8(isolate, "Instance"), Local<Function>::New(isolate, Instance::constructor.Get(isolate)));
			}
		}"""

vk.forEach (v, i, a)-> recurse_path v, '/' + v?.nodeName

#console.log getNodesByPath(vk[0], '/commands/command/proto/name/text()')

protectedCommands = {}
getNodesByPath(vk[0], '/extensions/extension').forEach (extensionNode)->
	def = getAttributeFromNode(extensionNode, 'protect')
	return unless def?
	#console.log def
	getNodesByPath(extensionNode, '/require/command').forEach (commandNode)->
		cmd = getAttributeFromNode(commandNode, 'name')
		protectedCommands[cmd] = def

#console.log protectedCommands
###
        <extension name="VK_KHR_android_surface" number="9" protect="VK_USE_PLATFORM_ANDROID_KHR" supported="vulkan">
            <require>
                <enum value="6"                                         name="VK_KHR_ANDROID_SURFACE_SPEC_VERSION"/>
                <enum value="&quot;VK_KHR_android_surface&quot;"        name="VK_KHR_ANDROID_SURFACE_EXTENSION_NAME"/>
                <enum offset="0" extends="VkStructureType"              name="VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR"/>
                <type name="VkAndroidSurfaceCreateFlagsKHR"/>
                <type name="VkAndroidSurfaceCreateInfoKHR"/>
                <command name="vkCreateAndroidSurfaceKHR"/>
            </require>
        </extension>
###

#fs.writeFileSync './allEnums.json', JSON.stringify(allEnums, null, '  ')
#fs.writeFileSync './managedObjects.json', JSON.stringify(managedObjects, null, '  ')
#fs.writeFileSync './vulkanObjects.json', JSON.stringify(vulkanObjects, null, '  ')

#fs.writeFileSync './vulkanCommands.json', JSON.stringify(vulkanCommands, null, '  ')
#fs.writeFileSync './vulkanCommandParams.json', JSON.stringify(vulkanCommandParams, null, '  ')

camelCaseToUpperCase = (str)->
	rePart = /[A-Z0-9][a-z]+/g
	return loop
		result = rePart.exec str
		break unless result?
		result[0]
	
createInfoType_to_structureType = (str)->
	return 'VK_STRUCTURE_TYPE_' + camelCaseToUpperCase('VkDeviceCreateInfo').slice(1).map((part)-> part.toUpperCase()).join('_')

buildManagedObjects()

