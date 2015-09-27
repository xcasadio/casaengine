
#include "MyConsole.h"
#include <Graphics/Renderer/Renderer.h>
#include "Addons/Console/Console.h"
#include "Addons/Console/Functor.h"
#include <sstream>
#include "Graphics/Vertices/VertexType.h"

#include <list>

#include <string>


#include "Game/GameInfo.h"


using namespace CasaEngine;


////////////////////////////////////////////////////////////
/// Constructeur par défaut
///
////////////////////////////////////////////////////////////
CMyConsole::CMyConsole() :
	m_State(STOPPED),
	m_Scale(0.0f),
	m_pEffect(nullptr)
{
    // Création du fond
    VertexPositionNormalTexture Vertices[4];
	Vertices[0].Position.Set(.0f, 0.0f, 0);		 Vertices[0].TexCoords.Set(0, 0);
	Vertices[1].Position.Set(640.0f,   0.0f, 0); Vertices[1].TexCoords.Set(1, 0);
	Vertices[2].Position.Set(  0.0f, 220.0f, 0); Vertices[2].TexCoords.Set(0, 1);
	Vertices[3].Position.Set(640.0f, 220.0f, 0); Vertices[3].TexCoords.Set(1, 1);

    unsigned short Indices[] = {0, 2, 1, 2, 3, 1};
    m_Background = NEW_AO Mesh(2, Vertices, 4, Indices, 6);
	Material *pMaterial = NEW_AO Material();
	Texture *pTexture = NEW_AO Texture();
	pTexture->CreateFromFile("console_bg.tga", PixelFormat::ARGB_8888);
	pMaterial->SetTexture0(pTexture);
	m_Background->SetMaterial(pMaterial);

	m_pEffect = IRenderer::Get().CreateEffectFromFile("simple");

    m_Transfo.CreateScale(0, 0, 0);
    AddLine();

    Console::Instance().RegisterCommand("clear", Bind(&std::list<GraphicString>::clear, m_Lines));
}


////////////////////////////////////////////////////////////
/// Fonction appelée lors de la mise à jour de la console
///
////////////////////////////////////////////////////////////
void CMyConsole::Update()
{
    // Mise à jour de la position de la console selon son état courant
    // et mise à jour de celui-ci
    if (m_State == SHOWING)
    {
        m_Transfo.CreateScale(m_Scale, m_Scale, 1);
        m_Scale += 0.01f;

        if (m_Scale > 1.0f)
        {
            m_Transfo.CreateScale(1, 1, 1);
            m_State = STOPPED;
            m_Scale   = 1.0f;
        }
    }
    else if (m_State == HIDDING)
    {
        m_Transfo.CreateScale(m_Scale, m_Scale, 1);
        m_Scale -= 0.01f;

        if (m_Scale < 0.01f)
        {
            m_Transfo.CreateScale(0, 0, 0);
            m_State = STOPPED;
            m_Scale   = 0.0f;
        }
    }
}


////////////////////////////////////////////////////////////
/// Fonction appelée lors de l'affichage de la console
///
////////////////////////////////////////////////////////////
void CMyConsole::Draw() const
{
	/*if (m_Scale == 0.0f)
	{
		return;
	}*/

    //IRenderer::Get().PushMatrix(MatrixType::ModelView);
    //IRenderer::Get().LoadMatrix(MatrixType::ModelView, m_Transfo);

	CA_ASSERT(GameInfo::Instance().GetActiveCamera() != nullptr, "GameInfo::Instance().GetActiveCamera() is nullptr");

	Matrix4 mat;
	mat = m_Transfo * GameInfo::Instance().GetActiveCamera()->GetProjectionMatrix();

	IRenderer::Get().Enable(RenderParameter::ZWrite, false);
    IRenderer::Get().Enable(RenderParameter::AlphaBlend, true);
    IRenderer::Get().SetupAlphaBlending(Blend::SrcAlpha, Blend::InvSrcAlpha);

    m_pEffect->Draw(m_Background, mat);

    IRenderer::Get().Enable(RenderParameter::AlphaBlend, false);

    for (std::list<GraphicString>::const_iterator i = m_Lines.begin(); i != m_Lines.end(); ++i)
        i->Draw(mat);

    IRenderer::Get().Enable(RenderParameter::ZWrite, true);
}


////////////////////////////////////////////////////////////
/// Fonction appelée lors de l'activation / désactivation de la console
///
/// \param Visible : Nouvel état de la console
///
////////////////////////////////////////////////////////////
void CMyConsole::Show(bool Visible)
{
    m_State = Visible ? SHOWING : HIDDING;
}


////////////////////////////////////////////////////////////
/// Fonction appelée après l'appel à une commande
///
/// \param Result : Résultat de l'appel de la commande
///
////////////////////////////////////////////////////////////
void CMyConsole::CommandCalled(const std::string& Result)
{
    if (!Result.empty())
        AddLine(Result, CColor::Green);
    AddLine();
}


////////////////////////////////////////////////////////////
/// Fonction appelée à chaque changement de la ligne courante
///
/// \param NewText : Nouveau texte
///
////////////////////////////////////////////////////////////
void CMyConsole::TextChanged(const std::string& NewText)
{
    m_Lines.front().Text = "> " + NewText;
}


////////////////////////////////////////////////////////////
/// Fonction appelée en cas d'erreur
///
/// \param Message : Message décrivant l'erreur
///
////////////////////////////////////////////////////////////
void CMyConsole::Error(const std::string& Message)
{
    // Décomposition du message en lignes
    std::string Line;
    std::istringstream iss(Message);
    while (std::getline(iss, Line))
        AddLine(Line, CColor::Red);

    AddLine();
}


////////////////////////////////////////////////////////////
/// Ajoute une ligne
///
/// \param Line :  Texte de la ligne à ajouter
/// \param Color : Couleur du texte
///
////////////////////////////////////////////////////////////
void CMyConsole::AddLine(const std::string& Line, const CColor& Color)
{
    // On supprime la dernière ligne si nécessaire
    if (m_Lines.size() == 20)
        m_Lines.pop_back();

	GraphicString gstr(Vector2I(10, 190), Line, Color, "courier_new", 12);
	Vector2I size = gstr.GetPixelSize();

    // On décale les autres
    for (std::list<GraphicString>::iterator i = m_Lines.begin(); i != m_Lines.end(); ++i)
    {
        i->Position.y -= size.y;
        //i->Color.Set(i->Color.GetRed(), i->Color.GetGreen(), i->Color.GetBlue(), i->Color.GetAlpha() - 20);
    }

    // Et on crée la nouvelle
    m_Lines.push_front(gstr);
}
