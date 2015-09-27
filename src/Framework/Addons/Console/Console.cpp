//==========================================================
// CasaEngine - Free C++ 3D engine
//
// Copyright (C) 2004-2005 Laurent Gomila
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc.,
// 59 Temple Place - Suite 330,
// Boston, MA  02111-1307, USA.
//
// E-mail : laurent.gom@gmail.com
//==========================================================

//==========================================================
// En-têtes
//==========================================================
#include "Base.h"

#include "Console.h"
#include "Exceptions.h"
#include <sstream>



namespace CasaEngine
{

////////////////////////////////////////////////////////////
// Implémentation des méthodes du singleton
////////////////////////////////////////////////////////////
SINGLETON_IMPL(Console)


////////////////////////////////////////////////////////////
/// Constructeur par défaut
///
////////////////////////////////////////////////////////////
Console::Console() :
	m_Current(""),
	m_Look   (nullptr),
	m_Enabled(false)
{
    RegisterCommand("?", Bind(&Console::GetCommands, *this));
}


////////////////////////////////////////////////////////////
/// Change l'apparence de la console
///
/// \param NewLook : Pointeur sur le nouveau look
///
////////////////////////////////////////////////////////////
void Console::ChangeLook(IConsoleLook* NewLook)
{
    CA_ASSERT(NewLook != nullptr, "Console::ChangeLook) : IConsoleLook is NULLL");

    m_Look = NewLook;
}


////////////////////////////////////////////////////////////
/// Enregistre une nouvelle commande
///
/// \param Name :     Nom de la commande
/// \param Function : Foncteur contenant la fonction associée
///
////////////////////////////////////////////////////////////
void Console::RegisterCommand(const std::string& Name, const Functor& Function)
{
    m_Commands[Name] = Function;
}


////////////////////////////////////////////////////////////
/// Envoie un nouveau caractère à la console
///
/// \param Character : Caractère
///
////////////////////////////////////////////////////////////
void Console::SendChar(char Character)
{
    // Si la console n'est pas active on ne traite pas le caractère
    if (!m_Enabled)
        return;

    // Traitement du caractère
    switch (Character)
    {
        // Saut de ligne : on traite la commande et on efface la ligne
        case '\n' :
        case '\r' :
            if (!m_Current.empty())
            {
                ProcessCurrent();
                m_Current.clear();
            }
            break;

        // Backspace : on efface le dernier caractère
        case '\b' :
            if (!m_Current.empty())
                m_Current.erase(m_Current.size() - 1);
            break;

        // Tout le reste : on ajoute le caractère à la ligne courante
        default :
            m_Current += Character;
            break;
    }

    // On notifie au "look" que le texte courant vient de changer
    m_Look->TextChanged(m_Current);
}


////////////////////////////////////////////////////////////
/// Met à jour la console
///
////////////////////////////////////////////////////////////
void Console::Update()
{
	if (m_Look != nullptr)
	{
		m_Look->Update();
	}
}


////////////////////////////////////////////////////////////
/// Affiche la console
///
////////////////////////////////////////////////////////////
void Console::Draw() const
{
	if (m_Look != nullptr)
	{
		m_Look->Draw();
	}
}


////////////////////////////////////////////////////////////
/// Active ou désactive la console
///
/// \param Enabled : Active / inactive
///
////////////////////////////////////////////////////////////
void Console::Enable(bool Enabled)
{
    m_Enabled = Enabled;
    m_Look->Show(Enabled);
}


////////////////////////////////////////////////////////////
/// Donne la liste des commandes enregistrées
///
/// \return Chaîne contenant la liste des commandes enregistrées
///
////////////////////////////////////////////////////////////
std::string Console::GetCommands() const
{
    std::string List;
    for (TCommandTable::const_iterator i = m_Commands.begin(); i != m_Commands.end(); ++i)
        List += i->first + " ";

    return List;
}


////////////////////////////////////////////////////////////
/// Traite la ligne courante et appelle la fonction correspondante
///
////////////////////////////////////////////////////////////
void Console::ProcessCurrent()
{
    // On récupère la commande
    std::string Command;
    std::istringstream iss(m_Current);
    iss >> Command;

    // On recherche la commande dans la table des commandes
    TCommandTable::iterator It = m_Commands.find(Command);

    // Si elle s'y trouve on appelle la fonction correspondante, sinon on génère une erreur
    if (It != m_Commands.end())
    {
        // Récupération des paramètres
        std::string Params;
        std::getline(iss, Params);

        // Appel du foncteur correspondant à la commande -
        // s'il y a une erreur on la rattrape et on l'affiche dans la console
        try
        {
            m_Look->CommandCalled(It->second(Params));
        }
		catch (CException& ex)
		{
			m_Look->Error(ex.what());
		}
        catch (std::exception& stdEx)
        {
            m_Look->Error(stdEx.what());
        }		
    }
    else
    {
        m_Look->Error("Unknown command '" + Command + "'");
    }
}


} // namespace CasaEngine
