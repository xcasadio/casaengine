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
	/*
	 *	
	 */
	class CA_EXPORT StaticSpriteComponent :
		public Component
	{
	private:
		std::string m_SpriteID;
		Sprite* m_pSprite;
		SpriteRenderer*	m_pSpriteRenderer;
		Transform3DComponent* m_pTransform;
		CColor m_Color;		
		eSpriteEffects m_SpriteEffect;

	public:
		StaticSpriteComponent(BaseEntity* pEntity_);
		virtual ~StaticSpriteComponent();

		std::string SpriteID() const;
		void SpriteID(std::string val);

		CColor GetColor() const;
		void SetColor(CColor val);
		eSpriteEffects GetSpriteEffect() const;
		void SetSpriteEffect(eSpriteEffects val);

		//all entities must implement an Initialize function
		void Initialize();

		/**
		 * 
		 */
		void Update(const GameTime& gameTime_);

		/**
		 * 
		 */
		void Draw();

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);

		//entities should be able to read/write their data to a stream
		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);
	};

}

#endif // STATICSPRITECOMPONENT_H_


