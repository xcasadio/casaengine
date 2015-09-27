#ifndef STEERINGPARAMS_H_
#define STEERINGPARAMS_H_

#include "CA_Export.h"

namespace CasaEngine
{
	/**
	 *	
	 */
	struct CA_EXPORT SteeringParams
	{
	public:
  
	  //length of the 'detection box' utilized in obstacle avoidance
	  float                 m_fDBoxLength;
  
	  //the length of the 'feeler/s' used in wall detection
	  float                 m_fWallDetectionFeelerLength;

	  //explained above
	  float        m_fWanderJitter;
	  float        m_fWanderRadius;
	  float        m_fWanderDistance;


	  //multipliers. These can be adjusted to effect strength of the  
	  //appropriate behavior. Useful to get flocking the way you require
	  //for example.
	  float        m_fWeightSeparation;
	  float        m_fWeightCohesion;
	  float        m_fWeightAlignment;
	  float        m_fWeightWander;
	  float        m_fWeightObstacleAvoidance;
	  float        m_fWeightWallAvoidance;
	  float        m_fWeightSeek;
	  float        m_fWeightFlee;
	  float        m_fWeightArrive;
	  float        m_fWeightPursuit;
	  float        m_fWeightOffsetPursuit;
	  float        m_fWeightInterpose;
	  float        m_fWeightHide;
	  float        m_fWeightEvade;
	  float        m_fWeightFollowPath;

	  //how close a neighbour must be before an agent perceives it (considers it
	  //to be within its neighborhood)
	  float        m_fViewDistance;

	  //these are the probabilities that a steering behavior will be used
	  //when the Prioritized Dither calculate method is used to sum
	  //combined behaviors
	  float m_PrWallAvoidance;
	  float m_PrObstacleAvoidance;
	  float m_PrSeparation;
	  float m_PrAlignment;
	  float m_PrCohesion;
	  float m_PrWander;
	  float m_PrSeek;
	  float m_PrFlee;
	  float m_PrEvade;
	  float m_PrHide;
	  float m_PrArrive;

  
	}; // struct SteeringParams

} // namespace CasaEngine

#endif // STEERINGPARAMS_H_
