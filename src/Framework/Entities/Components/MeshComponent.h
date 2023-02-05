#pragma once

#include "CA_Export.h"
#include "GameTime.h"
#include <iosfwd>
#include "Entities/Component.h"
#include "Graphics/Mesh/Mesh.h"
#include "Game/MeshRendererGameComponent.h"

namespace CasaEngine
{
	class CA_EXPORT MeshComponent :
		public Component
	{
	public:
		MeshComponent(BaseEntity* entity);

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw() override;

		Mesh *GetModel() const;
		void SetModel(Mesh *val);

		Program *GetEffect() const;
		void SetProgram(Program *pVal_);

		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);
	private:
		Mesh *m_pModel;
		Program *m_pProgram;
		MeshRendererGameComponent *m_pModelRenderer;

#if EDITOR
	public:
		void ShowDebugWidget() override;
#endif
	};
}
