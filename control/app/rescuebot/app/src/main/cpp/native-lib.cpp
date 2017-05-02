#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_luctins_rescuebot_mainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
