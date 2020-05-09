#include "Base.h"

#include "Game/Line3DRendererComponent.h"
#include "Game/Game.h"
#include "GameTime.h"
#include "Maths/Matrix4.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Renderer/Enums.h"



#include "Entities/Components/CameraComponent.h"
#include "GameInfo.h"
#include "Graphics/Color.h"
#include "Maths/Vector3.h"


#include "Memory/MemoryAllocation.h"

#include <vector>

#include "Graphics/Vertices/VertexType.h"

namespace CasaEngine
{
	static const unsigned int NbLineMax = 1024;


	/**
	 * 
	 */
	Line3DRendererComponent::Line3DRendererComponent(Game* pGame_) : 
		DrawableGameComponent(pGame_),
		m_bRecomputeVB(false),
		m_NbLines(0),
		m_pProgram(nullptr)
	{
		DrawOrder(1000);
		UpdateOrder(5000);

		m_Lines.reserve(100);
	}

	/**
	 * 
	 */
	Line3DRendererComponent::~Line3DRendererComponent()
	{
		DELETE_AO m_pProgram;
		bgfx::destroy(m_VertexBuffer);
	}

	/**
	 * 
	 */
	void Line3DRendererComponent::OnLoadContent() 
	{
		m_pProgram = NEW_AO Program("vs_3Dlines", "fs_3Dlines");
		m_VertexBuffer = bgfx::createDynamicVertexBuffer(NbLineMax * 2, VertexPositionColor::ms_layout);
	}

	/**
	 * 
	 */
	void Line3DRendererComponent::Update(const GameTime& /*gameTime_*/)
	{
		BuildVB();

		for (std::vector<LineRenderer3DData *>::iterator it = m_Lines.begin();
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
	void Line3DRendererComponent::Draw()
	{
		if (m_NbLines == 0)
		{
			return;
		}

		CameraComponent *pCamera = Game::Instance().GetGameInfo().GetActiveCamera();
		bgfx::setViewTransform(0, pCamera->GetViewMatrix(), pCamera->GetProjectionMatrix());
		bgfx::setVertexBuffer(0, m_VertexBuffer, 0, m_NbLines * 2);
		//bgfx::setIndexBuffer(m_IndexBuffer);
		//bgfx::setBuffer(0, m_VertexBuffer, bgfx::Access::Write);

		Matrix4 id;
		bgfx::setTransform(id);
		//bgfx::setUniform(m_TextureRepitionUniform,  Vector4F(m_pMaterial->GetTexture0Repeat().x, m_pMaterial->GetTexture0Repeat().y, 1.0f, 1.0f));
		bgfx::setState(BGFX_STATE_WRITE_RGB // depth always ??
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_BLEND_ALPHA
			| BGFX_STATE_PT_LINES);

		bgfx::submit(0, m_pProgram->Handle());
	}

	/**
	 * 
	 */
	void Line3DRendererComponent::AddLine( const Vector3F &start_, const CColor &startColor_, 
		const Vector3F &end_, const CColor &endColor_ )
	{
		AddLine(start_, startColor_.ToABGR(), end_, endColor_.ToABGR());
	}

	/**
	 * 
	 */
	void Line3DRendererComponent::AddLine( const Vector3F &start_, const unsigned int &startColor_, 
		const Vector3F &end_, const unsigned int &endColor_ )
	{
		LineRenderer3DData *pLineData = ::new LineRenderer3DData();

		pLineData->Start = start_;
		pLineData->StartColor = startColor_;
		pLineData->End = end_;
		pLineData->EndColor = endColor_;
		
		m_Lines.push_back(pLineData);
		m_bRecomputeVB = true;
	}

	/**
	 * 
	 */
	void Line3DRendererComponent::BuildVB()
	{
		if (m_bRecomputeVB == false)
		{
			return;
		}

		// TODO : don't do a new, use a temporary list (as a member)
		// or use directly a structure than it can be copied directly
		VertexPositionColor* pVertices = ::new VertexPositionColor[m_Lines.size() * 2];
		int index = 0;

		for (std::vector<LineRenderer3DData *>::const_iterator it = m_Lines.cbegin(); 
			it != m_Lines.cend(); 
			it++)
		{
			LineRenderer3DData *pLineData = *it;

			pVertices[index * 2 + 0].Position = pLineData->Start;
			pVertices[index * 2 + 0].Color = pLineData->StartColor;
			
			pVertices[index * 2 + 1].Position = pLineData->End;			
			pVertices[index * 2 + 1].Color = pLineData->EndColor;

			index++;
		}

		bgfx::update(m_VertexBuffer , 0, 
			bgfx::copy(pVertices, (uint32_t)(m_Lines.size() * 2 * sizeof(VertexPositionColor)) ));

		::delete[] pVertices;

		m_bRecomputeVB = false;
		m_NbLines = m_Lines.size();
	}

}
