#pragma once

#include <list>
#include <vector>
#include <iosfwd>

#include "CA_Export.h"

#include "Entities/BaseEntity.h"
#include "Entities/Component.h"
#include "GameTime.h"
#include "Maths/2D/Line2D.h"
#include "Maths/2D/Path.h"
#include "MovingEntity2DComponent.h"
#include "Maths/Vector2.h"


namespace CasaEngine
{
	const float WanderRad    = 1.2f; //the radius of the constraining circle for the wander behavior
	const float WanderDist   = 2.0f; //distance the wander circle is projected in front of the agent
	const float WanderJitterPerSec = 80.0f; //the maximum amount of displacement along the circle each frame
	const float WaypointSeekDist   = 20.f; //used in path following

	class CA_EXPORT SteeringBehaviorComponent :
		public Component
	{
	public:
		enum summing_method{WEIGHTED_AVERAGE, PRIORITIZED, DITHERED};

	private:

		enum behavior_type
		{
			none               = 0x00000,
			seek               = 0x00002,
			flee               = 0x00004,
			arrive             = 0x00008,
			wander             = 0x00010,
			cohesion           = 0x00020,
			separation         = 0x00040,
			allignment         = 0x00080,
			obstacle_avoidance = 0x00100,
			wall_avoidance     = 0x00200,
			follow_path        = 0x00400,
			pursuit            = 0x00800,
			evade              = 0x01000,
			interpose          = 0x02000,
			hide               = 0x04000,
			flock              = 0x08000,
			offset_pursuit     = 0x10000,
		};

	private:
		//PhysicComponent* m_pPhysicComponent;
		MovingEntity2DComponent* m_pMovingEntity;
		Vector2 m_Position2D;

		//a pointer to the owner of this instance
		//BaseEntity*     m_pVehicle;   

		//the steering force created by the combined effect of all
		//the selected behaviors
		Vector2    m_vSteeringForce;

		//these can be used to keep track of friends, pursuers, or prey
		BaseEntity*     m_pTargetAgent1;
		BaseEntity*     m_pTargetAgent2;

		//the current target
		Vector2    m_vTarget;

		//a vertex buffer to contain the feelers required for wall avoidance  
		std::vector<Vector2> m_Feelers;

		//====== Steering behavior settings =========

		//the current position on the wander circle the agent is
		//attempting to steer towards
		Vector2     m_vWanderTarget; 

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

		//length of the 'detection box' utilized in obstacle avoidance
		float        m_fDBoxLength;

		//the length of the 'feeler/s' used in wall detection
		float        m_fWallDetectionFeelerLength;

		//how far the agent can 'see'
		float        m_fViewDistance;		

		//the distance (squared) a BaseEntity has to be from a path waypoint before
		//it starts seeking to the next waypoint
		float        m_fWaypointSeekDistSq;

		//these are the probabilities that a steering behavior will be used
		//when the prioritized dither calculate method is used
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

		//=========================================

		//any offset used for formations or offset pursuit
		Vector2     m_vOffset;

		//binary flags to indicate whether or not a behavior should be active
		int           m_iFlags;

		//pointer to any current path
		Path*          m_pPath;


		//Arrive makes use of these to determine how quickly a BaseEntity
		//should decelerate to its target
		enum Deceleration{SLOW = 3, NORMAL = 2, FAST = 1};

		//default
		Deceleration m_Deceleration;

		//is cell space partitioning to be used or not?
		bool          m_bCellSpaceOn;

		//what type of method is used to sum any active behavior
		summing_method  m_SummingMethod;

		//this is used to store any valid neighbors when an agent searches
		//its neighboring space
		std::vector<BaseEntity *> m_Neighbors;

	public:
		SteeringBehaviorComponent(BaseEntity* pEntity_);
		virtual ~SteeringBehaviorComponent();

		//all entities must implement an Initialize function
		void Initialize();

		//all entities must implement an update function
		void  Update(const GameTime& gameTime_);

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);
		// 
		//calculates and sums the steering forces from any active behaviors
		Vector2 Calculate(float elapsedTime_);

		//calculates the component of the steering force that is parallel
		//with the BaseEntity heading
		float    ForwardComponent();

		//calculates the component of the steering force that is perpendicular
		//with the BaseEntity heading
		float    SideComponent();



		//renders visual aids and info for seeing how each behavior is
		//calculated
		void      RenderAids();

		void      SetTarget(const Vector2 t){m_vTarget = t;}

		void      SetTargetAgent1(BaseEntity* Agent){m_pTargetAgent1 = Agent;}
		void      SetTargetAgent2(BaseEntity* Agent){m_pTargetAgent2 = Agent;}

		void      SetOffset(const Vector2 offset){m_vOffset = offset;}
		Vector2  GetOffset()const{return m_vOffset;}

		void      SetPath(std::list<Vector2> new_path){m_pPath->Set(new_path);}
		/*void      CreateRandomPath(int num_waypoints, int mx, int my, int cx, int cy)const
			{m_pPath->CreateRandomPath(num_waypoints, mx, my, cx, cy);}*/

		Vector2 Force()const{return m_vSteeringForce;}

		void      ToggleSpacePartitioningOnOff(){m_bCellSpaceOn = !m_bCellSpaceOn;}
		bool      isSpacePartitioningOn()const{return m_bCellSpaceOn;}

		void      SetSummingMethod(summing_method sm){m_SummingMethod = sm;}


		void FleeOn(){m_iFlags |= flee;}
		void SeekOn(){m_iFlags |= seek;}
		void ArriveOn(){m_iFlags |= arrive;}
		void WanderOn(){m_iFlags |= wander;}
		void PursuitOn(BaseEntity* v){m_iFlags |= pursuit; m_pTargetAgent1 = v;}
		void EvadeOn(BaseEntity* v){m_iFlags |= evade; m_pTargetAgent1 = v;}
		void CohesionOn(){m_iFlags |= cohesion;}
		void SeparationOn(){m_iFlags |= separation;}
		void AlignmentOn(){m_iFlags |= allignment;}
		void ObstacleAvoidanceOn(){m_iFlags |= obstacle_avoidance;}
		void WallAvoidanceOn(){m_iFlags |= wall_avoidance;}
		void FollowPathOn(){m_iFlags |= follow_path;}
		void InterposeOn(BaseEntity* v1, BaseEntity* v2){m_iFlags |= interpose; m_pTargetAgent1 = v1; m_pTargetAgent2 = v2;}
		void HideOn(BaseEntity* v){m_iFlags |= hide; m_pTargetAgent1 = v;}
		void OffsetPursuitOn(BaseEntity* v1, const Vector2 offset){m_iFlags |= offset_pursuit; m_vOffset = offset; m_pTargetAgent1 = v1;}  
		void FlockingOn(){CohesionOn(); AlignmentOn(); SeparationOn(); WanderOn();}

		void FleeOff()  {if(On(flee))   m_iFlags ^=flee;}
		void SeekOff()  {if(On(seek))   m_iFlags ^=seek;}
		void ArriveOff(){if(On(arrive)) m_iFlags ^=arrive;}
		void WanderOff(){if(On(wander)) m_iFlags ^=wander;}
		void PursuitOff(){if(On(pursuit)) m_iFlags ^=pursuit;}
		void EvadeOff(){if(On(evade)) m_iFlags ^=evade;}
		void CohesionOff(){if(On(cohesion)) m_iFlags ^=cohesion;}
		void SeparationOff(){if(On(separation)) m_iFlags ^=separation;}
		void AlignmentOff(){if(On(allignment)) m_iFlags ^=allignment;}
		void ObstacleAvoidanceOff(){if(On(obstacle_avoidance)) m_iFlags ^=obstacle_avoidance;}
		void WallAvoidanceOff(){if(On(wall_avoidance)) m_iFlags ^=wall_avoidance;}
		void FollowPathOff(){if(On(follow_path)) m_iFlags ^=follow_path;}
		void InterposeOff(){if(On(interpose)) m_iFlags ^=interpose;}
		void HideOff(){if(On(hide)) m_iFlags ^=hide;}
		void OffsetPursuitOff(){if(On(offset_pursuit)) m_iFlags ^=offset_pursuit;}
		void FlockingOff(){CohesionOff(); AlignmentOff(); SeparationOff(); WanderOff();}

		bool isFleeOn(){return On(flee);}
		bool isSeekOn(){return On(seek);}
		bool isArriveOn(){return On(arrive);}
		bool isWanderOn(){return On(wander);}
		bool isPursuitOn(){return On(pursuit);}
		bool isEvadeOn(){return On(evade);}
		bool isCohesionOn(){return On(cohesion);}
		bool isSeparationOn(){return On(separation);}
		bool isAlignmentOn(){return On(allignment);}
		bool isObstacleAvoidanceOn(){return On(obstacle_avoidance);}
		bool isWallAvoidanceOn(){return On(wall_avoidance);}
		bool isFollowPathOn(){return On(follow_path);}
		bool isInterposeOn(){return On(interpose);}
		bool isHideOn(){return On(hide);}
		bool isOffsetPursuitOn(){return On(offset_pursuit);}

		//=================== settings ======================

		// GET
		float DBoxLength()const{return m_fDBoxLength;}
		const std::vector<Vector2>& GetFeelers()const{return m_Feelers;}

		float WanderJitter()const{return m_fWanderJitter;}
		float WanderDistance()const{return m_fWanderDistance;}
		float WanderRadius()const{return m_fWanderRadius;}

		float SeparationWeight()const{return m_fWeightSeparation;}
		float AlignmentWeight()const{return m_fWeightAlignment;}
		float CohesionWeight()const{return m_fWeightCohesion;}

		float WanderWeight()const{return m_fWeightWander;}
		float ObstacleAvoidanceWeight()const{return m_fWeightObstacleAvoidance;}
		float WallAvoidanceWeight()const{return m_fWeightWallAvoidance;}
		float SeekWeight()const{return m_fWeightSeek;}
		float FleeWeight()const{return m_fWeightFlee;}
		float ArriveWeight()const{return m_fWeightArrive;}
		float PursuitWeight()const{return m_fWeightPursuit;}
		float OffsetPursuitWeight()const{return m_fWeightOffsetPursuit;}
		float InterposeWeight()const{return m_fWeightInterpose;}
		float HideWeight()const{return m_fWeightHide;}
		float EvadeWeight()const{return m_fWeightEvade;}
		float FollowPathWeight()const{return m_fWeightFollowPath;}

		float PrWallAvoidance()const{return m_PrWallAvoidance;}
		float PrObstacleAvoidance()const{return m_PrObstacleAvoidance;}
		float PrSeparation()const{return m_PrSeparation;}
		float PrAlignment()const{return m_PrAlignment;}
		float PrCohesion()const{return m_PrCohesion;}
		float PrWander()const{return m_PrWander;}
		float PrSeek()const{return m_PrSeek;}
		float PrFlee()const{return m_PrFlee;}
		float PrEvade()const{return m_PrEvade;}
		float PrHide()const{return m_PrHide;}
		float PrArrive()const{return m_PrArrive;}

		// SET
		void DBoxLength(float val_){m_fDBoxLength = val_;}

		void WallDetectionFeelerLength(float val_){m_fWallDetectionFeelerLength = val_;}
		void ViewDistance(float val_){m_fViewDistance = val_;}
		void WaypointSeekDist(float val_){m_fWaypointSeekDistSq = val_ * val_;}
		
		void WanderJitter(float val_){m_fWanderJitter = val_;}
		void WanderDistance(float val_){m_fWanderDistance = val_;}
		void WanderRadius(float val_){m_fWanderRadius = val_;}
		
		void SeparationWeight(float val_){m_fWeightSeparation = val_;}
		void AlignmentWeight(float val_){m_fWeightAlignment = val_;}
		void CohesionWeight(float val_){m_fWeightCohesion = val_;}
		
		void WanderWeight(float val_){m_fWeightWander = val_;}
		void ObstacleAvoidanceWeight(float val_){m_fWeightObstacleAvoidance = val_;}
		void WallAvoidanceWeight(float val_){m_fWeightWallAvoidance = val_;}
		void SeekWeight(float val_){m_fWeightSeek = val_;}
		void FleeWeight(float val_){m_fWeightFlee = val_;}
		void ArriveWeight(float val_){m_fWeightArrive = val_;}
		void PursuitWeight(float val_){m_fWeightPursuit = val_;}
		void OffsetPursuitWeight(float val_){m_fWeightOffsetPursuit = val_;}
		void InterposeWeight(float val_){m_fWeightInterpose = val_;}
		void HideWeight(float val_){m_fWeightHide = val_;}
		void EvadeWeight(float val_){m_fWeightEvade = val_;}
		void FollowPathWeight(float val_){m_fWeightFollowPath = val_;}
		
		void PrWallAvoidance(float val_){m_PrWallAvoidance = val_;}
		void PrObstacleAvoidance(float val_){m_PrObstacleAvoidance = val_;}
		void PrSeparation(float val_){m_PrSeparation = val_;}
		void PrAlignment(float val_){m_PrAlignment = val_;}
		void PrCohesion(float val_){m_PrCohesion = val_;}
		void PrWander(float val_){m_PrWander = val_;}
		void PrSeek(float val_){m_PrSeek = val_;}
		void PrFlee(float val_){m_PrFlee = val_;}
		void PrEvade(float val_){m_PrEvade = val_;}
		void PrHide(float val_){m_PrHide = val_;}
		void PrArrive(float val_){m_PrArrive = val_;}

		//=========================================

		//entities should be able to read/write their data to a stream
		void Write(std::ostream&  os)const;
		void Read (std::ifstream& is);

	private:
		//this function tests if a specific bit of m_iFlags is set
		bool      On(behavior_type bt){return (m_iFlags & bt) == bt;}

		bool      AccumulateForce(Vector2 &sf, Vector2 ForceToAdd);

		//creates the antenna utilized by the wall avoidance behavior
		void      CreateFeelers();

		/* .......................................................

						BEGIN BEHAVIOR DECLARATIONS

			.......................................................*/

		//this behavior moves the agent towards a target position
		Vector2 Seek(Vector2 TargetPos);

		//this behavior returns a vector that moves the agent away
		//from a target position
		Vector2 Flee(Vector2 TargetPos);

		//this behavior is similar to seek but it attempts to arrive 
		//at the target position with a zero velocity
		Vector2 Arrive(Vector2     TargetPos,
						Deceleration deceleration);

		//this behavior predicts where an agent will be in time T and seeks
		//towards that point to intercept it.
		Vector2 Pursuit(BaseEntity* evader);

		//this behavior maintains a position, in the direction of offset
		//from the target BaseEntity
		Vector2 OffsetPursuit(BaseEntity* agent, const Vector2 offset);

		//this behavior attempts to evade a pursuer
		Vector2 Evade(BaseEntity* pursuer);

		//this behavior makes the agent wander about randomly
		Vector2 Wander(float elapsedTime_);

		//this returns a steering force which will attempt to keep the agent 
		//away from any obstacles it may encounter
		Vector2 ObstacleAvoidance(const std::vector<BaseEntity*>& obstacles);

		//this returns a steering force which will keep the agent away from any
		//walls it may encounter
		Vector2 WallAvoidance(const std::vector<Line2D> &walls);

  
		//given a series of Vector2Ds, this method produces a force that will
		//move the agent along the waypoints in order
		Vector2 FollowPath();

		//this results in a steering force that attempts to steer the BaseEntity
		//to the center of the vector connecting two moving agents.
		Vector2 Interpose(BaseEntity* VehicleA, BaseEntity* VehicleB);

		//given another agent position to hide from and a list of BaseGameEntitys this
		//method attempts to put an obstacle between itself and its opponent
		Vector2 Hide(BaseEntity* hunter, const std::vector<BaseEntity*>& obstacles);


		// -- Group Behaviors -- //

		Vector2 Cohesion(const std::vector<BaseEntity*> &agents);
  
		Vector2 Separation(const std::vector<BaseEntity*> &agents);

		Vector2 Alignment(const std::vector<BaseEntity*> &agents);

		//the following three are the same as above but they use cell-space
		//partitioning to find the neighbors
		Vector2 CohesionPlus(const std::vector<BaseEntity*> &agents);
		Vector2 SeparationPlus(const std::vector<BaseEntity*> &agents);
		Vector2 AlignmentPlus(const std::vector<BaseEntity*> &agents);

		/* .......................................................

							END BEHAVIOR DECLARATIONS

			.......................................................*/

		//calculates and sums the steering forces from any active behaviors
		Vector2 CalculateWeightedSum(float elapsedTime_);
		Vector2 CalculatePrioritized(float elapsedTime_);
		Vector2 CalculateDithered(float elapsedTime_);

		//helper method for Hide. Returns a position located on the other
		//side of an obstacle to the pursuer
		Vector2 GetHidingPosition(const Vector2& posOb,
									const float     radiusOb,
									const Vector2& posHunter);
	}; // class SteeringBehaviourComponent
}
