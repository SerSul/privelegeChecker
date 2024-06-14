#include <napi.h>
#include <windows.h>
#include <lm.h>
#include <string>

#pragma comment(lib, "netapi32.lib")

/*

  USER_PRIV_GUEST     0
  USER_PRIV_USER      1
  USER_PRIV_ADMIN     2

  NetUserGetInfo (
        LPCWSTR    servername OPTIONAL,
        LPCWSTR    username,
        DWORD      level,
        LPBYTE     *bufptr
  );

 */

#define PRIVILEGE_STRINGS {"Пользователь", "Гость", "Администратор"}
#define NET_USER_LEVEL 1
#define NET_API_SUCCESS NERR_Success
#define NET_API_ERROR "нет"

std::wstring Utf8ToWstring(const std::string& str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.data(), str.size(), nullptr, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.data(), str.size(), &wstr[0], size_needed);
    return wstr;
}

Napi::String CheckUserPrivilege(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::wstring wname = Utf8ToWstring(info[0].As<Napi::String>());

    DWORD level = NET_USER_LEVEL;
    LPBYTE buffer = nullptr;
    NET_API_STATUS res = NetUserGetInfo(nullptr, wname.c_str(), level, &buffer);
    if (res == NET_API_SUCCESS) {
        USER_INFO_1* userInfo = reinterpret_cast<USER_INFO_1*>(buffer);
        const char* privilegeStrings[] = PRIVILEGE_STRINGS;
        std::string privilege = privilegeStrings[userInfo->usri1_priv];
        NetApiBufferFree(buffer);
        return Napi::String::New(env, privilege);
    } else {
        return Napi::String::New(env, NET_API_ERROR);
    }
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "checkUserPrivilege"), Napi::Function::New(env, CheckUserPrivilege));
    return exports;
}

NODE_API_MODULE(privilege_check, Init)