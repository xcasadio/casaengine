
#include "Base.h"
#include "Entities/BaseEntity.h"

#include "GridComponent.h"
#include "Game/Line3DRendererComponent.h"
#include "Game/Game.h"
#include "Entities/ComponentTypeEnum.h"

namespace CasaEngine
{

	/**
	 * 
	 */
	GridComponent::GridComponent(BaseEntity* pEntity_) : 
		Component(pEntity_, GRID),
		m_iSize(50),
		m_pLineManager(nullptr),
		m_bNeedToUpdateBuffers(true)
	{
		
	}

	/**
	 * 
	 */
	GridComponent::~GridComponent()
	{
	}

	/**
	 * 
	 */
	void GridComponent::Initialize()
	{
		m_pLineManager = Game::Instance().GetGameComponent<Line3DRendererComponent>();
		CA_ASSERT(m_pLineManager != nullptr, "GridComponent::Initialize() : Line3DRendererComponent is nullptr");
	
		CreateBuffers();
	}

	/**
	 * 
	 */
	void GridComponent::Update(const GameTime& /*gameTime_*/)
	{
		CreateBuffers();
	}

	/**
	 * 
	 */
	void GridComponent::Draw()
	{
		for (std::vector<TGridPointData>::const_iterator it = m_Vertices.cbegin();
			it != m_Vertices.cend();
			it++)
		{
			m_pLineManager->AddLine((*it).Start, (*it).StartColor, (*it).End, (*it).EndColor);
		}
	}

	/**
	 * 
	 */
	int GridComponent::Size() const 
	{ 
		return m_iSize; 
	}

	/**
	 * 
	 */
	void GridComponent::Size(int val) 
	{
		if (m_iSize != val)
		{
			m_iSize = val;
			m_bNeedToUpdateBuffers = true;
		}
	}

	/**
	 * 
	 */
	void GridComponent::CreateBuffers()
	{
		if (m_bNeedToUpdateBuffers == true)
		{
			m_bNeedToUpdateBuffers = false;
		
			m_Vertices.clear();
			Color color;

			//Initialize the custom vertex values for the lines.
			for (int x = m_iSize; x > 0; x--)
			{
				if (x % 10 == 0)
				{
					color = Color::DarkBlue;
				}
				else if (x % 5 == 0)
				{
					color = Color::DarkGray;
				}
				else
				{
					color = Color::DimGray;
				}

				m_Vertices.push_back(TGridPointData(
					Vector3(static_cast<float>(x), 0.0f, static_cast<float>(m_iSize)), color,
					Vector3(static_cast<float>(x), 0.0f, -static_cast<float>(m_iSize)), color));

				m_Vertices.push_back(TGridPointData(
					Vector3(-static_cast<float>(x), 0.0f, static_cast<float>(m_iSize)), color,
					Vector3(-static_cast<float>(x), 0.0f, -static_cast<float>(m_iSize)), color));

				m_Vertices.push_back(TGridPointData(
					Vector3(static_cast<float>(m_iSize), 0.0f, static_cast<float>(x)), color,
					Vector3(-static_cast<float>(m_iSize), 0.0f, static_cast<float>(x)), color));

				m_Vertices.push_back(TGridPointData(
					Vector3(static_cast<float>(m_iSize), 0.0f, -static_cast<float>(x)), color,
					Vector3(-static_cast<float>(m_iSize), 0.0f, -static_cast<float>(x)), color));
			}

			color = Color::DarkBlue;

			m_Vertices.push_back(TGridPointData(
				Vector3(-static_cast<float>(m_iSize), 0.0f, 0.0f), color,
				Vector3(static_cast<float>(m_iSize), 0.0f, 0.0f), color));
			m_Vertices.push_back(TGridPointData(
				Vector3(0.0f, 0.0f, static_cast<float>(m_iSize)), color,
				Vector3(0.0f, 0.0f, -static_cast<float>(m_iSize)), color));
		}
	}

/**
 * 
 */
/*void StaticSpriteComponent::HandleEvent(const Event* pEvent_)
{

}*/

/**
 * 
 */
void GridComponent::Write(std::ostream& /*os*/) const
{

}

/**
 * 
 */
void GridComponent::Read (std::ifstream& /*is*/)
{

}

}
