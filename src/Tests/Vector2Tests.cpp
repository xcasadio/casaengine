#include "gtest/gtest.h"

#include "Maths/Vector2.h"
#include "Maths/Math.h"
#include "Maths/Quaternion.h"

using namespace CasaEngine;

namespace CasaEngineTests
{
	// A test for Distance (Vector2f, Vector2f)

	TEST(Vector2, DistanceTest)
	{
		const Vector2 a(1.0f, 2.0f);
		const Vector2 b(3.0f, 4.0f);

		const float expected = sqrtf(8);

		const float actual = Vector2::Distance(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Distance (Vector2f, Vector2f)
	// Distance from the same point

	TEST(Vector2, DistanceTest2)
	{
		const Vector2 a(1.051f, 2.05f);
		const Vector2 b(1.051f, 2.05f);

		const float actual = Vector2::Distance(a, b);
		EXPECT_EQ(0.0f, actual);
	}

	// A test for DistanceSquared (Vector2f, Vector2f)

	TEST(Vector2, DistanceSquaredTest)
	{
		const Vector2 a(1.0f, 2.0f);
		const Vector2 b(3.0f, 4.0f);

		const float expected = 8.0f;

		const float actual = Vector2::DistanceSquared(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Dot (Vector2f, Vector2f)

	TEST(Vector2, DotTest)
	{
		const Vector2 a(1.0f, 2.0f);
		const Vector2 b(3.0f, 4.0f);

		const float expected = 11.0f;

		const float actual = Vector2::Dot(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Dot (Vector2f, Vector2f)
	// Dot test for perpendicular vector

	TEST(Vector2, DotTest1)
	{
		const Vector2 a(1.55f, 1.55f);
		const Vector2 b(-1.55f, 1.55f);

		const float expected = 0.0f;
		const float actual = Vector2::Dot(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Dot (Vector2f, Vector2f)
	// Dot test with specail float values

	TEST(Vector2, DotTest2)
	{
		const Vector2 a(-MaxFloat, -MaxFloat);
		const Vector2 b(MaxFloat, MaxFloat);

		const float actual = Vector2::Dot(a, b);
		EXPECT_TRUE(IsNegativeInfinity(actual));
	}

	// A test for Length ()

	TEST(Vector2, LengthTest)
	{
		const Vector2 a(2.0f, 4.0f);

		const Vector2 target = a;

		const float expected = sqrtf(20);

		const float actual = target.Length();

		EXPECT_EQ(expected, actual);
	}

	// A test for Length ()
	// Length test where length is zero

	TEST(Vector2, LengthTest1)
	{
		Vector2 target;
		target.x = 0.0f;
		target.y = 0.0f;

		const float expected = 0.0f;

		const float actual = target.Length();

		EXPECT_EQ(expected, actual);
	}

	// A test for LengthSquared ()

	TEST(Vector2, LengthSquaredTest)
	{
		const Vector2 a(2.0f, 4.0f);

		const Vector2 target = a;

		const float expected = 20.0f;

		const float actual = target.LengthSquared();

		EXPECT_TRUE(expected == actual);
	}

	// A test for LengthSquared ()
	// LengthSquared test where the result is zero

	TEST(Vector2, LengthSquaredTest1)
	{
		const Vector2 a(0.0f, 0.0f);

		const float expected = 0.0f;
		const float actual = a.LengthSquared();

		EXPECT_EQ(expected, actual);
	}

	// A test for Min (Vector2f, Vector2f)

	TEST(Vector2, MinTest)
	{
		const Vector2 a(-1.0f, 4.0f);
		const Vector2 b(2.0f, 1.0f);

		const Vector2 expected(-1.0f, 1.0f);
		const Vector2 actual = Vector2::Min(a, b);
		EXPECT_TRUE(expected == actual);
	}


	TEST(Vector2, MinMaxCodeCoverageTest)
	{
		const Vector2 min(0, 0);
		const Vector2 max(1, 1);

		// Min.
		Vector2 actual = Vector2::Min(min, max);
		EXPECT_EQ(actual, min);

		actual = Vector2::Min(max, min);
		EXPECT_EQ(actual, min);

		// Max.
		actual = Vector2::Max(min, max);
		EXPECT_EQ(actual, max);

		actual = Vector2::Max(max, min);
		EXPECT_EQ(actual, max);
	}

	// A test for Max (Vector2f, Vector2f)

	TEST(Vector2, MaxTest)
	{
		const Vector2 a(-1.0f, 4.0f);
		const Vector2 b(2.0f, 1.0f);

		const Vector2 expected(2.0f, 4.0f);
		const Vector2 actual = Vector2::Max(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Clamp (Vector2f, Vector2f, Vector2f)

	TEST(Vector2, ClampTest)
	{
		Vector2 a(0.5f, 0.3f);
		Vector2 min(0.0f, 0.1f);
		Vector2 max(1.0f, 1.1f);

		// Normal case.
		// Case N1: specified value is in the range.
		Vector2 expected(0.5f, 0.3f);
		Vector2 actual = Vector2::Clamp(a, min, max);
		EXPECT_EQ(expected, actual);
		// Normal case.
		// Case N2: specified value is bigger than max value.
		a = Vector2(2.0f, 3.0f);
		expected = max;
		actual = Vector2::Clamp(a, min, max);
		EXPECT_EQ(expected, actual);
		// Case N3: specified value is smaller than max value.
		a = Vector2(-1.0f, -2.0f);
		expected = min;
		actual = Vector2::Clamp(a, min, max);
		EXPECT_EQ(expected, actual);
		// Case N4: combination case.
		a = Vector2(-2.0f, 4.0f);
		expected = Vector2(min.x, max.y);
		actual = Vector2::Clamp(a, min, max);
		EXPECT_EQ(expected, actual);

		// User specified min value is bigger than max value.
		max = Vector2(0.0f, 0.1f);
		min = Vector2(1.0f, 1.1f);

		// Case W1: specified value is in the range.
		a = Vector2(0.5f, 0.3f);
		expected = max;
		actual = Vector2::Clamp(a, min, max);
		EXPECT_EQ(expected, actual);

		// Normal case.
		// Case W2: specified value is bigger than max and min value.
		a = Vector2(2.0f, 3.0f);
		expected = max;
		actual = Vector2::Clamp(a, min, max);
		EXPECT_EQ(expected, actual);

		// Case W3: specified value is smaller than min and max value.
		a = Vector2(-1.0f, -2.0f);
		expected = max;
		actual = Vector2::Clamp(a, min, max);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector2f, Vector2f, float)

	TEST(Vector2, LerpTest)
	{
		const Vector2 a(1.0f, 2.0f);
		const Vector2 b(3.0f, 4.0f);

		const float t = 0.5f;

		const Vector2 expected(2.0f, 3.0f);
		const Vector2 actual = Vector2::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector2f, Vector2f, float)
	// Lerp test with factor zero

	TEST(Vector2, LerpTest1)
	{
		const Vector2 a(0.0f, 0.0f);
		const Vector2 b(3.18f, 4.25f);

		const float t = 0.0f;
		const Vector2 expected = Vector2::Zero();
		const Vector2 actual = Vector2::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector2f, Vector2f, float)
	// Lerp test with factor one

	TEST(Vector2, LerpTest2)
	{
		const Vector2 a(0.0f, 0.0f);
		const Vector2 b(3.18f, 4.25f);

		const float t = 1.0f;
		const Vector2 expected(3.18f, 4.25f);
		const Vector2 actual = Vector2::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector2f, Vector2f, float)
	// Lerp test with factor > 1

	TEST(Vector2, LerpTest3)
	{
		const Vector2 a(0.0f, 0.0f);
		const Vector2 b(3.18f, 4.25f);

		const float t = 2.0f;
		const Vector2 expected = b * 2.0f;
		const Vector2 actual = Vector2::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector2f, Vector2f, float)
	// Lerp test with factor < 0

	TEST(Vector2, LerpTest4)
	{
		const Vector2 a(0.0f, 0.0f);
		const Vector2 b(3.18f, 4.25f);

		const float t = -2.0f;
		const Vector2 expected = -(b * 2.0f);
		const Vector2 actual = Vector2::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector2f, Vector2f, float)
	// Lerp test with special float value
	/*
	TEST(Vector2, LerpTest5)
	{
		Vector2 a(45.67f, 90.0f);
		Vector2 b(MaxFloat, -MaxFloat);

		float t = 0.408f;
		Vector2 actual = Vector2::Lerp(a, b, t);
		EXPECT_TRUE(IsPositiveInfinity(actual.x));
		EXPECT_TRUE(IsNegativeInfinity(actual.y));
	}*/

	// A test for Lerp (Vector2f, Vector2f, float)
	// Lerp test from the same point

	TEST(Vector2, LerpTest6)
	{
		const Vector2 a(1.0f, 2.0f);
		const Vector2 b(1.0f, 2.0f);

		const float t = 0.5f;

		const Vector2 expected(1.0f, 2.0f);
		const Vector2 actual = Vector2::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector2f, Vector2f, float)
	// Lerp test with values known to be innacurate with the old lerp impl

	TEST(Vector2, LerpTest7)
	{
		const Vector2 a(0.44728136f);
		const Vector2 b(0.46345946f);

		const float t = 0.26402435f;

		const Vector2 expected(0.45155275f);
		const Vector2 actual = Vector2::Lerp(a, b, t);
		EXPECT_EQ(expected, actual);
	}

	// A test for Lerp (Vector2f, Vector2f, float)
	// Lerp test with values known to be innacurate with the old lerp impl
	// (Old code incorrectly gets 0.33333588)

	TEST(Vector2, LerpTest8)
	{
		const Vector2 a(-100);
		const Vector2 b(0.3333333333f);

		const float t = 1.0f;

		const Vector2 expected(0.3333333333f);
		const Vector2 actual = Vector2::Lerp(a, b, t);
		EXPECT_NEAR(expected.x, actual.x, Epsilon);
		EXPECT_NEAR(expected.y, actual.y, Epsilon);
	}

	// A test for Transform(Vector2f, Matrix4)

	TEST(Vector2, TransformTest)
	{
		const Vector2 v(1.0f, 2.0f);
		Matrix4 m =
			Matrix4::CreateRotationX(ToRadian(30.0f)) *
			Matrix4::CreateRotationY(ToRadian(30.0f)) *
			Matrix4::CreateRotationZ(ToRadian(30.0f));
		m.m41 = 10.0f;
		m.m42 = 20.0f;
		m.m43 = 30.0f;

		const Vector2 expected(10.316987f, 22.183012f);

		const Vector2 actual = Vector2::Transform(v, m);
		EXPECT_EQ(expected, actual);
	}

	// A test for Transform(Vector2f, Matrix3x2)
	/*
	TEST(Vector2, Transform3x2Test)
	{
		Vector2 v(1.0f, 2.0f);
		Matrix3x2 m = Matrix3x2.CreateRotation(ToRadian(30.0f));
		m.M31 = 10.0f;
		m.M32 = 20.0f;

		Vector2 expected(9.866025f, 22.23205f);
		Vector2 actual;

		actual = Vector2::Transform(v, m);
		EXPECT_EQ(expected, actual);
	}*/

	// A test for TransformNormal (Vector2f, Matrix4)

	TEST(Vector2, TransformNormalTest)
	{
		const Vector2 v(1.0f, 2.0f);
		Matrix4 m =
			Matrix4::CreateRotationX(ToRadian(30.0f)) *
			Matrix4::CreateRotationY(ToRadian(30.0f)) *
			Matrix4::CreateRotationZ(ToRadian(30.0f));
		m.m41 = 10.0f;
		m.m42 = 20.0f;
		m.m43 = 30.0f;

		const Vector2 expected(0.3169873f, 2.18301272f);

		const Vector2 actual = Vector2::TransformNormal(v, m);
		EXPECT_EQ(expected, actual);
	}

	// A test for TransformNormal (Vector2f, Matrix3x2)
	/*
	TEST(Vector2, TransformNormal3x2Test)
	{
		Vector2 v(1.0f, 2.0f);
		Matrix3x2 m = Matrix3x2.CreateRotation(ToRadian(30.0f));
		m.M31 = 10.0f;
		m.M32 = 20.0f;

		Vector2 expected(-0.133974612f, 2.232051f);
		Vector2 actual;

		actual = Vector2::TransformNormal(v, m);
		EXPECT_EQ(expected, actual);
	}
	*/
	// A test for Transform (Vector2f, Quaternion)

	TEST(Vector2, TransformByQuaternionTest)
	{
		const Vector2 v(1.0f, 2.0f);

		const Matrix4 m =
			Matrix4::CreateRotationX(ToRadian(30.0f)) *
			Matrix4::CreateRotationY(ToRadian(30.0f)) *
			Matrix4::CreateRotationZ(ToRadian(30.0f));
		const Quaternion q = Quaternion::CreateFromRotationMatrix(m);

		const Vector2 expected = Vector2::Transform(v, m);
		const Vector2 actual = Vector2::Transform(v, q);
		EXPECT_EQ(expected, actual);
	}

	// A test for Transform (Vector2f, Quaternion)
	// Transform Vector2f with zero quaternion

	TEST(Vector2, TransformByQuaternionTest1)
	{
		const Vector2 v(1.0f, 2.0f);
		const Quaternion q;
		const Vector2 expected = v;

		const Vector2 actual = Vector2::Transform(v, q);
		EXPECT_EQ(expected, actual);
	}

	// A test for Transform (Vector2f, Quaternion)
	// Transform Vector2f with identity quaternion

	TEST(Vector2, TransformByQuaternionTest2)
	{
		const Vector2 v(1.0f, 2.0f);
		const Quaternion q = Quaternion::CreateIdentity();
		const Vector2 expected = v;

		const Vector2 actual = Vector2::Transform(v, q);
		EXPECT_EQ(expected, actual);
	}

	// A test for Normalized (Vector2f)

	TEST(Vector2, NormalizeTest)
	{
		const Vector2 a(2.0f, 3.0f);
		const Vector2 expected(0.554700196225229122018341733457f, 0.8320502943378436830275126001855f);

		const Vector2 actual = Vector2::Normalized(a);
		EXPECT_EQ(expected, actual);
	}

	// A test for Normalized (Vector2f)
	// Normalized zero length vector

	TEST(Vector2, NormalizeTest1)
	{
		const Vector2 a; // no parameter, default to 0.0f
		const Vector2 actual = Vector2::Normalized(a);
		EXPECT_EQ(actual, a);
	}

	// A test for Normalized (Vector2f)
	// Normalized infinite length vector

	TEST(Vector2, NormalizeTest2)
	{
		const Vector2 a(MaxFloat, MaxFloat);
		const Vector2 actual = Vector2::Normalized(a);
		const Vector2 expected(0, 0);
		EXPECT_EQ(expected, actual);
	}

	// A test for operator - (Vector2f)

	TEST(Vector2, UnaryNegationTest)
	{
		const Vector2 a(1.0f, 2.0f);

		const Vector2 expected(-1.0f, -2.0f);

		const Vector2 actual = -a;

		EXPECT_EQ(expected, actual);
	}



	// A test for operator - (Vector2f)
	// Negate test with special float value
	/*
	TEST(Vector2, UnaryNegationTest1)
	{
		Vector2 a(MaxFloat, -MaxFloat);

		Vector2 actual = -a;

		EXPECT_TRUE(IsNaN(actual.x));
		EXPECT_TRUE(IsNaN(actual.y));
	}
	*/
	// A test for operator - (Vector2f)
	// Negate test with special float value

	TEST(Vector2, UnaryNegationTest2)
	{
		const Vector2 a(NaN(), 0.0f);
		const Vector2 actual = -a;

		EXPECT_TRUE(IsNaN(actual.x));
		EXPECT_EQ(0.0f, actual.y);
	}

	// A test for operator - (Vector2f, Vector2f)

	TEST(Vector2, SubtractionTest)
	{
		const Vector2 a(1.0f, 3.0f);
		const Vector2 b(2.0f, 1.5f);

		const Vector2 expected(-1.0f, 1.5f);

		const Vector2 actual = a - b;

		EXPECT_EQ(expected, actual);
	}

	// A test for operator * (Vector2f, float)

	TEST(Vector2, MultiplyOperatorTest)
	{
		const Vector2 a(2.0f, 3.0f);
		const float factor = 2.0f;

		const Vector2 expected(4.0f, 6.0f);

		const Vector2 actual = a * factor;
		EXPECT_EQ(expected, actual);
	}

	// A test for operator * (float, Vector2f)

	TEST(Vector2, MultiplyOperatorTest2)
	{
		const Vector2 a(2.0f, 3.0f);
		const float factor = 2.0f;

		const Vector2 expected(4.0f, 6.0f);

		const Vector2 actual = factor * a;
		EXPECT_EQ(expected, actual);
	}

	// A test for operator * (Vector2f, Vector2f)

	TEST(Vector2, MultiplyOperatorTest3)
	{
		const Vector2 a(2.0f, 3.0f);
		const Vector2 b(4.0f, 5.0f);

		const Vector2 expected(8.0f, 15.0f);

		const Vector2 actual = a * b;

		EXPECT_EQ(expected, actual);
	}

	// A test for operator / (Vector2f, float)

	TEST(Vector2, DivisionTest)
	{
		const Vector2 a(2.0f, 3.0f);

		const float div = 2.0f;

		const Vector2 expected(1.0f, 1.5f);

		const Vector2 actual = a / div;

		EXPECT_EQ(expected, actual);
	}

	// A test for operator / (Vector2f, Vector2f)

	TEST(Vector2, DivisionTest1)
	{
		const Vector2 a(2.0f, 3.0f);
		const Vector2 b(4.0f, 5.0f);

		const Vector2 expected(2.0f / 4.0f, 3.0f / 5.0f);

		const Vector2 actual = a / b;

		EXPECT_EQ(expected, actual);
	}

	// A test for operator / (Vector2f, float)
	// Divide by zero

	TEST(Vector2, DivisionTest2)
	{
		const Vector2 a(-2.0f, 3.0f);

		const float div = 0.0f;

		const Vector2 actual = a / div;

		EXPECT_TRUE(IsNegativeInfinity(actual.x));
		EXPECT_TRUE(IsPositiveInfinity(actual.y));
	}

	// A test for operator / (Vector2f, Vector2f)
	// Divide by zero

	TEST(Vector2, DivisionTest3)
	{
		const Vector2 a(0.047f, -3.0f);
		const Vector2 b;

		const Vector2 actual = a / b;

		EXPECT_TRUE(IsPositiveInfinity(actual.x));
		EXPECT_TRUE(IsNegativeInfinity(actual.y));
	}

	// A test for operator + (Vector2f, Vector2f)

	TEST(Vector2, AdditionTest)
	{
		const Vector2 a(1.0f, 2.0f);
		const Vector2 b(3.0f, 4.0f);

		const Vector2 expected(4.0f, 6.0f);

		const Vector2 actual = a + b;

		EXPECT_EQ(expected, actual);
	}

	// A test for Vector2f (float, float)

	TEST(Vector2, ConstructorTest)
	{
		const float x = 1.0f;
		const float y = 2.0f;

		const Vector2 target(x, y);
		EXPECT_EQ(target.x, x);
		EXPECT_EQ(target.y, y);
	}

	// A test for Vector2f ()
	// Constructor with no parameter

	TEST(Vector2, ConstructorTest2)
	{
		const Vector2 target;
		EXPECT_EQ(0.0f, target.x);
		EXPECT_EQ(0.0f, target.y);
	}

	// A test for Vector2f (float, float)
	// Constructor with special floating values

	TEST(Vector2, ConstructorTest3)
	{
		const Vector2 target(NaN(), MaxFloat);
		EXPECT_TRUE(IsNaN(target.x));
		EXPECT_EQ(MaxFloat, target.y);
	}

	// A test for Vector2f (float)
	/*
	TEST(Vector2, ConstructorTest4)
	{
		float value = 1.0f;
		Vector2 target(value);

		Vector2 expected(value, value);
		EXPECT_EQ(expected, target);

		value = 2.0f;
		target = Vector2(value);
		expected = Vector2(value, value);
		EXPECT_EQ(expected, target);
	}
	*/
	// A test for Add (Vector2f, Vector2f)

	TEST(Vector2, AddTest)
	{
		const Vector2 a(1.0f, 2.0f);
		const Vector2 b(5.0f, 6.0f);

		const Vector2 expected(6.0f, 8.0f);

		const Vector2 actual = Vector2::Add(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Divide (Vector2f, float)

	TEST(Vector2, DivideTest)
	{
		const Vector2 a(1.0f, 2.0f);
		const float div = 2.0f;
		const Vector2 expected(0.5f, 1.0f);
		const Vector2 actual = Vector2::Divide(a, div);
		EXPECT_EQ(expected, actual);
	}

	// A test for Divide (Vector2f, Vector2f)

	TEST(Vector2, DivideTest1)
	{
		const Vector2 a(1.0f, 6.0f);
		const Vector2 b(5.0f, 2.0f);

		const Vector2 expected(1.0f / 5.0f, 6.0f / 2.0f);

		const Vector2 actual = Vector2::Divide(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Multiply (Vector2f, float)

	TEST(Vector2, MultiplyTest)
	{
		const Vector2 a(1.0f, 2.0f);
		const float factor = 2.0f;
		const Vector2 expected(2.0f, 4.0f);
		const Vector2 actual = Vector2::Multiply(a, factor);
		EXPECT_EQ(expected, actual);
	}

	// A test for Multiply (float, Vector2f)

	TEST(Vector2, MultiplyTest2)
	{
		const Vector2 a(1.0f, 2.0f);
		const float factor = 2.0f;
		const Vector2 expected(2.0f, 4.0f);
		const Vector2 actual = Vector2::Multiply(factor, a);
		EXPECT_EQ(expected, actual);
	}

	// A test for Multiply (Vector2f, Vector2f)

	TEST(Vector2, MultiplyTest3)
	{
		const Vector2 a(1.0f, 2.0f);
		const Vector2 b(5.0f, 6.0f);

		const Vector2 expected(5.0f, 12.0f);

		const Vector2 actual = Vector2::Multiply(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for Negate (Vector2f)

	TEST(Vector2, NegateTest)
	{
		const Vector2 a(1.0f, 2.0f);

		const Vector2 expected(-1.0f, -2.0f);

		const Vector2 actual = Vector2::Negate(a);
		EXPECT_EQ(expected, actual);
	}

	// A test for operator != (Vector2f, Vector2f)

	TEST(Vector2, InequalityTest)
	{
		const Vector2 a(1.0f, 2.0f);
		Vector2 b(1.0f, 2.0f);

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

	// A test for operator == (Vector2f, Vector2f)

	TEST(Vector2, EqualityTest)
	{
		const Vector2 a(1.0f, 2.0f);
		Vector2 b(1.0f, 2.0f);

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

	// A test for Subtract (Vector2f, Vector2f)

	TEST(Vector2, SubtractTest)
	{
		const Vector2 a(1.0f, 6.0f);
		const Vector2 b(5.0f, 2.0f);

		const Vector2 expected(-4.0f, 4.0f);

		const Vector2 actual = Vector2::Subtract(a, b);
		EXPECT_EQ(expected, actual);
	}

	// A test for UnitX

	TEST(Vector2, UnitXTest)
	{
		const Vector2 val(1.0f, 0.0f);
		EXPECT_EQ(val, Vector2::UnitX());
	}

	// A test for UnitY

	TEST(Vector2, UnitYTest)
	{
		const Vector2 val(0.0f, 1.0f);
		EXPECT_EQ(val, Vector2::UnitY());
	}

	// A test for One

	TEST(Vector2, OneTest)
	{
		const Vector2 val(1.0f, 1.0f);
		EXPECT_EQ(val, Vector2::One());
	}

	// A test for Zero

	TEST(Vector2, ZeroTest)
	{
		const Vector2 val(0.0f, 0.0f);
		EXPECT_EQ(val, Vector2::Zero());
	}

	// A test for Vector2f comparison involving NaN values

	TEST(Vector2, EqualsNanTest)
	{
		const Vector2 a(NaN(), 0);
		const Vector2 b(0, NaN());

		EXPECT_FALSE(a == Vector2::Zero());
		EXPECT_FALSE(b == Vector2::Zero());

		EXPECT_TRUE(a != Vector2::Zero());
		EXPECT_TRUE(b != Vector2::Zero());
	}

	// A test for Reflect (Vector2f, Vector2f)

	TEST(Vector2, ReflectTest)
	{
		const Vector2 a = Vector2::Normalized(Vector2(1.0f, 1.0f));

		// Reflect on XZ plane.
		Vector2 n(0.0f, 1.0f);
		Vector2 expected(a.x, -a.y);
		Vector2 actual = Vector2::Reflect(a, n);
		EXPECT_EQ(expected, actual);

		// Reflect on XY plane.
		n = Vector2(0.0f, 0.0f);
		expected = Vector2(a.x, a.y);
		actual = Vector2::Reflect(a, n);
		EXPECT_EQ(expected, actual);

		// Reflect on YZ plane.
		n = Vector2(1.0f, 0.0f);
		expected = Vector2(-a.x, a.y);
		actual = Vector2::Reflect(a, n);
		EXPECT_EQ(expected, actual);
	}

	// A test for Reflect (Vector2f, Vector2f)
	// Reflection when normal and source are the same

	TEST(Vector2, ReflectTest1)
	{
		Vector2 n(0.45f, 1.28f);
		n = Vector2::Normalized(n);
		const Vector2 a = n;

		const Vector2 expected = -n;
		const Vector2 actual = Vector2::Reflect(a, n);
		EXPECT_EQ(expected, actual);
	}

	// A test for Reflect (Vector2f, Vector2f)
	// Reflection when normal and source are negation

	TEST(Vector2, ReflectTest2)
	{
		Vector2 n(0.45f, 1.28f);
		n = Vector2::Normalized(n);
		const Vector2 a = -n;

		const Vector2 expected = n;
		const Vector2 actual = Vector2::Reflect(a, n);
		EXPECT_EQ(expected, actual);
	}


	TEST(Vector2, AbsTest)
	{
		const Vector2 v1(-2.5f, 2.0f);
		const Vector2 v3 = Vector2::Abs(Vector2(0.0f, -MaxFloat));
		const Vector2 v = Vector2::Abs(v1);
		EXPECT_EQ(2.5f, v.x);
		EXPECT_EQ(2.0f, v.y);
		EXPECT_EQ(0.0f, v3.x);
		EXPECT_EQ(MaxFloat, v3.y);
	}

	/*
	TEST(Vector2, SqrtTest)
	{
		Vector2 v1(-2.5f, 2.0f);
		Vector2 v2(5.5f, 4.5f);
		EXPECT_EQ(2, (int)Vector2::SquareRoot(v2).x);
		EXPECT_EQ(2, (int)Vector2::SquareRoot(v2).y);
		EXPECT_EQ(NaN(), Vector2::SquareRoot(v1).x);
	}*/
}
