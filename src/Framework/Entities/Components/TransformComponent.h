#ifndef TRANSFORMCOMPONENT_H_
#define TRANSFORMCOMPONENT_H_

#include <string>

#include "CA_Export.h"
#include "GameTime.h"
#include <iosfwd>
#include "Entities/Component.h"
#include "Maths/Matrix4.h"

namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT TransformComponent :
		public Component
	{
	private:

	protected:
		Matrix4 m_LocalMatrix;
		Matrix4 m_WorldMatrix;

		bool m_LocalMatrixChanged;
		
	public:

		Matrix4 GetLocalMatrix();
		virtual void SetLocalMatrix(Matrix4 val) = 0;

		Matrix4 GetWorldMatrix();
		virtual void SetWorldMatrix(Matrix4 val) = 0;

		//all entities must implement an update function
		virtual void  Update(const GameTime& gameTime_) = 0;

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//virtual void HandleEvent(const Event* pEvent_) = 0;

		//entities should be able to read/write their data to a stream
		virtual void Write(std::ostream&  os)const;
		virtual void Read (std::ifstream& is);

	protected:
		TransformComponent(BaseEntity* pEntity_, int type_);
		virtual ~TransformComponent();

		virtual void UpdateLocalMatrix() = 0;
		virtual void UpdateWorldMatrix() = 0;
	};

}

#endif // TRANSFORMCOMPONENT_H_


