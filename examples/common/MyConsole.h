
#ifndef MYCONSOLE_H
#define MYCONSOLE_H

#include "Graphics/Mesh/Mesh.h"
#include "Maths/Matrix4.h"
#include <list>

#include <string>


////////////////////////////////////////////////////////////
/// Classe définissant un look personnalisé pour la console
////////////////////////////////////////////////////////////
class CMyConsole : public CasaEngine::IConsoleLook
{
public :

    //----------------------------------------------------------
    // Constructeur par défaut
    //----------------------------------------------------------
    CMyConsole();

    //----------------------------------------------------------
    // Fonction appelée lors de la mise à jour de la console
    //----------------------------------------------------------
    virtual void Update();

    //----------------------------------------------------------
    // Fonction appelée lors de l'affichage de la console
    //----------------------------------------------------------
    virtual void Draw() const;

    //----------------------------------------------------------
    // Fonction appelée lors de l'activation / désactivation de la console
    //----------------------------------------------------------
    virtual void Show(bool Visible);

    //----------------------------------------------------------
    // Fonction appelée après l'appel à une commande
    //----------------------------------------------------------
    virtual void CommandCalled(const std::string& Result);

    //----------------------------------------------------------
    // Fonction appelée à chaque changement de la ligne courante
    //----------------------------------------------------------
    virtual void TextChanged(const std::string& NewText);

    //----------------------------------------------------------
    // Fonction appelée en cas d'erreur
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
    // Sélectionne la police suivante
    //----------------------------------------------------------
    std::string  NextFont();

    //----------------------------------------------------------
    // Données membres
    //----------------------------------------------------------
    CasaEngine::TModelPtr	m_Background; ///< Quad représentant le fond de la console
    std::list<CasaEngine::GraphicString>	m_Lines;      ///< Dernières lignes affichées sur la console
    CasaEngine::Matrix4		m_Transfo;    ///< Matrice de transformation associée à l'affichage de la console
	TState		m_State;      ///< "Etat" de l'animation de la console
	float		m_Scale; ///< scale to create animation when showing/hidding
	CasaEngine::IEffect		*m_pEffect;
};

#endif // MYCONSOLE_H
