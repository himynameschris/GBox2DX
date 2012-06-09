LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := helloworld/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/TestScene.cpp \
                   ../../Classes/TestScreenEdge.cpp \
                   ../../../../lua/cocos2dx_support/CCLuaEngine.cpp \
                                      ../../../../lua/cocos2dx_support/Cocos2dxLuaLoader.cpp \
                                      ../../../../lua/cocos2dx_support/LuaCocos2d.cpp \
                                      ../../../../lua/cocos2dx_support/tolua_fix.c
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../../GBox2D \
                    $(LOCAL_PATH)/../../../GBox2D/Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static box2d_static cocos_lua_static gbox2d_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) $(call import-module,cocos2dx) $(call import-module,Box2D) $(call import-module,lua/proj.android/jni) $(call import-module,GBox2D/Classes)
