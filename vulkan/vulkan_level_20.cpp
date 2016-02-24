#include "vulkan_levels.h"

namespace vulkan_level_20 {
	void Init(Local<Object> exports) {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		Instance::Init(isolate);
		PhysicalDevice::Init(isolate);

		exports->Set(String::NewFromUtf8(isolate, "Instance"), Local<Function>::New(isolate, Instance::constructor));
	}

}

/*
Directory of C:\VulkanSDK\1.0.3.1\Demos\Win32\Debug

02/15/2016  03:26 PM           253,208 vulkan-1.dll
1 File(s)        253,208 bytes

Directory of C:\VulkanSDK\1.0.3.1\Demos\x64\Debug

02/15/2016  03:26 PM           309,016 vulkan-1.dll
1 File(s)        309,016 bytes

Directory of C:\VulkanSDK\1.0.3.1\Source\lib

02/15/2016  03:26 PM           309,016 vulkan-1.dll
1 File(s)        309,016 bytes

Directory of C:\VulkanSDK\1.0.3.1\Source\lib32

02/15/2016  03:26 PM           253,208 vulkan-1.dll
1 File(s)        253,208 bytes

Directory of C:\Windows\System32

02/13/2016  05:46 PM           126,232 vulkan-1-1-0-3-0.dll
02/15/2016  03:26 PM           126,232 vulkan-1-1-0-3-1.dll
02/15/2016  03:26 PM           126,232 vulkan-1.dll
3 File(s)        378,696 bytes

Directory of C:\Windows\SysWOW64

02/13/2016  05:47 PM           125,720 vulkan-1-1-0-3-0.dll
02/15/2016  03:27 PM           125,720 vulkan-1-1-0-3-1.dll
02/15/2016  03:27 PM           125,720 vulkan-1.dll
3 File(s)        377,160 bytes

*/