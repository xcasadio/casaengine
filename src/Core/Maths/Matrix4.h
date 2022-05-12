#pragma once

#include <iosfwd>

#include "CA_Export.h"
#include "Plane.h"
#include "Rectangle.h"
#include "Maths/Vector3.h"
#include "Maths/Vector4.h"

namespace CasaEngine
{
	class Quaternion;

	class CA_EXPORT Matrix4
	{
	public:
		float m11, m12, m13, m14;
		float m21, m22, m23, m24;
		float m31, m32, m33, m34;
		float m41, m42, m43, m44;

		//float m11, m21, m31, m41;
		//float m12, m22, m32, m42;
		//float m13, m23, m33, m43;
		//float m14, m24, m34, m44;

		Matrix4();
		Matrix4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31,
			float m32, float m33, float m34, float m41, float m42, float m43, float m44);
		Matrix4(Vector4 row1, Vector4 row2, Vector4 row3, Vector4 row4);

		static Matrix4 CreateIdentity();
		void Identity();
		bool IsIdentity() const;

		Vector3 Backward();
		void Backward(const Vector3& value);
		Vector3 Down() const;
		void Down(const Vector3& value);
		Vector3 Forward() const;
		void Forward(const Vector3& value);
		Vector3 Left() const;
		void Left(const Vector3& value);
		Vector3 Right();
		void Right(Vector3 value);
		Vector3 Up();
		void Up(Vector3 value);

		Vector3 Translation();
		void Translation(const Vector3& value);
		void Translation(float x, float y, float z);

		void CreateFromDirection(const Vector3& forward, const Vector3& side, const Vector3& up);
		void Transformation(const Vector3* pscalingcenter,
			const Quaternion* pscalingrotation, const Vector3* pscaling,
			const Vector3* protationcenter, const Quaternion* protation,
			const Vector3* ptranslation);
		
		Vector3 Transform(const Vector3& v, float w) const;
		Vector4 Transform(const Vector4& v) const;
		Vector3 Transform(const Vector3& position);
		void Transform(const std::vector<Vector3>& sourceArray, std::vector<Vector3>& destinationArray);
		Vector3 TransformNormal(const Vector3& normal) const;
		void TransformNormal(const Vector3& normal, Vector3& result) const;

		/// <summary>
		/// Creates a new <see cref="Matrix"/> for spherical billboarding that rotates around specified object position.
		/// </summary>
		/// <param name="objectPosition">Position of billboard object. It will rotate around that vector.</param>
		/// <param name="cameraPosition">The camera position.</param>
		/// <param name="cameraUpVector">The camera up vector.</param>
		/// <param name="cameraForwardVector">Optional camera forward vector.</param>
		/// <returns>The <see cref="Matrix"/> for spherical billboarding.</returns>
		static Matrix4 CreateBillboard(Vector3 objectPosition, Vector3 cameraPosition,
			Vector3 cameraUpVector, Vector3* cameraForwardVector = nullptr);

		/// <summary>
		/// Creates a new <see cref="Matrix"/> for cylindrical billboarding that rotates around specified axis.
		/// </summary>
		/// <param name="objectPosition">Object position the billboard will rotate around.</param>
		/// <param name="cameraPosition">Camera position.</param>
		/// <param name="rotateAxis">Axis of billboard for rotation.</param>
		/// <param name="cameraForwardVector">Optional camera forward vector.</param>
		/// <param name="objectForwardVector">Optional object forward vector.</param>
		/// <returns>The <see cref="Matrix"/> for cylindrical billboarding.</returns>
		static Matrix4 CreateConstrainedBillboard(Vector3 objectPosition, Vector3 cameraPosition,
			Vector3 rotateAxis, Vector3* cameraForwardVector = nullptr, Vector3* objectForwardVector = nullptr);

		/// <summary>
		/// Creates a new <see cref="Matrix"/> which contains the rotation moment around specified axis.
		/// </summary>
		/// <param name="axis">The axis of rotation.</param>
		/// <param name="angle">The angle of rotation in radians.</param>
		/// <returns>The rotation <see cref="Matrix"/>.</returns>
		static Matrix4 CreateFromAxisAngle(Vector3 axis, float angle);

		/// <summary>
		/// Creates a new rotation <see cref="Matrix"/> from a <see cref="Quaternion"/>.
		/// </summary>
		/// <param name="quaternion"><see cref="Quaternion"/> of rotation moment.</param>
		/// <returns>The rotation <see cref="Matrix"/>.</returns>
		static Matrix4 CreateFromQuaternion(Quaternion quaternion);

		/// <summary>
		/// Creates a new rotation <see cref="Matrix"/> from the specified yaw, pitch and roll values.
		/// </summary>
		/// <param name="yaw">The yaw rotation value in radians.</param>
		/// <param name="pitch">The pitch rotation value in radians.</param>
		/// <param name="roll">The roll rotation value in radians.</param>
		/// <returns>The rotation <see cref="Matrix"/>.</returns>
		/// <remarks>For more information about yaw, pitch and roll visit http://en.wikipedia.org/wiki/Euler_angles.
		/// </remarks>
		static Matrix4 CreateFromYawPitchRoll(float yaw, float pitch, float roll);

		/// <summary>
		/// Creates a new viewing <see cref="Matrix"/>.
		/// </summary>
		/// <param name="cameraPosition">Position of the camera.</param>
		/// <param name="cameraTarget">Lookup vector of the camera.</param>
		/// <param name="cameraUpVector">The direction of the upper edge of the camera.</param>
		/// <returns>The viewing <see cref="Matrix"/>.</returns>
		static Matrix4 CreateLookAt(Vector3 cameraPosition, Vector3 cameraTarget, Vector3 cameraUpVector);

		/// <summary>
		/// Creates a new projection <see cref="Matrix"/> for orthographic view.
		/// </summary>
		/// <param name="width">Width of the viewing volume.</param>
		/// <param name="height">Height of the viewing volume.</param>
		/// <param name="zNearPlane">Depth of the near plane.</param>
		/// <param name="zFarPlane">Depth of the far plane.</param>
		/// <returns>The new projection <see cref="Matrix"/> for orthographic view.</returns>
		static Matrix4 CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);

		/// <summary>
		/// Creates a new projection <see cref="Matrix"/> for customized orthographic view.
		/// </summary>
		/// <param name="left">Lower x-value at the near plane.</param>
		/// <param name="right">Upper x-value at the near plane.</param>
		/// <param name="bottom">Lower y-coordinate at the near plane.</param>
		/// <param name="top">Upper y-value at the near plane.</param>
		/// <param name="zNearPlane">Depth of the near plane.</param>
		/// <param name="zFarPlane">Depth of the far plane.</param>
		/// <returns>The new projection <see cref="Matrix"/> for customized orthographic view.</returns>
		static Matrix4 CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);

		/// <summary>
		/// Creates a new projection <see cref="Matrix"/> for perspective view.
		/// </summary>
		/// <param name="width">Width of the viewing volume.</param>
		/// <param name="height">Height of the viewing volume.</param>
		/// <param name="nearPlaneDistance">Distance to the near plane.</param>
		/// <param name="farPlaneDistance">Distance to the far plane.</param>
		/// <returns>The new projection <see cref="Matrix"/> for perspective view.</returns>
		static Matrix4 CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance);

		/// <summary>
		/// Creates a new projection <see cref="Matrix"/> for perspective view with field of view.
		/// </summary>
		/// <param name="fieldOfView">Field of view in the y direction in radians.</param>
		/// <param name="aspectRatio">Width divided by height of the viewing volume.</param>
		/// <param name="nearPlaneDistance">Distance to the near plane.</param>
		/// <param name="farPlaneDistance">Distance to the far plane, or <see cref="std::numeric_limits<float>::max()"/>.</param>
		/// <returns>The new projection <see cref="Matrix"/> for perspective view with FOV.</returns>
		static Matrix4 CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);

		/// <summary>
		/// Creates a new projection <see cref="Matrix"/> for customized perspective view.
		/// </summary>
		/// <param name="left">Lower x-value at the near plane.</param>
		/// <param name="right">Upper x-value at the near plane.</param>
		/// <param name="bottom">Lower y-coordinate at the near plane.</param>
		/// <param name="top">Upper y-value at the near plane.</param>
		/// <param name="nearPlaneDistance">Distance to the near plane.</param>
		/// <param name="farPlaneDistance">Distance to the far plane.</param>
		/// <returns>The new <see cref="Matrix"/> for customized perspective view.</returns>
		static Matrix4 CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance);

		/// <summary>
		/// Creates a new projection <see cref="Matrix"/> for customized perspective view.
		/// </summary>
		/// <param name="viewingVolume">The viewing volume.</param>
		/// <param name="nearPlaneDistance">Distance to the near plane.</param>
		/// <param name="farPlaneDistance">Distance to the far plane.</param>
		/// <returns>The new <see cref="Matrix"/> for customized perspective view.</returns>
		static Matrix4 CreatePerspectiveOffCenter(Rectangle viewingVolume, float nearPlaneDistance, float farPlaneDistance);

		static Matrix4 CreateRotationX(float radians);
		static Matrix4 CreateRotationX(float radians, Vector3 centerPoint);
		static Matrix4 CreateRotationY(float radians);
		static Matrix4 CreateRotationY(float radians, Vector3 centerPoint);
		static Matrix4 CreateRotationZ(float radians);
		static Matrix4 CreateRotationZ(float radians, Vector3 centerPoint);

		static Matrix4 CreateScale(float scale);
		//static Matrix4 CreateScale(float xScale, float yScale, float zScale);
		//static Matrix4 CreateScale(Vector3 scales);
		static Matrix4 CreateScale(float xScale, float yScale, float zScale, Vector3 centerPoint = Vector3::Zero());
		static Matrix4 CreateScale(Vector3 scales, Vector3 centerPoint = Vector3::Zero());

		/// <summary>
		/// Creates a new <see cref="Matrix"/> that flattens geometry into a specified <see cref="Plane"/> as if casting a shadow from a specified light source. 
		/// </summary>
		/// <param name="lightDirection">A vector specifying the direction from which the light that will cast the shadow is coming.</param>
		/// <param name="plane">The plane onto which the new Matrix4 should flatten geometry so as to cast a shadow.</param>
		/// <returns>A <see cref="Matrix"/> that can be used to flatten geometry onto the specified plane from the specified direction. </returns>
		static Matrix4 CreateShadow(Vector3 lightDirection, Plane plane);
		static Matrix4 CreateTranslation(float xPosition, float yPosition, float zPosition);
		static Matrix4 CreateTranslation(Vector3 position);
		static Matrix4 CreateReflection(Plane value);
		static Matrix4 CreateWorld(Vector3 position, Vector3 forward, Vector3 up);

		bool Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation) const;
		float Determinant() const;
		static Matrix4 Invert(Matrix4 matrix);
		static Matrix4 Transpose(Matrix4 matrix);

		// Creates a new <see cref="Matrix"/> that contains linear interpolation of the values in specified matrixes.
		// <param name="amount">Weighting value(between 0.0 and 1.0).</param>
		static Matrix4 Lerp(Matrix4 matrix1, Matrix4 matrix2, float amount);

		static Matrix4 Add(const Matrix4& matrix1, const Matrix4& matrix2);
		static Matrix4 Subtract(Matrix4 matrix1, Matrix4 matrix2);
		static Matrix4 Multiply(Matrix4 matrix1, Matrix4 matrix2);
		static Matrix4 Multiply(Matrix4 matrix1, float scaleFactor);
		static Matrix4 Divide(Matrix4 matrix1, Matrix4 matrix2);
		static Matrix4 Divide(Matrix4 matrix1, float divider);
		static Matrix4 Negate(Matrix4 matrix);

		static float* ToFloatArray(Matrix4 matrix);

		/// <summary>
		/// Get or set the Matrix4 element at the given index, indexed in row major order.
		/// </summary>
		/// <param name="index">The linearized, zero-based index of the Matrix4 element.</param>
		/// <exception cref="ArgumentOutOfRangeException">
		/// If the index is less than <code>0</code> or larger than <code>15</code>.
		/// </exception>
		float operator[] (int index) const;
		float& operator ()(std::size_t i, std::size_t j);
		const float& operator ()(std::size_t i, std::size_t j) const;
		operator float* ();
		operator const float* () const;

		bool operator ==(const Matrix4& m) const;
		bool operator !=(const Matrix4& m) const;
		Matrix4 operator +(const Matrix4& matrix2);
		Matrix4 operator /(const Matrix4& matrix2);
		Matrix4 operator /(float divider);
		Matrix4 operator *(const Matrix4& matrix2);
		const Matrix4& operator *=(const Matrix4& m);


		Matrix4 operator *(float scaleFactor); // Multiplies the elements of Matrix4 by a scalar.

		Matrix4 operator -(const Matrix4& matrix2);
		Matrix4 operator -();
	};
}
