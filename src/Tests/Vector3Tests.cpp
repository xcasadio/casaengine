#include "gtest/gtest.h"

#include "Maths/Matrix4.h"
#include "Maths/Quaternion.h"
#include "Maths/Vector3.h"

using namespace CasaEngine;

namespace CasaEngineTests
{
	TEST(Vector3, Normalization)
	{
		Vector3 v(0.0f, 3.0f, 4.0f);
		v.Normalize();
		EXPECT_NEAR(0.8f, v.GetZ(), 0.01f);
	}

	TEST(Vector3, DotProduct)
	{
		const Vector3 v(2.0f, 4.0f, 6.0f);
		EXPECT_NEAR(56.0f, Vector3::Dot(v, v), 0.01f);
	}

	TEST(Vector3, Addition)
	{
		Vector3 v1(1.0f, 2.0f, 3.0f);
		const Vector3 v2(2.0f, 4.0f, 6.0f);
		v1 = Vector3::Add(v1, v2);
		EXPECT_NEAR(9.0f, v1.GetZ(), 0.01f);
	}

	TEST(Vector3, OperatorAddition)
	{
		Vector3 v1(1.0f, 2.0f, 3.0f);
		const Vector3 v2(2.0f, 4.0f, 6.0f);
		Vector3 v3(2.0f, 4.0f, 6.0f);
		v1 = v1 + v2;
		EXPECT_NEAR(9.0f, v1.GetZ(), 0.01f);
	}

	TEST(Vector3, OperatorEqualAddition)
	{
		Vector3 v1(1.0f, 2.0f, 3.0f);
		const Vector3 v2(2.0f, 4.0f, 6.0f);
		v1 += v1 + v2;
		EXPECT_NEAR(12.0f, v1.GetZ(), 0.01f);
	}

	TEST(Vector3, Substraction)
	{
		Vector3 v1(1.0f, 2.0f, 3.0f);
		const Vector3 v2(2.0f, 4.0f, 6.0f);
		v1 = Vector3::Subtract(v1, v2);
		EXPECT_NEAR(-3.0f, v1.GetZ(), 0.01f);
	}

	TEST(Vector3, OperatorSubstraction)
	{
		Vector3 v1(1.0f, 2.0f, 3.0f);
		const Vector3 v2(2.0f, 4.0f, 6.0f);
		v1 = v1 - v2 - v1;
		EXPECT_NEAR(-6.0f, v1.GetZ(), 0.01f);
	}

	TEST(Vector3, OperatorEqualSubstraction)
	{
		Vector3 v1(1.0f, 2.0f, 3.0f);
		const Vector3 v2(2.0f, 4.0f, 6.0f);
		v1 -= v2 - v1;
		EXPECT_NEAR(0.0f, v1.GetZ(), 0.01f);
	}

	TEST(Vector3, SquaredLength)
	{
		const Vector3 v(3.0f, 1.0f, 4.0f);
		EXPECT_NEAR(26.0f, v.LengthSquared(), 0.01f);
	}

	TEST(Vector3, Length)
	{
		const Vector3 v(3.0f, 0.0f, 4.0f);
		EXPECT_NEAR(5.0f, v.Length(), 0.01f);
	}

	TEST(Vector3, CrossProduct)
	{
		const Vector3 v1(3.0f, 2.0f, 5.0f);
		const Vector3 v2(4.0f, 6.0f, 1.0f);
		const Vector3 v3 = Vector3::Cross(v1, v2);
		EXPECT_NEAR(10.0f, v3.GetZ(), 0.01f);
	}

	TEST(Vector3, LERP)
	{
		const Vector3 v1(1.0f, 10.0f, 100.0f);
		const Vector3 v2(0.0f, 0.0f, 0.0f);
		const Vector3 v3 = Vector3::Lerp(v1, v2, 0.75f);
		EXPECT_NEAR(25.0f, v3.GetZ(), 0.01f);
	}

	TEST(Vector3, MultiplicationWithFloat)
	{
		Vector3 v(1.0f, 1.0f, 1.0f);
		v *= 3.0f;
		EXPECT_NEAR(3.0f, v.GetZ(), 0.01f);
	}

	TEST(Vector3, OperatorMultiplication)
	{
		Vector3 v(1.0f, 1.0f, 1.0f);
		v = v * 3.0f * 3.0f;
		EXPECT_NEAR(9.0f, v.GetZ(), 0.01f);
	}
	/*
	TEST(Vector3, Blend)
	{
		Vector3 v1(1.0f, 1.0f, 1.0f);
		Vector3 v2(4.0f, 4.0f, 4.0f);
		Vector3 v3(8.0f, 8.0f, 8.0f);
		Vector3 v4(16.0f, 16.0f, 16.0f);

		Vector3 vBlendResult = Vector3::Blend(v1, v2, v3, v4, 0.25f, 0.25f, 0.25f);
		EXPECT_NEAR(7.25f, vBlendResult.GetZ(), 0.01f);
	}
	*/

	// A test for Cross (Vector3f, Vector3f)

	TEST(Vector3, CrossTest)
	{
		const Vector3 a(1.0f, 0.0f, 0.0f);
		const Vector3 b(0.0f, 1.0f, 0.0f);

		const Vector3 expected(0.0f, 0.0f, 1.0f);
		const Vector3 actual = Vector3::Cross(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Cross (Vector3f, Vector3f)
	// Cross test of the same vector

	TEST(Vector3, CrossTest1)
	{
		const Vector3 a(0.0f, 1.0f, 0.0f);
		const Vector3 b(0.0f, 1.0f, 0.0f);

		const Vector3 expected(0.0f, 0.0f, 0.0f);
		const Vector3 actual = Vector3::Cross(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Distance (Vector3f, Vector3f)

	TEST(Vector3, DistanceTest)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);
		const Vector3 b(4.0f, 5.0f, 6.0f);

		const float expected = sqrtf(27);
		const float actual = Vector3::Distance(a, b);

		EXPECT_EQ(expected, actual);
	}

	// A test for Distance (Vector3f, Vector3f)
	// Distance from the same point

	TEST(Vector3, DistanceTest1)
	{
		const Vector3 a(1.051f, 2.05f, 3.478f);
		const Vector3 b(1.051f, 2.05f, 3.478f);

		const float actual = Vector3::Distance(a, b);
		EXPECT_EQ(0.0f, actual);
	}

	// A test for DistanceSquared (Vector3f, Vector3f)

	TEST(Vector3, DistanceSquaredTest)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);
		const Vector3 b(4.0f, 5.0f, 6.0f);

		const float expected = 27.0f;
		const float actual = Vector3::DistanceSquared(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Dot (Vector3f, Vector3f)

	TEST(Vector3, DotTest)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);
		const Vector3 b(4.0f, 5.0f, 6.0f);

		const float expected = 32.0f;
		const float actual = Vector3::Dot(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Dot (Vector3f, Vector3f)
	// Dot test for perpendicular vector

	TEST(Vector3, DotTest1)
	{
		const Vector3 a(1.55f, 1.55f, 1);
		const Vector3 b(2.5f, 3, 1.5f);
		const Vector3 c = Vector3::Cross(a, b);

		const float expected = 0.0f;
		const float actual1 = Vector3::Dot(a, c);
		const float actual2 = Vector3::Dot(b, c);
		EXPECT_NEAR(expected, actual1, 0.01f);
		EXPECT_NEAR(expected, actual2, 0.01f);
	}

	// A test for Length ()

	TEST(Vector3, LengthTest)
	{
		const auto a = Vector2(1.0f, 2.0f);

		const float z = 3.0f;

		const Vector3 target(a.x, a.y, z);

		const float expected = sqrtf(14.0f);

		const float actual = target.Length();
		EXPECT_EQ(expected, actual);
	}

	// A test for Length ()
	// Length test where length is zero

	TEST(Vector3, LengthTest1)
	{
		const Vector3 target;

		const float expected = 0.0f;
		const float actual = target.Length();
		EXPECT_EQ(expected, actual);
	}

	// A test for LengthSquared ()

	TEST(Vector3, LengthSquaredTest)
	{
		const auto a = Vector2(1.0f, 2.0f);

		const float z = 3.0f;

		const Vector3 target(a.x, a.y, z);

		const float expected = 14.0f;

		const float actual = target.LengthSquared();
		EXPECT_EQ(expected, actual);
	}

	// A test for Min (Vector3f, Vector3f)

	TEST(Vector3, MinTest)
	{
		const Vector3 a(-1.0f, 4.0f, -3.0f);
		const Vector3 b(2.0f, 1.0f, -1.0f);

		const Vector3 expected(-1.0f, 1.0f, -3.0f);
		const Vector3 actual = Vector3::Min(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Max (Vector3f, Vector3f)

	TEST(Vector3, MaxTest)
	{
		const Vector3 a(-1.0f, 4.0f, -3.0f);
		const Vector3 b(2.0f, 1.0f, -1.0f);

		const Vector3 expected(2.0f, 4.0f, -1.0f);
		const Vector3 actual = Vector3::Max(a, b);
		EXPECT_EQ(expected, actual);
	}


	TEST(Vector3, MinMaxCodeCoverageTest)
	{
		const Vector3 min = Vector3::Zero();
		const Vector3 max = Vector3::One();

		// Min.
		Vector3 actual = Vector3::Min(min, max);
		EXPECT_EQ(actual, min);

		actual = Vector3::Min(max, min);
		EXPECT_EQ(actual, min);

		// Max.
		actual = Vector3::Max(min, max);
		EXPECT_EQ(actual, max);

		actual = Vector3::Max(max, min);
		EXPECT_EQ(actual, max);
	}

	// A test for Lerp (Vector3f, Vector3f, float)

	TEST(Vector3, LerpTest)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);
		const Vector3 b(4.0f, 5.0f, 6.0f);

		const float t = 0.5f;

		const Vector3 expected(2.5f, 3.5f, 4.5f);

		const Vector3 actual = Vector3::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector3f, Vector3f, float)
	// Lerp test with factor zero

	TEST(Vector3, LerpTest1)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);
		const Vector3 b(4.0f, 5.0f, 6.0f);

		const float t = 0.0f;
		const Vector3 expected(1.0f, 2.0f, 3.0f);
		const Vector3 actual = Vector3::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector3f, Vector3f, float)
	// Lerp test with factor one

	TEST(Vector3, LerpTest2)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);
		const Vector3 b(4.0f, 5.0f, 6.0f);

		const float t = 1.0f;
		const Vector3 expected(4.0f, 5.0f, 6.0f);
		const Vector3 actual = Vector3::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector3f, Vector3f, float)
	// Lerp test with factor > 1

	TEST(Vector3, LerpTest3)
	{
		const Vector3 a(0.0f, 0.0f, 0.0f);
		const Vector3 b(4.0f, 5.0f, 6.0f);

		const float t = 2.0f;
		const Vector3 expected(8.0f, 10.0f, 12.0f);
		const Vector3 actual = Vector3::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector3f, Vector3f, float)
	// Lerp test with factor < 0

	TEST(Vector3, LerpTest4)
	{
		const Vector3 a(0.0f, 0.0f, 0.0f);
		const Vector3 b(4.0f, 5.0f, 6.0f);

		const float t = -2.0f;
		const Vector3 expected(-8.0f, -10.0f, -12.0f);
		const Vector3 actual = Vector3::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector3f, Vector3f, float)
	// Lerp test with special float value

	TEST(Vector3, LerpTest5)
	{
		const Vector3 a(45.67f, 90.0f, 0.0f);
		const Vector3 b(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::lowest(), 0);

		const float t = 0.408f;
		const Vector3 actual = Vector3::Lerp(a, b, t);
		EXPECT_TRUE(IsPositiveInfinity(actual.x));
		EXPECT_TRUE(IsNegativeInfinity(actual.y));
	}

	// A test for Lerp (Vector3f, Vector3f, float)
	// Lerp test from the same point

	TEST(Vector3, LerpTest6)
	{
		const Vector3 a(1.68f, 2.34f, 5.43f);
		const Vector3 b = a;

		const float t = 0.18f;
		const Vector3 expected(1.68f, 2.34f, 5.43f);
		const Vector3 actual = Vector3::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector3f, Vector3f, float)
	// Lerp test with values known to be innacurate with the old lerp impl

	TEST(Vector3, LerpTest7)
	{
		const Vector3 a(0.44728136f, 0.44728136f, 0.44728136f);
		const Vector3 b(0.46345946f, 0.46345946f, 0.46345946f);

		const float t = 0.26402435f;

		const Vector3 expected(0.45155275f, 0.45155275f, 0.45155275f);
		const Vector3 actual = Vector3::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector3f, Vector3f, float)
	// Lerp test with values known to be innacurate with the old lerp impl
	// (Old code incorrectly gets 0.33333588)

	TEST(Vector3, LerpTest8)
	{
		const Vector3 a(-100, -100, -100);
		const Vector3 b(0.33333334f, 0.33333334f, 0.33333334f);

		const float t = 1.0f;

		const Vector3 expected(0.33333334f, 0.33333334f, 0.33333334f);
		const Vector3 actual = Vector3::Lerp(a, b, t);
		EXPECT_NEAR(expected.x, actual.x, 0.01f);
		EXPECT_NEAR(expected.y, actual.y, 0.01f);
		EXPECT_NEAR(expected.z, actual.z, 0.01f);
	}

	// A test for Reflect (Vector3f, Vector3f)

	TEST(Vector3, ReflectTest)
	{
		Vector3 a = Vector3::Normalize(Vector3(1.0f, 1.0f, 1.0f));

		// Reflect on XZ plane.
		Vector3 n(0.0f, 1.0f, 0.0f);
		Vector3 expected(a.x, -a.y, a.z);
		Vector3 actual = Vector3::Reflect(a, n);
		EXPECT_EQ(expected, actual);

		// Reflect on XY plane.
		n = Vector3(0.0f, 0.0f, 1.0f);
		expected = Vector3(a.x, a.y, -a.z);
		actual = Vector3::Reflect(a, n);
		EXPECT_EQ(expected, actual);

		// Reflect on YZ plane.
		n = Vector3(1.0f, 0.0f, 0.0f);
		expected = Vector3(-a.x, a.y, a.z);
		actual = Vector3::Reflect(a, n);
		EXPECT_EQ(expected, actual);
	}

	// A test for Reflect (Vector3f, Vector3f)
	// Reflection when normal and source are the same

	TEST(Vector3, ReflectTest1)
	{
		Vector3 n(0.45f, 1.28f, 0.86f);
		n = Vector3::Normalize(n);
		Vector3 a = n;

		const Vector3 expected = -n;
		const Vector3 actual = Vector3::Reflect(a, n);
		EXPECT_EQ(expected, actual);
	}

	// A test for Reflect (Vector3f, Vector3f)
	// Reflection when normal and source are negation

	TEST(Vector3, ReflectTest2)
	{
		Vector3 n(0.45f, 1.28f, 0.86f);
		n = Vector3::Normalize(n);
		Vector3 a = -n;

		const Vector3 expected = n;
		const Vector3 actual = Vector3::Reflect(a, n);
		EXPECT_EQ(expected, actual);
	}

	// A test for Reflect (Vector3f, Vector3f)
	// Reflection when normal and source are perpendicular (a dot n = 0)

	TEST(Vector3, ReflectTest3)
	{
		Vector3 n(0.45f, 1.28f, 0.86f);
		const Vector3 temp(1.28f, 0.45f, 0.01f);
		// find a perpendicular vector of n
		Vector3 a = Vector3::Cross(temp, n);

		const Vector3 expected = a;
		const Vector3 actual = Vector3::Reflect(a, n);

		EXPECT_NEAR(expected.x, actual.x, 0.01f);
		EXPECT_NEAR(expected.y, actual.y, 0.01f);
		EXPECT_NEAR(expected.z, actual.z, 0.01f);
	}

	// A test for Transform(Vector3f, Matrix4)

	TEST(Vector3, TransformTest)
	{
		const Vector3 v(1.0f, 2.0f, 3.0f);
		Matrix4 m =
			Matrix4::CreateRotationX(ToRadian(30.0f)) *
			Matrix4::CreateRotationY(ToRadian(30.0f)) *
			Matrix4::CreateRotationZ(ToRadian(30.0f));
		m.m41 = 10.0f;
		m.m42 = 20.0f;
		m.m43 = 30.0f;

		const Vector3 expected(12.191987f, 21.533493f, 32.616024f);

		const Vector3 actual = m.Transform(v);
		EXPECT_EQ(expected, actual);
	}

	// A test for Clamp (Vector3f, Vector3f, Vector3f)

	TEST(Vector3, ClampTest)
	{
		Vector3 a(0.5f, 0.3f, 0.33f);
		Vector3 min(0.0f, 0.1f, 0.13f);
		Vector3 max(1.0f, 1.1f, 1.13f);

		// Normal case.
		// Case N1: specified value is in the range.
		Vector3 expected(0.5f, 0.3f, 0.33f);
		Vector3 actual = Vector3::Clamp(a, min, max);
		EXPECT_EQ(expected, actual);

		// Normal case.
		// Case N2: specified value is bigger than max value.
		a = Vector3(2.0f, 3.0f, 4.0f);
		expected = max;
		actual = Vector3::Clamp(a, min, max);
		EXPECT_EQ(expected, actual);

		// Case N3: specified value is smaller than max value.
		a = Vector3(-2.0f, -3.0f, -4.0f);
		expected = min;
		actual = Vector3::Clamp(a, min, max);
		EXPECT_EQ(expected, actual);

		// Case N4: combination case.
		a = Vector3(-2.0f, 0.5f, 4.0f);
		expected = Vector3(min.x, a.y, max.z);
		actual = Vector3::Clamp(a, min, max);
		EXPECT_EQ(expected, actual);

		// User specified min value is bigger than max value.
		max = Vector3(0.0f, 0.1f, 0.13f);
		min = Vector3(1.0f, 1.1f, 1.13f);

		// Case W1: specified value is in the range.
		a = Vector3(0.5f, 0.3f, 0.33f);
		expected = min;
		actual = Vector3::Clamp(a, min, max);
		EXPECT_EQ(expected, actual);

		// Normal case.
		// Case W2: specified value is bigger than max and min value.
		a = Vector3(2.0f, 3.0f, 4.0f);
		expected = min;
		actual = Vector3::Clamp(a, min, max);
		EXPECT_EQ(expected, actual);

		// Case W3: specified value is smaller than min and max value.
		a = Vector3(-2.0f, -3.0f, -4.0f);
		expected = min;
		actual = Vector3::Clamp(a, min, max);
		EXPECT_EQ(expected, actual);
	}

	// A test for TransformNormal (Vector3f, Matrix4)

	TEST(Vector3, TransformNormalTest)
	{
		const Vector3 v(1.0f, 2.0f, 3.0f);
		Matrix4 m =
			Matrix4::CreateRotationX(ToRadian(30.0f)) *
			Matrix4::CreateRotationY(ToRadian(30.0f)) *
			Matrix4::CreateRotationZ(ToRadian(30.0f));
		m.m41 = 10.0f;
		m.m42 = 20.0f;
		m.m43 = 30.0f;

		const Vector3 expected(2.19198728f, 1.53349364f, 2.61602545f);

		const Vector3 actual = m.TransformNormal(v);
		EXPECT_EQ(expected, actual);
	}

	// A test for Transform (Vector3f, Quaternion)

	TEST(Vector3, TransformByQuaternionTest)
	{
		const Vector3 v(1.0f, 2.0f, 3.0f);

		Matrix4 m =
			Matrix4::CreateRotationX(ToRadian(30.0f)) *
			Matrix4::CreateRotationY(ToRadian(30.0f)) *
			Matrix4::CreateRotationZ(ToRadian(30.0f));
		const Quaternion q = Quaternion::CreateFromRotationMatrix(m);

		const Vector3 expected = m.Transform(v);
		const Vector3 actual = q.Transform(v);

		EXPECT_NEAR(expected.x, actual.x, 0.01f);
		EXPECT_NEAR(expected.y, actual.y, 0.01f);
		EXPECT_NEAR(expected.z, actual.z, 0.01f);
	}

	// A test for Transform (Vector3f, Quaternion)
	// Transform vector3 with zero quaternion

	TEST(Vector3, TransformByQuaternionTest1)
	{
		const Vector3 v(1.0f, 2.0f, 3.0f);
		const Quaternion q;
		const Vector3 expected = v;

		const Vector3 actual = q.Transform(v);
		EXPECT_EQ(expected, actual);
	}

	// A test for Transform (Vector3f, Quaternion)
	// Transform vector3 with identity quaternion

	TEST(Vector3, TransformByQuaternionTest2)
	{
		const Vector3 v(1.0f, 2.0f, 3.0f);
		const Quaternion q = Quaternion::CreateIdentity();
		const Vector3 expected = v;

		const Vector3 actual = q.Transform(v);
		EXPECT_EQ(expected, actual);
	}

	// A test for Normalized (Vector3f)

	TEST(Vector3, NormalizeTest)
	{
		Vector3 a(1.0f, 2.0f, 3.0f);

		const Vector3 expected(
			0.26726124191242438468455348087975f,
			0.53452248382484876936910696175951f,
			0.80178372573727315405366044263926f);
		const Vector3 actual = Vector3::Normalize(a);
		EXPECT_EQ(expected, actual);
	}

	// A test for Normalized (Vector3f)
	// Normalized vector of length one

	TEST(Vector3, NormalizeTest1)
	{
		Vector3 a(1.0f, 0.0f, 0.0f);

		const Vector3 expected(1.0f, 0.0f, 0.0f);
		const Vector3 actual = Vector3::Normalize(a);
		EXPECT_EQ(expected, actual);
	}

	// A test for Normalized (Vector3f)
	// Normalized vector of length zero

	TEST(Vector3, NormalizeTest2)
	{
		Vector3 a(0.0f, 0.0f, 0.0f);

		const Vector3 expected(0.0f, 0.0f, 0.0f);
		const Vector3 actual = Vector3::Normalize(a);
		EXPECT_EQ(expected, actual);
	}

	// A test for operator - (Vector3f)

	TEST(Vector3, UnaryNegationTest)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);

		const Vector3 expected(-1.0f, -2.0f, -3.0f);

		const Vector3 actual = -a;

		EXPECT_EQ(expected, actual);
	}


	TEST(Vector3, UnaryNegationTest1)
	{
		const Vector3 a = -Vector3(NaN(), std::numeric_limits<float>::max(), std::numeric_limits<float>::lowest());
		const Vector3 b = -Vector3(0.0f, 0.0f, 0.0f);
		EXPECT_TRUE(IsNaN(a.x));
		EXPECT_EQ(std::numeric_limits<float>::lowest(), a.y);
		EXPECT_EQ(std::numeric_limits<float>::max(), a.z);
		EXPECT_EQ(0.0f, b.x);
		EXPECT_EQ(0.0f, b.y);
		EXPECT_EQ(0.0f, b.z);
	}

	// A test for operator - (Vector3f, Vector3f)

	TEST(Vector3, SubtractionTest)
	{
		const Vector3 a(4.0f, 2.0f, 3.0f);

		const Vector3 b(1.0f, 5.0f, 7.0f);

		const Vector3 expected(3.0f, -3.0f, -4.0f);

		const Vector3 actual = a - b;

		EXPECT_EQ(expected, actual);
	}

	// A test for operator * (Vector3f, float)

	TEST(Vector3, MultiplyOperatorTest)
	{
		Vector3 a(1.0f, 2.0f, 3.0f);

		const float factor = 2.0f;

		const Vector3 expected(2.0f, 4.0f, 6.0f);

		const Vector3 actual = a * factor;

		EXPECT_EQ(expected, actual);
	}

	// A test for operator * (float, Vector3f)

	TEST(Vector3, MultiplyOperatorTest2)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);

		const float factor = 2.0f;

		const Vector3 expected(2.0f, 4.0f, 6.0f);

		const Vector3 actual = factor * a;

		EXPECT_EQ(expected, actual);
	}

	// A test for operator * (Vector3f, Vector3f)

	TEST(Vector3, MultiplyOperatorTest3)
	{
		Vector3 a(1.0f, 2.0f, 3.0f);

		const Vector3 b(4.0f, 5.0f, 6.0f);

		const Vector3 expected(4.0f, 10.0f, 18.0f);
		const Vector3 actual = a * b;

		EXPECT_EQ(expected, actual);
	}

	// A test for operator / (Vector3f, float)

	TEST(Vector3, DivisionTest)
	{
		Vector3 a(1.0f, 2.0f, 3.0f);

		const float div = 2.0f;

		const Vector3 expected(0.5f, 1.0f, 1.5f);
		const Vector3 actual = a / div;

		EXPECT_EQ(expected, actual);
	}

	// A test for operator / (Vector3f, Vector3f)

	TEST(Vector3, DivisionTest1)
	{
		Vector3 a(4.0f, 2.0f, 3.0f);

		const Vector3 b(1.0f, 5.0f, 6.0f);

		const Vector3 expected(4.0f, 0.4f, 0.5f);
		const Vector3 actual = a / b;

		EXPECT_EQ(expected, actual);
	}

	// A test for operator / (Vector3f, Vector3f)
	// Divide by zero

	TEST(Vector3, DivisionTest2)
	{
		Vector3 a(-2.0f, 3.0f, MaxFloat);

		const float div = 0.0f;

		const Vector3 actual = a / div;

		EXPECT_TRUE(IsNegativeInfinity(actual.x));
		EXPECT_TRUE(IsPositiveInfinity(actual.y));
		EXPECT_TRUE(IsPositiveInfinity(actual.z));
	}

	// A test for operator / (Vector3f, Vector3f)
	// Divide by zero

	TEST(Vector3, DivisionTest3)
	{
		Vector3 a(0.047f, -3.0f, std::numeric_limits<float>::lowest());
		const Vector3 b;

		const Vector3 actual = a / b;

		EXPECT_TRUE(IsPositiveInfinity(actual.x));
		EXPECT_TRUE(IsNegativeInfinity(actual.y));
		EXPECT_TRUE(IsNegativeInfinity(actual.z));
	}

	// A test for operator + (Vector3f, Vector3f)

	TEST(Vector3, AdditionTest)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);
		const Vector3 b(4.0f, 5.0f, 6.0f);

		const Vector3 expected(5.0f, 7.0f, 9.0f);
		const Vector3 actual = a + b;

		EXPECT_EQ(expected, actual);
	}

	// A test for Vector3f (float, float, float)

	TEST(Vector3, ConstructorTest)
	{
		const float x = 1.0f;
		const float y = 2.0f;
		const float z = 3.0f;

		const Vector3 target(x, y, z);
		EXPECT_EQ(target.x, x);
		EXPECT_EQ(target.y, y);
		EXPECT_EQ(target.z, z);
	}

	TEST(Vector3, ConstructorTest3)
	{
		const Vector3 a;

		EXPECT_EQ(0.0f, a.x);
		EXPECT_EQ(0.0f, a.y);
		EXPECT_EQ(0.0f, a.z);
	}

	// A test for Vector2f (float, float)
	// Constructor with special floating values

	TEST(Vector3, ConstructorTest4)
	{
		const Vector3 target(NaN(), MaxFloat, std::numeric_limits<float>::infinity());

		EXPECT_TRUE(IsNaN(target.x));
		EXPECT_TRUE(MaxFloat == target.y);
		EXPECT_TRUE(IsPositiveInfinity(target.z));
	}

	// A test for Add (Vector3f, Vector3f)

	TEST(Vector3, AddTest)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);
		const Vector3 b(5.0f, 6.0f, 7.0f);

		const Vector3 expected(6.0f, 8.0f, 10.0f);

		const Vector3 actual = Vector3::Add(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Divide (Vector3f, float)

	TEST(Vector3, DivideTest)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);
		const float div = 2.0f;
		const Vector3 expected(0.5f, 1.0f, 1.5f);
		const Vector3 actual = Vector3::Divide(a, div);
		EXPECT_EQ(expected, actual);
	}

	// A test for Divide (Vector3f, Vector3f)

	TEST(Vector3, DivideTest1)
	{
		const Vector3 a(1.0f, 6.0f, 7.0f);
		const Vector3 b(5.0f, 2.0f, 3.0f);

		const Vector3 expected(1.0f / 5.0f, 6.0f / 2.0f, 7.0f / 3.0f);

		const Vector3 actual = Vector3::Divide(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Multiply (Vector3f, float)

	TEST(Vector3, MultiplyTest)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);
		const float factor = 2.0f;
		const Vector3 expected(2.0f, 4.0f, 6.0f);
		const Vector3 actual = Vector3::Multiply(a, factor);
		EXPECT_EQ(expected, actual);
	}

	// A test for Multiply (float, Vector3f)

	TEST(Vector3, MultiplyTest2)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);
		const float factor = 2.0f;
		const Vector3 expected(2.0f, 4.0f, 6.0f);
		const Vector3 actual = Vector3::Multiply(factor, a);
		EXPECT_EQ(expected, actual);
	}

	// A test for Multiply (Vector3f, Vector3f)

	TEST(Vector3, MultiplyTest3)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);
		const Vector3 b(5.0f, 6.0f, 7.0f);

		const Vector3 expected(5.0f, 12.0f, 21.0f);

		const Vector3 actual = Vector3::Multiply(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Negate (Vector3f)

	TEST(Vector3, NegateTest)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);

		const Vector3 expected(-1.0f, -2.0f, -3.0f);

		const Vector3 actual = Vector3::Negate(a);
		EXPECT_EQ(expected, actual);
	}

	// A test for operator != (Vector3f, Vector3f)

	TEST(Vector3, InequalityTest)
	{
		const Vector3 a(1.0f, 2.0f, 3.0f);
		Vector3 b(1.0f, 2.0f, 3.0f);

		// case 1: compare between same values
		bool expected = false;
		bool actual = a != b;
		EXPECT_EQ(expected, actual);

		// case 2: compare between different values
		b.x = 10.0f;
		expected = true;
		actual = a != b;
		EXPECT_EQ(expected, actual);
	}

	// A test for operator == (Vector3f, Vector3f)

	TEST(Vector3, EqualityTest)
	{
		Vector3 a(1.0f, 2.0f, 3.0f);
		Vector3 b(1.0f, 2.0f, 3.0f);

		// case 1: compare between same values
		bool expected = true;
		bool actual = a == b;
		EXPECT_EQ(expected, actual);

		// case 2: compare between different values
		b.x = 10.0f;
		expected = false;
		actual = a == b;
		EXPECT_EQ(expected, actual);
	}

	// A test for Subtract (Vector3f, Vector3f)

	TEST(Vector3, SubtractTest)
	{
		const Vector3 a(1.0f, 6.0f, 3.0f);
		const Vector3 b(5.0f, 2.0f, 3.0f);

		const Vector3 expected(-4.0f, 4.0f, 0.0f);

		const Vector3 actual = Vector3::Subtract(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for One

	TEST(Vector3, OneTest)
	{
		const Vector3 val(1.0f, 1.0f, 1.0f);
		EXPECT_EQ(val, Vector3::One());
	}

	// A test for UnitX

	TEST(Vector3, UnitXTest)
	{
		const Vector3 val(1.0f, 0.0f, 0.0f);
		EXPECT_EQ(val, Vector3::UnitX());
	}

	// A test for UnitY

	TEST(Vector3, UnitYTest)
	{
		const Vector3 val(0.0f, 1.0f, 0.0f);
		EXPECT_EQ(val, Vector3::UnitY());
	}

	// A test for UnitZ

	TEST(Vector3, UnitZTest)
	{
		const Vector3 val(0.0f, 0.0f, 1.0f);
		EXPECT_EQ(val, Vector3::UnitZ());
	}

	// A test for Zero

	TEST(Vector3, ZeroTest)
	{
		const Vector3 val(0.0f, 0.0f, 0.0f);
		EXPECT_EQ(val, Vector3::Zero());
	}

	// A test for Vector3f comparison involving NaN values

	TEST(Vector3, EqualsNanTest)
	{
		const Vector3 a(NaN(), 0, 0);
		const Vector3 b(0, NaN(), 0);
		const Vector3 c(0, 0, NaN());

		EXPECT_FALSE(a == Vector3::Zero());
		EXPECT_FALSE(b == Vector3::Zero());
		EXPECT_FALSE(c == Vector3::Zero());

		EXPECT_TRUE(a != Vector3::Zero());
		EXPECT_TRUE(b != Vector3::Zero());
		EXPECT_TRUE(c != Vector3::Zero());
	}


	TEST(Vector3, AbsTest)
	{
		const Vector3 v1(-2.5f, 2.0f, 0.5f);
		const Vector3 v3 = Vector3::Abs(Vector3(0.0f, std::numeric_limits<float>::lowest(), NaN()));
		const Vector3 v = Vector3::Abs(v1);
		EXPECT_EQ(2.5f, v.x);
		EXPECT_EQ(2.0f, v.y);
		EXPECT_EQ(0.5f, v.z);
		EXPECT_EQ(0.0f, v3.x);
		EXPECT_EQ(std::numeric_limits<float>::max(), v3.y);
		EXPECT_TRUE(IsNaN(v3.z));
	}


	TEST(Vector3, SqrtTest)
	{
		Vector3 a(-2.5f, 2.0f, 0.5f);
		Vector3 b(5.5f, 4.5f, 16.5f);
		EXPECT_EQ(2, (int)Vector3::SquareRoot(b).x);
		EXPECT_EQ(2, (int)Vector3::SquareRoot(b).y);
		EXPECT_EQ(4, (int)Vector3::SquareRoot(b).z);
		EXPECT_TRUE(IsNaN(Vector3::SquareRoot(a).x));
	}
}
