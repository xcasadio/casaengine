#pragma once
#include <cereal/cereal.hpp>

#include <vector>
#include <string>

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

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(X));
		ar(CEREAL_NVP(Y));
		ar(CEREAL_NVP(SpriteSizeX));
		ar(CEREAL_NVP(SpriteSizeY));
		ar(CEREAL_NVP(posInTextureX));
		ar(CEREAL_NVP(posInTextureY));
		ar(CEREAL_NVP(Id));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(X));
		ar(CEREAL_NVP(Y));
		ar(CEREAL_NVP(SpriteSizeX));
		ar(CEREAL_NVP(SpriteSizeY));
		ar(CEREAL_NVP(posInTextureX));
		ar(CEREAL_NVP(posInTextureY));
		ar(CEREAL_NVP(Id));
	}
};

struct sprites
{
	std::vector<sprite> sprites;

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(sprites));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(sprites));
	}
};

struct blending
{
	int BlendType;
	float SourceFactor, DestinationFactor;

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(BlendType));
		ar(CEREAL_NVP(SourceFactor));
		ar(CEREAL_NVP(DestinationFactor));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(BlendType));
		ar(CEREAL_NVP(SourceFactor));
		ar(CEREAL_NVP(DestinationFactor));
	}
};

struct collision
{
	int ClsnType;
	int X, Y, Width, Height;

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(ClsnType));
		ar(CEREAL_NVP(X));
		ar(CEREAL_NVP(Y));
		ar(CEREAL_NVP(Width));
		ar(CEREAL_NVP(Height));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(ClsnType));
		ar(CEREAL_NVP(X));
		ar(CEREAL_NVP(Y));
		ar(CEREAL_NVP(Width));
		ar(CEREAL_NVP(Height));
	}
};

struct frame
{
	std::string SpriteId;
	int OffsetX, OffsetY;
	int GameTick;
	blending Blending;
	int Flip;
	std::vector<collision> Collisions;

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(SpriteId));
		ar(CEREAL_NVP(OffsetX));
		ar(CEREAL_NVP(OffsetY));
		ar(CEREAL_NVP(GameTick));
		ar(CEREAL_NVP(Blending));
		ar(CEREAL_NVP(Flip));
		ar(CEREAL_NVP(Collisions));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(SpriteId));
		ar(CEREAL_NVP(OffsetX));
		ar(CEREAL_NVP(OffsetY));
		ar(CEREAL_NVP(GameTick));
		ar(CEREAL_NVP(Blending));
		ar(CEREAL_NVP(Flip));
		ar(CEREAL_NVP(Collisions));
	}
};

struct animation
{
	int Number;
	int Loopstart;
	std::vector<frame> Frames;

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(Number));
		ar(CEREAL_NVP(Loopstart));
		ar(CEREAL_NVP(Frames));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(Number));
		ar(CEREAL_NVP(Loopstart));
		ar(CEREAL_NVP(Frames));
	}
};

struct animations
{
	std::vector<animation> animations;

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(animations));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(animations));
	}
};