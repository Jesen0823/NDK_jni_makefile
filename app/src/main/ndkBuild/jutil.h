//
// Created by X1 Carbon on 2021/8/6.
//

#ifndef NDK_JNI_MAKEFILE_JUTIL_H
#define NDK_JNI_MAKEFILE_JUTIL_H

#include <stdio.h>

//定义宏
#define SIZE 11

// string转jstring
jstring s2Js(JNIEnv *env, const char *pat);
// char*转jstring
jstring char2Js(JNIEnv *env, const char *str);


#endif //NDK_JNI_MAKEFILE_JUTIL_H
