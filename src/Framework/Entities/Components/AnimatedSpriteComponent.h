#ifndef AnimatedSPRITECOMPONENT_H_
#define AnimatedSPRITECOMPONENT_H_

#include <string>
#include <iosfwd>
#include <vector>

#include "CA_Export.h"
#include "Animations/IAnimationEventListener.h"
#include "Entities/Component.h"
#include "GameTime.h"
#include "Graphics/Color.h"
#include "Parsers/Xml/tinyxml2.h"
#include "Sprite/SpriteRenderer.h"
#include "Sprite/SpriteTypes.h"
#include "Transform2DComponent.h"
#include "Transform3DComponent.h"
#include "Animations/Animation2D.h"
#include "EventHandler\EventSet.h"
#include "EventHandler/Event.h"

#include "Physics/PhysicsObjectContainer.h"
#include "CompilationMacro.h"


namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT AnimatedSpriteComponent :
		public Component,
		public EventSet
	{
	private:
		SpriteRenderer*	m_pSpriteRenderer;
		Transform3DComponent* m_pTransform;
		CColor m_Color;		
		eSpriteEffects m_SpriteEffect;
		Animation2D *m_pCurrentAnim;

		std::vector<Animation2D *> m_AnimationList;
		// keep physics object created by the current frame in order to remove them after
		// the frame change
		std::vector<ICollisionObjectContainer *> m_LastSpriteCollisionObjects;

		Event::Connection m_FrameChangedConnection;
		Event::Connection m_AnimFinishedConnection;

	public:
		AnimatedSpriteComponent(BaseEntity* pEntity_);
		virtual ~AnimatedSpriteComponent();

		CColor GetColor() const;
		void SetColor(CColor val);
		eSpriteEffects GetSpriteEffect() const;
		void SetSpriteEffect(eSpriteEffects val);

		/**
		 * 
		 */
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

		void SetCurrentAnimation(int index_);
		void SetCurrentAnimation(std::string name_);

		void AddAnimation(Animation2D *pAnim_);

		//Event
		bool OnFrameChanged(const EventArgs &e);
		bool OnAnimationFinished(const EventArgs &e);

		void Read (std::ifstream& is) OVERRIDE;
		void Read (const tinyxml2::XMLElement &el_) OVERRIDE;

#if EDITOR

		void Write(tinyxml2::XMLElement &el_) OVERRIDE;
		void Write(std::ostream& os) OVERRIDE;

#endif
		
	};

}

#endif // AnimatedSPRITECOMPONENT_H_


