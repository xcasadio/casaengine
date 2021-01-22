#include "Base.h"

#include "BoxPrimitive.h"
#include "Exceptions.h"
#include "Maths/Vector3.h"
#include "Maths/Vector2.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Mesh/Mesh.h"


namespace CasaEngine
{
	/**
	 * 
	 */
	BoxPrimitive::BoxPrimitive(float width_, float height_, float length_) :
		IPrimitive3D(IPrimitive3D::BOX)
	{
		m_Width = width_;
		m_Height = height_;
		m_Length = length_;

		//TODO : UVs are not the same with OpenGL and DX

		//front
		AddIndex(false);
		IPrimitive3D::AddVertex((Vector3F::UnitZ() * length_ - Vector3F::UnitY() * height_ - Vector3F::UnitX() * width_) / 2.0f,  Vector3F::UnitZ(), Vector2F::Zero());
		IPrimitive3D::AddVertex((Vector3F::UnitZ() * length_ - Vector3F::UnitY() * height_ + Vector3F::UnitX() * width_) / 2.0f,  Vector3F::UnitZ(), Vector2F::UnitX());
		IPrimitive3D::AddVertex((Vector3F::UnitZ() * length_ + Vector3F::UnitY() * height_ - Vector3F::UnitX() * width_) / 2.0f,  Vector3F::UnitZ(), Vector2F::UnitY());
		IPrimitive3D::AddVertex((Vector3F::UnitZ() * length_ + Vector3F::UnitY() * height_ + Vector3F::UnitX() * width_) / 2.0f,  Vector3F::UnitZ(), Vector2F::One());

		//back
		AddIndex(true);
		IPrimitive3D::AddVertex((-Vector3F::UnitZ() * length_ - Vector3F::UnitY() * height_ - Vector3F::UnitX() * width_) / 2.0f, -Vector3F::UnitZ(), Vector2F::Zero());
		IPrimitive3D::AddVertex((-Vector3F::UnitZ() * length_ - Vector3F::UnitY() * height_ + Vector3F::UnitX() * width_) / 2.0f, -Vector3F::UnitZ(), Vector2F::UnitX());
		IPrimitive3D::AddVertex((-Vector3F::UnitZ() * length_ + Vector3F::UnitY() * height_ - Vector3F::UnitX() * width_) / 2.0f, -Vector3F::UnitZ(), Vector2F::UnitY());
		IPrimitive3D::AddVertex((-Vector3F::UnitZ() * length_ + Vector3F::UnitY() * height_ + Vector3F::UnitX() * width_) / 2.0f, -Vector3F::UnitZ(), Vector2F::One());
		
		//up
		AddIndex(true);
		IPrimitive3D::AddVertex((-Vector3F::UnitZ() * length_ + Vector3F::UnitY() * height_ - Vector3F::UnitX() * width_) / 2.0f,  Vector3F::UnitY(), Vector2F::Zero());
		IPrimitive3D::AddVertex((-Vector3F::UnitZ() * length_ + Vector3F::UnitY() * height_ + Vector3F::UnitX() * width_) / 2.0f,  Vector3F::UnitY(), Vector2F::UnitX());
		IPrimitive3D::AddVertex(( Vector3F::UnitZ() * length_ + Vector3F::UnitY() * height_ - Vector3F::UnitX() * width_) / 2.0f,  Vector3F::UnitY(), Vector2F::UnitY());
		IPrimitive3D::AddVertex(( Vector3F::UnitZ() * length_ + Vector3F::UnitY() * height_ + Vector3F::UnitX() * width_) / 2.0f,  Vector3F::UnitY(), Vector2F::One());

		//bottom
		AddIndex(false);
		IPrimitive3D::AddVertex((-Vector3F::UnitZ() * length_ - Vector3F::UnitY() * height_ - Vector3F::UnitX() * width_) / 2.0f, -Vector3F::UnitY(), Vector2F::Zero());
		IPrimitive3D::AddVertex((-Vector3F::UnitZ() * length_ - Vector3F::UnitY() * height_ + Vector3F::UnitX() * width_) / 2.0f, -Vector3F::UnitY(), Vector2F::UnitX());
		IPrimitive3D::AddVertex(( Vector3F::UnitZ() * length_ - Vector3F::UnitY() * height_ - Vector3F::UnitX() * width_) / 2.0f, -Vector3F::UnitY(), Vector2F::UnitY());
		IPrimitive3D::AddVertex(( Vector3F::UnitZ() * length_ - Vector3F::UnitY() * height_ + Vector3F::UnitX() * width_) / 2.0f, -Vector3F::UnitY(), Vector2F::One());

		//right
		AddIndex(true);
		IPrimitive3D::AddVertex((-Vector3F::UnitZ() * length_ - Vector3F::UnitY() * height_ + Vector3F::UnitX() * width_) / 2.0f,  Vector3F::UnitX(), Vector2F::Zero());
		IPrimitive3D::AddVertex(( Vector3F::UnitZ() * length_ - Vector3F::UnitY() * height_ + Vector3F::UnitX() * width_) / 2.0f,  Vector3F::UnitX(), Vector2F::UnitX());
		IPrimitive3D::AddVertex((-Vector3F::UnitZ() * length_ + Vector3F::UnitY() * height_ + Vector3F::UnitX() * width_) / 2.0f,  Vector3F::UnitX(), Vector2F::UnitY());
		IPrimitive3D::AddVertex(( Vector3F::UnitZ() * length_ + Vector3F::UnitY() * height_ + Vector3F::UnitX() * width_) / 2.0f,  Vector3F::UnitX(), Vector2F::One());
		
		//left
		AddIndex(false);
		IPrimitive3D::AddVertex((-Vector3F::UnitZ() * length_ - Vector3F::UnitY() * height_ - Vector3F::UnitX() * width_) / 2.0f, -Vector3F::UnitX(), Vector2F::Zero());
		IPrimitive3D::AddVertex((Vector3F::UnitZ() * length_ - Vector3F::UnitY() * height_ - Vector3F::UnitX() * width_) / 2.0f, -Vector3F::UnitX(), Vector2F::UnitX());
		IPrimitive3D::AddVertex((-Vector3F::UnitZ() * length_ + Vector3F::UnitY() * height_ - Vector3F::UnitX() * width_) / 2.0f, -Vector3F::UnitX(), Vector2F::UnitY());
		IPrimitive3D::AddVertex((Vector3F::UnitZ() * length_ + Vector3F::UnitY() * height_ - Vector3F::UnitX() * width_) / 2.0f, -Vector3F::UnitX(), Vector2F::One());
	
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
