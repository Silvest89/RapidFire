LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../vendor/entityx/entityx/Entity.cc  \
					../../vendor/entityx/entityx/Event.cc  \
					../../vendor/entityx/entityx/System.cc \
					../../vendor/entityx/entityx/help/Pool.cc \
					../../vendor/entityx/entityx/help/Timer.cc \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/SplashScreen.cpp \
                   ../../Classes/MainMenu.cpp \
                   ../../Classes/Game.cpp \
                   ../../Classes/Player.cpp \
                   ../../Classes/Input/SneakyButton.cpp \
                   ../../Classes/Input/SneakyButtonSkinnedBase.cpp \
                   ../../Classes/Input/SneakyJoystick.cpp \
                   ../../Classes/Input/SneakyJoystickSkinnedBase.cpp \
                   ../../Classes/Input/Controller.cpp \
                   ../../Classes/HealthBar.cpp \
                   ../../Classes/GameController.cpp \
                   ../../Classes/InfiniteParallax.cpp \
                   ../../Classes/GLES-Render.cpp \
                   ../../vendor/entityx/entityx/Entity.cc  \
					../../vendor/entityx/entityx/Event.cc  \
					../../vendor/entityx/entityx/System.cc \
					../../vendor/entityx/entityx/help/Pool.cc \
					../../vendor/entityx/entityx/help/Timer.cc \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/AI \
					$(LOCAL_PATH)/../../Classes/Components \
					$(LOCAL_PATH)/../../Classes/Input \
					$(LOCAL_PATH)/../../Classes/Systems \
					$(LOCAL_PATH)/../../vendor/entityx

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static \

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
