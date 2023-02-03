#ifndef CELLSPACEPARTITION_H
#define CELLSPACEPARTITION_H

//-----------------------------------------------------------------------------
//
//  Name:   CellSpacePartition.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to divide a 2D space into a grid of cells each of which
//          may contain a number of entities. Once created and initialized 
//          with entities, fast proximity queries can be made by calling the
//          CalculateNeighbors method with a position and proximity radius.
//
//          If an entity is capable of moving, and therefore capable of moving
//          between cells, the Update method should be called each update-cycle
//          to synchronize the entity and the cell space it occupies
//
//-----------------------------------------------------------------------------
#pragma warning (disable:4786)

#include <vector>
#include <list>

#include "Maths/2D/InvertedAABBox2D.h"
#include "Maths/Vector2.h"

namespace CasaEngine
{
	//------------------------------------------------------------------------
	//
	//  defines a cell containing a list of pointers to entities
	//------------------------------------------------------------------------
	template <class entity>
	struct Cell
	{
		//all the entities inhabiting this cell
		std::list<entity>    Members;

		//the cell's bounding box (it's inverted because the Window's default
		//co-ordinate system has a y axis that increases as it descends)
		InvertedAABBox2D     BBox;

		Cell(Vector2 topleft,
			Vector2 botright) :BBox(InvertedAABBox2D(topleft, botright))
		{}
	};

	/////////// //////////////////////////////////////////////////////////////////
	//  the subdivision class
	///////////////////////////////////////////////////////////////////////////////
	template <class entity>
	class CellSpacePartition
	{
	private:

		//the required amount of cells in the space
		std::vector<Cell<entity> >               m_Cells;

		//this is used to store any valid neighbors when an agent searches
		//its neighboring space
		std::vector<entity>                      m_Neighbors;

		//this iterator will be used by the methods next and begin to traverse
		//through the above vector of neighbors
		typename std::vector<entity>::iterator   m_curNeighbor;

		//the width and height of the world space the entities inhabit
		float  m_fSpaceWidth;
		float  m_fSpaceHeight;

		//the number of cells the space is going to be divided up into
		int    m_iNumCellsX;
		int    m_iNumCellsY;

		float  m_fCellSizeX;
		float  m_fCellSizeY;


		//given a position in the game space this method determines the           
		//relevant cell's index
		int  PositionToIndex(const Vector2& pos)const;

	public:
		CellSpacePartition();

		//initialize partition
		void Build(float width, //width of the environment
			float height,       //height ...
			int   cellsX,       //number of cells horizontally
			int   cellsY);      //number of cells vertically

		//adds entities to the class by allocating them to the appropriate cell
		void AddEntity(const entity& ent);

		//update an entity's cell by calling this from your entity's Update method 
		void UpdateEntity(const entity& ent, Vector2 OldPos);

		//this method calculates all a target's neighbors and stores them in
		//the neighbor vector. After you have called this method use the begin, 
		//next and end methods to iterate through the vector.
		void CalculateNeighbors(Vector2 TargetPos, float QueryRadius);

		//returns a reference to the entity at the front of the neighbor vector
		entity& begin() { m_curNeighbor = m_Neighbors.begin(); return *m_curNeighbor; }

		//this returns the next entity in the neighbor vector
		entity& next() { ++m_curNeighbor; return *m_curNeighbor; }

		//returns true if the end of the vector is found (a zero value marks the end)
		bool   end() { return (m_curNeighbor == m_Neighbors.end()) || (*m_curNeighbor == 0); }

		//empties the cells of entities
		void        EmptyCells();

		//call this to use the gdi to render the cell edges
		void RenderCells() const;
	};



	//----------------------------- ctor ---------------------------------------
	//--------------------------------------------------------------------------
	template<class entity>
	CellSpacePartition<entity>::CellSpacePartition() :
		m_fSpaceWidth(0),
		m_fSpaceHeight(0),
		m_iNumCellsX(0),
		m_iNumCellsY(0),
		m_fCellSizeX(0),
		m_fCellSizeY(0)
	{
	}

	//
	template<class entity>
	void CellSpacePartition<entity>::Build(
		float  width,        //width of 2D space
		float  height,       //height...
		int    cellsX,       //number of divisions horizontally
		int    cellsY)       //and vertically
	{
		m_fSpaceWidth = width;
		m_fSpaceHeight = height;
		m_iNumCellsX = cellsX;
		m_iNumCellsY = cellsY;

		m_Cells.clear();

		//calculate bounds of each cell
		m_fCellSizeX = width / cellsX;
		m_fCellSizeY = height / cellsY;

		//create the cells
		for (int y = 0; y < m_iNumCellsY; ++y)
		{
			for (int x = 0; x < m_iNumCellsX; ++x)
			{
				float left = x * m_fCellSizeX;
				float right = left + m_fCellSizeX;
				float top = y * m_fCellSizeY;
				float bot = top + m_fCellSizeY;

				m_Cells.push_back(Cell<entity>(Vector2(left, top), Vector2(right, bot)));
			}
		}
	}

	//----------------------- CalculateNeighbors ----------------------------
	//
	//  This must be called to create the vector of neighbors.This method 
	//  examines each cell within range of the target, If the 
	//  cells contain entities then they are tested to see if they are situated
	//  within the target's neighborhood region. If they are they are added to
	//  neighbor list
	//------------------------------------------------------------------------
	template<class entity>
	void CellSpacePartition<entity>::CalculateNeighbors(Vector2 TargetPos, float QueryRadius)
	{
		//create an iterator and set it to the beginning of the neighbor vector
		typename std::vector<entity>::iterator curNbor = m_Neighbors.begin();

		//create the query box that is the bounding box of the target's query area
		InvertedAABBox2D QueryBox(TargetPos - Vector2(QueryRadius, QueryRadius), TargetPos + Vector2(QueryRadius, QueryRadius));

		//iterate through each cell and test to see if its bounding box overlaps
		//with the query box. If it does and it also contains entities then
		//make further proximity tests.
		typename std::vector<Cell<entity> >::iterator curCell;
		for (curCell = m_Cells.begin(); curCell != m_Cells.end(); ++curCell)
		{
			//test to see if this cell contains members and if it overlaps the
			//query box
			if (curCell->BBox.isOverlappedWith(QueryBox) && !curCell->Members.empty())
			{
				//add any entities found within query radius to the neighbor list
				typename  std::list<entity>::iterator it = curCell->Members.begin();
				for (it; it != curCell->Members.end(); ++it)
				{
					auto position = (*it)->GetCoordinates().GetPosition();

					if (Vector2(position.x, position.y).DistanceSquared(TargetPos) < QueryRadius * QueryRadius)
					{
						*curNbor++ = *it;
					}
				}
			}
		}//next cell

		//mark the end of the list with a zero.
		*curNbor = 0;
	}


	//--------------------------- Empty --------------------------------------
	//
	//  clears the cells of all entities
	//------------------------------------------------------------------------
	template<class entity>
	void CellSpacePartition<entity>::EmptyCells()
	{
		typename std::vector<Cell<entity> >::iterator it = m_Cells.begin();

		for (it; it != m_Cells.end(); ++it)
		{
			it->Members.clear();
		}
	}

	//--------------------- PositionToIndex ----------------------------------
	//
	//  Given a 2D vector representing a position within the game world, this
	//  method calculates an index into its appropriate cell
	//------------------------------------------------------------------------
	template<class entity>
	int CellSpacePartition<entity>::PositionToIndex(const Vector2& pos)const
	{
		int idx = static_cast<int>(m_iNumCellsX * pos.x / m_fSpaceWidth) +
			static_cast<int>(m_iNumCellsY * pos.y / m_fSpaceHeight) * m_iNumCellsX;

		//if the entity's position is equal to Vector2(m_fSpaceWidth, m_fSpaceHeight)
		//then the index will overshoot. We need to check for this and adjust
		if (idx > static_cast<int>(m_Cells.size()) - 1) idx = static_cast<int>(m_Cells.size()) - 1;

		return idx;
	}

	//----------------------- AddEntity --------------------------------------
	//
	//  Used to add the entities to the data structure
	//------------------------------------------------------------------------
	template<class entity>
	void CellSpacePartition<entity>::AddEntity(const entity& ent)
	{
		CA_ASSERT(ent, "CellSpacePartition<entity>::AddEntity() : entity is nullptr");

		Transform2DComponent* pTrans = ent->GetComponentMgr()->template GetComponent<Transform2DComponent>();
		CA_ASSERT(pTrans != nullptr, "CellSpacePartition<entity>::AddEntity() : can't find Transform2DComponent");

		int sz = m_Cells.size();
		int idx = PositionToIndex(pTrans->GetPosition());

		m_Cells[idx].Members.push_back(ent);
	}

	//----------------------- UpdateEntity -----------------------------------
	//
	//  Checks to see if an entity has moved cells. If so the data structure
	//  is updated accordingly
	//------------------------------------------------------------------------
	template<class entity>
	void CellSpacePartition<entity>::UpdateEntity(const entity& ent,
		Vector2       OldPos)
	{
		//if the index for the old pos and the new pos are not equal then
		//the entity has moved to another cell.
		int OldIdx = PositionToIndex(OldPos);

		Transform2DComponent* pTrans = ent->GetComponentMgr()->template GetComponent<Transform2DComponent>();
		CA_ASSERT(pTrans != nullptr, "CellSpacePartition<entity>::UpdateEntity() : can't find Transform2DComponent");

		int NewIdx = PositionToIndex(pTrans->GetPosition());

		if (NewIdx == OldIdx) return;

		//the entity has moved into another cell so delete from current cell
		//and add to new one
		m_Cells[OldIdx].Members.remove(ent);
		m_Cells[NewIdx].Members.push_back(ent);
	}

	//-------------------------- RenderCells -----------------------------------
	//--------------------------------------------------------------------------
	template<class entity>
	void CellSpacePartition<entity>::RenderCells()const
	{
		typename std::vector<Cell<entity> >::const_iterator curCell;
		for (curCell = m_Cells.begin(); curCell != m_Cells.end(); ++curCell)
		{
			curCell->BBox.Render(false);
		}
	}

}

#endif