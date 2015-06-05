LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
#                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Expand/ImageScale/CCImageScaleEvent.cpp \
                   ../../Classes/Expand/SpriteButtom/CCSpriteButtomEvent.cpp \
                   ../../Classes/Expand/Hero/CCSpriteHeroEvent.cpp \
                   ../../Classes/Role/CCRole.cpp \
                   ../../Classes/Role/CCRoleFactory.cpp \
                   ../../Classes/Rule/CCNormalRule.cpp \
                   ../../Classes/Adapter/CConfigFileAdapter.cpp \
                   ../../Classes/Adapter/CCHeroAdapterOfPhysics.cpp \
                   ../../Classes/Adapter/CCSupportAdapterOfPhysics.cpp \
                   ../../Classes/Adapter/CCRoleAdapter.cpp \
                   ../../Classes/AppConfig/CCAppConfig.cpp \
                   ../../Classes/Scene/CCLoaderScene.cpp \
                   ../../Classes/Scene/CCMenuScene.cpp \
                   ../../Classes/Scene/CCGameScene.cpp \
                   ../../Classes/Layer/CCGeadShotLayer.cpp \
                   ../../Classes/Layer/CCPhotoLayer.cpp \
                   ../../Classes/Layer/CCStoreLayer.cpp \
                   ../../Classes/Layer/CCSelectLevelLayer.cpp 
                   
LOCAL_SRC_FILES += $(filter %.cpp, $(shell where /R "..\Classes"  /T *.cpp))

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)
