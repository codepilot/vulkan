//#include "vulkanDll.h"
#include "vulkan_levels.h"

namespace vulkan_autogen {
	void Init(Local<Object> exports);
}

namespace EternalStrings {
#define createELit(eLit) v8::Eternal<v8::String> es_##eLit;
#include "EternalStrings.h"
#undef createELit
}

namespace {

	using v8::Object;
	using v8::Isolate;
	using v8::HandleScope;
	using v8::Local;
	using v8::String;
	using node::AtExit;

	BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
		switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
		}

		return TRUE;
	}

#ifdef _DEBUG
	static void AtExit_DebugCallback(void*) {
		puts("\n\nAtExit_DebugCallback()\nPress any key to exit...");
		getchar();
	}
#endif

	void Init(Local<Object> exports) {
		Isolate* isolate = Isolate::GetCurrent();
		HandleScope handle_scope(isolate);

		{
#define createELit(eLit) { EternalStrings::es_##eLit.Set(isolate, String::NewFromTwoByte(isolate, ptr_to_ptr<const wchar_t *, const uint16_t *>(L#eLit), v8::String::kInternalizedString)); }
#include "EternalStrings.h"
#undef createELit
		}

	#ifdef _DEBUG
		AtExit(AtExit_DebugCallback);
	#endif
		Local<Object> level_10{ Object::New(isolate) };
		Local<Object> level_20{ Object::New(isolate) };
		Local<Object> vulkan_autogen{ Object::New(isolate) };
		
		setELitValue(exports, level_10, level_10);
		setELitValue(exports, level_20, level_20);
		setELitValue(exports, vulkan_autogen, vulkan_autogen);

		vulkan_level_10::Init(level_10);
		vulkan_level_20::Init(level_20);
		vulkan_autogen::Init(vulkan_autogen);
	//VulkanDll::Init(exports);
	}
	NODE_MODULE(addon, Init)
}