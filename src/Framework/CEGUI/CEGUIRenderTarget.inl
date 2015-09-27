#include "CEGUIRenderTarget.h"
#include "CEGUIGeometryBuffer.h"
#include "Entities\Components\CameraComponent.h"
#include "Graphics\RenderTarget.h"
#include "Graphics\Viewport.h"
#include "Maths\Matrix4.h"
#include "Maths\Vector3.h"
#include "Maths\Plane.h"
#include "Game\Game.h"
#include "CA_Assert.h"


#include "CEGUI\GeometryBuffer.h"
#include "CEGUI\Rect.h"
#include "CEGUI\RenderQueue.h"
#include "CEGUI\Vector.h"
#include "CEGUI\RenderTarget.h"

namespace CasaEngine
{

	/**
	 * 
	 */
	template <typename T>
	CEGUIRenderTarget<T>::CEGUIRenderTarget(CasaEngine::RenderTarget *pRenderTarget_) :
		m_IsMatrixValid(false)
	{
		CA_TRACE("CEGUIRenderTarget(%p) created\n", this);

		CA_ASSERT(pRenderTarget_ != nullptr, "CEGUIRenderTarget() : RenderTarget is nullptr");

		m_pRenderTarget = pRenderTarget_;

		setArea(CEGUI::Rectf(
			static_cast<float>(m_pRenderTarget->GetArea().Left()),
			static_cast<float>(m_pRenderTarget->GetArea().Top()),
			static_cast<float>(m_pRenderTarget->GetArea().Right()), // Width
			static_cast<float>(m_pRenderTarget->GetArea().Bottom()) )); // Height
	}

	/**
	 * 
	 */
	/*const CEGUIRenderTarget& CEGUIRenderTarget<T>::operator = (const CEGUIRenderTarget& rsh_)
	{
		m_pRenderTarget = rsh_.m_pRenderTarget;
		return *this;
	}*/

	/**
	 * 
	 */
	template <typename T>
	CEGUIRenderTarget<T>::~CEGUIRenderTarget()
	{
		delete m_pRenderTarget;
	}

	/**
	 * 
	 */
	template <typename T>
	void CEGUIRenderTarget<T>::draw(const CEGUI::GeometryBuffer& buffer)
	{
		buffer.draw();
	}

	/**
	 * 
	 */
	template <typename T>
	void CEGUIRenderTarget<T>::draw(const CEGUI::RenderQueue& queue)
	{
		queue.draw();
	}

	/**
	 * 
	 */
	template <typename T>
	void CEGUIRenderTarget<T>::setArea(const CEGUI::Rectf& area)
	{
		CA_TRACE("CEGUIRenderTarget(%p) area %f %f %f %f\n", this,
			area.left(), area.top(), area.right(), area.bottom());

		m_Area = area;
		m_IsMatrixValid = false;

		m_pRenderTarget->SetArea(CRectangle(m_Area.left(), m_Area.top(), m_Area.getWidth(), m_Area.getHeight()));

		CEGUI::RenderTargetEventArgs args(this);
		T::fireEvent(CEGUI::RenderTarget::EventAreaChanged, args);
	}

	/**
	 * 
	 */
	template <typename T>
	const CEGUI::Rectf& CEGUIRenderTarget<T>::getArea() const
	{
		return m_Area;
	}

	/**
	 * 
	 */
	template <typename T>
	bool CEGUIRenderTarget<T>::isImageryCache() const
	{
		return m_pRenderTarget->IsImageryCache();
	}

	/**
	 * 
	 */
	template <typename T>
	void CEGUIRenderTarget<T>::activate()
	{
		UpdateMatrix();
		m_pRenderTarget->Activate();
		Game::Instance()->GetCEGUIRenderer()->SetViewProjMatrix(m_ViewProjMatrix);
	}

	/**
	 * 
	 */
	template <typename T>
	void CEGUIRenderTarget<T>::deactivate()
	{
		m_pRenderTarget->Deactivate();
	}

	/**
	 * 
	 */
	template <typename T>
	void CEGUIRenderTarget<T>::unprojectPoint(const CEGUI::GeometryBuffer& buff, const CEGUI::Vector2f& p_in, CEGUI::Vector2f& p_out) const
	{
		UpdateMatrix();
		const CEGUIGeometryBuffer& gb = static_cast<const CEGUIGeometryBuffer&>(buff);

		//CameraComponent *pCamera = GameInfo::Instance().GetActiveCamera();
		//Viewport &vp = pCamera->GetViewport();
		Viewport vp(m_Area.d_min.d_x, m_Area.d_min.d_y, m_Area.d_max.d_x, m_Area.d_max.d_y);
		Vector3F in_vec;
		Matrix4 view = m_ViewMatrix;//pCamera->GetViewMatrix();
		Matrix4 proj = m_ProjMatrix; //pCamera->GetProjectionMatrix();
		Matrix4 world = gb.GetMatrix();

		// project points to create a plane orientated with GeometryBuffer's data
		Vector3F p1, p2, p3;
		in_vec.x = 0;
		in_vec.y = 0;
		p1 = vp.Project(in_vec, proj, view, world);

		in_vec.x = 1;
		in_vec.y = 0;
		p2 = vp.Project(in_vec, proj, view, world);

		in_vec.x = 0;
		in_vec.y = 1;
		p3 = vp.Project(in_vec, proj, view, world);

		// create plane from projected points
		CPlane plane;
		plane.BuildFromPoints(p1, p2, p3);

		// unproject ends of ray
		in_vec.x = vp.Width() * 0.5f;
		in_vec.y = vp.Height() * 0.5f;
		in_vec.z = -m_ViewDistance;//pCamera->GetViewDistance();
		Vector3F t1 = vp.Unproject(in_vec, proj, view, world);

		in_vec.x = p_in.d_x;
		in_vec.y = p_in.d_y;
		in_vec.z = 0.0f;
		Vector3F t2 = vp.Unproject(in_vec, proj, view, world);

		// get intersection of ray and plane
		Vector3F intersect;
		if (plane.IntersectLine(t1, t2, &intersect) == true)
		{
			p_out.d_x = intersect.x;
			p_out.d_y = intersect.y;
		}
	}

	/**
	 * 
	 */
	template <typename T>
	void CEGUIRenderTarget<T>::UpdateMatrix() const
	{
		if (m_IsMatrixValid == true)
		{
			return;
		}

		/*const float fov = 0.523598776f;
		const float w = m_Area.getWidth();
		const float h = m_Area.getHeight();
		const float aspect = w / h;
		const float midx = w * 0.5f;
		const float midy = h * 0.5f;
		m_ViewDistance = midx / (aspect * 0.267949192431123f);

		Vector3F eye(midx, midy, -m_ViewDistance);
		Vector3F at(midx, midy, 1);

		m_ViewMatrix.LookAt(eye, at, Vector3F::Up());
		m_ProjMatrix.PerspectiveFOV(fov, aspect, m_ViewDistance * 0.5f, m_ViewDistance * 2.0f);*/
		m_ProjMatrix.OrthoOffCenter(m_Area.d_min.d_x, m_Area.d_min.d_y, m_Area.d_max.d_x, m_Area.d_max.d_y);
		m_ViewProjMatrix = m_ViewMatrix * m_ProjMatrix;

		m_IsMatrixValid = true;
	}
}
