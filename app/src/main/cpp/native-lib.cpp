#include <jni.h>
#include "BNM/Loading.hpp"
#include "include/Menu/ModMenu.hpp"
#include "BNM/UnityStructures.hpp"
#include "BNM/Method.hpp"
#include "BNM/Class.hpp"
#include "BNMResolve.hpp"
#include "BNM/Il2CppHeaders.hpp"
#include <BNMIncludes.hpp>
#include <NotiLib/NotiLib.hpp>
#include <httplib.h>
#include <json.hpp>
#include <random>
#include <string>
#include <BNM/Class.hpp>
#include <BNM/Method.hpp>
#include <BNM/Field.hpp>

//----- Variables -----\\-
//Methods -----

void (*Awake)(void*);
void new_Awake(void* instance) {
    Awake(instance);
    ModMenu::Init();

    BNM_LOG_INFO("Menu Initialization Called");
}

bool isUpdated = true;
void (*LateUpdate)(void*);
void new_LateUpdate(void* instance) {
    LateUpdate(instance);
    ModMenu::Update();

    if (isUpdated) {
        BNM_LOG_INFO(BNM_OBFUSCATE("Menu Update Called"));
        isUpdated = false;
    }
}

void (*DispatchReport)(void*);
void new_DispatchReport(void* instance) {
    BNM_LOG_INFO("Blocked MonkeAgent / GorillaNot caller.");
}

void OnLoaded() {
    BNM_LOG_INFO(BNM_OBFUSCATE("Hooking Methods Now!!"));

    InvokeHook(Class(BNM_OBFUSCATE("GorillaLocomotion"), BNM_OBFUSCATE("Player"), Image(
            BNM_OBFUSCATE("Assembly-CSharp.dll"))).GetMethod(BNM_OBFUSCATE("LateUpdate")), new_LateUpdate, LateUpdate);

    InvokeHook(Class(BNM_OBFUSCATE("GorillaLocomotion"), BNM_OBFUSCATE("Player"), Image(
            BNM_OBFUSCATE("Assembly-CSharp.dll"))).GetMethod(BNM_OBFUSCATE("Awake")), new_Awake, Awake);

    // MonkeAgent is in the latest GTAG release so older fan games would bypass this.
    bool hookedDispatchReport = InvokeHook(Class(BNM_OBFUSCATE("MonkeAgent"), Image(
            BNM_OBFUSCATE("Assembly-CSharp.dll"))).GetMethod(BNM_OBFUSCATE("DispatchReport")), new_DispatchReport, DispatchReport);
    if (hookedDispatchReport) {
        // All good so just continue
    } else {
        // Try the other ac
        hookedDispatchReport = InvokeHook(Class(BNM_OBFUSCATE("GorillaNot"), Image(
                BNM_OBFUSCATE("Assembly-CSharp.dll"))).GetMethod(BNM_OBFUSCATE("DispatchReport")), new_DispatchReport, DispatchReport);
    }

    BNM_LOG_INFO(BNM_OBFUSCATE("Hooked Methods..."));
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, [[maybe_unused]] void *reserved) {
    JNIEnv *env;

    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        BNM_LOG_ERR("Failed to get JNI environment!");
        return JNI_ERR;
    }

    BNM::Loading::AddOnLoadedEvent(OnLoaded);

    BNM_LOG_INFO("loaded! Calling TryLoadByJNI...");
    if (!BNM::Loading::TryLoadByJNI(env)) {
        BNM_LOG_ERR("TryLoadByJNI failed!");
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}