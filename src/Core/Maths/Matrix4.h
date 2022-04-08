#ifndef MATRIX4_H
#define MATRIX4_H

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

		/// <summary>
		/// Constructs a matrix.
		/// </summary>
		/// <param name="row1">A first row of the created matrix.</param>
		/// <param name="row2">A second row of the created matrix.</param>
		/// <param name="row3">A third row of the created matrix.</param>
		/// <param name="row4">A fourth row of the created matrix.</param>
		Matrix4(Vector4F row1, Vector4F row2, Vector4F row3, Vector4F row4);

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

		static Matrix4 CreateIdentity();
		void Identity();

		Vector3F Backward();
		void Backward(const Vector3F& value);
		Vector3F Down() const;
		void Down(const Vector3F& value);
		Vector3F Forward() const;
		void Forward(const Vector3F& value);
		Vector3F Left() const;
		void Left(const Vector3F& value);
		Vector3F Right();
		void Right(Vector3F value);
		Vector3F Up();
		void Up(Vector3F value);

		void CreateFromDirection(const Vector3F& forward, const Vector3F& side, const Vector3F& up);
		void Transformation(const Vector3F* pscalingcenter,
			const Quaternion* pscalingrotation, const Vector3F* pscaling,
			const Vector3F* protationcenter, const Quaternion* protation,
			const Vector3F* ptranslation);

		Vector3F Translation();
		void Translation(const Vector3F& value);
		void Translation(float x, float y, float z);

		/// <summary>
		  /// Creates a new <see cref="Matrix"/> which contains sum of two matrixes.
		  /// </summary>
		  /// <param name="matrix1">The first Matrix4 to add.</param>
		  /// <param name="matrix2">The second Matrix4 to add.</param>
		  /// <returns>The result of the Matrix4 addition.</returns>
		static Matrix4 Add(Matrix4 matrix1, Matrix4 matrix2);

		Vector3F Transform(const Vector3F& v, float w) const;
		Vector4F Transform(const Vector4F& v) const;
		Vector3F Transform(const Vector3F& position);
		void Transform(const std::vector<Vector3F>& sourceArray, std::vector<Vector3F>& destinationArray);
		void TransformNormal(const Vector3F& normal, Vector3F& result) const;

		/// <summary>
		  /// Creates a new <see cref="Matrix"/> for spherical billboarding that rotates around specified object position.
		  /// </summary>
		  /// <param name="objectPosition">Position of billboard object. It will rotate around that vector.</param>
		  /// <param name="cameraPosition">The camera position.</param>
		  /// <param name="cameraUpVector">The camera up vector.</param>
		  /// <param name="cameraForwardVector">Optional camera forward vector.</param>
		  /// <returns>The <see cref="Matrix"/> for spherical billboarding.</returns>
		static Matrix4 CreateBillboard(Vector3F objectPosition, Vector3F cameraPosition,
			Vector3F cameraUpVector, Vector3F* cameraForwardVector = nullptr);

		/// <summary>
		  /// Creates a new <see cref="Matrix"/> for cylindrical billboarding that rotates around specified axis.
		  /// </summary>
		  /// <param name="objectPosition">Object position the billboard will rotate around.</param>
		  /// <param name="cameraPosition">Camera position.</param>
		  /// <param name="rotateAxis">Axis of billboard for rotation.</param>
		  /// <param name="cameraForwardVector">Optional camera forward vector.</param>
		  /// <param name="objectForwardVector">Optional object forward vector.</param>
		  /// <returns>The <see cref="Matrix"/> for cylindrical billboarding.</returns>
		static Matrix4 CreateConstrainedBillboard(Vector3F objectPosition, Vector3F cameraPosition,
			Vector3F rotateAxis, Vector3F* cameraForwardVector = nullptr, Vector3F* objectForwardVector = nullptr);

		/// <summary>
		  /// Creates a new <see cref="Matrix"/> which contains the rotation moment around specified axis.
		  /// </summary>
		  /// <param name="axis">The axis of rotation.</param>
		  /// <param name="angle">The angle of rotation in radians.</param>
		  /// <returns>The rotation <see cref="Matrix"/>.</returns>
		static Matrix4 CreateFromAxisAngle(Vector3F axis, float angle);

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
		static Matrix4 CreateLookAt(Vector3F cameraPosition, Vector3F cameraTarget, Vector3F cameraUpVector);

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
		  /// <param name="farPlaneDistance">Distance to the far plane, or <see cref="float.PositiveInfinity"/>.</param>
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
		static Matrix4 CreatePerspectiveOffCenter(RectangleF viewingVolume, float nearPlaneDistance, float farPlaneDistance);

		/// <summary>
		  /// Creates a new rotation <see cref="Matrix"/> around X axis.
		  /// </summary>
		  /// <param name="radians">Angle in radians.</param>
		  /// <returns>The rotation <see cref="Matrix"/> around X axis.</returns>
		static Matrix4 CreateRotationX(float radians);

		/// <summary>
		  /// Creates a new rotation <see cref="Matrix"/> around Y axis.
		  /// </summary>
		  /// <param name="radians">Angle in radians.</param>
		  /// <returns>The rotation <see cref="Matrix"/> around Y axis.</returns>
		static Matrix4 CreateRotationY(float radians);

		/// <summary>
		  /// Creates a new rotation <see cref="Matrix"/> around Z axis.
		  /// </summary>
		  /// <param name="radians">Angle in radians.</param>
		  /// <returns>The rotation <see cref="Matrix"/> around Z axis.</returns>
		static Matrix4 CreateRotationZ(float radians);

		/// <summary>
		  /// Creates a new scaling <see cref="Matrix"/>.
		  /// </summary>
		  /// <param name="scale">Scale value for all three axises.</param>
		  /// <returns>The scaling <see cref="Matrix"/>.</returns>
		static Matrix4 CreateScale(float scale);

		/// <summary>
		  /// Creates a new scaling <see cref="Matrix"/>.
		  /// </summary>
		  /// <param name="xScale">Scale value for X axis.</param>
		  /// <param name="yScale">Scale value for Y axis.</param>
		  /// <param name="zScale">Scale value for Z axis.</param>
		  /// <returns>The scaling <see cref="Matrix"/>.</returns>
		static Matrix4 CreateScale(float xScale, float yScale, float zScale);

		/// <summary>
		  /// Creates a new scaling <see cref="Matrix"/>.
		  /// </summary>
		  /// <param name="scales"><see cref="Vector3F"/> representing x,y and z scale values.</param>
		  /// <returns>The scaling <see cref="Matrix"/>.</returns>
		static Matrix4 CreateScale(Vector3F scales);

		/// <summary>
		  /// Creates a new <see cref="Matrix"/> that flattens geometry into a specified <see cref="Plane"/> as if casting a shadow from a specified light source. 
		  /// </summary>
		  /// <param name="lightDirection">A vector specifying the direction from which the light that will cast the shadow is coming.</param>
		  /// <param name="plane">The plane onto which the new Matrix4 should flatten geometry so as to cast a shadow.</param>
		  /// <returns>A <see cref="Matrix"/> that can be used to flatten geometry onto the specified plane from the specified direction. </returns>
		static Matrix4 CreateShadow(Vector3F lightDirection, Plane plane);

		/// <summary>
		  /// Creates a new translation <see cref="Matrix"/>.
		  /// </summary>
		  /// <param name="xPosition">X coordinate of translation.</param>
		  /// <param name="yPosition">Y coordinate of translation.</param>
		  /// <param name="zPosition">Z coordinate of translation.</param>
		  /// <returns>The translation <see cref="Matrix"/>.</returns>
		static Matrix4 CreateTranslation(float xPosition, float yPosition, float zPosition);

		/// <summary>
		  /// Creates a new translation <see cref="Matrix"/>.
		  /// </summary>
		  /// <param name="position">X,Y and Z coordinates of translation.</param>
		  /// <returns>The translation <see cref="Matrix"/>.</returns>
		static Matrix4 CreateTranslation(Vector3F position);

		/// <summary>
		  /// Creates a new reflection <see cref="Matrix"/>.
		  /// </summary>
		  /// <param name="value">The plane that used for reflection calculation.</param>
		  /// <returns>The reflection <see cref="Matrix"/>.</returns>
		static Matrix4 CreateReflection(Plane value);

		/// <summary>
		  /// Creates a new world <see cref="Matrix"/>.
		  /// </summary>
		  /// <param name="position">The position vector.</param>
		  /// <param name="forward">The forward direction vector.</param>
		  /// <param name="up">The upward direction vector. Usually <see cref="Vector3F.Up"/>.</param>
		  /// <returns>The world <see cref="Matrix"/>.</returns>
		static Matrix4 CreateWorld(Vector3F position, Vector3F forward, Vector3F up);

		/// <summary>
		  /// Decomposes this Matrix4 to translation, rotation and scale elements. Returns <c>true</c> if Matrix4 can be decomposed; <c>false</c> otherwise.
		  /// </summary>
		  /// <param name="scale">Scale vector as an output parameter.</param>
		  /// <param name="rotation">Rotation quaternion as an output parameter.</param>
		  /// <param name="translation">Translation vector as an output parameter.</param>
		  /// <returns><c>true</c> if Matrix4 can be decomposed; <c>false</c> otherwise.</returns>
		bool Decompose(Vector3F& scale, Quaternion& rotation, Vector3F& translation);

		/// <summary>
		  /// Returns a determinant of this <see cref="Matrix"/>.
		  /// </summary>
		  /// <returns>Determinant of this <see cref="Matrix"/></returns>
		  /// <remarks>See more about determinant here - http://en.wikipedia.org/wiki/Determinant.
		  /// </remarks>
		float Determinant() const;

		/// <summary>
		  /// Divides the elements of a <see cref="Matrix"/> by the elements of another matrix.
		  /// </summary>
		  /// <param name="matrix1">Source <see cref="Matrix"/>.</param>
		  /// <param name="matrix2">Divisor <see cref="Matrix"/>.</param>
		  /// <returns>The result of dividing the matrix.</returns>
		static Matrix4 Divide(Matrix4 matrix1, Matrix4 matrix2);

		/// <summary>
		  /// Divides the elements of a <see cref="Matrix"/> by a scalar.
		  /// </summary>
		  /// <param name="matrix1">Source <see cref="Matrix"/>.</param>
		  /// <param name="divider">Divisor scalar.</param>
		  /// <returns>The result of dividing a Matrix4 by a scalar.</returns>
		static Matrix4 Divide(Matrix4 matrix1, float divider);

		/// <summary>
		  /// Creates a new <see cref="Matrix"/> which contains inversion of the specified matrix. 
		  /// </summary>
		  /// <param name="matrix">Source <see cref="Matrix"/>.</param>
		  /// <returns>The inverted matrix.</returns>
		static Matrix4 Invert(Matrix4 matrix);

		/// <summary>
		  /// Creates a new <see cref="Matrix"/> that contains linear interpolation of the values in specified matrixes.
		  /// </summary>
		  /// <param name="matrix1">The first <see cref="Matrix"/>.</param>
		  /// <param name="matrix2">The second <see cref="Vector2"/>.</param>
		  /// <param name="amount">Weighting value(between 0.0 and 1.0).</param>
		  /// <returns>>The result of linear interpolation of the specified matrixes.</returns>
		static Matrix4 Lerp(Matrix4 matrix1, Matrix4 matrix2, float amount);

		/// <summary>
		  /// Creates a new <see cref="Matrix"/> that contains a multiplication of two matrix.
		  /// </summary>
		  /// <param name="matrix1">Source <see cref="Matrix"/>.</param>
		  /// <param name="matrix2">Source <see cref="Matrix"/>.</param>
		  /// <returns>Result of the Matrix4 multiplication.</returns>
		static Matrix4 Multiply(Matrix4 matrix1, Matrix4 matrix2);

		/// <summary>
		  /// Creates a new <see cref="Matrix"/> that contains a multiplication of <see cref="Matrix"/> and a scalar.
		  /// </summary>
		  /// <param name="matrix1">Source <see cref="Matrix"/>.</param>
		  /// <param name="scaleFactor">Scalar value.</param>
		  /// <returns>Result of the Matrix4 multiplication with a scalar.</returns>
		static Matrix4 Multiply(Matrix4 matrix1, float scaleFactor);

		/// <summary>
		/// Copy the values of specified <see cref="Matrix"/> to the float array.
		/// </summary>
		/// <param name="matrix">The source <see cref="Matrix"/>.</param>
		/// <returns>The array which Matrix4 values will be stored.</returns>
		/// <remarks>
		/// Required for OpenGL 2.0 projection Matrix4 stuff.
		/// </remarks>
		static float* ToFloatArray(Matrix4 matrix);

		/// <summary>
		  /// Returns a Matrix4 with the all values negated.
		  /// </summary>
		  /// <param name="matrix">Source <see cref="Matrix"/>.</param>
		  /// <returns>Result of the Matrix4 negation.</returns>
		static Matrix4 Negate(Matrix4 matrix);

		bool operator ==(const Matrix4& m) const;

		bool operator !=(const Matrix4& m) const;

		/// <summary>
		  /// Adds two matrixes.
		  /// </summary>
		  /// <param name="matrix1">Source <see cref="Matrix"/> on the left of the add sign.</param>
		  /// <param name="matrix2">Source <see cref="Matrix"/> on the right of the add sign.</param>
		  /// <returns>Sum of the matrixes.</returns>
		Matrix4& operator +(const Matrix4& matrix2);

		/// <summary>
		  /// Divides the elements of a <see cref="Matrix"/> by the elements of another <see cref="Matrix"/>.
		  /// </summary>
		  /// <param name="matrix1">Source <see cref="Matrix"/> on the left of the div sign.</param>
		  /// <param name="matrix2">Divisor <see cref="Matrix"/> on the right of the div sign.</param>
		  /// <returns>The result of dividing the matrixes.</returns>
		Matrix4& operator /(const Matrix4& matrix2);

		/// <summary>
		  /// Divides the elements of a <see cref="Matrix"/> by a scalar.
		  /// </summary>
		  /// <param name="matrix">Source <see cref="Matrix"/> on the left of the div sign.</param>
		  /// <param name="divider">Divisor scalar on the right of the div sign.</param>
		  /// <returns>The result of dividing a Matrix4 by a scalar.</returns>
		Matrix4 operator /(float divider);

		/// <summary>
		  /// Multiplies two matrixes.
		  /// </summary>
		  /// <param name="matrix1">Source <see cref="Matrix"/> on the left of the mul sign.</param>
		  /// <param name="matrix2">Source <see cref="Matrix"/> on the right of the mul sign.</param>
		  /// <returns>Result of the Matrix4 multiplication.</returns>
		  /// <remarks>
		  /// Using Matrix4 multiplication algorithm - see http://en.wikipedia.org/wiki/Matrix_multiplication.
		  /// </remarks>
		Matrix4 operator *(const Matrix4& matrix2);
		const Matrix4& operator *=(const Matrix4& m);

		/// <summary>
		  /// Multiplies the elements of Matrix4 by a scalar.
		  /// </summary>
		  /// <param name="matrix">Source <see cref="Matrix"/> on the left of the mul sign.</param>
		  /// <param name="scaleFactor">Scalar value on the right of the mul sign.</param>
		  /// <returns>Result of the Matrix4 multiplication with a scalar.</returns>
		Matrix4 operator *(float scaleFactor);

		/// <summary>
		  /// Subtracts the values of one <see cref="Matrix"/> from another <see cref="Matrix"/>.
		  /// </summary>
		  /// <param name="matrix1">Source <see cref="Matrix"/> on the left of the sub sign.</param>
		  /// <param name="matrix2">Source <see cref="Matrix"/> on the right of the sub sign.</param>
		  /// <returns>Result of the Matrix4 subtraction.</returns>
		Matrix4 operator -(const Matrix4& matrix2);

		/// <summary>
		  /// Inverts values in the specified <see cref="Matrix"/>.
		  /// </summary>
		  /// <param name="matrix">Source <see cref="Matrix"/> on the right of the sub sign.</param>
		  /// <returns>Result of the inversion.</returns>
		Matrix4 operator -();

		/// <summary>
		  /// Creates a new <see cref="Matrix"/> that contains subtraction of one Matrix4 from another.
		  /// </summary>
		  /// <param name="matrix1">The first <see cref="Matrix"/>.</param>
		  /// <param name="matrix2">The second <see cref="Matrix"/>.</param>
		  /// <returns>The result of the Matrix4 subtraction.</returns>
		static Matrix4 Subtract(Matrix4 matrix1, Matrix4 matrix2);

		/// <summary>
		  /// Swap the Matrix4 rows and columns.
		  /// </summary>
		  /// <param name="matrix">The Matrix4 for transposing operation.</param>
		  /// <returns>The new <see cref="Matrix"/> which contains the transposing result.</returns>
		static Matrix4 Transpose(Matrix4 matrix);
	};
}

#endif
