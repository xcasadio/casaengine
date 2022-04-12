#include "BoxPrimitive.h"
#include "Maths/Vector3.h"
#include "Maths/Vector2.h"

namespace CasaEngine
{
	BoxPrimitive::BoxPrimitive(float width_, float height_, float length_) :
		IPrimitive3D(Primitive3DType::BOX)
	{
		m_Width = width_;
		m_Height = height_;
		m_Length = length_;

		//TODO : UVs are not the same with OpenGL and DX

		//front
		AddIndex(false);
		IPrimitive3D::AddVertex((Vector3::UnitZ() * length_ - Vector3::UnitY() * height_ - Vector3::UnitX() * width_) / 2.0f, Vector3::UnitZ(), Vector2::Zero());
		IPrimitive3D::AddVertex((Vector3::UnitZ() * length_ - Vector3::UnitY() * height_ + Vector3::UnitX() * width_) / 2.0f, Vector3::UnitZ(), Vector2::UnitX());
		IPrimitive3D::AddVertex((Vector3::UnitZ() * length_ + Vector3::UnitY() * height_ - Vector3::UnitX() * width_) / 2.0f, Vector3::UnitZ(), Vector2::UnitY());
		IPrimitive3D::AddVertex((Vector3::UnitZ() * length_ + Vector3::UnitY() * height_ + Vector3::UnitX() * width_) / 2.0f, Vector3::UnitZ(), Vector2::One());

		//back
		AddIndex(true);
		IPrimitive3D::AddVertex((-Vector3::UnitZ() * length_ - Vector3::UnitY() * height_ - Vector3::UnitX() * width_) / 2.0f, -Vector3::UnitZ(), Vector2::Zero());
		IPrimitive3D::AddVertex((-Vector3::UnitZ() * length_ - Vector3::UnitY() * height_ + Vector3::UnitX() * width_) / 2.0f, -Vector3::UnitZ(), Vector2::UnitX());
		IPrimitive3D::AddVertex((-Vector3::UnitZ() * length_ + Vector3::UnitY() * height_ - Vector3::UnitX() * width_) / 2.0f, -Vector3::UnitZ(), Vector2::UnitY());
		IPrimitive3D::AddVertex((-Vector3::UnitZ() * length_ + Vector3::UnitY() * height_ + Vector3::UnitX() * width_) / 2.0f, -Vector3::UnitZ(), Vector2::One());

		//up
		AddIndex(true);
		IPrimitive3D::AddVertex((-Vector3::UnitZ() * length_ + Vector3::UnitY() * height_ - Vector3::UnitX() * width_) / 2.0f, Vector3::UnitY(), Vector2::Zero());
		IPrimitive3D::AddVertex((-Vector3::UnitZ() * length_ + Vector3::UnitY() * height_ + Vector3::UnitX() * width_) / 2.0f, Vector3::UnitY(), Vector2::UnitX());
		IPrimitive3D::AddVertex((Vector3::UnitZ() * length_ + Vector3::UnitY() * height_ - Vector3::UnitX() * width_) / 2.0f, Vector3::UnitY(), Vector2::UnitY());
		IPrimitive3D::AddVertex((Vector3::UnitZ() * length_ + Vector3::UnitY() * height_ + Vector3::UnitX() * width_) / 2.0f, Vector3::UnitY(), Vector2::One());

		//bottom
		AddIndex(false);
		IPrimitive3D::AddVertex((-Vector3::UnitZ() * length_ - Vector3::UnitY() * height_ - Vector3::UnitX() * width_) / 2.0f, -Vector3::UnitY(), Vector2::Zero());
		IPrimitive3D::AddVertex((-Vector3::UnitZ() * length_ - Vector3::UnitY() * height_ + Vector3::UnitX() * width_) / 2.0f, -Vector3::UnitY(), Vector2::UnitX());
		IPrimitive3D::AddVertex((Vector3::UnitZ() * length_ - Vector3::UnitY() * height_ - Vector3::UnitX() * width_) / 2.0f, -Vector3::UnitY(), Vector2::UnitY());
		IPrimitive3D::AddVertex((Vector3::UnitZ() * length_ - Vector3::UnitY() * height_ + Vector3::UnitX() * width_) / 2.0f, -Vector3::UnitY(), Vector2::One());

		//right
		AddIndex(true);
		IPrimitive3D::AddVertex((-Vector3::UnitZ() * length_ - Vector3::UnitY() * height_ + Vector3::UnitX() * width_) / 2.0f, Vector3::UnitX(), Vector2::Zero());
		IPrimitive3D::AddVertex((Vector3::UnitZ() * length_ - Vector3::UnitY() * height_ + Vector3::UnitX() * width_) / 2.0f, Vector3::UnitX(), Vector2::UnitX());
		IPrimitive3D::AddVertex((-Vector3::UnitZ() * length_ + Vector3::UnitY() * height_ + Vector3::UnitX() * width_) / 2.0f, Vector3::UnitX(), Vector2::UnitY());
		IPrimitive3D::AddVertex((Vector3::UnitZ() * length_ + Vector3::UnitY() * height_ + Vector3::UnitX() * width_) / 2.0f, Vector3::UnitX(), Vector2::One());

		//left
		AddIndex(false);
		IPrimitive3D::AddVertex((-Vector3::UnitZ() * length_ - Vector3::UnitY() * height_ - Vector3::UnitX() * width_) / 2.0f, -Vector3::UnitX(), Vector2::Zero());
		IPrimitive3D::AddVertex((Vector3::UnitZ() * length_ - Vector3::UnitY() * height_ - Vector3::UnitX() * width_) / 2.0f, -Vector3::UnitX(), Vector2::UnitX());
		IPrimitive3D::AddVertex((-Vector3::UnitZ() * length_ + Vector3::UnitY() * height_ - Vector3::UnitX() * width_) / 2.0f, -Vector3::UnitX(), Vector2::UnitY());
		IPrimitive3D::AddVertex((Vector3::UnitZ() * length_ + Vector3::UnitY() * height_ - Vector3::UnitX() * width_) / 2.0f, -Vector3::UnitX(), Vector2::One());

		m_nbPrimitives = 12;
	}

	/**
	 *
	 */
	BoxPrimitive::~BoxPrimitive()
	{
	}

	/**
	 *
	 */
	void BoxPrimitive::AddIndex(bool dir_)
	{
		if (dir_)
		{
			IPrimitive3D::AddIndex(GetCurrentVertex() + 0);
			IPrimitive3D::AddIndex(GetCurrentVertex() + 1);
			IPrimitive3D::AddIndex(GetCurrentVertex() + 2);

			IPrimitive3D::AddIndex(GetCurrentVertex() + 1);
			IPrimitive3D::AddIndex(GetCurrentVertex() + 3);
			IPrimitive3D::AddIndex(GetCurrentVertex() + 2);
		}
		else
		{
			IPrimitive3D::AddIndex(GetCurrentVertex() + 0);
			IPrimitive3D::AddIndex(GetCurrentVertex() + 2);
			IPrimitive3D::AddIndex(GetCurrentVertex() + 1);

			IPrimitive3D::AddIndex(GetCurrentVertex() + 1);
			IPrimitive3D::AddIndex(GetCurrentVertex() + 2);
			IPrimitive3D::AddIndex(GetCurrentVertex() + 3);
		}
	}
}