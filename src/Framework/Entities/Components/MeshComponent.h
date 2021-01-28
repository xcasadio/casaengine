#ifndef MeshComponent_H_
#define MeshComponent_H_


#include "CA_Export.h"
#include "GameTime.h"
#include <iosfwd>
#include "Entities/Component.h"
#include "TransformComponent.h"
#include "Graphics/Mesh/Mesh.h"
#include "Game/MeshRendererGameComponent.h"


namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT MeshComponent :
		public Component
	{
	public:
		MeshComponent(BaseEntity* pEntity_);
		virtual ~MeshComponent();

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
		
		Mesh *GetModel() const;
		void SetModel(Mesh *val);

		Program *GetEffect() const;
		void SetProgram(Program *pVal_);

		//entities should be able to read/write their data to a stream
		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);

		void ShowDebugWidget();

	private:
		TransformComponent* m_pTransform;
		Mesh *m_pModel;
		Program *m_pProgram;
		MeshRendererGameComponent *m_pModelRenderer;
	};

}

#endif // MeshComponent_H_


