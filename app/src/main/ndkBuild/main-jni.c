//
// Created by X1 Carbon on 2021/8/6.
//

#include <jni.h>
#include <string.h>
#include "jutil.h"

int test() {
    return 10086;
}

// 如果包名有数字需要加1，如 com.example.test_1_3
// 要转为 com_example_test_11_13(_MainActivity)
jint Java_com_example_ndk_1jni_1makefile_MainActivity_nativeTest(JNIEnv *env, jclass thiz) {
    return test();
}

// jni调用java层getDataFromJava()
//JNIEXPORT jstring JNICALL
jstring Java_com_example_ndk_1jni_1makefile_NativeUtil_callJavaStaticNative(JNIEnv *env, jclass thiz) {
    jclass jclaz = (*env)->FindClass(env, "com/example/ndk_jni_makefile/JniJava");
    if (NULL == jclaz) {
        return s2Js(env, "can,t find JniJava.");
    }
    jmethodID getDataFromJava = (*env)->GetStaticMethodID(env, jclaz, "getDataFromJava",
                                                          "()Ljava/lang/String;");

    if (NULL == getDataFromJava) {
        (*env)->DeleteLocalRef(env, jclaz);
        return s2Js(env, "can‘t find method getDataFromJava from JniJava.");
    }

    jstring result = (*env)->CallStaticObjectMethod(env, jclaz, getDataFromJava);
    const char *resultChar = (*env)->GetStringUTFChars(env, result, NULL);
    (*env)->DeleteLocalRef(env, jclaz);
    (*env)->DeleteLocalRef(env, result);
    return char2Js(env, resultChar);
}
