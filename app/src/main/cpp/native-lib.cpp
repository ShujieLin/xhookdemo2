#include <jni.h>
#include <string>
#include <android/log.h>
#include "xhook.h"
#include <malloc.h>

void hooktest();

extern "C" JNIEXPORT jstring JNICALL
Java_com_linshujie_xhookdemo_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    hooktest();
    return env->NewStringUTF(hello.c_str());
}

void* my_malloc(size_t __byte_count){
    __android_log_print(ANDROID_LOG_INFO, "xhook", "hook malloc successful : __byte_count = %d ",__byte_count);
    return malloc(__byte_count);
}

void hooktest() {
    __android_log_print(ANDROID_LOG_INFO, "xhook", "hooktest");

    xhook_enable_debug(true);
    xhook_enable_sigsegv_protection(false);
    xhook_register(".*\\.so$", "malloc",  (void *)my_malloc,  NULL);
    xhook_refresh(true);
}
