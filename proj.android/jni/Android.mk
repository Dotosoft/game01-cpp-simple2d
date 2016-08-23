LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)






LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

# Debug Local Source
#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                   ../../Classes/debug/AppDelegate.cpp \
#                   ../../Classes/debug/B2DebugDrawLayer.cpp \
#                   ../../Classes/debug/GB2ShapeCacheX.cpp \
#                   ../../Classes/debug/GLESRender.cpp \
#                   ../../Classes/debug/VisibleRect.cpp

# Simple Shooter Local Source
#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                   ../../Classes/simpleshooter/AppDelegate.cpp \
#                   ../../Classes/simpleshooter/HelloWorldScene.cpp \
#                   ../../Classes/simpleshooter/Monster.cpp \
#                   ../../Classes/simpleshooter/Level.cpp \
#                   ../../Classes/simpleshooter/LevelManager.cpp \
#                   ../../Classes/simpleshooter/GameOverScene.cpp

# Flappy Local Source                   
#LOCAL_SRC_FILES := hellocpp/main.cpp \
#				    ../../Classes/flappy/AppDelegate.cpp \
#                   ../../Classes/flappy/GameOverScene.cpp \
#                   ../../Classes/flappy/GameScene.cpp \
#                   ../../Classes/flappy/MainMenuScene.cpp \
#                   ../../Classes/flappy/Pipe.cpp \
#                   ../../Classes/flappy/Bird.cpp \
#                   ../../Classes/flappy/SplashScene.cpp

# Tower Defense Local Source
#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                   ../../Classes/towerdefense/AppDelegate.cpp \
#				    ../../Classes/towerdefense/IntroScene.cpp \
#                   ../../Classes/towerdefense/HelloWorldScene.cpp \
#                   ../../Classes/towerdefense/Tower.cpp \
#                   ../../Classes/towerdefense/Waypoint.cpp \
#                   ../../Classes/towerdefense/Enemy.cpp
 
# Ball Trajectory Local Source
#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                   ../../Classes/balltrajectory/AppDelegate.cpp \
#				    ../../Classes/balltrajectory/HelloWorldScene.cpp

# Puzzle Local Source
#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                   ../../Classes/puzzle/AppDelegate.cpp \
#                   ../../Classes/puzzle/Piece.cpp \
#				    ../../Classes/puzzle/GamePlayScene.cpp
				    
# FreeHand Local Source
#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                    ../../Classes/freehand/AppDelegate.cpp \
#                    ../../Classes/freehand/HelloWorldScene.cpp
                    
# Gallery Local Source
#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                    ../../Classes/gallery/AppDelegate.cpp \
#                    ../../Classes/gallery/HelloWorldScene.cpp

# SpaceShooter Local Source
#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                    ../../Classes/spaceshooter/AppDelegate.cpp \
#                    ../../Classes/spaceshooter/GameOverScene.cpp \
#                    ../../Classes/spaceshooter/GameScene.cpp \
#                    ../../Classes/spaceshooter/MainMenuScene.cpp \
#                    ../../Classes/spaceshooter/PauseScene.cpp

# SpaceShooter Local Source
#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                    ../../Classes/scrollview/AppDelegate.cpp \
#                    ../../Classes/scrollview/HelloWorldScene.cpp

# Breakout Local Source
#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                    ../../Classes/breakout/AppDelegate.cpp \
#                    ../../Classes/breakout/HelloWorldScene.cpp

# Colour Smasher Local Source
LOCAL_SRC_FILES := hellocpp/main.cpp \
                    ../../Classes/coloursmash/AppDelegate.cpp \
                    ../../Classes/coloursmash/GameWorldScene.cpp \
                    ../../Classes/coloursmash/HelloWorldScene.cpp

                    
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

#$(call import-module,./prebuilt-mk)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/prebuilt-mk)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
