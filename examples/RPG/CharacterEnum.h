#ifndef CHARACTERANIMATION_H_
#define CHARACTERANIMATION_H_

/**
 *
 */
enum orientation
{
	UP          = 0x1,
	DOWN        = 0x2,
	LEFT        = 0x4,
	RIGHT       = 0x8,

	UP_LEFT      = LEFT | UP,
	DOWN_LEFT    = LEFT | DOWN,
	UP_RIGHT     = RIGHT | UP,
	DOWN_RIGHT   = RIGHT | DOWN
};

/**
 * Define the type of controller for each type of character
 */
enum class CharacterType
{
	// Character who can be controlled by player (local or network)
	PLAYER,
	// simple ennemy
	ENEMY,
	// medium ennemy
	ENEMY_CHIEF,
	// Ennemy with better AI
	BOSS
};

/**
 * Don't change the order else change characterEditorForm and the project file
 */
enum AnimationIndex
{
	IDLE_RIGHT,
	IDLE_LEFT,
	IDLE_UP,
	IDLE_DOWN,
	IDLE_UP_RIGHT,
	IDLE_DOWN_RIGHT,
	IDLE_UP_LEFT,
	IDLE_DOWN_LEFT,

	RUN_RIGHT,
	RUN_LEFT,
	RUN_UP,
	RUN_DOWN,
	RUN_UP_RIGHT,
	RUN_DOWN_RIGHT,
	RUN_UP_LEFT,
	RUN_DOWN_LEFT,        

	ATTACK1_RIGHT,
	ATTACK1_LEFT,
	ATTACK1_UP,
	ATTACK1_DOWN,
	ATTACK1_UP_RIGHT,
	ATTACK1_DOWN_RIGHT,
	ATTACK1_UP_LEFT,
	ATTACK1_DOWN_LEFT,

	ATTACK2_RIGHT,
	ATTACK2_LEFT,
	ATTACK2_UP,
	ATTACK2_DOWN,
	ATTACK2_UP_RIGHT,
	ATTACK2_DOWN_RIGHT,
	ATTACK2_UP_LEFT,
	ATTACK2_DOWN_LEFT,

	ATTACK3_RIGHT,
	ATTACK3_LEFT,
	ATTACK3_UP,
	ATTACK3_DOWN,
	ATTACK3_UP_RIGHT,
	ATTACK3_DOWN_RIGHT,
	ATTACK3_UP_LEFT,
	ATTACK3_DOWN_LEFT,

	HIT_RIGHT,
	HIT_LEFT,
	HIT_UP,
	HIT_DOWN,
	HIT_UP_RIGHT,
	HIT_DOWN_RIGHT,
	HIT_UP_LEFT,
	HIT_DOWN_LEFT,

	MAGIC1_RIGHT,
	MAGIC1_LEFT,
	MAGIC1_UP,
	MAGIC1_DOWN,
	MAGIC1_UP_RIGHT,
	MAGIC1_DOWN_RIGHT,
	MAGIC1_UP_LEFT,
	MAGIC1_DOWN_LEFT,

	MAGIC2_RIGHT,
	MAGIC2_LEFT,
	MAGIC2_UP,
	MAGIC2_DOWN,
	MAGIC2_UP_RIGHT,
	MAGIC2_DOWN_RIGHT,
	MAGIC2_UP_LEFT,
	MAGIC2_DOWN_LEFT,

	DYING_RIGHT,
	DYING_LEFT,
	DYING_UP,
	DYING_DOWN,
	DYING_UP_RIGHT,
	DYING_DOWN_RIGHT,
	DYING_UP_LEFT,
	DYING_DOWN_LEFT,

	DEAD_RIGHT,
	DEAD_LEFT,
	DEAD_UP,
	DEAD_DOWN,
	DEAD_UP_RIGHT,
	DEAD_DOWN_RIGHT,
	DEAD_UP_LEFT,
	DEAD_DOWN_LEFT,

	TO_RAGE_RIGHT,
	TO_RAGE_LEFT,
	TO_RAGE_UP,
	TO_RAGE_DOWN,
	TO_RAGE_UP_RIGHT,
	TO_RAGE_DOWN_RIGHT,
	TO_RAGE_UP_LEFT,
	TO_RAGE_DOWN_LEFT,
      
	TO_NORMAL_RIGHT,
	TO_NORMAL_LEFT,
	TO_NORMAL_UP,
	TO_NORMAL_DOWN,
	TO_NORMAL_UP_RIGHT,
	TO_NORMAL_DOWN_RIGHT,
	TO_NORMAL_UP_LEFT,
	TO_NORMAL_DOWN_LEFT,


	FURY_IDLE_RIGHT,
	FURY_IDLE_LEFT,
	FURY_IDLE_UP,
	FURY_IDLE_DOWN,
	FURY_IDLE_UP_RIGHT,
	FURY_IDLE_DOWN_RIGHT,
	FURY_IDLE_UP_LEFT,
	FURY_IDLE_DOWN_LEFT,
        
	FURY_RUN_RIGHT,
	FURY_RUN_LEFT,
	FURY_RUN_UP,
	FURY_RUN_DOWN,
	FURY_RUN_UP_RIGHT,
	FURY_RUN_DOWN_RIGHT,
	FURY_RUN_UP_LEFT,
	FURY_RUN_DOWN_LEFT,
        
	FURY_ATTACK1_RIGHT,
	FURY_ATTACK1_LEFT,
	FURY_ATTACK1_UP,
	FURY_ATTACK1_DOWN,
	FURY_ATTACK1_UP_RIGHT,
	FURY_ATTACK1_DOWN_RIGHT,
	FURY_ATTACK1_UP_LEFT,
	FURY_ATTACK1_DOWN_LEFT,
        
	FURY_ATTACK2_RIGHT,
	FURY_ATTACK2_LEFT,
	FURY_ATTACK2_UP,
	FURY_ATTACK2_DOWN,
	FURY_ATTACK2_UP_RIGHT,
	FURY_ATTACK2_DOWN_RIGHT,
	FURY_ATTACK2_UP_LEFT,
	FURY_ATTACK2_DOWN_LEFT,
        
	FURY_ATTACK3_RIGHT,
	FURY_ATTACK3_LEFT,
	FURY_ATTACK3_UP,
	FURY_ATTACK3_DOWN,
	FURY_ATTACK3_UP_RIGHT,
	FURY_ATTACK3_DOWN_RIGHT,
	FURY_ATTACK3_UP_LEFT,
	FURY_ATTACK3_DOWN_LEFT,
        
	FURY_HIT_RIGHT,
	FURY_HIT_LEFT,
	FURY_HIT_UP,
	FURY_HIT_DOWN,
	FURY_HIT_UP_RIGHT,
	FURY_HIT_DOWN_RIGHT,
	FURY_HIT_UP_LEFT,
	FURY_HIT_DOWN_LEFT,
        
	FURY_MAGIC1_RIGHT,
	FURY_MAGIC1_LEFT,
	FURY_MAGIC1_UP,
	FURY_MAGIC1_DOWN,
	FURY_MAGIC1_UP_RIGHT,
	FURY_MAGIC1_DOWN_RIGHT,
	FURY_MAGIC1_UP_LEFT,
	FURY_MAGIC1_DOWN_LEFT,
        
	FURY_MAGIC2_RIGHT,
	FURY_MAGIC2_LEFT,
	FURY_MAGIC2_UP,
	FURY_MAGIC2_DOWN,
	FURY_MAGIC2_UP_RIGHT,
	FURY_MAGIC2_DOWN_RIGHT,
	FURY_MAGIC2_UP_LEFT,
	FURY_MAGIC2_DOWN_LEFT,
        
	FURY_DYING_RIGHT,
	FURY_DYING_LEFT,
	FURY_DYING_UP,
	FURY_DYING_DOWN,
	FURY_DYING_UP_RIGHT,
	FURY_DYING_DOWN_RIGHT,
	FURY_DYING_UP_LEFT,
	FURY_DYING_DOWN_LEFT,
        
	FURY_DEAD_RIGHT,
	FURY_DEAD_LEFT,
	FURY_DEAD_UP,
	FURY_DEAD_DOWN,
	FURY_DEAD_UP_RIGHT,
	FURY_DEAD_DOWN_RIGHT,
	FURY_DEAD_UP_LEFT,
	FURY_DEAD_DOWN_LEFT,
};

#endif
