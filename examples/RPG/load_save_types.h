#ifndef LOAD_SAVE_TYPES_H_
#define LOAD_SAVE_TYPES_H_

#include "Character.h"

using namespace CasaEngine;

struct frame
{
	float delay;
	unsigned int sprite_id;

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(sprite_id));
		ar(CEREAL_NVP(delay));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(sprite_id));
		ar(CEREAL_NVP(delay));
	}
};

struct animation
{
	std::string name;
	std::vector<frame> frames;

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(name));
		ar(CEREAL_NVP(frames));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(name));
		ar(CEREAL_NVP(frames));
	}
};

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

using _sprite = struct _sprite {
	int id;
	//tilesetID
	int x, y, w, h; // sprites_to_delete du sprite dans l image
	int px, py; // hot spot

	std::vector<RectangleI> att; // rectangle d'attaque
	std::vector<RectangleI> def; // rect de defense savoir si touche

	_sprite() : x(0), y(0), w(0), h(0), px(0), py(0)
	{
		//id = next_id++;
	}

private:
	//static int next_id;

	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(id));
		ar(CEREAL_NVP(x));
		ar(CEREAL_NVP(y));
		ar(CEREAL_NVP(w));
		ar(CEREAL_NVP(h));
		ar(CEREAL_NVP(px));
		ar(CEREAL_NVP(py));
		ar(CEREAL_NVP(att));
		ar(CEREAL_NVP(def));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(id));
		ar(CEREAL_NVP(x));
		ar(CEREAL_NVP(y));
		ar(CEREAL_NVP(w));
		ar(CEREAL_NVP(h));
		ar(CEREAL_NVP(att));
		ar(CEREAL_NVP(def));
	}
};

typedef struct {
	int mapX, mapY; // futur script a charger : map_X_Y.txt
	int jx, jy; // position du joueur sur la map
	int dir;	// dir du joueur
	int tileX, tileY; // position de la sortie_to_delete sur la map

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(mapX));
		ar(CEREAL_NVP(mapY));
		ar(CEREAL_NVP(jx));
		ar(CEREAL_NVP(jy));
		ar(CEREAL_NVP(dir));
		ar(CEREAL_NVP(tileX));
		ar(CEREAL_NVP(tileY));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(mapX));
		ar(CEREAL_NVP(mapY));
		ar(CEREAL_NVP(jx));
		ar(CEREAL_NVP(jy));
		ar(CEREAL_NVP(dir));
		ar(CEREAL_NVP(tileX));
		ar(CEREAL_NVP(tileY));
	}
} _mapExit;

typedef struct {
	int equipement; // equipement id : a mettre dans la struct player

	int attack;
	int attribute; // a changer => etat de l'arme : soit element (eau, feu ..) soit etat positif ( booster, anti poison ...)
	int type; // projectil , a main
	std::string tileset;

	//OSL_IMAGE* img;
	_sprite* sprites_to_delete;
	union {
		int* tabAnim;//tableau arme droite, h, bas, gauche
		int nbSprite;//ou nombre de sprite si projectile ( juste image qui tourne )
	};

	std::vector<_sprite> sprites;
	std::vector<animation> animations;

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(type));
		ar(CEREAL_NVP(attack));
		ar(CEREAL_NVP(attribute));
		ar(CEREAL_NVP(tileset));
		ar(CEREAL_NVP(animations));
		ar(CEREAL_NVP(sprites));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(type));
		ar(CEREAL_NVP(attack));
		ar(CEREAL_NVP(attribute));
		ar(CEREAL_NVP(tileset));
		ar(CEREAL_NVP(animations));
		ar(CEREAL_NVP(sprites));
	}
} _statutEquipement;

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

typedef struct _ennemi {
	std::string tile_set;
	std::vector<animation> animations;
	std::vector<_sprite> sprites;
	_statut stats; // caracteristique de l ennemi
	int mapX, mapY; // position sur la map
	int mov;
	int dir;
	int dDeplacement;
	int touche, toucheDelai; // delai d'invincibilite ( une fois touche)
	int recul; // lorsque touché, l'ennemi recul
	int imgCourant;
	int exp; // experience donne au joueur une fois vaincu
	RectangleI mapCollision; // rectangle de collision integer x,y,w,h
	//to change
	int ptMatX, ptMatY; // point Materiel, repere l'ennemi sur la map, permet de positionner les sprite selon leur point chaud
	int* tabAnim; // mov, min, max, mov, min, max...  permet d'attribuer une animation selon le mov
	int nbAnim;
	_sprite* sprites_to_delete;
	_statutEquipement armeEquip;

	// specific to ennmy
	int imgDelai, imgDelaiMax; // delai entre chq animation ( image)
	int deplacement; // calcul du nombre de pixel effectué lors d'un mouvement ( sert a recentrer les ennemi sur les tiles)
	bool repositionX, repositionY;// l' ennemi a reculer il faut le centrer sur la tile
	int type; // pour l'initialisation et pout l IA
	int ID; // pour identifié l'ennemi lors de selection de magie par ex..
	_IA IA;

	struct _ennemi* next; // liste chaine d'ennemi

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(tile_set));
		ar(cereal::make_nvp("hp_max", stats.HPMax));
		ar(cereal::make_nvp("mp_max", stats.MPMax));
		ar(cereal::make_nvp("speed", stats.dVit));
		ar(cereal::make_nvp("spirit", stats.mag));
		ar(cereal::make_nvp("strength", stats.force));
		ar(cereal::make_nvp("defense", stats.def));
		ar(cereal::make_nvp("defense_magic", stats.defMag));
		ar(CEREAL_NVP(exp));
		ar(CEREAL_NVP(animations));
		ar(CEREAL_NVP(sprites));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(tile_set));
		ar(cereal::make_nvp("hp_max", stats.HPMax));
		ar(cereal::make_nvp("mp_max", stats.MPMax));
		ar(cereal::make_nvp("speed", stats.dVit));
		ar(cereal::make_nvp("spirit", stats.mag));
		ar(cereal::make_nvp("strength", stats.force));
		ar(cereal::make_nvp("defense", stats.def));
		ar(cereal::make_nvp("defense_magic", stats.defMag));
		ar(CEREAL_NVP(exp));
		ar(CEREAL_NVP(animations));
		ar(CEREAL_NVP(sprites));
	}
} _ennemi;

typedef struct {
	std::string tile_set;
	std::vector<animation> animations;
	std::vector<_sprite> sprites;
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
	RectangleI mapCollision; // rectangle de collision
	RectangleI ptMateriel;// repere sur la map, utiliser pour les points chaud
	_statutEquipement armeEquipe;

	//specific to player
	int ennemiChoisi; // selection pour la magie etc...
	int magieChoisi; // magie ou skill choisi, plusieurs utilisation
	int dBlock, gBlock, hBlock, bBlock;
	int expMax; // exp pour le level suivant

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(tile_set));
		ar(CEREAL_NVP(hp_max));
		ar(CEREAL_NVP(mp_max));
		ar(CEREAL_NVP(exp));
		ar(CEREAL_NVP(level));
		ar(CEREAL_NVP(speed));
		ar(CEREAL_NVP(spirit));
		ar(CEREAL_NVP(strength));
		ar(CEREAL_NVP(defense));
		ar(CEREAL_NVP(defense_magic));
		ar(CEREAL_NVP(animations));
		ar(CEREAL_NVP(sprites));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(tile_set));
		ar(CEREAL_NVP(hp_max));
		ar(CEREAL_NVP(mp_max));
		ar(CEREAL_NVP(exp));
		ar(CEREAL_NVP(level));
		ar(CEREAL_NVP(speed));
		ar(CEREAL_NVP(spirit));
		ar(CEREAL_NVP(strength));
		ar(CEREAL_NVP(defense));
		ar(CEREAL_NVP(defense_magic));
		ar(CEREAL_NVP(animations));
		ar(CEREAL_NVP(sprites));
	}
} _joueur;

using ennemy_map_info = struct
{
	int type;
	int mapX, mapY;

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(type));
		ar(CEREAL_NVP(mapX));
		ar(CEREAL_NVP(mapY));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(type));
		ar(CEREAL_NVP(mapX));
		ar(CEREAL_NVP(mapY));
	}
};

typedef struct {
	//OSL_IMAGE* img; // image contenant toutes les tiles
	//OSL_MAP* couche1, * couche2, * couche3, * couche4; // map format OSLIB
	int* tabCouche1, * tabCouche2, /**tabCouche3,*/* tabCouche4; // tableau avec numero correspondant aux tiles dans l'image img
	int* couche1Type;//, *couche2Type, *couche3Type, *couche4Type; // pour les collisions 11111 => premier chiffre collision ou pas
	//int *couche1Topo, *couche2Topo, *couche3Topo, *couche4Topo; // relief pour ralentir les perso

	int worldX, worldY; // coordonnees de la map dans le monde
	int nbrSortie; // nombre de sortie_to_delete
	_mapExit* sortie_to_delete; // tableau de nombre
	int zone; // zone dans laquelle se trouve la map

	//OSL_SOUND* bgm;// musique de la map
	//
	std::string tile_set;
	int sizeX, sizeY; // nbre de tile
	std::vector<_mapExit> exits; // donnée des sorties ( position sortie_to_delete, map a chargée ..)
	std::vector<int> tile_type_layer_1;
	std::vector<int> tile_layer_1;
	std::vector<int> tile_layer_2;
	std::vector<int> tile_layer_4;
	std::vector<ennemy_map_info> ennemy_info;

private:
	friend class cereal::access;

	template <class Archive>
	void save(Archive& ar) const
	{
		ar(CEREAL_NVP(tile_set));
		ar(CEREAL_NVP(sizeX));
		ar(CEREAL_NVP(sizeY));
		ar(CEREAL_NVP(exits));
		ar(CEREAL_NVP(tile_type_layer_1));
		ar(CEREAL_NVP(tile_layer_1));
		ar(CEREAL_NVP(tile_layer_2));
		ar(CEREAL_NVP(tile_layer_4));
		ar(CEREAL_NVP(ennemy_info));
	}

	template <class Archive>
	void load(Archive& ar)
	{
		ar(CEREAL_NVP(tile_set));
		ar(CEREAL_NVP(sizeX));
		ar(CEREAL_NVP(sizeY));
		ar(CEREAL_NVP(exits));
		ar(CEREAL_NVP(tile_type_layer_1));
		ar(CEREAL_NVP(tile_layer_1));
		ar(CEREAL_NVP(tile_layer_2));
		ar(CEREAL_NVP(tile_layer_4));
		ar(CEREAL_NVP(ennemy_info));
	}
} _map;

typedef struct { // pas encore definie
	int* file; // script chargé
	//char *imgCharge; // pour savoir quel image charge
	//char *musicCharge;
} _script;

#endif
