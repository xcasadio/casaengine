#pragma once

#include <string>
#include <iosfwd>

#include "CA_Export.h"
#include "GameTime.h"
#include "Entities/Component.h"
#include "Sprite/SpriteRenderer.h"
#include "Graphics/Color.h"
#include "Sprite/SpriteTypes.h"

namespace CasaEngine
{
	class CA_EXPORT StaticSpriteComponent :
		public Component
	{
	private:
		std::string _spriteId;
		Sprite* _sprite;
		SpriteRenderer* _spriteRenderer;
		Color _color;
		eSpriteEffects _spriteEffect;

	public:
		StaticSpriteComponent(BaseEntity* entity);
		~StaticSpriteComponent() override;

		std::string GetSpriteID() const;
		void SetSpriteID(std::string val);

		Color GetColor() const;
		void SetColor(Color val);
		eSpriteEffects GetSpriteEffect() const;
		void SetSpriteEffect(eSpriteEffects val);

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw() override;
	};
}
