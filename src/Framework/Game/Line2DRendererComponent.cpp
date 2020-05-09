
#include "Base.h"

#include "Game/Line2DRendererComponent.h"
#include "Game/Game.h"
#include "GameTime.h"
#include "Maths/Matrix4.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Renderer/Enums.h"



#include "Entities/Components/CameraComponent.h"
#include "GameInfo.h"
#include "Graphics/Color.h"
#include "Maths/Vector2.h"

#include "Maths/Vector3.h"
#include "Memory/MemoryAllocation.h"

#include <vector>

namespace CasaEngine
{
	static const unsigned int NbLineMax = 1024;


	/**
	 * 
	 */
	Line2DRendererComponent::Line2DRendererComponent(Game* pGame_) : 
		DrawableGameComponent(pGame_),
		m_bRecomputeVB(false),
		m_NbLines(0)
	{
		DrawOrder(100000);
		UpdateOrder(5000);

		m_Lines.reserve(100);
	}

	/**
	 * 
	 */
	Line2DRendererComponent::~Line2DRendererComponent()
	{
		bgfx::destroy(m_VertexBuffer);
	}

	/**
	 * 
	 */
	void Line2DRendererComponent::OnLoadContent() 
	{
		m_VertexBuffer = bgfx::createDynamicVertexBuffer(NbLineMax * 2, VertexPositionColor::ms_layout);
		//m_pEffect = IRenderer::Get().CreateEffectFromFile("line_renderer");
	}

	/**
	 * 
	 */
	void Line2DRendererComponent::Update(const GameTime& /*gameTime_*/)
	{
		BuildVB();

		for (std::vector<LineRenderer2DData *>::iterator it = m_Lines.begin();
			it != m_Lines.end();
			it++)
		{
			::delete (*it);
			*it = nullptr;
		}

		m_Lines.clear();
	}

	/**
	 * 
	 */
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

		Matrix4 matProj;
		matProj.OrthoOffCenter(
			static_cast<float>(pCamera->GetViewport().X() * GetGame()->GetWindow()->getSize().x),
			static_cast<float>(pCamera->GetViewport().Y() * GetGame()->GetWindow()->getSize().y),
			static_cast<float>(pCamera->GetViewport().Width() * GetGame()->GetWindow()->getSize().x),
			static_cast<float>(pCamera->GetViewport().Height() * GetGame()->GetWindow()->getSize().y),
			0.0f, 1000.0f);

		bgfx::setVertexBuffer(0, m_VertexBuffer, 0, m_NbLines);
	}

	/**
	 * 
	 */
	void Line2DRendererComponent::AddLine( const Vector2F &start_, const CColor &startColor_, 
		const Vector2F &end_, const CColor &endColor_ )
	{
		AddLine(start_, startColor_.ToABGR(), end_, endColor_.ToABGR());
	}

	/**
	 * 
	 */
	void Line2DRendererComponent::AddLine( const Vector2F &start_, const unsigned int &startColor_, 
		const Vector2F &end_, const unsigned int &endColor_ )
	{
		LineRenderer2DData *pLineData = ::new LineRenderer2DData();

		pLineData->Start = start_;
		pLineData->StartColor = startColor_;
		pLineData->End = end_;
		pLineData->EndColor = endColor_;
		
		m_Lines.push_back(pLineData);
		m_bRecomputeVB = true;
		m_NbLines = m_Lines.size();
	}

	/**
	 * 
	 */
	void Line2DRendererComponent::BuildVB()
	{
		if (m_bRecomputeVB == false)
		{
			return;
		}

		VertexPositionColor* pVertices = ::new VertexPositionColor[m_Lines.size() * 2];
		int nbLines = 0;

		for (std::vector<LineRenderer2DData *>::const_iterator it = m_Lines.cbegin(); 
			it != m_Lines.cend(); 
			it++)
		{
			LineRenderer2DData *pLineData = *it;

			pVertices[nbLines * 2 + 0].Position = Vector3F(pLineData->Start.x, pLineData->Start.y);
			pVertices[nbLines * 2 + 0].Color = pLineData->StartColor;

			pVertices[nbLines * 2 + 1].Position = Vector3F(pLineData->End.x, pLineData->End.y);
			pVertices[nbLines * 2 + 1].Color = pLineData->EndColor;

			nbLines++;
		}

		bgfx::update(m_VertexBuffer, 0 , bgfx::copy(pVertices, (uint32_t)m_Lines.size() * 2 * sizeof(VertexPositionColor) ));
		::delete[] pVertices;

		m_bRecomputeVB = false;
	}

}
