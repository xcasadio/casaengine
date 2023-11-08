
#ifndef MYCONSOLE_H
#define MYCONSOLE_H

#include "Graphics/Mesh/Mesh.h"
#include "Maths/Matrix4.h"
#include <list>

#include <string>


////////////////////////////////////////////////////////////
/// Classe d�finissant un look personnalis� pour la console
////////////////////////////////////////////////////////////
class CMyConsole : public CasaEngine::IConsoleLook
{
public :

    //----------------------------------------------------------
    // Constructeur par d�faut
    //----------------------------------------------------------
    CMyConsole();

    //----------------------------------------------------------
    // Fonction appel�e lors de la mise � jour de la console
    //----------------------------------------------------------
    virtual void Update();

    //----------------------------------------------------------
    // Fonction appel�e lors de l'affichage de la console
    //----------------------------------------------------------
    virtual void Draw() const;

    //----------------------------------------------------------
    // Fonction appel�e lors de l'activation / d�sactivation de la console
    //----------------------------------------------------------
    virtual void Show(bool Visible);

    //----------------------------------------------------------
    // Fonction appel�e apr�s l'appel � une commande
    //----------------------------------------------------------
    virtual void CommandCalled(const std::string& Result);

    //----------------------------------------------------------
    // Fonction appel�e � chaque changement de la ligne courante
    //----------------------------------------------------------
    virtual void TextChanged(const std::string& NewText);

    //----------------------------------------------------------
    // Fonction appel�e en cas d'erreur
    //----------------------------------------------------------
    virtual void Error(const std::string& Message);

private :

    //----------------------------------------------------------
    // Types
    //----------------------------------------------------------
    enum TState {STOPPED, HIDDING, SHOWING};

    //----------------------------------------------------------
    // Ajoute une ligne
    //----------------------------------------------------------
    void AddLine(const std::string& Line = "> ", const CasaEngine::CColor& Color = CasaEngine::CColor::White);

    //----------------------------------------------------------
    // S�lectionne la police suivante
    //----------------------------------------------------------
    std::string  NextFont();

    //----------------------------------------------------------
    // Donn�es membres
    //----------------------------------------------------------
    CasaEngine::TModelPtr	m_Background; ///< Quad repr�sentant le fond de la console
    std::list<CasaEngine::GraphicString>	m_Lines;      ///< Derni�res lignes affich�es sur la console
    CasaEngine::Matrix4		m_Transfo;    ///< Matrice de transformation associ�e � l'affichage de la console
	TState		m_State;      ///< "Etat" de l'animation de la console
	float		m_Scale; ///< scale to create animation when showing/hidding
	CasaEngine::IEffect		*m_pEffect;
};

#endif // MYCONSOLE_H
