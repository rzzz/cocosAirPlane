LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := airplane_shared

LOCAL_MODULE_FILENAME := libairplane

# LOCAL_SRC_FILES := airplane/main.cpp

define walk
  $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef
ALLFILES = $(call walk, $(LOCAL_PATH)/../../Classes)
FILE_LIST := hellocpp/main.cpp
FILE_LIST += $(filter %.cpp, $(ALLFILES))
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(COCOS2DX_ROOT)) \ 
$(call import-add-path, $(COCOS2DX_ROOT)/cocos2dx/platform/third_party/android/prebuilt) \ 

$(call import-module,cocos2dx) \
$(call import-module,CocosDenshion/android) \
$(call import-module,extensions)
