package com.example.ndk_jni_makefile

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.example.ndk_jni_makefile.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var mBinding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        mBinding = ActivityMainBinding.inflate(layoutInflater)
        //setContentView(R.layout.activity_main)
        setContentView(mBinding.root)

        mBinding.msg.text = "nativeTest: ${nativeTest()}"

        val toJniToJava = NativeUtil.callJavaStaticNative();
        mBinding.javaJniJava.text = "currentTime: $toJniToJava"
    }

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("main-jni-test")
        }

        @JvmStatic
        external fun nativeTest(): Int
    }
}















