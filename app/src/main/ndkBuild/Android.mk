# 定义模块当前路径
LOCAL_PATH := $(call my-dir)

# 情况当前环境变量
include $(CLEAR_VARS)

# 当前模块名
LOCAL_MODULE := main-jni-test
# 当前模块包含的源代码文件
LOCAL_SRC_FILES := main-jni.c jutil.c jutil.h

# 生成一个动态库
include $(BUILD_SHARED_LIBRARY)
