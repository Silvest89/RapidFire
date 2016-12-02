LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../Classes/SplashScreen.cpp \
                   ../../../Classes/MainMenu.cpp \
                   ../../../Classes/Game.cpp \
                   ../../../Classes/Player.cpp \
                   ../../../Classes/Input/SneakyButton.cpp \
                   ../../../Classes/Input/SneakyButtonSkinnedBase.cpp \
                   ../../../Classes/Input/SneakyJoystick.cpp \
                   ../../../Classes/Input/SneakyJoystickSkinnedBase.cpp \
                   ../../../Classes/Input/Controller.cpp \
                   ../../../Classes/CreatureBar.cpp \
                   ../../../Classes/GameController.cpp \
                   ../../../Classes/InfiniteParallax.cpp \
                   ../../../Classes/GLES-Render.cpp \
                   ../../../Classes/PhysicsLoader.cpp \
                   ../../../vendor/entityx/entityx/Entity.cc  \
					../../../vendor/entityx/entityx/Event.cc  \
					../../../vendor/entityx/entityx/System.cc \
					../../../vendor/entityx/entityx/help/Pool.cc \
					../../../vendor/entityx/entityx/help/Timer.cc \
					../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/Animation.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/AnimationState.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/AnimationStateData.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/Atlas.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/AtlasAttachmentLoader.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/Attachment.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/AttachmentLoader.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/Bone.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/BoneData.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/BoundingBoxAttachment.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/Event.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/EventData.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/IkConstraint.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/IkConstraintData.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/Json.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/MeshAttachment.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/PathAttachment.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/PathConstraint.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/PathConstraintData.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/RegionAttachment.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/Skeleton.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/SkeletonBinary.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/SkeletonBounds.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/SkeletonData.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/SkeletonJson.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/Skin.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/Slot.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/SlotData.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/TransformConstraint.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/TransformConstraintData.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/VertexAttachment.c \
				   ../../../../../Libraries/spine-runtimes/spine-c/spine-c/src/spine/extension.c \
                 	../../../../../Libraries/spine-runtimes/spine-cocos2dx/src/spine/AttachmentVertices.cpp \
                   ../../../../../Libraries/spine-runtimes/spine-cocos2dx/src/spine/Cocos2dAttachmentLoader.cpp \
                   ../../../../../Libraries/spine-runtimes/spine-cocos2dx/src/spine/SkeletonAnimation.cpp \
                   ../../../../../Libraries/spine-runtimes/spine-cocos2dx/src/spine/SkeletonBatch.cpp \
                   ../../../../../Libraries/spine-runtimes/spine-cocos2dx/src/spine/SkeletonRenderer.cpp \
                   ../../../../../Libraries/spine-runtimes/spine-cocos2dx/src/spine/spine-cocos2dx.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
					$(LOCAL_PATH)/../../../Classes/AI \
					$(LOCAL_PATH)/../../../Classes/Components \
					$(LOCAL_PATH)/../../../Classes/Input \
					$(LOCAL_PATH)/../../../Classes/Systems \
					$(LOCAL_PATH)/../../../Classes/rapidjson \
					$(LOCAL_PATH)/../../../vendor \
					$(LOCAL_PATH)/../../../vendor/entityx \
					$(LOCAL_PATH)/../../../../../Libraries/spine-runtimes/spine-c/spine-c/include \
					$(LOCAL_PATH)/../../../../../Libraries/spine-runtimes/spine-cocos2dx/src \

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
