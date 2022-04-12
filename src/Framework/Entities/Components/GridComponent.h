#ifndef GRIDCOMPONENT_H_
#define GRIDCOMPONENT_H_

#include <string>
#include <iosfwd>

#include "CA_Export.h"
#include "GameTime.h"
#include "Entities/Component.h"
#include "Graphics/Color.h"


#include "Maths/Vector3.h"

#include "Game/Line3DRendererComponent.h"

namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT GridComponent :
		public Component
	{
	public:
		/**
		 * 
		 */
		struct TGridPointData
		{
			TGridPointData(Vector3 startPos_, CColor startColor_,
				Vector3 endPos_, CColor endColor_)
			{
				Start = startPos_;
				StartColor = startColor_;
				End = endPos_;
				EndColor = endColor_;
			}

			Vector3 Start, End;
			CColor StartColor, EndColor;
		};

	public:
		GridComponent(BaseEntity* pEntity_);
		virtual ~GridComponent();

		int Size() const;
		void Size(int val);

		//all entities must implement an Initialize function
		void Initialize();

		/**
		 * 
		 */
		void  Update(const GameTime& gameTime_);

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

	private:
		void CreateBuffers();

	private:
		//CDeclarationPtr m_Declaration;  ///< Déclaration de vertex		
		//Buffer<TVertexPositionColor> m_VertexBuffer; ///< Vertex buffer contenant les vertices du modèle
		std::vector<TGridPointData> m_Vertices;
		Line3DRendererComponent *m_pLineManager;

		int m_iSize;
		bool m_bNeedToUpdateBuffers;
	};

}

#endif // STATICSPRITECOMPONENT_H_


