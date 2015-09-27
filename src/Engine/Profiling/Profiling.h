/***************************************************************************************************
**
** Real-Time Hierarchical Profiling for Game Programming Gems 3
**
** by Greg Hjelstrom & Byon Garrabrant
**
***************************************************************************************************/

#include "CompilationConfig.h"

#ifndef CA_NO_PROFILE

#ifndef PROFILING_H_
#define PROFILING_H_

#include "CA_Export.h"
#include "Memory\MemoryAllocation.h"


namespace CasaEngine
{
	//To disable built-in profiling, please comment out next line
	//#define CA_NO_PROFILE 1

	///A node in the Profile Hierarchy Tree
	class CA_EXPORT ProfileNode :
		public AllocatedObject<ProfileNode>
	{

	public:
		ProfileNode( const char * name, ProfileNode * parent );
		~ProfileNode( void );

		ProfileNode * Get_Sub_Node( const char * name );

		ProfileNode * Get_Parent( void )		{ return Parent; }
		ProfileNode * Get_Sibling( void )		{ return Sibling; }
		ProfileNode * Get_Child( void )			{ return Child; }

		void			CleanupMemory();
		void			Reset( void );
		void			Call( void );
		bool			Return( void );

		const char *	Get_Name( void )				{ return Name; }
		int				Get_Total_Calls( void )		{ return TotalCalls; }
		float			Get_Total_Time( void )		{ return TotalTime; }
		void*			GetUserPointer() const {return m_userPtr;}
		void			SetUserPointer(void* ptr) { m_userPtr = ptr;}
	protected:

		const char *	Name;
		int				TotalCalls;
		float				TotalTime;
		unsigned long int			StartTime;
		int				RecursionCounter;

		ProfileNode *	Parent;
		ProfileNode *	Child;
		ProfileNode *	Sibling;
		void*	m_userPtr;
	};

	//////////////////////////////////////////////////////////////////////////
	///An iterator to navigate through the tree
	class CA_EXPORT ProfileIterator :
		public AllocatedObject<ProfileIterator>
	{
	public:
		// Access all the children of the current parent
		void				First(void);
		void				Next(void);
		bool				Is_Done(void);
		bool                Is_Root(void) { return (CurrentParent->Get_Parent() == 0); }

		void				Enter_Child( int index );		// Make the given child the new parent
		void				Enter_Largest_Child( void );	// Make the largest child the new parent
		void				Enter_Parent( void );			// Make the current parent's parent the new parent

		// Access the current child
		const char *	Get_Current_Name( void )			{ return CurrentChild->Get_Name(); }
		int				Get_Current_Total_Calls( void )	{ return CurrentChild->Get_Total_Calls(); }
		float				Get_Current_Total_Time( void )	{ return CurrentChild->Get_Total_Time(); }

		void*	Get_Current_UserPointer( void )			{ return CurrentChild->GetUserPointer(); }
		void	Set_Current_UserPointer(void* ptr) {CurrentChild->SetUserPointer(ptr);}
		// Access the current parent
		const char *	Get_Current_Parent_Name( void )			{ return CurrentParent->Get_Name(); }
		int				Get_Current_Parent_Total_Calls( void )	{ return CurrentParent->Get_Total_Calls(); }
		float			Get_Current_Parent_Total_Time( void )	{ return CurrentParent->Get_Total_Time(); }



	protected:

		ProfileNode *	CurrentParent;
		ProfileNode *	CurrentChild;


		ProfileIterator( ProfileNode * start );
		friend	class		ProfileManager;
	};

	//////////////////////////////////////////////////////////////////////////
	///The Manager for the Profile system
	class CA_EXPORT ProfileManager :
		public AllocatedObject<ProfileManager>
	{
	public:
		static	void						Start_Profile( const char * name );
		static	void						Stop_Profile( void );

		static	void						CleanupMemory(void)
		{
			Root.CleanupMemory();
		}

		static	void						Reset( void );
		static	void						Increment_Frame_Counter( void );
		static	int						Get_Frame_Count_Since_Reset( void )		{ return FrameCounter; }
		static	float						Get_Time_Since_Reset( void );

		static	ProfileIterator *	Get_Iterator( void )	
		{
			return NEW_AO ProfileIterator( &Root ); 
		}
		static	void						Release_Iterator(ProfileIterator * iterator ) { delete ( iterator); }

		static void	dumpRecursive(ProfileIterator* profileIterator, int spacing);
		static void	dumpAll();

		static void	dumpRecursive(FILE* f, ProfileIterator* profileIterator, int spacing);
		static void	dumpAll(FILE* f);

	private:
		static	ProfileNode			Root;
		static	ProfileNode *			CurrentNode;
		static	int						FrameCounter;
		static	unsigned long int					ResetTime;
	};

	//////////////////////////////////////////////////////////////////////////
	/**
	 * 
	 */
	class CA_EXPORT ProfileZone
	{
	public:
		ProfileZone(const char* name) { ProfileManager::Start_Profile(name); }
		~ProfileZone() { ProfileManager::Stop_Profile(); }
	};

	#define	CA_PROFILE( name ) CasaEngine::ProfileZone __profile( name )

#endif // PROFILING_H_

} // namespace CasaEngine

#else

#define	CA_PROFILE( name )

#endif //#ifndef CA_NO_PROFILE