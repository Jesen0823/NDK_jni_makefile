package com.example.ndk_jni_makefile

import java.text.SimpleDateFormat
import java.util.*

// 待jni层调用
object JniJava {

    @JvmStatic
    fun getDataFromJava(): String {
        val lsdFormat = SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.CHINESE)
        return lsdFormat.format(Date().time)
    }

}