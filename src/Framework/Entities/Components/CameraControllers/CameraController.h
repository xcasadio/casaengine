#pragma once

#include "CA_Export.h"
#include "GameTime.h"
#include <iosfwd>
#include "Entities/Components/CameraComponent.h"
#include "Maths/Matrix4.h"


namespace CasaEngine
{
	class CA_EXPORT ICameraController
	{
	public:
		virtual ~ICameraController();

		virtual void Initialize() = 0;
		virtual void  Update(const GameTime& gameTime_) = 0;
		virtual void ViewMatrix(Matrix4& viewMatrix_) = 0;
		virtual void ProjectionMatrix(Matrix4& projectionMatrix_) = 0;

		virtual void Write(std::ostream& os);
		virtual void Read(std::ifstream& is);

	protected:
		ICameraController(CameraComponent* pCamera);
		CameraComponent* Camera() const;

	private:
		CameraComponent* m_pCamera;
	};
}
