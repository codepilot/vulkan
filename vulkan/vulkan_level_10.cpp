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
#include <windows.h>

#pragma comment(lib, "node.lib")

namespace {
	using v8::Uint32;
	using v8::HandleScope;
	using v8::Array;
	using v8::Exception;
	using v8::FunctionCallbackInfo;
	using v8::Persistent;

	using v8::FunctionTemplate;
	using v8::Function;
	using v8::Isolate;
	using v8::Local;
	using v8::Number;
	using v8::Object;
	using v8::String;
	using v8::Value;

	using msl::utilities::SafeInt;

	using node::AtExit;

#ifdef _DEBUG
	static void AtExit_DebugCallback(void*) {
		puts("\n\nAtExit_DebugCallback()\nPress any key to exit...");
		getchar();
	}
#endif

	void Init(Local<Object> exports) {
#ifdef _DEBUG
		AtExit(AtExit_DebugCallback);
#endif
	}
	NODE_MODULE(addon, Init)
}