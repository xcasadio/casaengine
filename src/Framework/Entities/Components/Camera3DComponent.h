#ifndef CAMERA3DCOMPONENT_H_
#define CAMERA3DCOMPONENT_H_

#include "CA_Export.h"
#include <iosfwd>
#include "Entities/Components/CameraComponent.h"
#include "Maths/Vector3.h"

namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT Camera3DComponent :
		public CameraComponent
	{
	public:
		Camera3DComponent(BaseEntity* pEntity_);
		virtual ~Camera3DComponent();

		//all entities must implement an update function
		void Initialize();

		/**
		 * 
		 */
		//void Update(const GameTime& gameTime_);

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);
		
		CasaEngine::Vector3F Position() const;
		void Position(CasaEngine::Vector3F val);

		CasaEngine::Vector3F Target() const;
		void Target(CasaEngine::Vector3F val);

		float FOV() const;
		void FOV(float val);

		float FarClipPlane() const;
		void FarClipPlane(float val);

		float NearClipPlane() const;
		void NearClipPlane(float val);

		//entities should be able to read/write their data to a stream
		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);

	protected:
		void ComputeProjectionMatrix() override;
		void ComputeViewMatrix() override;

	private:
		Vector3F m_Target, m_Position;
		float m_fFOV;
	};
}

#endif // CAMERA3DCOMPONENT_H_


