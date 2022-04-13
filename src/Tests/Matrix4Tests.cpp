#include "gtest/gtest.h"

#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"
#include "Maths/Math.h"
#include "Maths/Quaternion.h"

using namespace CasaEngine;

namespace CasaEngineTests
{
	TEST(Matrix4, TransformPoint)
	{
		Vector3 v = Vector3::Zero();
		Matrix4 translate;
		translate.Translation(-5.0f, -10.0f, 4.0f);
		v = translate.Transform(v);

		EXPECT_NEAR(-5.0f, v.GetX(), 0.01f);
		EXPECT_NEAR(-10.0f, v.GetY(), 0.01f);
		EXPECT_NEAR(4.0f, v.GetZ(), 0.01f);

		Matrix4 translate2;
		translate2.Translation(5.0f, 10.0f, -4.0f);

		v = translate2.Transform(v);

		EXPECT_NEAR(0.0f, v.GetX(), 0.01f);
		EXPECT_NEAR(0.0f, v.GetY(), 0.01f);
		EXPECT_NEAR(0.0f, v.GetZ(), 0.01f);
	}
	/*
	TEST(Matrix4, Multiplication)
	{
		Vector3 v(1.0f, 1.0f, 1.0f);
		Matrix4 world_transform = Matrix4::CreateScale(3.0f);
		Matrix4 translate;
		translate.Translation(5.0f, 10.0f, -4.0f);
		world_transform *= translate;

		v = world_transform.Transform(v);

		EXPECT_NEAR(18.0f, v.GetX(), 0.01f);
		EXPECT_NEAR(33.0f, v.GetY(), 0.01f);
		EXPECT_NEAR(-9.0f, v.GetZ(), 0.01f);
	}
	*/
	TEST(Matrix4, Add)
	{
		Vector3 v(1.0f, 1.0f, 1.0f);
		Matrix4 world_transform = Matrix4::CreateScale(3.0f);
		const Matrix4 translate;

		world_transform = Matrix4::Add(world_transform, translate);

		v = world_transform.Transform(v);

		EXPECT_NEAR(4.0f, v.GetX(), 0.01f);
		EXPECT_NEAR(4.0f, v.GetY(), 0.01f);
		EXPECT_NEAR(4.0f, v.GetZ(), 0.01f);
	}

	TEST(Matrix4, Subtraction)
	{
		Vector3 v(1.0f, 1.0f, 1.0f);
		Matrix4 world_transform = Matrix4::CreateScale(3.0f);
		const Matrix4 translate;
		world_transform = Matrix4::Subtract(world_transform, translate);

		v = world_transform.Transform(v);

		EXPECT_NEAR(2.0f, v.GetX(), 0.01f);
		EXPECT_NEAR(2.0f, v.GetY(), 0.01f);
		EXPECT_NEAR(2.0f, v.GetZ(), 0.01f);
	}

	TEST(Matrix4, Scale)
	{
		Matrix4 scale = Matrix4::CreateScale(3.0f);
		Vector3 v(1.0f, 1.0f, 1.0f);
		v = scale.Transform(v);

		EXPECT_NEAR(3.0f, v.GetX(), 0.01f);
		EXPECT_NEAR(3.0f, v.GetY(), 0.01f);
		EXPECT_NEAR(3.0f, v.GetZ(), 0.01f);
	}

	TEST(Matrix4, RotateX)
	{
		Matrix4 rot = Matrix4::CreateRotationX(PI / 2.0f);
		Vector3 v(Vector3::UnitY());
		v = rot.Transform(v);

		EXPECT_NEAR(0.0f, v.GetX(), 0.01f);
		EXPECT_NEAR(0.0f, v.GetY(), 0.01f);
		EXPECT_NEAR(1.0f, v.GetZ(), 0.01f);
	}

	TEST(Matrix4, RotateY)
	{
		Matrix4 rot = Matrix4::CreateRotationY(PI / 2.0f);
		Vector3 v(Vector3::UnitX());
		v = rot.Transform(v);

		EXPECT_NEAR(0.0f, v.GetX(), 0.01f);
		EXPECT_NEAR(0.0f, v.GetY(), 0.01f);
		EXPECT_NEAR(-1.0f, v.GetZ(), 0.01f);
	}

	TEST(Matrix4, RotateZ)
	{
		Matrix4 rot = Matrix4::CreateRotationZ(PI / 2.0f);
		Vector3 v(Vector3::UnitX());
		v = rot.Transform(v);

		EXPECT_NEAR(0.0f, v.GetX(), 0.01f);
		EXPECT_NEAR(1.0f, v.GetY(), 0.01f);
		EXPECT_NEAR(0.0f, v.GetZ(), 0.01f);
	}

	TEST(Matrix4, Translate)
	{
		Matrix4 trans = Matrix4::CreateTranslation(Vector3(5.0f, 10.0f, -4.0f));
		Vector3 v(Vector3::Zero());
		v = trans.Transform(v);

		EXPECT_NEAR(5.0f, v.GetX(), 0.01f);
		EXPECT_NEAR(10.0f, v.GetY(), 0.01f);
		EXPECT_NEAR(-4.0f, v.GetZ(), 0.01f);
	}

	Matrix4 GenerateIncrementalMatrixNumber(float value = 0.0f)
	{
		Matrix4 a;
		a.m11 = value + 1.0f;
		a.m12 = value + 2.0f;
		a.m13 = value + 3.0f;
		a.m14 = value + 4.0f;
		a.m21 = value + 5.0f;
		a.m22 = value + 6.0f;
		a.m23 = value + 7.0f;
		a.m24 = value + 8.0f;
		a.m31 = value + 9.0f;
		a.m32 = value + 10.0f;
		a.m33 = value + 11.0f;
		a.m34 = value + 12.0f;
		a.m41 = value + 13.0f;
		a.m42 = value + 14.0f;
		a.m43 = value + 15.0f;
		a.m44 = value + 16.0f;
		return a;
	}

	Matrix4 GenerateTestMatrix()
	{
		Matrix4 m =
			Matrix4::CreateRotationX(ToRadian(30.0f)) *
			Matrix4::CreateRotationY(ToRadian(30.0f)) *
			Matrix4::CreateRotationZ(ToRadian(30.0f));
		m.Translation(111.0f, 222.0f, 333.0f);
		return m;
	}
	
	// A test for Identity
	TEST(Matrix4, Identity)
	{
		Matrix4 val;
		val.m11 = val.m22 = val.m33 = val.m44 = 1.0f;

		EXPECT_EQ(val, Matrix4::CreateIdentity());
	}

	// A test for Determinant
	TEST(Matrix4, Determinant)
	{
		const Matrix4 target =
			Matrix4::CreateRotationX(ToRadian(30.0f)) *
			Matrix4::CreateRotationY(ToRadian(30.0f)) *
			Matrix4::CreateRotationZ(ToRadian(30.0f));

		const float val = 1.0f;
		const float det = target.Determinant();

		EXPECT_EQ(val, det);
	}

	// A test for Determinant
	// Determinant test |A| = 1 / |A'|
	void Matrix4DeterminantTest1()
	{
		Matrix4 a;
		a.m11 = 5.0f;
		a.m12 = 2.0f;
		a.m13 = 8.25f;
		a.m14 = 1.0f;
		a.m21 = 12.0f;
		a.m22 = 6.8f;
		a.m23 = 2.14f;
		a.m24 = 9.6f;
		a.m31 = 6.5f;
		a.m32 = 1.0f;
		a.m33 = 3.14f;
		a.m34 = 2.22f;
		a.m41 = 0.0f;
		a.m42 = 0.86f;
		a.m43 = 4.0f;
		a.m44 = 1.0f;
		Matrix4 i = Matrix4::Invert(i);

		const float detA = a.Determinant();
		const float detI = i.Determinant();
		const float t = 1.0f / detI;

		// only accurate to 3 precision
		EXPECT_TRUE(abs(detA - t) < 1e-3);
	}

	// A test for Invert (Matrix4)
	TEST(Matrix4, Invert)
	{
		Matrix4 mtx =
			Matrix4::CreateRotationX(ToRadian(30.0f)) *
			Matrix4::CreateRotationY(ToRadian(30.0f)) *
			Matrix4::CreateRotationZ(ToRadian(30.0f));

		Matrix4 expected;
		expected.m11 = 0.74999994f;
		expected.m12 = -0.216506317f;
		expected.m13 = 0.62499994f;
		expected.m14 = 0.0f;

		expected.m21 = 0.433012635f;
		expected.m22 = 0.87499994f;
		expected.m23 = -0.216506317f;
		expected.m24 = 0.0f;

		expected.m31 = -0.49999997f;
		expected.m32 = 0.433012635f;
		expected.m33 = 0.74999994f;
		expected.m34 = 0.0f;

		expected.m41 = 0.0f;
		expected.m42 = 0.0f;
		expected.m43 = 0.0f;
		expected.m44 = 0.99999994f;

		const Matrix4 actual = Matrix4::Invert(mtx);
		EXPECT_EQ(expected, actual);
		// Make sure M*M is identity matrix
		const Matrix4 i = mtx * actual;
		EXPECT_EQ(i, Matrix4::CreateIdentity());
	}

	// A test for Invert (Matrix4)

	TEST(Matrix4, InvertIdentity)
	{
		const Matrix4 mtx = Matrix4::CreateIdentity();

		Matrix4 actual;
		actual = Matrix4::Invert(mtx);

		EXPECT_EQ(actual, Matrix4::CreateIdentity());
	}

	// A test for Invert (Matrix4)

	TEST(Matrix4, InvertTranslation)
	{
		Matrix4 mtx = Matrix4::CreateTranslation(23, 42, 666);

		Matrix4 actual;
		actual = Matrix4::Invert(mtx);

		const Matrix4 i = mtx * actual;
		EXPECT_EQ(i, Matrix4::CreateIdentity());
	}

	// A test for Invert (Matrix4)

	TEST(Matrix4, InvertRotation)
	{
		Matrix4 mtx = Matrix4::CreateFromYawPitchRoll(3, 4, 5);

		Matrix4 actual;
		actual = Matrix4::Invert(mtx);

		const Matrix4 i = mtx * actual;
		EXPECT_EQ(i, Matrix4::CreateIdentity());
	}

	// A test for Invert (Matrix4)

	TEST(Matrix4, InvertScale)
	{
		Matrix4 mtx = Matrix4::CreateScale(23, 42, -666);

		Matrix4 actual;
		actual = Matrix4::Invert(mtx);

		const Matrix4 i = mtx * actual;
		EXPECT_EQ(i, Matrix4::CreateIdentity());
	}

	// A test for Invert (Matrix4)

	TEST(Matrix4, InvertProjection)
	{
		Matrix4 mtx = Matrix4::CreatePerspectiveFieldOfView(1, 1.333f, 0.1f, 666);

		Matrix4 actual;
		actual = Matrix4::Invert(mtx);

		const Matrix4 i = mtx * actual;
		EXPECT_EQ(i, Matrix4::CreateIdentity());
	}

	// A test for Invert (Matrix4)

	TEST(Matrix4, InvertAffine)
	{
		Matrix4 mtx = Matrix4::CreateFromYawPitchRoll(3, 4, 5) *
			Matrix4::CreateScale(23, 42, -666) *
			Matrix4::CreateTranslation(17, 53, 89);

		const Matrix4 actual = Matrix4::Invert(mtx);

		const Matrix4 i = mtx * actual;
		EXPECT_EQ(i, Matrix4::CreateIdentity());
	}

	// A test for Invert (Matrix4)

	void Matrix4InvertRank3()
	{
		// A 4x4 Matrix having a rank of 3
		Matrix4 mtx(1.0f, 2.0f, 3.0f, 0.0f,
			5.0f, 1.0f, 6.0f, 0.0f,
			8.0f, 9.0f, 1.0f, 0.0f,
			4.0f, 7.0f, 3.0f, 0.0f);

		const Matrix4 actual  = Matrix4::Invert(mtx);

		const Matrix4 i = mtx * actual;
		EXPECT_EQ(i, Matrix4::CreateIdentity());
	}

	void DecomposeTest(float yaw, float pitch, float roll, Vector3 expectedTranslation, Vector3 expectedScales)
	{
		const Quaternion expectedRotation = Quaternion::CreateFromYawPitchRoll(ToRadian(yaw),
		                                                                       ToRadian(pitch),
		                                                                       ToRadian(roll));

		const Matrix4 m = Matrix4::CreateScale(expectedScales) *
			Matrix4::CreateFromQuaternion(expectedRotation) *
			Matrix4::CreateTranslation(expectedTranslation);

		Vector3 scales;
		Quaternion rotation;
		Vector3 translation;

		const bool actualResult = m.Decompose(scales, rotation, translation);
		EXPECT_TRUE(actualResult);

		const bool scaleIsZeroOrNegative = expectedScales.x <= 0 ||
			expectedScales.y <= 0 ||
			expectedScales.z <= 0;

		if (scaleIsZeroOrNegative)
		{
			EXPECT_EQ(abs(expectedScales.x), abs(scales.x));
			EXPECT_EQ(abs(expectedScales.y), abs(scales.y));
			EXPECT_EQ(abs(expectedScales.z), abs(scales.z));
		}
		else
		{
			EXPECT_EQ(expectedScales, scales);
			EXPECT_EQ(expectedRotation, rotation);
		}

		EXPECT_EQ(expectedTranslation, translation);
	}

	// Various rotation decompose test.

	void Matrix4DecomposeTest01()
	{
		DecomposeTest(10.0f, 20.0f, 30.0f, Vector3(10, 20, 30), Vector3(2, 3, 4));

		const float step = 35.0f;

		for (float yawAngle = -720.0f; yawAngle <= 720.0f; yawAngle += step)
		{
			for (float pitchAngle = -720.0f; pitchAngle <= 720.0f; pitchAngle += step)
			{
				for (float rollAngle = -720.0f; rollAngle <= 720.0f; rollAngle += step)
				{
					DecomposeTest(yawAngle, pitchAngle, rollAngle, Vector3(10, 20, 30), Vector3(2, 3, 4));
				}
			}
		}
	}

	// Various scaled matrix decompose test.

	void Matrix4DecomposeTest02()
	{
		DecomposeTest(10.0f, 20.0f, 30.0f, Vector3(10, 20, 30), Vector3(2, 3, 4));

		// Various scales.
		DecomposeTest(0, 0, 0, Vector3::Zero(), Vector3(1, 2, 3));
		DecomposeTest(0, 0, 0, Vector3::Zero(), Vector3(1, 3, 2));
		DecomposeTest(0, 0, 0, Vector3::Zero(), Vector3(2, 1, 3));
		DecomposeTest(0, 0, 0, Vector3::Zero(), Vector3(2, 3, 1));
		DecomposeTest(0, 0, 0, Vector3::Zero(), Vector3(3, 1, 2));
		DecomposeTest(0, 0, 0, Vector3::Zero(), Vector3(3, 2, 1));

		DecomposeTest(0, 0, 0, Vector3::Zero(), Vector3(-2, 1, 1));

		// Small scales.
		DecomposeTest(0, 0, 0, Vector3::Zero(), Vector3(1e-4f, 2e-4f, 3e-4f));
		DecomposeTest(0, 0, 0, Vector3::Zero(), Vector3(1e-4f, 3e-4f, 2e-4f));
		DecomposeTest(0, 0, 0, Vector3::Zero(), Vector3(2e-4f, 1e-4f, 3e-4f));
		DecomposeTest(0, 0, 0, Vector3::Zero(), Vector3(2e-4f, 3e-4f, 1e-4f));
		DecomposeTest(0, 0, 0, Vector3::Zero(), Vector3(3e-4f, 1e-4f, 2e-4f));
		DecomposeTest(0, 0, 0, Vector3::Zero(), Vector3(3e-4f, 2e-4f, 1e-4f));

		// Zero scales.
		DecomposeTest(0, 0, 0, Vector3(10, 20, 30), Vector3(0, 0, 0));
		DecomposeTest(0, 0, 0, Vector3(10, 20, 30), Vector3(1, 0, 0));
		DecomposeTest(0, 0, 0, Vector3(10, 20, 30), Vector3(0, 1, 0));
		DecomposeTest(0, 0, 0, Vector3(10, 20, 30), Vector3(0, 0, 1));
		DecomposeTest(0, 0, 0, Vector3(10, 20, 30), Vector3(0, 1, 1));
		DecomposeTest(0, 0, 0, Vector3(10, 20, 30), Vector3(1, 0, 1));
		DecomposeTest(0, 0, 0, Vector3(10, 20, 30), Vector3(1, 1, 0));

		// Negative scales.
		DecomposeTest(0, 0, 0, Vector3(10, 20, 30), Vector3(-1, -1, -1));
		DecomposeTest(0, 0, 0, Vector3(10, 20, 30), Vector3(1, -1, -1));
		DecomposeTest(0, 0, 0, Vector3(10, 20, 30), Vector3(-1, 1, -1));
		DecomposeTest(0, 0, 0, Vector3(10, 20, 30), Vector3(-1, -1, 1));
		DecomposeTest(0, 0, 0, Vector3(10, 20, 30), Vector3(-1, 1, 1));
		DecomposeTest(0, 0, 0, Vector3(10, 20, 30), Vector3(1, -1, 1));
		DecomposeTest(0, 0, 0, Vector3(10, 20, 30), Vector3(1, 1, -1));
	}

	void DecomposeScaleTest(float sx, float sy, float sz)
	{
		const Matrix4 m = Matrix4::CreateScale(sx, sy, sz);

		const Vector3 expectedScales(sx, sy, sz);
		Vector3 scales;
		Quaternion rotation;
		Vector3 translation;

		const bool actualResult = m.Decompose(scales, rotation, translation);
		EXPECT_TRUE(actualResult);
		EXPECT_EQ(expectedScales, scales);
		EXPECT_EQ(Quaternion::CreateIdentity(), rotation);
		EXPECT_EQ(Vector3::Zero(), translation);
	}

	// Tiny scale decompose test.

	void Matrix4DecomposeTest03()
	{
		DecomposeScaleTest(1, 2e-4f, 3e-4f);
		DecomposeScaleTest(1, 3e-4f, 2e-4f);
		DecomposeScaleTest(2e-4f, 1, 3e-4f);
		DecomposeScaleTest(2e-4f, 3e-4f, 1);
		DecomposeScaleTest(3e-4f, 1, 2e-4f);
		DecomposeScaleTest(3e-4f, 2e-4f, 1);
	}


	void Matrix4DecomposeTest04()
	{
		Vector3 scales;
		Quaternion rotation;
		Vector3 translation;

		EXPECT_FALSE(GenerateIncrementalMatrixNumber().Decompose(scales, rotation, translation));
	}

	// Transform by quaternion test

	TEST(Matrix4, Transform)
	{
		Matrix4 target = GenerateIncrementalMatrixNumber();

		const Matrix4 m =
			Matrix4::CreateRotationX(ToRadian(30.0f)) *
			Matrix4::CreateRotationY(ToRadian(30.0f)) *
			Matrix4::CreateRotationZ(ToRadian(30.0f));

		const Quaternion q = Quaternion::CreateFromRotationMatrix(m);

		const Matrix4 expected = target * m;
		auto from_quaternion = Matrix4::CreateFromQuaternion(q);
		Matrix4 actual = target * from_quaternion;
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateRotationX (float)

	TEST(Matrix4, CreateRotationX)
	{
		const float radians = ToRadian(30.0f);

		Matrix4 expected;

		expected.m11 = 1.0f;
		expected.m22 = 0.8660254f;
		expected.m23 = 0.5f;
		expected.m32 = -0.5f;
		expected.m33 = 0.8660254f;
		expected.m44 = 1.0f;

		Matrix4 actual = Matrix4::CreateRotationX(radians);

		EXPECT_EQ(expected, actual);
	}

	// A test for CreateRotationX (float)
	// CreateRotationX of zero degree

	void Matrix4CreateRotationXTest1()
	{
		const float radians = 0;

		const Matrix4 expected = Matrix4::CreateIdentity();
		const Matrix4 actual = Matrix4::CreateRotationX(radians);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateRotationX (float, Vector3f)
	TEST(Matrix4, CreateRotationXCenter)
	{
		float radians = ToRadian(30.0f);
		Vector3 center = Vector3(23, 42, 66);

		Matrix4 rotateAroundZero = Matrix4::CreateRotationX(radians, Vector3::Zero());
		Matrix4 rotateAroundZeroExpected = Matrix4::CreateRotationX(radians);
		EXPECT_EQ(rotateAroundZero, rotateAroundZeroExpected);

		Matrix4 rotateAroundCenter = Matrix4::CreateRotationX(radians, center);
		Matrix4 rotateAroundCenterExpected = Matrix4::CreateTranslation(-center) * Matrix4::CreateRotationX(radians) * Matrix4::CreateTranslation(center);
		EXPECT_EQ(rotateAroundCenter, rotateAroundCenterExpected);
	}
	
	// A test for CreateRotationY (float)

	TEST(Matrix4, CreateRotationY)
	{
		const float radians = ToRadian(60.0f);

		Matrix4 expected;

		expected.m11 = 0.49999997f;
		expected.m13 = -0.866025448f;
		expected.m22 = 1.0f;
		expected.m31 = 0.866025448f;
		expected.m33 = 0.49999997f;
		expected.m44 = 1.0f;

		Matrix4 actual = Matrix4::CreateRotationY(radians);
		EXPECT_EQ(expected, actual);
	}

	// A test for RotationY (float)
	// CreateRotationY test for negative angle

	void Matrix4CreateRotationYTest1()
	{
		const float radians = ToRadian(-300.0f);

		Matrix4 expected;

		expected.m11 = 0.49999997f;
		expected.m13 = -0.866025448f;
		expected.m22 = 1.0f;
		expected.m31 = 0.866025448f;
		expected.m33 = 0.49999997f;
		expected.m44 = 1.0f;

		const Matrix4 actual = Matrix4::CreateRotationY(radians);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateRotationY (float, Vector3f)
	
	TEST(Matrix4, CreateRotationYCenter)
	{
		float radians = ToRadian(30.0f);
		Vector3 center = Vector3(23, 42, 66);

		Matrix4 rotateAroundZero = Matrix4::CreateRotationY(radians, Vector3::Zero());
		Matrix4 rotateAroundZeroExpected = Matrix4::CreateRotationY(radians);
		EXPECT_EQ(rotateAroundZero, rotateAroundZeroExpected);

		Matrix4 rotateAroundCenter = Matrix4::CreateRotationY(radians, center);
		Matrix4 rotateAroundCenterExpected = Matrix4::CreateTranslation(-center) * Matrix4::CreateRotationY(radians) * Matrix4::CreateTranslation(center);
		EXPECT_EQ(rotateAroundCenter, rotateAroundCenterExpected);
	}
	
	// A test for CreateFromAxisAngle(Vector3f,float)

	TEST(Matrix4, CreateFromAxisAngle)
	{
		float radians = ToRadian(-30.0f);

		Matrix4 expected = Matrix4::CreateRotationX(radians);
		Matrix4 actual = Matrix4::CreateFromAxisAngle(Vector3::UnitX(), radians);
		EXPECT_EQ(expected, actual);
		expected = Matrix4::CreateRotationY(radians);
		actual = Matrix4::CreateFromAxisAngle(Vector3::UnitY(), radians);
		EXPECT_EQ(expected, actual);
		expected = Matrix4::CreateRotationZ(radians);
		actual = Matrix4::CreateFromAxisAngle(Vector3::UnitZ(), radians);
		EXPECT_EQ(expected, actual);
		expected = Matrix4::CreateFromQuaternion(Quaternion::CreateFromAxisAngle(Vector3::Normalize(Vector3::One()), radians));
		actual = Matrix4::CreateFromAxisAngle(Vector3::Normalize(Vector3::One()), radians);
		EXPECT_EQ(expected, actual);

		const int rotCount = 16;
		for (int i = 0; i < rotCount; ++i)
		{
			float latitude = (2.0f * PI) * ((float)i / (float)rotCount);
			for (int j = 0; j < rotCount; ++j)
			{
				float longitude = -PI_OVER_2 + PI * ((float)j / (float)rotCount);

				Matrix4 m = Matrix4::CreateRotationZ(longitude) * Matrix4::CreateRotationY(latitude);
				Vector3 axis = m.Right();
				for (int k = 0; k < rotCount; ++k)
				{
					float rot = (2.0f * PI) * ((float)k / (float)rotCount);
					expected = Matrix4::CreateFromQuaternion(Quaternion::CreateFromAxisAngle(axis, rot));
					actual = Matrix4::CreateFromAxisAngle(axis, rot);
					EXPECT_EQ(expected, actual);
				}
			}
		}
	}


	void Matrix4CreateFromYawPitchRollTest1()
	{
		const float yawAngle = ToRadian(30.0f);
		const float pitchAngle = ToRadian(40.0f);
		const float rollAngle = ToRadian(50.0f);

		const Matrix4 yaw = Matrix4::CreateFromAxisAngle(Vector3::UnitY(), yawAngle);
		const Matrix4 pitch = Matrix4::CreateFromAxisAngle(Vector3::UnitX(), pitchAngle);
		Matrix4 roll = Matrix4::CreateFromAxisAngle(Vector3::UnitZ(), rollAngle);

		const Matrix4 expected = roll * pitch * yaw;
		const Matrix4 actual = Matrix4::CreateFromYawPitchRoll(yawAngle, pitchAngle, rollAngle);
		EXPECT_EQ(expected, actual);
	}

	// Covers more numeric rigions

	void Matrix4CreateFromYawPitchRollTest2()
	{
		const float step = 35.0f;

		for (float yawAngle = -720.0f; yawAngle <= 720.0f; yawAngle += step)
		{
			for (float pitchAngle = -720.0f; pitchAngle <= 720.0f; pitchAngle += step)
			{
				for (float rollAngle = -720.0f; rollAngle <= 720.0f; rollAngle += step)
				{
					float yawRad = ToRadian(yawAngle);
					float pitchRad = ToRadian(pitchAngle);
					float rollRad = ToRadian(rollAngle);
					Matrix4 yaw = Matrix4::CreateFromAxisAngle(Vector3::UnitY(), yawRad);
					Matrix4 pitch = Matrix4::CreateFromAxisAngle(Vector3::UnitX(), pitchRad);
					Matrix4 roll = Matrix4::CreateFromAxisAngle(Vector3::UnitZ(), rollRad);

					Matrix4 expected = roll * pitch * yaw;
					Matrix4 actual = Matrix4::CreateFromYawPitchRoll(yawRad, pitchRad, rollRad);
					EXPECT_EQ(expected, actual);
				}
			}
		}
	}

	// Simple shadow test.
	void Matrix4CreateShadowTest01()
	{
		Vector3 lightDir = Vector3::UnitY();
		Plane plane(Vector3::UnitY(), 0);

		Matrix4 expected = Matrix4::CreateScale(1, 0, 1);

		Matrix4 actual = Matrix4::CreateShadow(lightDir, plane);
		EXPECT_EQ(expected, actual);
	}

	// Various plane projections.
	
	void Matrix4CreateShadowTest02()
	{
		// Complex cases.
		Plane planes[] = {
			Plane(0, 1, 0, 0),
			Plane(1, 2, 3, 4),
			Plane(5, 6, 7, 8),
			Plane(-1,-2,-3,-4),
			Plane(-5,-6,-7,-8),
		};

		Vector3 points[] = {
			Vector3(1, 2, 3),
			Vector3(5, 6, 7),
			Vector3(8, 9, 10),
			Vector3(-1,-2,-3),
			Vector3(-5,-6,-7),
			Vector3(-8,-9,-10),
		};

		for (const Plane& p : planes)
		{
			Plane plane = Plane::Normalize(p);

			// Try various direction of light directions.
			Vector3 testDirections[] =
			{
				Vector3(-1.0f, 1.0f, 1.0f),
				Vector3(0.0f, 1.0f, 1.0f),
				Vector3(1.0f, 1.0f, 1.0f),
				Vector3(-1.0f, 0.0f, 1.0f),
				Vector3(0.0f, 0.0f, 1.0f),
				Vector3(1.0f, 0.0f, 1.0f),
				Vector3(-1.0f,-1.0f, 1.0f),
				Vector3(0.0f,-1.0f, 1.0f),
				Vector3(1.0f,-1.0f, 1.0f),

				Vector3(-1.0f, 1.0f, 0.0f),
				Vector3(0.0f, 1.0f, 0.0f),
				Vector3(1.0f, 1.0f, 0.0f),
				Vector3(-1.0f, 0.0f, 0.0f),
				Vector3(0.0f, 0.0f, 0.0f),
				Vector3(1.0f, 0.0f, 0.0f),
				Vector3(-1.0f,-1.0f, 0.0f),
				Vector3(0.0f,-1.0f, 0.0f),
				Vector3(1.0f,-1.0f, 0.0f),

				Vector3(-1.0f, 1.0f,-1.0f),
				Vector3(0.0f, 1.0f,-1.0f),
				Vector3(1.0f, 1.0f,-1.0f),
				Vector3(-1.0f, 0.0f,-1.0f),
				Vector3(0.0f, 0.0f,-1.0f),
				Vector3(1.0f, 0.0f,-1.0f),
				Vector3(-1.0f,-1.0f,-1.0f),
				Vector3(0.0f,-1.0f,-1.0f),
				Vector3(1.0f,-1.0f,-1.0f),
			};

			for (Vector3& lightDirInfo : testDirections)
			{
				if (lightDirInfo.Length() < 0.1f)
					continue;
				Vector3 lightDir = Vector3::Normalize(lightDirInfo);

				if (Plane::DotNormal(plane, lightDir) < 0.1f)
					continue;

				Matrix4 m = Matrix4::CreateShadow(lightDir, plane);
				Vector3 pp = -plane.d * plane.n; // origin of the Plane::

				for (Vector3& point : points)
				{
					auto transform = m.Transform(point);
					Vector4 v4(transform.x, transform.y, transform.z);

					Vector3 sp = Vector3(v4.x, v4.y, v4.z) / v4.w;

					// Make sure transformed position is on the Plane::
					Vector3 v = sp - pp;
					float d = Vector3::Dot(v, plane.n);
					EXPECT_EQ(d, 0);

					// make sure direction between transformed position and original position are same as light direction.
					if (Vector3::Dot(point - pp, plane.n) > 0.0001f)
					{
						Vector3 dir = Vector3::Normalize(point - sp);
						EXPECT_EQ(dir, lightDir);
					}
				}
			}
		}
	}
	
	void CreateReflectionTest(Plane plane, Matrix4 expected)
	{
		Matrix4 actual = Matrix4::CreateReflection(plane);
		EXPECT_EQ(actual, expected);
	}


	void Matrix4CreateReflectionTest01()
	{
		// XY Plane::
		CreateReflectionTest(Plane(Vector3::UnitZ(), 0), Matrix4::CreateScale(1, 1, -1));
		// XZ Plane::
		CreateReflectionTest(Plane(Vector3::UnitY(), 0), Matrix4::CreateScale(1, -1, 1));
		// YZ Plane::
		CreateReflectionTest(Plane(Vector3::UnitX(), 0), Matrix4::CreateScale(-1, 1, 1));

		// Complex cases.
		Plane planes[] = {
			Plane(0, 1, 0, 0),
			Plane(1, 2, 3, 4),
			Plane(5, 6, 7, 8),
			Plane(-1,-2,-3,-4),
			Plane(-5,-6,-7,-8),
		};

		Vector3 points[] = {
			Vector3(1, 2, 3),
			Vector3(5, 6, 7),
			Vector3(-1,-2,-3),
			Vector3(-5,-6,-7),
		};

		for (auto& p : planes)
		{
			Plane plane = Plane::Normalize(p);
			Matrix4 m = Matrix4::CreateReflection(plane);
			Vector3 pp = -plane.d * plane.n; // Position on the Plane::
			
			for (auto& point : points)
			{
				Vector3 rp = m.Transform(point);

				// Manually compute reflection point and compare results.
				Vector3 v = point - pp;
				float d = Vector3::Dot(v, plane.n);
				Vector3 vp = point - 2.0f * d * plane.n;
				EXPECT_EQ(rp, vp);
			}
		}
	}
	
	// A test for CreateRotationZ (float)

	TEST(Matrix4, CreateRotationZ)
	{
		const float radians = ToRadian(50.0f);

		Matrix4 expected;
		expected.m11 = 0.642787635f;
		expected.m12 = 0.766044438f;
		expected.m21 = -0.766044438f;
		expected.m22 = 0.642787635f;
		expected.m33 = 1.0f;
		expected.m44 = 1.0f;

		const Matrix4 actual = Matrix4::CreateRotationZ(radians);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateRotationZ (float, Vector3f)

	TEST(Matrix4, CreateRotationZCenter)
	{
		const float radians = ToRadian(30.0f);
		const Vector3 center = Vector3(23, 42, 66);

		const Matrix4 rotateAroundZero = Matrix4::CreateRotationZ(radians, Vector3::Zero());
		const Matrix4 rotateAroundZeroExpected = Matrix4::CreateRotationZ(radians);
		EXPECT_EQ(rotateAroundZero, rotateAroundZeroExpected);

		const Matrix4 rotateAroundCenter = Matrix4::CreateRotationZ(radians, center);
		const Matrix4 rotateAroundCenterExpected = Matrix4::CreateTranslation(-center) * Matrix4::CreateRotationZ(radians) * Matrix4::CreateTranslation(center);
		EXPECT_EQ(rotateAroundCenter, rotateAroundCenterExpected);
	}

	// A test for CrateLookAt (Vector3f, Vector3f, Vector3f)

	TEST(Matrix4, CreateLookAt)
	{
		const Vector3 cameraPosition(10.0f, 20.0f, 30.0f);
		const Vector3 cameraTarget(3.0f, 2.0f, -4.0f);
		const Vector3 cameraUpVector(0.0f, 1.0f, 0.0f);

		Matrix4 expected;
		expected.m11 = 0.979457f;
		expected.m12 = -0.0928267762f;
		expected.m13 = 0.179017f;

		expected.m21 = 0.0f;
		expected.m22 = 0.8877481f;
		expected.m23 = 0.460329473f;

		expected.m31 = -0.201652914f;
		expected.m32 = -0.450872928f;
		expected.m33 = 0.8695112f;

		expected.m41 = -3.74498272f;
		expected.m42 = -3.30050683f;
		expected.m43 = -37.0820961f;
		expected.m44 = 1.0f;

		const Matrix4 actual = Matrix4::CreateLookAt(cameraPosition, cameraTarget, cameraUpVector);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateWorld (Vector3f, Vector3f, Vector3f)

	TEST(Matrix4, CreateWorld)
	{
		const Vector3 objectPosition(10.0f, 20.0f, 30.0f);
		Vector3 objectForwardDirection(3.0f, 2.0f, -4.0f);
		Vector3 objectUpVector(0.0f, 1.0f, 0.0f);

		Matrix4 expected;
		expected.m11 = 0.799999952f;
		expected.m12 = 0;
		expected.m13 = 0.599999964f;
		expected.m14 = 0;

		expected.m21 = -0.2228344f;
		expected.m22 = 0.928476632f;
		expected.m23 = 0.297112525f;
		expected.m24 = 0;

		expected.m31 = -0.557086f;
		expected.m32 = -0.371390671f;
		expected.m33 = 0.742781341f;
		expected.m34 = 0;

		expected.m41 = 10;
		expected.m42 = 20;
		expected.m43 = 30;
		expected.m44 = 1.0f;

		Matrix4 actual = Matrix4::CreateWorld(objectPosition, objectForwardDirection, objectUpVector);
		EXPECT_EQ(expected, actual);
		EXPECT_EQ(objectPosition, actual.Translation());
		EXPECT_TRUE(Vector3::Dot(Vector3::Normalize(objectUpVector), Vector3(actual.m21, actual.m22, actual.m23)) > 0);
		EXPECT_TRUE(Vector3::Dot(Vector3::Normalize(objectForwardDirection), Vector3(-actual.m31, -actual.m32, -actual.m33)) > 0.999f);
	}

	// A test for CreateOrtho (float, float, float, float)

	TEST(Matrix4, CreateOrtho)
	{
		const float width = 100.0f;
		const float height = 200.0f;
		const float zNearPlane = 1.5f;
		const float zFarPlane = 1000.0f;

		Matrix4 expected(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		expected.m11 = 0.02f;
		expected.m22 = 0.01f;
		expected.m33 = -0.00100150227f;
		expected.m43 = -0.00150225335f;
		expected.m44 = 1.0f;

		const Matrix4 actual = Matrix4::CreateOrthographic(width, height, zNearPlane, zFarPlane);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateOrthoOffCenter (float, float, float, float, float, float)

	TEST(Matrix4, CreateOrthoOffCenter)
	{
		const float left = 10.0f;
		const float right = 90.0f;
		const float bottom = 20.0f;
		const float top = 180.0f;
		const float zNearPlane = 1.5f;
		const float zFarPlane = 1000.0f;

		Matrix4 expected(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		expected.m11 = 0.025f;
		expected.m22 = 0.0125f;
		expected.m33 = -0.00100150227f;
		expected.m41 = -1.25f;
		expected.m42 = -1.25f;
		expected.m43 = -0.00150225335f;
		expected.m44 = 1.0f;

		Matrix4 actual;
		actual = Matrix4::CreateOrthographicOffCenter(left, right, bottom, top, zNearPlane, zFarPlane);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreatePerspective (float, float, float, float)

	TEST(Matrix4, CreatePerspective)
	{
		const float width = 100.0f;
		const float height = 200.0f;
		const float zNearPlane = 1.5f;
		const float zFarPlane = 1000.0f;

		Matrix4 expected(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		expected.m11 = 0.03f;
		expected.m22 = 0.015f;
		expected.m33 = -1.00150228f;
		expected.m34 = -1.0f;
		expected.m43 = -1.50225341f;

		Matrix4 actual;
		actual = Matrix4::CreatePerspective(width, height, zNearPlane, zFarPlane);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreatePerspectiveFieldOfView (float, float, float, float)

	TEST(Matrix4, CreatePerspectiveFieldOfView)
	{
		const float fieldOfView = ToRadian(30.0f);
		const float aspectRatio = 1280.0f / 720.0f;
		const float zNearPlane = 1.5f;
		const float zFarPlane = 1000.0f;

		Matrix4 expected(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		expected.m11 = 2.09927845f;
		expected.m22 = 3.73205066f;
		expected.m33 = -1.00150228f;
		expected.m34 = -1.0f;
		expected.m43 = -1.50225341f;
		Matrix4 actual = Matrix4::CreatePerspectiveFieldOfView(fieldOfView, aspectRatio, zNearPlane, zFarPlane);

		EXPECT_EQ(expected, actual);
	}

	// A test for CreatePerspectiveOffCenter (float, float, float, float, float, float)

	TEST(Matrix4, CreatePerspectiveOffCenter)
	{
		const float left = 10.0f;
		const float right = 90.0f;
		const float bottom = 20.0f;
		const float top = 180.0f;
		const float zNearPlane = 1.5f;
		const float zFarPlane = 1000.0f;

		Matrix4 expected(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		expected.m11 = 0.0375f;
		expected.m22 = 0.01875f;
		expected.m31 = 1.25f;
		expected.m32 = 1.25f;
		expected.m33 = -1.00150228f;
		expected.m34 = -1.0f;
		expected.m43 = -1.50225341f;

		const Matrix4 actual = Matrix4::CreatePerspectiveOffCenter(left, right, bottom, top, zNearPlane, zFarPlane);
		EXPECT_EQ(expected, actual);
	}
	
	// A test for Invert (Matrix4)
	// Non invertible matrix - determinant is zero - singular matrix

	void Matrix4InvertTest1()
	{
		Matrix4 a;
		a.m11 = 1.0f;
		a.m12 = 2.0f;
		a.m13 = 3.0f;
		a.m14 = 4.0f;
		a.m21 = 5.0f;
		a.m22 = 6.0f;
		a.m23 = 7.0f;
		a.m24 = 8.0f;
		a.m31 = 9.0f;
		a.m32 = 10.0f;
		a.m33 = 11.0f;
		a.m34 = 12.0f;
		a.m41 = 13.0f;
		a.m42 = 14.0f;
		a.m43 = 15.0f;
		a.m44 = 16.0f;

		const float detA = a.Determinant();
		EXPECT_EQ(detA, 0.0f);

		const Matrix4 actual = Matrix4::Invert(a);

		// all the elements in Actual is NaN
		EXPECT_TRUE(
			IsNaN(actual.m11) && IsNaN(actual.m12) && IsNaN(actual.m13) && IsNaN(actual.m14) &&
			IsNaN(actual.m21) && IsNaN(actual.m22) && IsNaN(actual.m23) && IsNaN(actual.m24) &&
			IsNaN(actual.m31) && IsNaN(actual.m32) && IsNaN(actual.m33) && IsNaN(actual.m34) &&
			IsNaN(actual.m41) && IsNaN(actual.m42) && IsNaN(actual.m43) && IsNaN(actual.m44));
	}

	// A test for Lerp (Matrix4, Matrix4, float)

	TEST(Matrix4, Lerp)
	{
		Matrix4 a;
		a.m11 = 11.0f;
		a.m12 = 12.0f;
		a.m13 = 13.0f;
		a.m14 = 14.0f;
		a.m21 = 21.0f;
		a.m22 = 22.0f;
		a.m23 = 23.0f;
		a.m24 = 24.0f;
		a.m31 = 31.0f;
		a.m32 = 32.0f;
		a.m33 = 33.0f;
		a.m34 = 34.0f;
		a.m41 = 41.0f;
		a.m42 = 42.0f;
		a.m43 = 43.0f;
		a.m44 = 44.0f;

		Matrix4 b = GenerateIncrementalMatrixNumber();

		float t = 0.5f;

		Matrix4 expected;
		expected.m11 = a.m11 + (b.m11 - a.m11) * t;
		expected.m12 = a.m12 + (b.m12 - a.m12) * t;
		expected.m13 = a.m13 + (b.m13 - a.m13) * t;
		expected.m14 = a.m14 + (b.m14 - a.m14) * t;

		expected.m21 = a.m21 + (b.m21 - a.m21) * t;
		expected.m22 = a.m22 + (b.m22 - a.m22) * t;
		expected.m23 = a.m23 + (b.m23 - a.m23) * t;
		expected.m24 = a.m24 + (b.m24 - a.m24) * t;

		expected.m31 = a.m31 + (b.m31 - a.m31) * t;
		expected.m32 = a.m32 + (b.m32 - a.m32) * t;
		expected.m33 = a.m33 + (b.m33 - a.m33) * t;
		expected.m34 = a.m34 + (b.m34 - a.m34) * t;

		expected.m41 = a.m41 + (b.m41 - a.m41) * t;
		expected.m42 = a.m42 + (b.m42 - a.m42) * t;
		expected.m43 = a.m43 + (b.m43 - a.m43) * t;
		expected.m44 = a.m44 + (b.m44 - a.m44) * t;

		Matrix4 actual;
		actual = Matrix4::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for operator - (Matrix4)

	TEST(Matrix4, UnaryNegation)
	{
		Matrix4 a = GenerateIncrementalMatrixNumber();

		Matrix4 expected;
		expected.m11 = -1.0f;
		expected.m12 = -2.0f;
		expected.m13 = -3.0f;
		expected.m14 = -4.0f;
		expected.m21 = -5.0f;
		expected.m22 = -6.0f;
		expected.m23 = -7.0f;
		expected.m24 = -8.0f;
		expected.m31 = -9.0f;
		expected.m32 = -10.0f;
		expected.m33 = -11.0f;
		expected.m34 = -12.0f;
		expected.m41 = -13.0f;
		expected.m42 = -14.0f;
		expected.m43 = -15.0f;
		expected.m44 = -16.0f;

		const Matrix4 actual = -a;
		EXPECT_EQ(expected, actual);
	}

	// A test for operator - (Matrix4, Matrix4)

	TEST(Matrix4, Subtraction2)
	{
		Matrix4 a = GenerateIncrementalMatrixNumber();
		const Matrix4 b = GenerateIncrementalMatrixNumber(-8.0f);

		Matrix4 expected;
		expected.m11 = a.m11 - b.m11;
		expected.m12 = a.m12 - b.m12;
		expected.m13 = a.m13 - b.m13;
		expected.m14 = a.m14 - b.m14;
		expected.m21 = a.m21 - b.m21;
		expected.m22 = a.m22 - b.m22;
		expected.m23 = a.m23 - b.m23;
		expected.m24 = a.m24 - b.m24;
		expected.m31 = a.m31 - b.m31;
		expected.m32 = a.m32 - b.m32;
		expected.m33 = a.m33 - b.m33;
		expected.m34 = a.m34 - b.m34;
		expected.m41 = a.m41 - b.m41;
		expected.m42 = a.m42 - b.m42;
		expected.m43 = a.m43 - b.m43;
		expected.m44 = a.m44 - b.m44;

		const Matrix4 actual = a - b;
		EXPECT_EQ(expected, actual);
	}

	// A test for operator * (Matrix4, Matrix4)
	TEST(Matrix4, Multiply1)
	{
		Matrix4 a = GenerateIncrementalMatrixNumber();
		const Matrix4 b = GenerateIncrementalMatrixNumber(-8.0f);

		Matrix4 expected;
		expected.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31 + a.m14 * b.m41;
		expected.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32 + a.m14 * b.m42;
		expected.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33 + a.m14 * b.m43;
		expected.m14 = a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34 + a.m14 * b.m44;

		expected.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31 + a.m24 * b.m41;
		expected.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32 + a.m24 * b.m42;
		expected.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33 + a.m24 * b.m43;
		expected.m24 = a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34 + a.m24 * b.m44;

		expected.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31 + a.m34 * b.m41;
		expected.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32 + a.m34 * b.m42;
		expected.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33 + a.m34 * b.m43;
		expected.m34 = a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34 + a.m34 * b.m44;

		expected.m41 = a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + a.m44 * b.m41;
		expected.m42 = a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + a.m44 * b.m42;
		expected.m43 = a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + a.m44 * b.m43;
		expected.m44 = a.m41 * b.m14 + a.m42 * b.m24 + a.m43 * b.m34 + a.m44 * b.m44;

		const Matrix4 actual = a * b;
		EXPECT_EQ(expected, actual);
	}

	// A test for operator * (Matrix4, Matrix4)
	// Multiply with identity matrix

	TEST(Matrix4, Multiply4)
	{
		Matrix4 a;
		a.m11 = 1.0f;
		a.m12 = 2.0f;
		a.m13 = 3.0f;
		a.m14 = 4.0f;
		a.m21 = 5.0f;
		a.m22 = -6.0f;
		a.m23 = 7.0f;
		a.m24 = -8.0f;
		a.m31 = 9.0f;
		a.m32 = 10.0f;
		a.m33 = 11.0f;
		a.m34 = 12.0f;
		a.m41 = 13.0f;
		a.m42 = -14.0f;
		a.m43 = 15.0f;
		a.m44 = -16.0f;

		const Matrix4 b = Matrix4::CreateIdentity();

		const Matrix4 expected = a;
		const Matrix4 actual = a * b;

		EXPECT_EQ(expected, actual);
	}

	// A test for operator + (Matrix4, Matrix4)

	TEST(Matrix4, Addition)
	{
		Matrix4 a = GenerateIncrementalMatrixNumber();
		const Matrix4 b = GenerateIncrementalMatrixNumber(-8.0f);

		Matrix4 expected;
		expected.m11 = a.m11 + b.m11;
		expected.m12 = a.m12 + b.m12;
		expected.m13 = a.m13 + b.m13;
		expected.m14 = a.m14 + b.m14;
		expected.m21 = a.m21 + b.m21;
		expected.m22 = a.m22 + b.m22;
		expected.m23 = a.m23 + b.m23;
		expected.m24 = a.m24 + b.m24;
		expected.m31 = a.m31 + b.m31;
		expected.m32 = a.m32 + b.m32;
		expected.m33 = a.m33 + b.m33;
		expected.m34 = a.m34 + b.m34;
		expected.m41 = a.m41 + b.m41;
		expected.m42 = a.m42 + b.m42;
		expected.m43 = a.m43 + b.m43;
		expected.m44 = a.m44 + b.m44;

		const Matrix4 actual = a + b;
		EXPECT_EQ(expected, actual);
	}

	// A test for Transpose (Matrix4)

	TEST(Matrix4, Transpose)
	{
		const Matrix4 a = GenerateIncrementalMatrixNumber();

		Matrix4 expected;
		expected.m11 = a.m11;
		expected.m12 = a.m21;
		expected.m13 = a.m31;
		expected.m14 = a.m41;
		expected.m21 = a.m12;
		expected.m22 = a.m22;
		expected.m23 = a.m32;
		expected.m24 = a.m42;
		expected.m31 = a.m13;
		expected.m32 = a.m23;
		expected.m33 = a.m33;
		expected.m34 = a.m43;
		expected.m41 = a.m14;
		expected.m42 = a.m24;
		expected.m43 = a.m34;
		expected.m44 = a.m44;

		const Matrix4 actual = Matrix4::Transpose(a);
		EXPECT_EQ(expected, actual);
	}

	// A test for Transpose (Matrix4)
	// Transpose Identity matrix
	TEST(Matrix4, Transpose1)
	{
		const Matrix4 a = Matrix4::CreateIdentity();
		const Matrix4 expected = Matrix4::CreateIdentity();

		const Matrix4 actual = Matrix4::Transpose(a);
		EXPECT_EQ(expected, actual);
	}

	// A test for Matrix4 (Quaternion)
	TEST(Matrix4, Quaternion1)
	{
		const Vector3 axis = Vector3::Normalize(Vector3(1.0f, 2.0f, 3.0f));
		const Quaternion q = Quaternion::CreateFromAxisAngle(axis, ToRadian(30.0f));

		Matrix4 expected;
		expected.m11 = 0.875595033f;
		expected.m12 = 0.420031041f;
		expected.m13 = -0.2385524f;
		expected.m14 = 0.0f;

		expected.m21 = -0.38175258f;
		expected.m22 = 0.904303849f;
		expected.m23 = 0.1910483f;
		expected.m24 = 0.0f;

		expected.m31 = 0.295970082f;
		expected.m32 = -0.07621294f;
		expected.m33 = 0.952151954f;
		expected.m34 = 0.0f;

		expected.m41 = 0.0f;
		expected.m42 = 0.0f;
		expected.m43 = 0.0f;
		expected.m44 = 1.0f;

		const Matrix4 target = Matrix4::CreateFromQuaternion(q);
		EXPECT_EQ(expected, target);
	}

	// A test for FromQuaternion (Matrix4)
	// Convert X axis rotation matrix
	TEST(Matrix4, Quaternion2)
	{
		for (int angle = 0; angle < 720; angle += 10)
		{
			Quaternion quat = Quaternion::CreateFromAxisAngle(Vector3::UnitX(), angle);

			Matrix4 expected = Matrix4::CreateRotationX(angle);
			Matrix4 actual = Matrix4::CreateFromQuaternion(quat);
			EXPECT_EQ(expected, actual);

			// make sure convert back to quaternion is same as we passed Quaternion::
			Quaternion q2 = Quaternion::CreateFromRotationMatrix(actual);
			EXPECT_EQ(quat, q2);
		}
	}

	// A test for FromQuaternion (Matrix4)
	// Convert Y axis rotation matrix
	TEST(Matrix4, Quaternion3)
	{
		for (int angle = 0; angle < 720; angle += 10)
		{
			Quaternion quat = Quaternion::CreateFromAxisAngle(Vector3::UnitY(), angle);

			Matrix4 expected = Matrix4::CreateRotationY(angle);
			Matrix4 actual = Matrix4::CreateFromQuaternion(quat);
			EXPECT_EQ(expected, actual);

			// make sure convert back to quaternion is same as we passed Quaternion::
			Quaternion q2 = Quaternion::CreateFromRotationMatrix(actual);
			EXPECT_EQ(quat, q2);
		}
	}

	// A test for FromQuaternion (Matrix4)
	// Convert Z axis rotation matrix
	TEST(Matrix4, Quaternion4)
	{
		for (int angle = 0; angle < 720; angle += 10)
		{
			Quaternion quat = Quaternion::CreateFromAxisAngle(Vector3::UnitZ(), angle);

			Matrix4 expected = Matrix4::CreateRotationZ(angle);
			Matrix4 actual = Matrix4::CreateFromQuaternion(quat);
			EXPECT_EQ(expected, actual);

				// make sure convert back to quaternion is same as we passed Quaternion::
				Quaternion q2 = Quaternion::CreateFromRotationMatrix(actual);
				EXPECT_EQ(quat, q2);
		}
	}

	// A test for FromQuaternion (Matrix4)
	// Convert XYZ axis rotation matrix
	TEST(Matrix4, Quaternion5)
	{
		for (int angle = 0; angle < 720; angle += 10)
		{
			Quaternion quat =
				Quaternion::CreateFromAxisAngle(Vector3::UnitZ(), angle) *
				Quaternion::CreateFromAxisAngle(Vector3::UnitY(), angle) *
				Quaternion::CreateFromAxisAngle(Vector3::UnitX(), angle);

			Matrix4 expected =
				Matrix4::CreateRotationX(angle) *
				Matrix4::CreateRotationY(angle) *
				Matrix4::CreateRotationZ(angle);
			Matrix4 actual = Matrix4::CreateFromQuaternion(quat);
			EXPECT_EQ(expected, actual);

				// make sure convert back to quaternion is same as we passed Quaternion::
				Quaternion q2 = Quaternion::CreateFromRotationMatrix(actual);
				EXPECT_EQ(quat, q2);
		}
	}

	// A test for Add (Matrix4, Matrix4)

	TEST(Matrix4, Add2)
	{
		const Matrix4 a = GenerateIncrementalMatrixNumber();
		const Matrix4 b = GenerateIncrementalMatrixNumber(-8.0f);

		Matrix4 expected;
		expected.m11 = a.m11 + b.m11;
		expected.m12 = a.m12 + b.m12;
		expected.m13 = a.m13 + b.m13;
		expected.m14 = a.m14 + b.m14;
		expected.m21 = a.m21 + b.m21;
		expected.m22 = a.m22 + b.m22;
		expected.m23 = a.m23 + b.m23;
		expected.m24 = a.m24 + b.m24;
		expected.m31 = a.m31 + b.m31;
		expected.m32 = a.m32 + b.m32;
		expected.m33 = a.m33 + b.m33;
		expected.m34 = a.m34 + b.m34;
		expected.m41 = a.m41 + b.m41;
		expected.m42 = a.m42 + b.m42;
		expected.m43 = a.m43 + b.m43;
		expected.m44 = a.m44 + b.m44;

		const Matrix4 actual = Matrix4::Add(a, b);
		EXPECT_EQ(expected, actual);
	}
	
	// A test for Multiply (Matrix4, Matrix4)

	void Matrix4MultiplyTest3()
	{
		Matrix4 a = GenerateIncrementalMatrixNumber();
		Matrix4 b = GenerateIncrementalMatrixNumber(-8.0f);

		Matrix4 expected;
		expected.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31 + a.m14 * b.m41;
		expected.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32 + a.m14 * b.m42;
		expected.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33 + a.m14 * b.m43;
		expected.m14 = a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34 + a.m14 * b.m44;

		expected.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31 + a.m24 * b.m41;
		expected.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32 + a.m24 * b.m42;
		expected.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33 + a.m24 * b.m43;
		expected.m24 = a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34 + a.m24 * b.m44;

		expected.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31 + a.m34 * b.m41;
		expected.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32 + a.m34 * b.m42;
		expected.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33 + a.m34 * b.m43;
		expected.m34 = a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34 + a.m34 * b.m44;

		expected.m41 = a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + a.m44 * b.m41;
		expected.m42 = a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + a.m44 * b.m42;
		expected.m43 = a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + a.m44 * b.m43;
		expected.m44 = a.m41 * b.m14 + a.m42 * b.m24 + a.m43 * b.m34 + a.m44 * b.m44;
		Matrix4 actual;
		actual = Matrix4::Multiply(a, b);

		EXPECT_EQ(expected, actual);
	}

	// A test for Multiply (Matrix4, float)

	void Matrix4MultiplyTest5()
	{
		const Matrix4 a = GenerateIncrementalMatrixNumber();
		const Matrix4 expected(3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48);
		const Matrix4 actual = Matrix4::Multiply(a, 3);

		EXPECT_EQ(expected, actual);
	}

	// A test for Multiply (Matrix4, float)

	void Matrix4MultiplyTest6()
	{
		Matrix4 a = GenerateIncrementalMatrixNumber();
		const Matrix4 expected(3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48);
		const Matrix4 actual = a * 3;

		EXPECT_EQ(expected, actual);
	}

	// A test for Negate (Matrix4)

	TEST(Matrix4, Negate)
	{
		const Matrix4 m = GenerateIncrementalMatrixNumber();

		Matrix4 expected;
		expected.m11 = -1.0f;
		expected.m12 = -2.0f;
		expected.m13 = -3.0f;
		expected.m14 = -4.0f;
		expected.m21 = -5.0f;
		expected.m22 = -6.0f;
		expected.m23 = -7.0f;
		expected.m24 = -8.0f;
		expected.m31 = -9.0f;
		expected.m32 = -10.0f;
		expected.m33 = -11.0f;
		expected.m34 = -12.0f;
		expected.m41 = -13.0f;
		expected.m42 = -14.0f;
		expected.m43 = -15.0f;
		expected.m44 = -16.0f;
		Matrix4 actual;

		actual = Matrix4::Negate(m);
		EXPECT_EQ(expected, actual);
	}

	// A test for operator != (Matrix4, Matrix4)

	TEST(Matrix4, Inequality)
	{
		const Matrix4 a = GenerateIncrementalMatrixNumber();
		Matrix4 b = GenerateIncrementalMatrixNumber();

		// case 1: compare between same values
		bool expected = false;
		bool actual = a != b;
		EXPECT_EQ(expected, actual);
		// case 2: compare between different values
		b.m11 = 11.0f;
		expected = true;
		actual = a != b;
		EXPECT_EQ(expected, actual);
	}

	// A test for operator == (Matrix4, Matrix4)

	TEST(Matrix4, Equality)
	{
		const Matrix4 a = GenerateIncrementalMatrixNumber();
		Matrix4 b = GenerateIncrementalMatrixNumber();

		// case 1: compare between same values
		bool expected = true;
		bool actual = a == b;
		EXPECT_EQ(expected, actual);
		// case 2: compare between different values
		b.m11 = 11.0f;
		expected = false;
		actual = a == b;
		EXPECT_EQ(expected, actual);
	}

	// A test for Subtract (Matrix4, Matrix4)

	TEST(Matrix4, Subtract)
	{
		const Matrix4 a = GenerateIncrementalMatrixNumber();
		const Matrix4 b = GenerateIncrementalMatrixNumber(-8.0f);

		Matrix4 expected;
		expected.m11 = a.m11 - b.m11;
		expected.m12 = a.m12 - b.m12;
		expected.m13 = a.m13 - b.m13;
		expected.m14 = a.m14 - b.m14;
		expected.m21 = a.m21 - b.m21;
		expected.m22 = a.m22 - b.m22;
		expected.m23 = a.m23 - b.m23;
		expected.m24 = a.m24 - b.m24;
		expected.m31 = a.m31 - b.m31;
		expected.m32 = a.m32 - b.m32;
		expected.m33 = a.m33 - b.m33;
		expected.m34 = a.m34 - b.m34;
		expected.m41 = a.m41 - b.m41;
		expected.m42 = a.m42 - b.m42;
		expected.m43 = a.m43 - b.m43;
		expected.m44 = a.m44 - b.m44;

		const Matrix4 actual = Matrix4::Subtract(a, b);
		EXPECT_EQ(expected, actual);
	}

	void CreateBillboardFact(Vector3 placeDirection, Vector3 cameraUpVector, Matrix4 expectedRotation)
	{
		const Vector3 cameraPosition = Vector3(3.0f, 4.0f, 5.0f);
		const Vector3 objectPosition = cameraPosition + placeDirection * 10.0f;
		const Matrix4 expected = expectedRotation * Matrix4::CreateTranslation(objectPosition);
		auto camera_forward_vector = Vector3(0, 0, -1);
		const Matrix4 actual = Matrix4::CreateBillboard(objectPosition, cameraPosition, cameraUpVector, &camera_forward_vector);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Forward side of camera on XZ-plane
	TEST(Matrix4, CreateBillboardTest01)
	{
		// Object placed at Forward of camera. result must be same as 180 degrees rotate along y-axis.
		CreateBillboardFact(Vector3(0, 0, -1), Vector3(0, 1, 0), Matrix4::CreateRotationY(ToRadian(180.0f)));
	}

	// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Backward side of camera on XZ-plane

	TEST(Matrix4, CreateBillboardTest02)
	{
		// Object placed at Backward of camera. This result must be same as 0 degrees rotate along y-axis.
		CreateBillboardFact(Vector3(0, 0, 1), Vector3(0, 1, 0), Matrix4::CreateRotationY(ToRadian(0)));
	}

	// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Right side of camera on XZ-plane

	TEST(Matrix4, CreateBillboardTest03)
	{
		// Place object at Right side of camera. This result must be same as 90 degrees rotate along y-axis.
		CreateBillboardFact(Vector3(1, 0, 0), Vector3(0, 1, 0), Matrix4::CreateRotationY(ToRadian(90)));
	}

	// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Left side of camera on XZ-plane

	TEST(Matrix4, CreateBillboardTest04)
	{
		// Place object at Left side of camera. This result must be same as -90 degrees rotate along y-axis.
		CreateBillboardFact(Vector3(-1, 0, 0), Vector3(0, 1, 0), Matrix4::CreateRotationY(ToRadian(-90)));
	}

	// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Up side of camera on XY-plane

	TEST(Matrix4, CreateBillboardTest05)
	{
		// Place object at Up side of camera. result must be same as 180 degrees rotate along z-axis after 90 degrees rotate along x-axis.
		CreateBillboardFact(Vector3(0, 1, 0), Vector3(0, 0, 1),
			Matrix4::CreateRotationX(ToRadian(90.0f)) * Matrix4::CreateRotationZ(ToRadian(180)));
	}

	// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Down side of camera on XY-plane

	TEST(Matrix4, CreateBillboardTest06)
	{
		// Place object at Down side of camera. result must be same as 0 degrees rotate along z-axis after 90 degrees rotate along x-axis.
		CreateBillboardFact(Vector3(0, -1, 0), Vector3(0, 0, 1),
			Matrix4::CreateRotationX(ToRadian(90.0f)) * Matrix4::CreateRotationZ(ToRadian(0)));
	}

	// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Right side of camera on XY-plane

	TEST(Matrix4, CreateBillboardTest07)
	{
		// Place object at Right side of camera. result must be same as 90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
		CreateBillboardFact(Vector3(1, 0, 0), Vector3(0, 0, 1),
			Matrix4::CreateRotationX(ToRadian(90.0f)) * Matrix4::CreateRotationZ(ToRadian(90.0f)));
	}

	// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Left side of camera on XY-plane

	TEST(Matrix4, CreateBillboardTest08)
	{
		// Place object at Left side of camera. result must be same as -90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
		CreateBillboardFact(Vector3(-1, 0, 0), Vector3(0, 0, 1),
			Matrix4::CreateRotationX(ToRadian(90.0f)) * Matrix4::CreateRotationZ(ToRadian(-90.0f)));
	}

	// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Up side of camera on YZ-plane

	TEST(Matrix4, CreateBillboardTest09)
	{
		// Place object at Up side of camera. result must be same as -90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
		CreateBillboardFact(Vector3(0, 1, 0), Vector3(-1, 0, 0),
			Matrix4::CreateRotationZ(ToRadian(90.0f)) * Matrix4::CreateRotationX(ToRadian(-90.0f)));
	}

	// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Down side of camera on YZ-plane

	TEST(Matrix4, CreateBillboardTest10)
	{
		// Place object at Down side of camera. result must be same as 90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
		CreateBillboardFact(Vector3(0, -1, 0), Vector3(-1, 0, 0),
			Matrix4::CreateRotationZ(ToRadian(90.0f)) * Matrix4::CreateRotationX(ToRadian(90.0f)));
	}

	// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Forward side of camera on YZ-plane

	TEST(Matrix4, CreateBillboardTest11)
	{
		// Place object at Forward side of camera. result must be same as 180 degrees rotate along x-axis after 90 degrees rotate along z-axis.
		CreateBillboardFact(Vector3(0, 0, -1), Vector3(-1, 0, 0),
			Matrix4::CreateRotationZ(ToRadian(90.0f)) * Matrix4::CreateRotationX(ToRadian(180.0f)));
	}

	// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Backward side of camera on YZ-plane

	TEST(Matrix4, CreateBillboardTest12)
	{
		// Place object at Backward side of camera. result must be same as 0 degrees rotate along x-axis after 90 degrees rotate along z-axis.
		CreateBillboardFact(Vector3(0, 0, 1), Vector3(-1, 0, 0),
			Matrix4::CreateRotationZ(ToRadian(90.0f)) * Matrix4::CreateRotationX(ToRadian(0.0f)));
	}

	// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Object and camera positions are too close and doesn't pass cameraForwardVector.

	TEST(Matrix4, CreateBillboardTooCloseTest1)
	{
		const Vector3 objectPosition = Vector3(3.0f, 4.0f, 5.0f);
		const Vector3 cameraPosition = objectPosition;
		const Vector3 cameraUpVector = Vector3(0, 1, 0);

		// Doesn't pass camera face direction. CreateBillboard uses Vector3Ff(0, 0, -1) direction. Result must be same as 180 degrees rotate along y-axis.
		const Matrix4 expected = Matrix4::CreateRotationY(ToRadian(180.0f)) * Matrix4::CreateTranslation(objectPosition);
		auto camera_forward_vector = Vector3(0, 0, 1);
		const Matrix4 actual = Matrix4::CreateBillboard(objectPosition, cameraPosition, cameraUpVector, &camera_forward_vector);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Object and camera positions are too close and passed cameraForwardVector.

	TEST(Matrix4, CreateBillboardTooCloseTest2)
	{
		const Vector3 objectPosition = Vector3(3.0f, 4.0f, 5.0f);
		const Vector3 cameraPosition = objectPosition;
		const Vector3 cameraUpVector = Vector3(0, 1, 0);

		// Passes Vector3f.Right as camera face direction. Result must be same as -90 degrees rotate along y-axis.
		const Matrix4 expected = Matrix4::CreateRotationY(ToRadian(-90.0f)) * Matrix4::CreateTranslation(objectPosition);
		auto camera_forward_vector = Vector3(1, 0, 0);
		const Matrix4 actual = Matrix4::CreateBillboard(objectPosition, cameraPosition, cameraUpVector, &camera_forward_vector);
		EXPECT_EQ(expected, actual);
	}

	void CreateConstrainedBillboardFact(Vector3 placeDirection, Vector3 rotateAxis, Matrix4 expectedRotation)
	{
		Vector3 cameraPosition = Vector3(3.0f, 4.0f, 5.0f);
		Vector3 objectPosition = cameraPosition + placeDirection * 10.0f;
		Matrix4 expected = expectedRotation * Matrix4::CreateTranslation(objectPosition);
		auto camera_forward_vector = Vector3(0, 0, -1);
		Matrix4 actual = Matrix4::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, &camera_forward_vector, &camera_forward_vector);
		EXPECT_EQ(expected, actual);
		// When you move camera along rotateAxis, result must be same.
		cameraPosition += rotateAxis * 10.0f;
		actual = Matrix4::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, &camera_forward_vector, &camera_forward_vector);
		EXPECT_EQ(expected, actual);
		cameraPosition -= rotateAxis * 30.0f;
		actual = Matrix4::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, &camera_forward_vector, &camera_forward_vector);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Forward side of camera on XZ-plane

	TEST(Matrix4, CreateConstrainedBillboardTest01)
	{
		// Object placed at Forward of camera. result must be same as 180 degrees rotate along y-axis.
		CreateConstrainedBillboardFact(Vector3(0, 0, -1), Vector3(0, 1, 0), Matrix4::CreateRotationY(ToRadian(180.0f)));
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Backward side of camera on XZ-plane

	TEST(Matrix4, CreateConstrainedBillboardTest02)
	{
		// Object placed at Backward of camera. This result must be same as 0 degrees rotate along y-axis.
		CreateConstrainedBillboardFact(Vector3(0, 0, 1), Vector3(0, 1, 0), Matrix4::CreateRotationY(ToRadian(0)));
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Right side of camera on XZ-plane

	TEST(Matrix4, CreateConstrainedBillboardTest03)
	{
		// Place object at Right side of camera. This result must be same as 90 degrees rotate along y-axis.
		CreateConstrainedBillboardFact(Vector3(1, 0, 0), Vector3(0, 1, 0), Matrix4::CreateRotationY(ToRadian(90)));
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Left side of camera on XZ-plane

	TEST(Matrix4, CreateConstrainedBillboardTest04)
	{
		// Place object at Left side of camera. This result must be same as -90 degrees rotate along y-axis.
		CreateConstrainedBillboardFact(Vector3(-1, 0, 0), Vector3(0, 1, 0), Matrix4::CreateRotationY(ToRadian(-90)));
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Up side of camera on XY-plane

	TEST(Matrix4, CreateConstrainedBillboardTest05)
	{
		// Place object at Up side of camera. result must be same as 180 degrees rotate along z-axis after 90 degrees rotate along x-axis.
		CreateConstrainedBillboardFact(Vector3(0, 1, 0), Vector3(0, 0, 1),
			Matrix4::CreateRotationX(ToRadian(90.0f)) * Matrix4::CreateRotationZ(ToRadian(180)));
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Down side of camera on XY-plane

	TEST(Matrix4, CreateConstrainedBillboardTest06)
	{
		// Place object at Down side of camera. result must be same as 0 degrees rotate along z-axis after 90 degrees rotate along x-axis.
		CreateConstrainedBillboardFact(Vector3(0, -1, 0), Vector3(0, 0, 1),
			Matrix4::CreateRotationX(ToRadian(90.0f)) * Matrix4::CreateRotationZ(ToRadian(0)));
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Right side of camera on XY-plane

	TEST(Matrix4, CreateConstrainedBillboardTest07)
	{
		// Place object at Right side of camera. result must be same as 90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
		CreateConstrainedBillboardFact(Vector3(1, 0, 0), Vector3(0, 0, 1),
			Matrix4::CreateRotationX(ToRadian(90.0f)) * Matrix4::CreateRotationZ(ToRadian(90.0f)));
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Left side of camera on XY-plane

	TEST(Matrix4, CreateConstrainedBillboardTest08)
	{
		// Place object at Left side of camera. result must be same as -90 degrees rotate along z-axis after 90 degrees rotate along x-axis.
		CreateConstrainedBillboardFact(Vector3(-1, 0, 0), Vector3(0, 0, 1),
			Matrix4::CreateRotationX(ToRadian(90.0f)) * Matrix4::CreateRotationZ(ToRadian(-90.0f)));
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Up side of camera on YZ-plane

	TEST(Matrix4, CreateConstrainedBillboardTest09)
	{
		// Place object at Up side of camera. result must be same as -90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
		CreateConstrainedBillboardFact(Vector3(0, 1, 0), Vector3(-1, 0, 0),
			Matrix4::CreateRotationZ(ToRadian(90.0f)) * Matrix4::CreateRotationX(ToRadian(-90.0f)));
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Down side of camera on YZ-plane

	TEST(Matrix4, CreateConstrainedBillboardTest10)
	{
		// Place object at Down side of camera. result must be same as 90 degrees rotate along x-axis after 90 degrees rotate along z-axis.
		CreateConstrainedBillboardFact(Vector3(0, -1, 0), Vector3(-1, 0, 0),
			Matrix4::CreateRotationZ(ToRadian(90.0f)) * Matrix4::CreateRotationX(ToRadian(90.0f)));
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Forward side of camera on YZ-plane

	TEST(Matrix4, CreateConstrainedBillboardTest11)
	{
		// Place object at Forward side of camera. result must be same as 180 degrees rotate along x-axis after 90 degrees rotate along z-axis.
		CreateConstrainedBillboardFact(Vector3(0, 0, -1), Vector3(-1, 0, 0),
			Matrix4::CreateRotationZ(ToRadian(90.0f)) * Matrix4::CreateRotationX(ToRadian(180.0f)));
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Place object at Backward side of camera on YZ-plane

	TEST(Matrix4, CreateConstrainedBillboardTest12)
	{
		// Place object at Backward side of camera. result must be same as 0 degrees rotate along x-axis after 90 degrees rotate along z-axis.
		CreateConstrainedBillboardFact(Vector3(0, 0, 1), Vector3(-1, 0, 0),
			Matrix4::CreateRotationZ(ToRadian(90.0f)) * Matrix4::CreateRotationX(ToRadian(0.0f)));
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Object and camera positions are too close and doesn't pass cameraForwardVector.

	TEST(Matrix4, CreateConstrainedBillboardTooCloseTest1)
	{
		const Vector3 objectPosition = Vector3(3.0f, 4.0f, 5.0f);
		const Vector3 cameraPosition = objectPosition;
		const Vector3 cameraUpVector = Vector3(0, 1, 0);

		// Doesn't pass camera face direction. CreateConstrainedBillboard uses Vector3Ff(0, 0, -1) direction. Result must be same as 180 degrees rotate along y-axis.
		const Matrix4 expected = Matrix4::CreateRotationY(ToRadian(180.0f)) * Matrix4::CreateTranslation(objectPosition);
		auto camera_forward_vector = Vector3(0, 0, 1);
		auto object_forward_vector = Vector3(0, 0, -1);
		const Matrix4 actual = Matrix4::CreateConstrainedBillboard(objectPosition, cameraPosition, cameraUpVector, &camera_forward_vector, &object_forward_vector);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Object and camera positions are too close and passed cameraForwardVector.

	TEST(Matrix4, CreateConstrainedBillboardTooCloseTest2)
	{
		const Vector3 objectPosition = Vector3(3.0f, 4.0f, 5.0f);
		const Vector3 cameraPosition = objectPosition;
		const Vector3 cameraUpVector = Vector3(0, 1, 0);

		// Passes Vector3f.Right as camera face direction. Result must be same as -90 degrees rotate along y-axis.
		const Matrix4 expected = Matrix4::CreateRotationY(ToRadian(-90.0f)) * Matrix4::CreateTranslation(objectPosition);
		auto camera_forward_vector = Vector3(1, 0, 0);
		auto object_forward_vector = Vector3(0, 0, -1);
		const Matrix4 actual = Matrix4::CreateConstrainedBillboard(objectPosition, cameraPosition, cameraUpVector, &camera_forward_vector, &object_forward_vector);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Angle between rotateAxis and camera to object vector is too small. And use doesn't passed objectForwardVector parameter.

	TEST(Matrix4, CreateConstrainedBillboardAlongAxisTest1)
	{
		// Place camera at up side of object.
		const Vector3 objectPosition = Vector3(3.0f, 4.0f, 5.0f);
		Vector3 rotateAxis = Vector3(0, 1, 0);
		const Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

		// In this case, CreateConstrainedBillboard picks Vector3Ff(0, 0, -1) as object forward vector.
		const Matrix4 expected = Matrix4::CreateRotationY(ToRadian(180.0f)) * Matrix4::CreateTranslation(objectPosition);
		auto camera_forward_vector = Vector3(0, 0, -1);
		const Matrix4 actual = Matrix4::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, &camera_forward_vector, &camera_forward_vector);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Angle between rotateAxis and camera to object vector is too small. And user doesn't passed objectForwardVector parameter.

	TEST(Matrix4, CreateConstrainedBillboardAlongAxisTest2)
	{
		// Place camera at up side of object.
		const Vector3 objectPosition = Vector3(3.0f, 4.0f, 5.0f);
		auto camera_forward_vector = Vector3(0, 0, -1);
		Vector3 rotateAxis = camera_forward_vector;
		const Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

		// In this case, CreateConstrainedBillboard picks Vector3Ff(1, 0, 0) as object forward vector.
		const Matrix4 expected = Matrix4::CreateRotationX(ToRadian(-90.0f)) * Matrix4::CreateRotationZ(ToRadian(-90.0f)) * Matrix4::CreateTranslation(objectPosition);
		const Matrix4 actual = Matrix4::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, &camera_forward_vector, &camera_forward_vector);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Angle between rotateAxis and camera to object vector is too small. And user passed correct objectForwardVector parameter.

	TEST(Matrix4, CreateConstrainedBillboardAlongAxisTest3)
	{
		// Place camera at up side of object.
		const Vector3 objectPosition = Vector3(3.0f, 4.0f, 5.0f);
		Vector3 rotateAxis = Vector3(0, 1, 0);
		const Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

		// User passes correct objectForwardVector.
		const Matrix4 expected = Matrix4::CreateRotationY(ToRadian(180.0f)) * Matrix4::CreateTranslation(objectPosition);
		auto camera_forward_vector = Vector3(0, 0, -1);
		const Matrix4 actual = Matrix4::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, &camera_forward_vector, &camera_forward_vector);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Angle between rotateAxis and camera to object vector is too small. And user passed incorrect objectForwardVector parameter.

	TEST(Matrix4, CreateConstrainedBillboardAlongAxisTest4)
	{
		// Place camera at up side of object.
		const Vector3 objectPosition(3.0f, 4.0f, 5.0f);
		Vector3 rotateAxis(0, 1, 0);
		const Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

		// User passes correct objectForwardVector.
		const Matrix4 expected = Matrix4::CreateRotationY(ToRadian(180.0f)) * Matrix4::CreateTranslation(objectPosition);
		Vector3 camera_forward_vector(0, 0, -1);
		Vector3 object_forward_vector(0, 1, 0);
		const Matrix4 actual = Matrix4::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, &camera_forward_vector, &object_forward_vector);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateConstrainedBillboard (Vector3f, Vector3f, Vector3f, Vector3f?)
	// Angle between rotateAxis and camera to object vector is too small. And user passed incorrect objectForwardVector parameter.

	TEST(Matrix4, CreateConstrainedBillboardAlongAxisTest5)
	{
		// Place camera at up side of object.
		const Vector3 objectPosition = Vector3(3.0f, 4.0f, 5.0f);
		auto camera_forward_vector = Vector3(0, 0, -1);
		Vector3 rotateAxis = camera_forward_vector;
		const Vector3 cameraPosition = objectPosition + rotateAxis * 10.0f;

		// In this case, CreateConstrainedBillboard picks Vector3f.Right as object forward vector.
		const Matrix4 expected = Matrix4::CreateRotationX(ToRadian(-90.0f)) * Matrix4::CreateRotationZ(ToRadian(-90.0f)) * Matrix4::CreateTranslation(objectPosition);
		const Matrix4 actual = Matrix4::CreateConstrainedBillboard(objectPosition, cameraPosition, rotateAxis, &camera_forward_vector, &camera_forward_vector);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateScale (Vector3f)

	TEST(Matrix4, CreateScaleTest1)
	{
		const Vector3 scales = Vector3(2.0f, 3.0f, 4.0f);
		const Matrix4 expected(
			2.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 3.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 4.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		const Matrix4 actual = Matrix4::CreateScale(scales);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateScale (Vector3f, Vector3f)

	TEST(Matrix4, CreateScaleCenterTest1)
	{
		const Vector3 scale = Vector3(3, 4, 5);
		const Vector3 center = Vector3(23, 42, 666);

		const Matrix4 scaleAroundZero = Matrix4::CreateScale(scale, Vector3::Zero());
		const Matrix4 scaleAroundZeroExpected = Matrix4::CreateScale(scale);
		EXPECT_EQ(scaleAroundZero, scaleAroundZeroExpected);

		const Matrix4 scaleAroundCenter = Matrix4::CreateScale(scale, center);
		const Matrix4 scaleAroundCenterExpected = Matrix4::CreateTranslation(-center) * Matrix4::CreateScale(scale) * Matrix4::CreateTranslation(center);
		EXPECT_EQ(scaleAroundCenter, scaleAroundCenterExpected);
	}

	// A test for CreateScale (float)

	TEST(Matrix4, CreateScaleTest2)
	{
		const float scale = 2.0f;
		const Matrix4 expected(
			2.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 2.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 2.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		const Matrix4 actual = Matrix4::CreateScale(scale);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateScale (float, Vector3f)

	TEST(Matrix4, CreateScaleCenterTest2)
	{
		const float scale = 5;
		const Vector3 center = Vector3(23, 42, 666);

		const Matrix4 scaleAroundZero = Matrix4::CreateScale(scale, scale, scale, Vector3::Zero());
		const Matrix4 scaleAroundZeroExpected = Matrix4::CreateScale(scale);
		EXPECT_EQ(scaleAroundZero, scaleAroundZeroExpected);

		const Matrix4 scaleAroundCenter = Matrix4::CreateScale(scale, scale, scale, center);
		const Matrix4 scaleAroundCenterExpected = Matrix4::CreateTranslation(-center) * Matrix4::CreateScale(scale) * Matrix4::CreateTranslation(center);
		EXPECT_EQ(scaleAroundCenter, scaleAroundCenterExpected);
	}

	// A test for CreateScale (float, float, float)

	TEST(Matrix4, CreateScaleTest3)
	{
		const float xScale = 2.0f;
		const float yScale = 3.0f;
		const float zScale = 4.0f;
		const Matrix4 expected(
			2.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 3.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 4.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		const Matrix4 actual = Matrix4::CreateScale(xScale, yScale, zScale);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateScale (float, float, float, Vector3f)

	TEST(Matrix4, CreateScaleCenterTest3)
	{
		const Vector3 scale = Vector3(3, 4, 5);
		const Vector3 center = Vector3(23, 42, 666);

		const Matrix4 scaleAroundZero = Matrix4::CreateScale(scale.x, scale.y, scale.z, Vector3::Zero());
		const Matrix4 scaleAroundZeroExpected = Matrix4::CreateScale(scale.x, scale.y, scale.z);
		EXPECT_EQ(scaleAroundZero, scaleAroundZeroExpected);

		const Matrix4 scaleAroundCenter = Matrix4::CreateScale(scale.x, scale.y, scale.z, center);
		const Matrix4 scaleAroundCenterExpected = Matrix4::CreateTranslation(-center) * Matrix4::CreateScale(scale.x, scale.y, scale.z) * Matrix4::CreateTranslation(center);
		EXPECT_EQ(scaleAroundCenter, scaleAroundCenterExpected);
	}

	// A test for CreateTranslation (Vector3f)

	TEST(Matrix4, CreateTranslationTest1)
	{
		const Vector3 position = Vector3(2.0f, 3.0f, 4.0f);
		const Matrix4 expected(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			2.0f, 3.0f, 4.0f, 1.0f);

		const Matrix4 actual = Matrix4::CreateTranslation(position);
		EXPECT_EQ(expected, actual);
	}

	// A test for CreateTranslation (float, float, float)

	TEST(Matrix4, CreateTranslationTest2)
	{
		const float xPosition = 2.0f;
		const float yPosition = 3.0f;
		const float zPosition = 4.0f;

		const Matrix4 expected(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			2.0f, 3.0f, 4.0f, 1.0f);

		const Matrix4 actual = Matrix4::CreateTranslation(xPosition, yPosition, zPosition);
		EXPECT_EQ(expected, actual);
	}

	// A test for Translation

	TEST(Matrix4, Translation)
	{
		Matrix4 a = GenerateTestMatrix();
		const Matrix4 b = a;

		// Transformed vector that has same semantics of property must be same.
		Vector3 val = Vector3(a.m41, a.m42, a.m43);
		EXPECT_EQ(val, a.Translation());

		// Set value and get value must be same.
		val = Vector3(1.0f, 2.0f, 3.0f);
		a.Translation(val);
		EXPECT_EQ(val, a.Translation());

		// Make sure it only modifies expected value of matrix.
		EXPECT_TRUE(
			a.m11 == b.m11 && a.m12 == b.m12 && a.m13 == b.m13 && a.m14 == b.m14 &&
			a.m21 == b.m21 && a.m22 == b.m22 && a.m23 == b.m23 && a.m24 == b.m24 &&
			a.m31 == b.m31 && a.m32 == b.m32 && a.m33 == b.m33 && a.m34 == b.m34 &&
			a.m41 != b.m41 && a.m42 != b.m42 && a.m43 != b.m43 && a.m44 == b.m44);
	}
	
	// A test for IsIdentity

	TEST(Matrix4, IsIdentity)
	{
		EXPECT_TRUE(Matrix4::CreateIdentity().IsIdentity());
		EXPECT_TRUE(Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1).IsIdentity());
		EXPECT_FALSE(Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0).IsIdentity());
	}

	TEST(Perspective, FarPlaneAtInfinity)
	{
		const auto nearPlaneDistance = 0.125f;
		const auto m = Matrix4::CreatePerspective(1.0f, 1.0f, nearPlaneDistance, std::numeric_limits<float>::infinity());
		EXPECT_EQ(-1.0f, m.m33);
		EXPECT_EQ(-nearPlaneDistance, m.m43);
	}

	TEST(PerspectiveFieldOfView, FarPlaneAtInfinity)
	{
		const auto nearPlaneDistance = 0.125f;
		const auto m = Matrix4::CreatePerspectiveFieldOfView(ToRadian(60.0f), 1.5f, nearPlaneDistance, std::numeric_limits<float>::infinity());
		EXPECT_EQ(-1.0f, m.m33);
		EXPECT_EQ(-nearPlaneDistance, m.m43);
	}

	TEST(PerspectiveOffCenter, FarPlaneAtInfinity)
	{
		const auto nearPlaneDistance = 0.125f;
		const auto m = Matrix4::CreatePerspectiveOffCenter(0.0f, 0.0f, 1.0f, 1.0f, nearPlaneDistance, std::numeric_limits<float>::infinity());
		EXPECT_EQ(-1.0f, m.m33);
		EXPECT_EQ(-nearPlaneDistance, m.m43);
	}
}
