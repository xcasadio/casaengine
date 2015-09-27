
#include "Base.h"
#include "EngineInfo.h"



namespace CasaEngine
{

SINGLETON_IMPL(EngineInfo)

/**
 * 
 */
EngineInfo::EngineInfo()
{
	//m_pCurrentViewport = &m_DefaultViewport;
}

/**
 * 
 */
EngineInfo::~EngineInfo()
{
}

/**
 * 
Viewport& EngineInfo::GetViewport() 
{
	return *m_pCurrentViewport; 
};

void EngineInfo::SetViewport(Viewport *pViewport_)
{
	m_pCurrentViewport = pViewport_ == nullptr ? &m_DefaultViewport : pViewport_;
}

Viewport* EngineInfo::GetDefaultViewport()
{
	return &m_DefaultViewport;
}
*/

} // namespace CasaEngine
