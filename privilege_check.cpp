#include <napi.h>
#include <windows.h>

Napi::String CheckUserPrivilege(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "Expected a string argument").ThrowAsJavaScriptException();
        return Napi::String::New(env, "Error");
    }

    return Napi::String::New(env, "User");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "checkUserPrivilege"), Napi::Function::New(env, CheckUserPrivilege));
    return exports;
}

NODE_API_MODULE(privilege_check, Init)
