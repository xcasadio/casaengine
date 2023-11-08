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

#ifndef CONSOLE_H
#define CONSOLE_H


#include "LibraryFrameworkExport.h"
#include "Singleton.h"
#include "Addons/Console/Functor.h"
#include "Addons/Console/Look.h"

#include <map>


namespace CasaEngine
{
    ////////////////////////////////////////////////////////////
    /// Gestion de la console
    ////////////////////////////////////////////////////////////
    class LIBRARY_FRAMEWORK_EXPORT Console : 
		public CSingleton<Console>
    {
    MAKE_SINGLETON(Console)

    public :
        //----------------------------------------------------------
        // Change l'apparence de la console
        //----------------------------------------------------------
        void ChangeLook(IConsoleLook* NewLook);

        //----------------------------------------------------------
        // Enregistre une nouvelle commande
        //----------------------------------------------------------
        void RegisterCommand(const std::string& Name, const Functor& Function);

        //----------------------------------------------------------
        // Envoie un nouveau caract�re � la console
        //----------------------------------------------------------
        void SendChar(char Character);

        //----------------------------------------------------------
        // Met � jour la console
        //----------------------------------------------------------
        void Update();

        //----------------------------------------------------------
        // Affiche la console
        //----------------------------------------------------------
        void Draw() const;

        //----------------------------------------------------------
        // Active ou d�sactive la console
        //----------------------------------------------------------
        void Enable(bool Enabled);

    private :

		//----------------------------------------------------------
		// Constructeur par d�faut
		//----------------------------------------------------------
		Console();

        //----------------------------------------------------------
        // Donne la liste des commandes enregistr�es
        //----------------------------------------------------------
        std::string GetCommands() const;

        //----------------------------------------------------------
        // Traite la ligne courante et appelle la fonction correspondante
        //----------------------------------------------------------
        void ProcessCurrent();

        //----------------------------------------------------------
        // Types
        //----------------------------------------------------------
        typedef std::map<std::string, Functor> TCommandTable;

        //----------------------------------------------------------
        // Donn�es membres
        //----------------------------------------------------------
        TCommandTable             m_Commands; ///< Table des commandes enregistr�es
        std::string               m_Current;  ///< Ligne courante
        SmartPtr<IConsoleLook>	  m_Look;     ///< Pointeur sur la classe g�rant l'apparence de la console
        bool                      m_Enabled;  ///< Indique si la console est active ou non
    };

} // namespace CasaEngine


#endif // CONSOLE_H
