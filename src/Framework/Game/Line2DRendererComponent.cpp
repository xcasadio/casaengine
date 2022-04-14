#include "Base.h"

#include "Game/Line2DRendererComponent.h"
#include "Game/Game.h"
#include "GameTime.h"
#include "Maths/Matrix4.h"


#include "Entities/Components/CameraComponent.h"
#include "GameInfo.h"
#include "Graphics/Color.h"
#include "Maths/Vector2.h"

#include "Maths/Vector3.h"

#include <vector>

#include "Graphics/Vertices/VertexType.h"

namespace CasaEngine
{
	static const unsigned int NbLineMax = 1024;

	Line2DRendererComponent::Line2DRendererComponent(Game* pGame_) : 
		DrawableGameComponent(pGame_),
		m_bRecomputeVB(false),
		m_NbLines(0)
	{
		DrawOrder(100000);
		UpdateOrder(5000);

		m_Lines.reserve(100);
	}

	Line2DRendererComponent::~Line2DRendererComponent()
	{
		destroy(m_VertexBuffer);
	}

	void Line2DRendererComponent::OnLoadContent() 
	{
		m_VertexBuffer = bgfx::createDynamicVertexBuffer(NbLineMax * 2, VertexPositionColor::ms_layout);
		//m_pEffect = IRenderer::Get().CreateEffectFromFile("line_renderer");
	}

	void Line2DRendererComponent::Update(const GameTime& /*gameTime_*/)
	{
		BuildVB();

		for (auto it = m_Lines.begin();
		     it != m_Lines.end();
		     ++it)
		{
			delete *it;
		}

		m_Lines.clear();
	}

	void Line2DRendererComponent::Draw()
	{
		if (m_NbLines == 0)
		{
			return;
		}

		CameraComponent *pCamera = Game::Instance().GetGameInfo().GetActiveCamera();

		bgfx::setState(BGFX_STATE_WRITE_RGB // depth always ??
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_BLEND_ALPHA
			| BGFX_STATE_PT_LINES);

		Matrix4 matProj = Matrix4::CreateOrthographicOffCenter(
			pCamera->GetViewport().X() * GetGame()->GetWindowSize().x,
			pCamera->GetViewport().Width() * GetGame()->GetWindowSize().x,
			pCamera->GetViewport().Y() * GetGame()->GetWindowSize().y,
			pCamera->GetViewport().Height() * GetGame()->GetWindowSize().y,
			pCamera->GetViewport().NearClipPlane(),
			pCamera->GetViewport().FarClipPlane());

		setVertexBuffer(0, m_VertexBuffer, 0, m_NbLines);
	}

	void Line2DRendererComponent::AddLine( const Vector2 &start_, const CColor &startColor_, 
		const Vector2 &end_, const CColor &endColor_ )
	{
		AddLine(start_, startColor_.ToABGR(), end_, endColor_.ToABGR());
	}

	void Line2DRendererComponent::AddLine( const Vector2 &start_, const unsigned int &startColor_, 
		const Vector2 &end_, const unsigned int &endColor_ )
	{
		const auto pLineData = ::new LineRenderer2DData();

		pLineData->Start = start_;
		pLineData->StartColor = startColor_;
		pLineData->End = end_;
		pLineData->EndColor = endColor_;
		
		m_Lines.push_back(pLineData);
		m_bRecomputeVB = true;
		m_NbLines = static_cast<unsigned int>(m_Lines.size());
	}

	void Line2DRendererComponent::BuildVB()
	{
		if (m_bRecomputeVB == false)
		{
			return;
		}
		//NEW_ARRAY_PT
		const auto pVertices = new VertexPositionColor[m_Lines.size() * 2];
		int nbLines = 0;

		for (auto it = m_Lines.cbegin(); 
		     it != m_Lines.cend(); 
		     ++it)
		{
			const LineRenderer2DData *pLineData = *it;

			pVertices[nbLines * 2 + 0].Position = Vector3(pLineData->Start.x, pLineData->Start.y, 0);
			pVertices[nbLines * 2 + 0].Color = pLineData->StartColor;

			pVertices[nbLines * 2 + 1].Position = Vector3(pLineData->End.x, pLineData->End.y, 0);
			pVertices[nbLines * 2 + 1].Color = pLineData->EndColor;

			nbLines++;
		}

		update(m_VertexBuffer, 0 , bgfx::copy(pVertices, static_cast<uint32_t>(m_Lines.size()) * 2 * sizeof(VertexPositionColor) ));
		//DELETE_ARRAY_PT
		delete pVertices;

		m_bRecomputeVB = false;
	}

}
