#include <node.h>

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "vulkan_level_10.h"

namespace {
	using v8::Object;
	using v8::Isolate;
	using v8::HandleScope;
	using v8::Local;
	using v8::String;
	using node::AtExit;

#define setKeyValue(dst, key, val) { dst->Set(String::NewFromTwoByte(isolate, reinterpret_cast<const uint16_t *>(TEXT(key))), val); };
#define setKeyInt32(dst, key, val) { setKeyValue(dst, key, Int32::New(isolate, val)); };
#define setKeyPtr(dst, key, val) { setKeyValue(dst, key, Number::New(isolate, ptr_to_double(val))); };

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

	#ifdef _DEBUG
		AtExit(AtExit_DebugCallback);
	#endif
		Local<Object> level_10{ Object::New(isolate) };
		setKeyValue(exports, "level_10", level_10);
		vulkan_level_10::Init(level_10);
	}
	NODE_MODULE(addon, Init)
}