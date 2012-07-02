LOCAL_PATH := $(call my-dir)

## STATIC LIBRARY

LOCAL_MODULE := gbox2d_static

APP_STL := stlport_static

#LOCAL_MODULE := libgbox2d

LOCAL_MODULE_FILENAME := libgbox2d

LOCAL_SRC_FILES := GB2Contact.cpp \
                   GB2CollisionRegistry.cpp \
				   GB2DebugDrawLayer.cpp \
				   GB2Engine.cpp \
				   GB2Node.cpp \
				   GB2ShapeCache.cpp \
				   GB2WorldContactListener.cpp \
				   GLES-Render.cpp

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
							$(LOCAL_PATH)/../../Box2D

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../cocos2dx \
					$(LOCAL_PATH)/../../Box2D \
                    $(LOCAL_PATH)/../../cocos2dx/platform \
                    $(LOCAL_PATH)/../../cocos2dx/platform/third_party/android/modules \
                    $(LOCAL_PATH)/../../cocos2dx/include \
                    $(LOCAL_PATH)/../../CocosDenshion/include \
                    $(LOCAL_PATH)/../../cocos2dx/lua_support \
					$(LOCAL_PATH)/..
					
LOCAL_STATIC_LIBRARIES := png_static_prebuilt
LOCAL_STATIC_LIBRARIES += xml2_static_prebuilt
LOCAL_STATIC_LIBRARIES += jpeg_static_prebuilt
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static box2d_static

include $(BUILD_STATIC_LIBRARY)



## SHARED LIBRARY

include $(CLEAR_VARS)

LOCAL_MODULE := gbox2d_shared

APP_STL := stlport_static

#LOCAL_MODULE := libgbox2d

LOCAL_MODULE_FILENAME := libgbox2d

LOCAL_SRC_FILES := GB2Contact.cpp \
				   GB2DebugDrawLayer.cpp \
				   GB2Engine.cpp \
				   GB2Node.cpp \
				   GB2ShapeCache.cpp \
				   GB2Sprite.cpp \
				   GB2WorldContactListener.cpp \
				   GLES-Render.cpp 
				   
                   
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) \
							$(LOCAL_PATH)/../../Box2d

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../cocos2dx \
					$(LOCAL_PATH)/../../Box2d \
                    $(LOCAL_PATH)/../../cocos2dx/platform \
                    $(LOCAL_PATH)/../../cocos2dx/platform/third_party/android/modules \
                    $(LOCAL_PATH)/../../cocos2dx/include \
                    $(LOCAL_PATH)/../../CocosDenshion/include \
                    $(LOCAL_PATH)/../../cocos2dx/lua_support \
					$(LOCAL_PATH)/..

LOCAL_STATIC_LIBRARIES := png_static_prebuilt
LOCAL_STATIC_LIBRARIES += xml2_static_prebuilt
LOCAL_STATIC_LIBRARIES += jpeg_static_prebuilt
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static box2d_static
                            
#include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)

$(call import-module,libpng)
$(call import-module,libxml2)
$(call import-module,libjpeg)
