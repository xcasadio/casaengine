#ifndef STATICSPRITECOMPONENT_H_
#define STATICSPRITECOMPONENT_H_

#include <string>
#include <iosfwd>

#include "CA_Export.h"
#include "GameTime.h"
#include "Entities/Component.h"
#include "Sprite/SpriteRenderer.h"
#include "Graphics/Color.h"
#include "Sprite/SpriteTypes.h"
#include "Transform3DComponent.h"

namespace CasaEngine
{
	class CA_EXPORT StaticSpriteComponent :
		public Component
	{
	private:
		std::string m_SpriteID;
		Sprite* m_pSprite;
		SpriteRenderer*	m_pSpriteRenderer;
		Transform3DComponent* m_pTransform;
		Color m_Color;		
		eSpriteEffects m_SpriteEffect;

	public:
		StaticSpriteComponent(BaseEntity* pEntity_);
		virtual ~StaticSpriteComponent();

		std::string GetSpriteID() const;
		void SetSpriteID(std::string val);

		Color GetColor() const;
		void SetColor(Color val);
		eSpriteEffects GetSpriteEffect() const;
		void SetSpriteEffect(eSpriteEffects val);

		void Initialize();
		void Update(const GameTime& gameTime_);
		void Draw();
	};

}

#endif
