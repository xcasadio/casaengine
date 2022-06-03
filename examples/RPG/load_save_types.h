#pragma once

#include "Maths/Rectangle.h"
#include "Serializer/Serializer.h"

#include <vector>

using namespace CasaEngine;

//struct frame
//{
//	float delay;
//	unsigned int sprite_id;
//};
//
//inline void to_json(nlohmann::json& j, const frame& t)
//{
//	JSON_TO(sprite_id)
//	JSON_TO(delay)
//}
//
//inline void from_json(const nlohmann::json& j, frame& t)
//{
//	JSON_FROM(sprite_id)
//	JSON_FROM(delay)
//}


//struct animation
//{
//	std::string name;
//	std::vector<frame> frames;
//};
//
//inline void to_json(nlohmann::json& j, const animation& t)
//{
//	JSON_TO(name)
//	JSON_TO(frames)
//}
//
//inline void from_json(const nlohmann::json& j, animation& t)
//{
//	JSON_FROM(name)
//	JSON_FROM(frames)
//}

struct animationMap
{
	std::string id;
	std::string name;
};

inline void to_json(nlohmann::json& j, const animationMap& t)
{
	JSON_TO(id)
	JSON_TO(name)
}

inline void from_json(const nlohmann::json& j, animationMap& t)
{
	JSON_FROM(id)
	JSON_FROM(name)
}

typedef struct { // statut : caracteristiques des individus
	int etatNeg; // voir les enum
	int etatPos;
	int etatRes;
	int HPMax;
	int MPMax;
	int HP;// peut etre < 0
	int MP;
	int mag; // max 255
	int force;
	int vit;
	int def;
	int defMag;
	int dDefMag; // variable qui permette de diminuer/augmenter les stats
	int dForce;
	int dDef;
	int dVit;
	int dMag;
} _statut;

//using _sprite = struct _sprite {
//	int id;
//	//tilesetID
//	int x, y, w, h; // sprites_to_delete du sprite dans l image
//	int px, py; // hot spot
//
//	std::vector<CasaEngine::Rectangle> att; // rectangle d'attaque
//	std::vector<CasaEngine::Rectangle> def; // rect de defense savoir si touche
//
//	_sprite() : x(0), y(0), w(0), h(0), px(0), py(0)
//	{
//		//id = next_id++;
//	}
//};
//
//inline void to_json(nlohmann::json& j, const _sprite& t)
//{
//	JSON_TO(id)
//	JSON_TO(x)
//	JSON_TO(y)
//	JSON_TO(w)
//	JSON_TO(h)
//	JSON_TO(px)
//	JSON_TO(py)
//	JSON_TO(att)
//	JSON_TO(def)
//
//}
//
//inline void from_json(const nlohmann::json& j, _sprite& t)
//{
//	JSON_FROM(id)
//	JSON_FROM(x)
//	JSON_FROM(y)
//	JSON_FROM(w)
//	JSON_FROM(h)
//	JSON_FROM(px)
//	JSON_FROM(py)
//	JSON_FROM(att)
//	JSON_FROM(def)
//}

typedef struct {
	int mapX, mapY; // futur script a charger : map_X_Y.txt
	int jx, jy; // position du joueur sur la map
	int dir;	// dir du joueur
	int tileX, tileY; // position de la sortie_to_delete sur la map
} _mapExit;

inline void to_json(nlohmann::json& j, const _mapExit& t)
{
	JSON_TO(mapX)
	JSON_TO(mapY)
	JSON_TO(jx)
	JSON_TO(jy)
	JSON_TO(dir)
	JSON_TO(tileX)
	JSON_TO(tileY)
}

inline void from_json(const nlohmann::json& j, _mapExit& t)
{
	JSON_FROM(mapX)
	JSON_FROM(mapY)
	JSON_FROM(jx)
	JSON_FROM(jy)
	JSON_FROM(dir)
	JSON_FROM(tileX)
	JSON_FROM(tileY)
}

typedef struct {
	int equipement; // equipement id : a mettre dans la struct player

	int attack;
	int attribute; // a changer => etat de l'arme : soit element (eau, feu ..) soit etat positif ( booster, anti poison ...)
	int type; // projectil , a main
	std::string tileset;

	//OSL_IMAGE* img;
	//_sprite* sprites_to_delete;
	union {
		int* tabAnim;//tableau arme droite, h, bas, gauche
		int nbSprite;//ou nombre de sprite si projectile ( juste image qui tourne )
	};

	//std::vector<_sprite> sprites;
	//std::vector<animation> animations;
} _statutEquipement;

inline void to_json(nlohmann::json& j, const _statutEquipement& t)
{
	JSON_TO(type)
	JSON_TO(attack)
	JSON_TO(attribute)
	JSON_TO(tileset)
	//JSON_TO(animations)
	//JSON_TO(sprites)
}

inline void from_json(const nlohmann::json& j, _statutEquipement& t)
{
	JSON_FROM(type)
	JSON_FROM(attack)
	JSON_FROM(attribute)
	JSON_FROM(tileset)
	//JSON_FROM(animations)
	//JSON_FROM(sprites)
}

typedef struct {
	int* numTileAnim; // numero de tiles
	int nbAnim;// nobre de tile ds le tableau
	int oldTile; // sert a retouve la tile changé | sinon on ne peut pas incrementer imgCourant
	int imgCourant; // tile affiche
} _animTile;

typedef struct {
	int nbAnim;
	_animTile* tabAnim;// tableau de nombre correspondant a tile a changer
} _animMap;

typedef struct {
	int enAction; // effectu une action
	int delaiAction;// tps entre chaque action
	int delaiAttaque;// tps entre chaque attaque
} _IA;

typedef struct {
	std::string tile_set;
	std::string name;
	std::vector<animationMap> animations;
	//std::vector<_sprite> sprites;
	int speed;
	int spirit;
	int strength;
private:
	//friend class cereal::access;
	//
	//template <class Archive>
	//void save(Archive& ar) const
	//{
	//	ar(CEREAL_NVP(tile_set));
	//	ar(CEREAL_NVP(name));
	//	ar(CEREAL_NVP(strength));
	//	ar(CEREAL_NVP(spirit));
	//	ar(CEREAL_NVP(speed));
	//	ar(CEREAL_NVP(sprites));
	//	ar(CEREAL_NVP(animations));
	//}
	//
	//template <class Archive>
	//void load(Archive& ar)
	//{
	//	ar(CEREAL_NVP(tile_set));
	//	ar(CEREAL_NVP(name));
	//	ar(CEREAL_NVP(strength));
	//	ar(CEREAL_NVP(spirit));
	//	ar(CEREAL_NVP(speed));
	//	ar(CEREAL_NVP(sprites));
	//	ar(CEREAL_NVP(animations));
	//}
} _weapon;


inline void to_json(nlohmann::json& j, const _weapon& t)
{
	JSON_TO(tile_set)
	JSON_TO(name)
	JSON_TO(strength)
	JSON_TO(spirit)
	JSON_TO(speed)
	//JSON_TO(sprites)
	JSON_TO(animations)
}

inline void from_json(const nlohmann::json& j, _weapon& t)
{
	JSON_FROM(tile_set)
	JSON_FROM(name)
	JSON_FROM(strength)
	JSON_FROM(spirit)
	JSON_FROM(speed)
	//JSON_FROM(sprites)
	JSON_FROM(animations)
}


typedef struct _ennemi {
	std::string tile_set;
	std::vector<animationMap> animations;
	//std::vector<_sprite> sprites;
	_statut stats; // caracteristique de l ennemi
	int mapX, mapY; // position sur la map
	int mov;
	int dir;
	int dDeplacement;
	int touche, toucheDelai; // delai d'invincibilite ( une fois touche)
	int recul; // lorsque touché, l'ennemi recul
	int imgCourant;
	int exp; // experience donne au joueur une fois vaincu
	CasaEngine::Rectangle mapCollision; // rectangle de collision integer x,y,w,h
	//to change
	int ptMatX, ptMatY; // point Materiel, repere l'ennemi sur la map, permet de positionner les sprite selon leur point chaud
	int* tabAnim; // mov, min, max, mov, min, max...  permet d'attribuer une animation selon le mov
	int nbAnim;
	//_sprite* sprites_to_delete;
	_statutEquipement armeEquip;

	// specific to ennmy
	int imgDelai, imgDelaiMax; // delai entre chq animation ( image)
	int deplacement; // calcul du nombre de pixel effectué lors d'un mouvement ( sert a recentrer les ennemi sur les tiles)
	bool repositionX, repositionY;// l' ennemi a reculer il faut le centrer sur la tile
	int type; // pour l'initialisation et pout l IA
	int ID; // pour identifié l'ennemi lors de selection de magie par ex..
	_IA IA;

	struct _ennemi* next; // liste chaine d'ennemi
} _ennemi;


inline void to_json(nlohmann::json& j, const _ennemi& t)
{
	JSON_TO(tile_set)
	JSON_TO(animations)
	//JSON_TO(sprites)
	JSON_TO(exp)
	JSON_TO_NAMED(hp_max, stats.HPMax)
	JSON_TO_NAMED(mp_max, stats.MPMax)
	JSON_TO_NAMED(speed, stats.dVit)
	JSON_TO_NAMED(spirit, stats.mag)
	JSON_TO_NAMED(strength, stats.force)
	JSON_TO_NAMED(defense, stats.def)
	JSON_TO_NAMED(defense_magic, stats.defMag)
}

inline void from_json(const nlohmann::json& j, _ennemi& t)
{
	JSON_FROM(tile_set)
	JSON_FROM(animations)
	//JSON_FROM(sprites)
	JSON_FROM(exp)
	JSON_FROM_NAMED(hp_max, stats.HPMax)
	JSON_FROM_NAMED(mp_max, stats.MPMax)
	JSON_FROM_NAMED(speed, stats.dVit)
	JSON_FROM_NAMED(spirit, stats.mag)
	JSON_FROM_NAMED(strength, stats.force)
	JSON_FROM_NAMED(defense, stats.def)
	JSON_FROM_NAMED(defense_magic, stats.defMag)
}


typedef struct {
	std::string tile_set;
	std::vector<animationMap> animations;
	//std::vector<_sprite> sprites;
	int level;
	int hp_max;
	int mp_max;
	int speed;
	int spirit;
	int strength;
	int defense;
	int defense_magic;
	int exp;
	_statut stats; // statut
	int mapX, mapY; // position sur la map
	int mov; // quel movement
	int dir; // direction
	int dDeplacement;
	int touche, toucheDelai; // duree d'invincibilite
	int recul; // lorsque touché, le perso recul
	int imgCourant; // numero du sprite courant
	CasaEngine::Rectangle mapCollision; // rectangle de collision
	CasaEngine::Rectangle ptMateriel;// repere sur la map, utiliser pour les points chaud
	_statutEquipement armeEquipe;

	//specific to player
	int ennemiChoisi; // selection pour la magie etc...
	int magieChoisi; // magie ou skill choisi, plusieurs utilisation
	int dBlock, gBlock, hBlock, bBlock;
	int expMax; // exp pour le level suivant
} _joueur;

inline void to_json(nlohmann::json& j, const _joueur& t)
{
	JSON_TO(tile_set)
	JSON_TO(hp_max)
	JSON_TO(mp_max)
	JSON_TO(exp)
	JSON_TO(level)
	JSON_TO(speed)
	JSON_TO(spirit)
	JSON_TO(strength)
	JSON_TO(defense)
	JSON_TO(defense_magic)
	JSON_TO(animations)
	//JSON_TO(sprites)
}

inline void from_json(const nlohmann::json& j, _joueur& t)
{
	JSON_FROM(tile_set)
	JSON_FROM(hp_max)
	JSON_FROM(mp_max)
	JSON_FROM(exp)
	JSON_FROM(level)
	JSON_FROM(speed)
	JSON_FROM(spirit)
	JSON_FROM(strength)
	JSON_FROM(defense)
	JSON_FROM(defense_magic)
	JSON_FROM(animations)
	//JSON_FROM(sprites)
}



using ennemy_map_info = struct
{
	int type;
	int mapX, mapY;
};

inline void to_json(nlohmann::json& j, const ennemy_map_info& t)
{
	JSON_TO(type)
	JSON_TO(mapX)
	JSON_TO(mapY)
}

inline void from_json(const nlohmann::json& j, ennemy_map_info& t)
{
	JSON_FROM(type)
	JSON_FROM(mapX)
	JSON_FROM(mapY)
}

typedef struct {
	//OSL_IMAGE* img; // image contenant toutes les tiles
	//OSL_MAP* couche1, * couche2, * couche3, * couche4; // map format OSLIB
	//int* tabCouche1, * tabCouche2, /**tabCouche3,*/* tabCouche4; // tableau avec numero correspondant aux tiles dans l'image img
	//int* couche1Type;//, *couche2Type, *couche3Type, *couche4Type; // pour les collisions 11111 => premier chiffre collision ou pas
	//int *couche1Topo, *couche2Topo, *couche3Topo, *couche4Topo; // relief pour ralentir les perso

	//int worldX, worldY; // coordonnees de la map dans le monde
	//int nbrSortie; // nombre de sortie_to_delete
	//_mapExit* sortie_to_delete; // tableau de nombre
	//int zone; // zone dans laquelle se trouve la map

	//OSL_SOUND* bgm;// musique de la map
	//
	std::string tile_set;
	int sizeX, sizeY; // nbre de tile
	std::vector<_mapExit> exits; // donnée des sorties ( position sortie_to_delete, map a chargée ..)
	std::vector<int> tile_type_layer_1;
	std::vector<int> tile_layer_1;
	std::vector<int> tile_layer_2;
	std::vector<int> auto_tile_layer;
	std::vector<int> tile_layer_4;
	std::vector<ennemy_map_info> ennemy_info;
} _map;


inline void to_json(nlohmann::json& j, const _map& t)
{
	JSON_TO(tile_set)
	JSON_TO(sizeX)
	JSON_TO(sizeY)
	JSON_TO(exits)
	JSON_TO(tile_type_layer_1)
	JSON_TO(tile_layer_1)
	JSON_TO(tile_layer_2)
	JSON_TO(auto_tile_layer)
	JSON_TO(tile_layer_4)
	JSON_TO(ennemy_info)

}

inline void from_json(const nlohmann::json& j, _map& t)
{
	JSON_FROM(tile_set)
	JSON_FROM(sizeX)
	JSON_FROM(sizeY)
	JSON_FROM(exits)
	JSON_FROM(tile_type_layer_1)
	JSON_FROM(tile_layer_1)
	JSON_FROM(tile_layer_2)
	JSON_FROM(auto_tile_layer)
	JSON_FROM(tile_layer_4)
	JSON_FROM(ennemy_info)
}
