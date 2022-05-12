#pragma once

#include <vector>
#include <string>

#include "Serializer/Serializer.h"

enum ClsnType
{
	None,
	Type1Attack,
	Type2Normal
};

struct sprite
{
	int X, Y;
	int SpriteSizeX, SpriteSizeY;
	int posInTextureX, posInTextureY;
	std::string Id;
};

inline void to_json(nlohmann::json& j, const sprite& t)
{
	JSON_TO(X)
	JSON_TO(Y)
	JSON_TO(SpriteSizeX)
	JSON_TO(SpriteSizeY)
	JSON_TO(posInTextureX)
	JSON_TO(posInTextureY)
	JSON_TO(Id)
}

inline void from_json(const nlohmann::json& j, sprite& t)
{
	JSON_FROM(X)
	JSON_FROM(Y)
	JSON_FROM(SpriteSizeX)
	JSON_FROM(SpriteSizeY)
	JSON_FROM(posInTextureX)
	JSON_FROM(posInTextureY)
	JSON_FROM(Id)
}

struct sprites
{
	std::vector<sprite> sprites;
};

inline void to_json(nlohmann::json& j, const sprites& t)
{
	JSON_TO(sprites)
}

inline void from_json(const nlohmann::json& j, sprites& t)
{
	JSON_FROM(sprites)
}

struct blending
{
	int BlendType;
	float SourceFactor, DestinationFactor;
};

inline void to_json(nlohmann::json& j, const blending& t)
{
	JSON_TO(BlendType)
	JSON_TO(SourceFactor)
	JSON_TO(DestinationFactor)
}

inline void from_json(const nlohmann::json& j, blending& t)
{
	JSON_FROM(BlendType)
	JSON_FROM(SourceFactor)
	JSON_FROM(DestinationFactor)
}

struct collision
{
	int ClsnType;
	int X, Y, Width, Height;
};

inline void to_json(nlohmann::json& j, const collision& t)
{
	JSON_TO(ClsnType)
	JSON_TO(X)
	JSON_TO(Y)
	JSON_TO(Width)
	JSON_TO(Height)
}

inline void from_json(const nlohmann::json& j, collision& t)
{
	JSON_FROM(ClsnType)
	JSON_FROM(X)
	JSON_FROM(Y)
	JSON_FROM(Width)
	JSON_FROM(Height)
}

struct frame
{
	std::string SpriteId;
	int OffsetX, OffsetY;
	int GameTick;
	blending Blending;
	int Flip;
	std::vector<collision> Collisions;
};

inline void to_json(nlohmann::json& j, const frame& t)
{
	JSON_TO(SpriteId)
	JSON_TO(OffsetX)
	JSON_TO(OffsetY)
	JSON_TO(GameTick)
	JSON_TO(Blending)
	JSON_TO(Flip)
	JSON_TO(Collisions)
}

inline void from_json(const nlohmann::json& j, frame& t)
{
	JSON_FROM(SpriteId)
	JSON_FROM(OffsetX)
	JSON_FROM(OffsetY)
	JSON_FROM(GameTick)
	JSON_FROM(Blending)
	JSON_FROM(Flip)
	JSON_FROM(Collisions)
}

struct animation
{
	int Number;
	int Loopstart;
	std::vector<frame> Frames;
};

inline void to_json(nlohmann::json& j, const animation& t)
{
	JSON_TO(Number)
	JSON_TO(Loopstart)
	JSON_TO(Frames)
}

inline void from_json(const nlohmann::json& j, animation& t)
{
	JSON_FROM(Number)
	JSON_FROM(Loopstart)
	JSON_FROM(Frames)
}

struct animations
{
	std::vector<animation> animations;
};

inline void to_json(nlohmann::json& j, const animations& t)
{
	JSON_TO(animations)
}

inline void from_json(const nlohmann::json& j, animations& t)
{
	JSON_FROM(animations)
}
