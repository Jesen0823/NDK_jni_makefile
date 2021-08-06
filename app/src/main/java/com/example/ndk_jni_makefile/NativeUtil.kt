package com.example.ndk_jni_makefile

object NativeUtil {
    // 去调用jni层

    @JvmStatic
    external fun callJavaStaticNative(): String
}