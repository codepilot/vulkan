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

#define setIndexValue(dst, key, val) { dst->Set(index, val); };
#define setIndexPtr(dst, index, val) { setIndexValue(dst, key, Number::New(isolate, ptr_to_double(val))); };

//#define setEternalLit(lit) { EternalStrings::es_##lit.Set(isolate, String::NewFromTwoByte(isolate, ptr_to_ptr<const wchar_t *, const uint16_t *>(L#lit), v8::String::kInternalizedString)); }
#define getEternalLit(lit) EternalStrings::es_##lit.Get(isolate)

#define getELitValue(src, eLit) src->Get(getEternalLit(eLit))
#define getELitValueFromObject(src, eLit) src->ToObject()->Get(getEternalLit(eLit))
#define getELitValueFromArgN(argN, eLit) args[argN]->ToObject()->Get(getEternalLit(eLit))

#define get_args_n_Elit_as_Array(argN, eLit) Local<Array>::Cast(args[argN]->ToObject()->Get(getEternalLit(eLit)))
#define get_args_n_Elit_as_Uint32(argN, eLit) args[argN]->ToObject()->Get(getEternalLit(eLit))->Uint32Value()

#define setELitValue(dst, eLit, val) { dst->Set(getEternalLit(eLit), val); };
#define setELitInt32(dst, eLit, val) { setELitValue(dst, eLit, Int32::New(isolate, val)); };
#define setELitUint32(dst, eLit, val) { setELitValue(dst, eLit, Uint32::New(isolate, val)); };
#define setELitPtr(dst, eLit, val) { setELitValue(dst, eLit, Number::New(isolate, ptr_to_double(val))); };


namespace EternalStrings {
#define createELit(eLit) extern v8::Eternal<v8::String> es_##eLit;
#include "EternalStrings.h"
#undef createELit
}


#include "vulkan_level_10.h"
#include "vulkan_level_20.h"
