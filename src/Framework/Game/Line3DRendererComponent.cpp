#include "Base.h"

#include "Game/Line3DRendererComponent.h"
#include "Game/Game.h"
#include "GameTime.h"
#include "Maths/Matrix4.h"


#include "Entities/Components/CameraComponent.h"
#include "GameInfo.h"
#include "Graphics/Color.h"
#include "Maths/Vector3.h"



#include <vector>

#include "Graphics/Vertices/VertexType.h"

namespace CasaEngine
{
	static constexpr unsigned int NbLineMax = 10000;
	
	Line3DRendererComponent::Line3DRendererComponent(Game* pGame_) : 
		DrawableGameComponent(pGame_),
		m_pProgram(nullptr),
		m_VertexBuffer{},
		m_bRecomputeVB(false),
		m_NbLines(0)
	{
		DrawOrder(1000);
		UpdateOrder(5000);

		m_Lines.reserve(100);
	}

	Line3DRendererComponent::~Line3DRendererComponent()
	{
		delete m_pProgram;
		destroy(m_VertexBuffer);
	}

	void Line3DRendererComponent::OnLoadContent() 
	{
		m_pProgram = new Program("vs_3Dlines", "fs_3Dlines");
		m_VertexBuffer = createDynamicVertexBuffer(NbLineMax * 2, VertexPositionColor::ms_layout);
	}

	void Line3DRendererComponent::Update(const GameTime& /*gameTime_*/)
	{
		BuildVB();

		for (auto it = m_Lines.begin();
		     it != m_Lines.end();
		     ++it)
		{
			delete *it;
			*it = nullptr;
		}

		m_Lines.clear();
	}

	void Line3DRendererComponent::Draw()
	{
		if (m_NbLines == 0)
		{
			return;
		}

		CameraComponent *pCamera = Game::Instance().GetGameInfo().GetActiveCamera();
		bgfx::setViewTransform(0, pCamera->GetViewMatrix(), pCamera->GetProjectionMatrix());
		setVertexBuffer(0, m_VertexBuffer, 0, m_NbLines * 2);
		//bgfx::setIndexBuffer(m_IndexBuffer);
		//bgfx::setBuffer(0, m_VertexBuffer, bgfx::Access::Write);

		Matrix4 id;
		id.Identity();
		bgfx::setTransform(id);
		//bgfx::setUniform(m_TextureRepetitionUniform,  Vector4(m_pMaterial->GetTexture0Repeat().x, m_pMaterial->GetTexture0Repeat().y, 1.0f, 1.0f));
		bgfx::setState(BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_BLEND_ALPHA
			| BGFX_STATE_PT_LINES);

		submit(0, m_pProgram->Handle());
	}

	void Line3DRendererComponent::AddLine(const Vector3& start_, const Vector3& end_, const CColor& color_)
	{
		AddLine(start_, color_.ToABGR(), end_, color_.ToABGR());
	}

	void Line3DRendererComponent::AddLine(const Vector3& start_, const Vector3& end_, const unsigned int color_)
	{
		AddLine(start_, color_, end_, color_);
	}

	void Line3DRendererComponent::AddLine( const Vector3 &start_, const CColor &startColor_, const Vector3 &end_, const CColor &endColor_ )
	{
		AddLine(start_, startColor_.ToABGR(), end_, endColor_.ToABGR());
	}

	void Line3DRendererComponent::AddLine( const Vector3 &start_, const unsigned int &startColor_, const Vector3 &end_, const unsigned int &endColor_ )
	{
		const auto pLineData = new LineRenderer3DData();

		pLineData->Start = start_;
		pLineData->StartColor = startColor_;
		pLineData->End = end_;
		pLineData->EndColor = endColor_;
		
		m_Lines.push_back(pLineData);
		m_bRecomputeVB = true;
	}

	void Line3DRendererComponent::BuildVB()
	{
		if (m_bRecomputeVB == false)
		{
			return;
		}

		// TODO : don't do a new, use a temporary list (as a member)
		// or use directly a structure than it can be copied directly
		const auto pVertices = new VertexPositionColor[m_Lines.size() * 2];
		int index = 0;

		for (auto it = m_Lines.cbegin(); 
		     it != m_Lines.cend(); 
		     ++it)
		{
			const LineRenderer3DData *pLineData = *it;

			pVertices[index * 2 + 0].Position = pLineData->Start;
			pVertices[index * 2 + 0].Color = pLineData->StartColor;
			
			pVertices[index * 2 + 1].Position = pLineData->End;			
			pVertices[index * 2 + 1].Color = pLineData->EndColor;

			index++;
		}

		update(m_VertexBuffer , 0, 
			bgfx::copy(pVertices, static_cast<uint32_t>(m_Lines.size() * 2 * sizeof(VertexPositionColor)) ));

		delete pVertices;

		m_bRecomputeVB = false;
		m_NbLines = static_cast<unsigned int>(m_Lines.size());
	}
}
