# Copyright (C) 2014 CasaEngine

LOCAL_PATH := $(call my-dir)

PROJECT_ROOT_PATH := $(LOCAL_PATH)/../../../../src/
CORE_RELATIVE_PATH := ../../../../src/Core
ENGINE_RELATIVE_PATH := ../../../../src/Engine
FRAMEWORK_RELATIVE_PATH := ../../../../src/Framework
CASAENGINE_RELATIVE_PATH := $(LOCAL_PATH)/../../../../src

include $(CLEAR_VARS)

LOCAL_MODULE := casaengine_shared
LOCAL_MODULE_FILENAME := libcasaengine

LOCAL_LDLIBS := -llog -lz -lm -ldl -landroid -lGLESv2 -lEGL
LOCAL_STATIC_LIBRARIES := bullet_static

APP_OPTIM := debug
LOCAL_CFLAGS   := -g -ggdb -O1 -DDEBUG -DANDROID_NDK -DANDROID
#LOCAL_CFLAGS   += -DANDROID

LOCAL_CPPFLAGS := -std=c++11
#LOCAL_CPP_FEATURES := rtti
#LOCAL_EXPORT_CFLAGS   := -Wno-psabi -DUSE_FILE32API
#LOCAL_EXPORT_CPPFLAGS := -Wno-literal-suffix
#

LOCAL_SRC_FILES := \
	$(CORE_RELATIVE_PATH)/ContainerUtil.cpp \
	$(CORE_RELATIVE_PATH)/DateTime.cpp \
	$(CORE_RELATIVE_PATH)/DynamicModule.cpp \
	$(CORE_RELATIVE_PATH)/EventHandler/BoundSlot.cpp \
	$(CORE_RELATIVE_PATH)/EventHandler/Event.cpp \
	$(CORE_RELATIVE_PATH)/EventHandler/EventArgs.cpp \
	$(CORE_RELATIVE_PATH)/EventHandler/EventSet.cpp \
	$(CORE_RELATIVE_PATH)/EventHandler/GlobalEventSet.cpp \
	$(CORE_RELATIVE_PATH)/EventHandler/SubscriberSlot.cpp \
	$(CORE_RELATIVE_PATH)/Exceptions.cpp \
	$(CORE_RELATIVE_PATH)/IO/File.cpp \
	$(CORE_RELATIVE_PATH)/IO/IFile.cpp \
	$(CORE_RELATIVE_PATH)/IO/IOManager.cpp \
	$(CORE_RELATIVE_PATH)/IO/android/FileAsset.cpp \
	$(CORE_RELATIVE_PATH)/Log/LogManager.cpp \
	$(CORE_RELATIVE_PATH)/Log/Logger.cpp \
	$(CORE_RELATIVE_PATH)/Log/LoggerAndroid.cpp \
	$(CORE_RELATIVE_PATH)/Log/LoggerFile.cpp \
	$(CORE_RELATIVE_PATH)/Maths/2D/Geometry.cpp \
	$(CORE_RELATIVE_PATH)/Maths/2D/InvertedAABBox2D.cpp \
	$(CORE_RELATIVE_PATH)/Maths/2D/Line2D.cpp \
	$(CORE_RELATIVE_PATH)/Maths/2D/Path.cpp \
	$(CORE_RELATIVE_PATH)/Maths/2D/Transformations.cpp \
	$(CORE_RELATIVE_PATH)/Maths/Matrix3.cpp \
	$(CORE_RELATIVE_PATH)/Maths/Matrix4.cpp \
	$(CORE_RELATIVE_PATH)/Maths/Quaternion.cpp \
	$(CORE_RELATIVE_PATH)/Maths/Rectangle.cpp \
	$(CORE_RELATIVE_PATH)/Maths/Shape/Box.cpp \
	$(CORE_RELATIVE_PATH)/Maths/Shape/Box2D.cpp \
	$(CORE_RELATIVE_PATH)/Maths/Shape/Capsule.cpp \
	$(CORE_RELATIVE_PATH)/Maths/Shape/Circle.cpp \
	$(CORE_RELATIVE_PATH)/Maths/Shape/IShape.cpp \
	$(CORE_RELATIVE_PATH)/Maths/Shape/Polygon.cpp \
	$(CORE_RELATIVE_PATH)/Maths/Shape/Sphere.cpp \
	$(CORE_RELATIVE_PATH)/Memory/MemoryDebugAllocator.cpp \
	$(CORE_RELATIVE_PATH)/Memory/MemoryReport.cpp \
	$(CORE_RELATIVE_PATH)/Parsers/Ini/INIReader.cpp \
	$(CORE_RELATIVE_PATH)/Parsers/Ini/ini.cpp \
	$(CORE_RELATIVE_PATH)/Parsers/Xml/XMLHelper.cpp \
	$(CORE_RELATIVE_PATH)/Parsers/Xml/tinyxml2.cpp \
	$(ENGINE_RELATIVE_PATH)/EngineInfo.cpp \
	$(ENGINE_RELATIVE_PATH)/GameTime.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Color.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Effects/Program.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Effects/Shader.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Materials/Material.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Mesh/Mesh.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Primitives/BoxPrimitive.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Primitives/CylinderPrimitive.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Primitives/PlanePrimitive.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Primitives/Primitive3D.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Primitives/SpherePrimitive.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Primitives/TorusPrimitive.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/RenderTarget.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Renderer/Renderer.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/TargetTexture.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Textures/Texture.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Vertices/VertexType.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/Viewport.cpp \
	$(ENGINE_RELATIVE_PATH)/Graphics/ViewportTarget.cpp \
	$(ENGINE_RELATIVE_PATH)/Loaders/XmlLoader.cpp \
	$(ENGINE_RELATIVE_PATH)/Physics/Bullet/BulletObjectsContainer.cpp \
	$(ENGINE_RELATIVE_PATH)/Physics/Bullet/BulletPhysicsEngine.cpp \
	$(ENGINE_RELATIVE_PATH)/Physics/Bullet/BulletPhysicsWorld.cpp \
	$(ENGINE_RELATIVE_PATH)/Physics/Bullet/btDynamicsWorldExt.cpp \
	$(ENGINE_RELATIVE_PATH)/Physics/IPhysicsWorld.cpp \
	$(ENGINE_RELATIVE_PATH)/Physics/PhysicsEngine.cpp \
	$(ENGINE_RELATIVE_PATH)/Profiling/Profiling.cpp \
	$(ENGINE_RELATIVE_PATH)/Resources/MediaManager.cpp \
	$(ENGINE_RELATIVE_PATH)/Resources/Resource.cpp \
	$(ENGINE_RELATIVE_PATH)/Resources/ResourceManager.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/AI/Fuzzy/FuzzyModule.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/AI/Fuzzy/FuzzyOperators.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/AI/Fuzzy/FuzzySet.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/AI/Fuzzy/FuzzySet_LeftShoulder.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/AI/Fuzzy/FuzzySet_RightShoulder.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/AI/Fuzzy/FuzzySet_Singleton.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/AI/Fuzzy/FuzzySet_Triangle.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/AI/Fuzzy/FuzzyVariable.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/AI/Messaging/MessageDispatcher.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Addons/Console/Console.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Animations/Animation.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Animations/Animation2D.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Animations/AnimationEvent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Animations/Animation2DPlayer.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Animations/SetFrameEvent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Assets/Asset.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Assets/AssetManager.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Assets/Assetable.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/CEGUI/CEGUIGeometryBuffer.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/CEGUI/CEGUIImageCodec.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/CEGUI/CEGUILogger.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/CEGUI/CEGUIRenderer.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/CEGUI/CEGUIResourceProvider.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/CEGUI/CEGUITexture.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/CEGUI/CEGUITextureTarget.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/CEGUI/CEGUIViewportTarget.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/CEGUI/CEGUIXMLParser.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/BaseEntity.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Component.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/ComponentManager.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/Camera2DComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/Camera3DComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/CameraComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/CameraControllers/ArcBallCameraController.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/CameraControllers/Camera2DController.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/CameraControllers/CameraController.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/FSMComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/GridComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/MeshComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/MovingEntity2DComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/StaticSpriteComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/Transform2DComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/Transform3DComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/TransformComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/Physics/Box2DColliderComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/Physics/BoxColliderComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/Physics/CapsuleColliderComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/Physics/Circle2DColliderComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/Physics/ColliderComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/Physics/RigidBodyComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Components/Physics/SphereColliderComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/DebugTools/FPSMonitoringComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/EntityManager.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Events/BaseEntityEvents.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Entities/Events/DebugToolEvents.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Game/DrawableGameComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Game/Game.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Game/GameComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Game/GameInfo.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Game/IDrawable.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Game/IUpdateable.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Game/Line2DRendererComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Game/Line3DRendererComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Game/MeshRendererGameComponent.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Project/ProjectManager.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Sprite/Sprite.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Sprite/SpriteRenderer.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/Tools/DebugSystem.cpp \
	$(FRAMEWORK_RELATIVE_PATH)/World/World.cpp

LOCAL_C_INCLUDES := $(PROJECT_ROOT_PATH)Core/ \
	$(PROJECT_ROOT_PATH)Engine/ \
	$(PROJECT_ROOT_PATH)Framework/ \
	$(PROJECT_ROOT_PATH)../external/bullet/include \
	$(PROJECT_ROOT_PATH)../external/SFML/include \
	$(PROJECT_ROOT_PATH)../external/bgfx/include

#include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)
