LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cpp_empty_test_shared

LOCAL_MODULE_FILENAME := libcpp_empty_test

LOCAL_SRC_FILES := main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/GameScene.cpp \
				   ../../Classes/MenuScene.cpp \
				   ../../Classes/RectPool.cpp \
				   ../../Classes/RetryScene.cpp \
				   ../../Classes/SessionController.cpp \
				   ../../Classes/LevelScene.cpp \
				   ../../Classes/CompletedWindow.cpp 
					
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)../../../../. \
					$(LOCAL_PATH)../../../../../extensions \
					$(LOCAL_PATH)../../../../../cocos \
					$(LOCAL_PATH)../../../../../cocos/ui \
					$(LOCAL_PATH)../../../../../cocos/editor-support/cocostudio \

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static 
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_gui_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)
$(call import-module,ui)
$(call import-module,editor-support/cocostudio)
