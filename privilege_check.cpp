#include <napi.h>
#include <windows.h>
#include <lm.h>
#include <string>

#pragma comment(lib, "netapi32.lib")

Napi::String CheckUserPrivilege(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsString()) {
        Napi::TypeError::New(env, "Expected a string argument").ThrowAsJavaScriptException();
        return Napi::String::New(env, "Error");
    }

    std::string name = info[0].As<Napi::String>().Utf8Value();

    std::wstring wname(name.begin(), name.end());
    LPWSTR username = (LPWSTR)wname.c_str();

    DWORD level = 1;
    LPBYTE buf = nullptr;
    NET_API_STATUS res = NetUserGetInfo(NULL, username, level, &buf);
    if (res == NERR_Success) {
        USER_INFO_1* userInfo = (USER_INFO_1*)buf;
        std::string privilege;
        if (userInfo->usri1_priv == USER_PRIV_ADMIN) {
            privilege = "Администратор";
        } else if (userInfo->usri1_priv == USER_PRIV_GUEST) {
            privilege = "Гость";
        } else {
            privilege = "Пользователь";
        }
        NetApiBufferFree(buf); 
        return Napi::String::New(env, privilege);
    } else {
        return Napi::String::New(env, "нет");
    }
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "checkUserPrivilege"), Napi::Function::New(env, CheckUserPrivilege));
    return exports;
}

NODE_API_MODULE(privilege_check, Init)
