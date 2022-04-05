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
	class CA_EXPORT MeshComponent :
		public Component
	{
	public:
		MeshComponent(BaseEntity* pEntity_);

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw() override;

		Mesh *GetModel() const;
		void SetModel(Mesh *val);

		Program *GetEffect() const;
		void SetProgram(Program *pVal_);

		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);

		void ShowDebugWidget() override;
	private:
		TransformComponent* m_pTransform;
		Mesh *m_pModel;
		Program *m_pProgram;
		MeshRendererGameComponent *m_pModelRenderer;
	};

}

#endif
