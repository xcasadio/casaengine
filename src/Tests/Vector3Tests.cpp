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
		Vector3 v(2.0f, 4.0f, 6.0f);
		EXPECT_NEAR(56.0f, Vector3::Dot(v, v), 0.01f);
	}

	TEST(Vector3, Addition)
	{
		Vector3 v1(1.0f, 2.0f, 3.0f);
		Vector3 v2(2.0f, 4.0f, 6.0f);
		v1 = Vector3::Add(v1, v2);
		EXPECT_NEAR(9.0f, v1.GetZ(), 0.01f);
	}

	TEST(Vector3, OperatorAddition)
	{
		Vector3 v1(1.0f, 2.0f, 3.0f);
		Vector3 v2(2.0f, 4.0f, 6.0f);
		Vector3 v3(2.0f, 4.0f, 6.0f);
		v1 = v1 + v2;
		EXPECT_NEAR(9.0f, v1.GetZ(), 0.01f);
	}

	TEST(Vector3, OperatorEqualAddition)
	{
		Vector3 v1(1.0f, 2.0f, 3.0f);
		Vector3 v2(2.0f, 4.0f, 6.0f);
		v1 += v1 + v2;
		EXPECT_NEAR(12.0f, v1.GetZ(), 0.01f);
	}

	TEST(Vector3, Substraction)
	{
		Vector3 v1(1.0f, 2.0f, 3.0f);
		Vector3 v2(2.0f, 4.0f, 6.0f);
		v1 = Vector3::Subtract(v1, v2);
		EXPECT_NEAR(-3.0f, v1.GetZ(), 0.01f);
	}

	TEST(Vector3, OperatorSubstraction)
	{
		Vector3 v1(1.0f, 2.0f, 3.0f);
		Vector3 v2(2.0f, 4.0f, 6.0f);
		v1 = v1 - v2 - v1;
		EXPECT_NEAR(-6.0f, v1.GetZ(), 0.01f);
	}

	TEST(Vector3, OperatorEqualSubstraction)
	{
		Vector3 v1(1.0f, 2.0f, 3.0f);
		Vector3 v2(2.0f, 4.0f, 6.0f);
		v1 -= v2 - v1;
		EXPECT_NEAR(0.0f, v1.GetZ(), 0.01f);
	}

	TEST(Vector3, SquaredLength)
	{
		Vector3 v(3.0f, 1.0f, 4.0f);
		EXPECT_NEAR(26.0f, v.LengthSquared(), 0.01f);
	}

	TEST(Vector3, Length)
	{
		Vector3 v(3.0f, 0.0f, 4.0f);
		EXPECT_NEAR(5.0f, v.Length(), 0.01f);
	}

	TEST(Vector3, CrossProduct)
	{
		Vector3 v1(3.0f, 2.0f, 5.0f);
		Vector3 v2(4.0f, 6.0f, 1.0f);
		Vector3 v3 = Vector3::Cross(v1, v2);
		EXPECT_NEAR(10.0f, v3.GetZ(), 0.01f);
	}

	TEST(Vector3, LERP)
	{
		Vector3 v1(1.0f, 10.0f, 100.0f);
		Vector3 v2(0.0f, 0.0f, 0.0f);
		Vector3 v3 = Vector3::Lerp(v1, v2, 0.75f);
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
        Vector3 a(1.0f, 0.0f, 0.0f);
        Vector3 b(0.0f, 1.0f, 0.0f);

        Vector3 expected(0.0f, 0.0f, 1.0f);
        Vector3 actual = Vector3::Cross(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Cross (Vector3f, Vector3f)
    // Cross test of the same vector

    TEST(Vector3, CrossTest1)
    {
        Vector3 a(0.0f, 1.0f, 0.0f);
        Vector3 b(0.0f, 1.0f, 0.0f);

        Vector3 expected(0.0f, 0.0f, 0.0f);
        Vector3 actual = Vector3::Cross(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Distance (Vector3f, Vector3f)

    TEST(Vector3, DistanceTest)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);
        Vector3 b(4.0f, 5.0f, 6.0f);

        float expected = sqrtf(27);
        float actual = Vector3::Distance(a, b);

        EXPECT_EQ(expected, actual);
    }

    // A test for Distance (Vector3f, Vector3f)
    // Distance from the same point

    TEST(Vector3, DistanceTest1)
    {
        Vector3 a(1.051f, 2.05f, 3.478f);
        Vector3 b(1.051f, 2.05f, 3.478f);

        float actual = Vector3::Distance(a, b);
        EXPECT_EQ(0.0f, actual);
    }

    // A test for DistanceSquared (Vector3f, Vector3f)

    TEST(Vector3, DistanceSquaredTest)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);
        Vector3 b(4.0f, 5.0f, 6.0f);

        float expected = 27.0f;
        float actual = Vector3::DistanceSquared(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Dot (Vector3f, Vector3f)

    TEST(Vector3, DotTest)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);
        Vector3 b(4.0f, 5.0f, 6.0f);

        float expected = 32.0f;
        float actual  = Vector3::Dot(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Dot (Vector3f, Vector3f)
    // Dot test for perpendicular vector

    TEST(Vector3, DotTest1)
    {
        Vector3 a(1.55f, 1.55f, 1);
        Vector3 b(2.5f, 3, 1.5f);
        Vector3 c = Vector3::Cross(a, b);

        float expected = 0.0f;
        float actual1 = Vector3::Dot(a, c);
        float actual2 = Vector3::Dot(b, c);
        EXPECT_NEAR(expected, actual1, 0.01f);
        EXPECT_NEAR(expected, actual2, 0.01f);
    }

    // A test for Length ()

    TEST(Vector3, LengthTest)
    {
        Vector2 a = Vector2(1.0f, 2.0f);

        float z = 3.0f;

        Vector3 target(a.x, a.y, z);

        float expected = sqrtf(14.0f);
        float actual;

        actual = target.Length();
        EXPECT_EQ(expected, actual);
    }

    // A test for Length ()
    // Length test where length is zero

    TEST(Vector3, LengthTest1)
    {
        Vector3 target;

        float expected = 0.0f;
        float actual = target.Length();
        EXPECT_EQ(expected, actual);
    }

    // A test for LengthSquared ()

    TEST(Vector3, LengthSquaredTest)
    {
        Vector2 a = Vector2(1.0f, 2.0f);

        float z = 3.0f;

        Vector3 target(a.x, a.y, z);

        float expected = 14.0f;
        float actual;

        actual = target.LengthSquared();
        EXPECT_EQ(expected, actual);
    }

    // A test for Min (Vector3f, Vector3f)

    TEST(Vector3, MinTest)
    {
        Vector3 a(-1.0f, 4.0f, -3.0f);
        Vector3 b(2.0f, 1.0f, -1.0f);

        Vector3 expected(-1.0f, 1.0f, -3.0f);
        Vector3 actual = Vector3::Min(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Max (Vector3f, Vector3f)

    TEST(Vector3, MaxTest)
    {
        Vector3 a(-1.0f, 4.0f, -3.0f);
        Vector3 b(2.0f, 1.0f, -1.0f);

        Vector3 expected(2.0f, 4.0f, -1.0f);
        Vector3 actual = Vector3::Max(a, b);
        EXPECT_EQ(expected, actual);
    }


    TEST(Vector3, MinMaxCodeCoverageTest)
    {
        Vector3 min = Vector3::Zero();
        Vector3 max = Vector3::One();
        Vector3 actual;

        // Min.
        actual = Vector3::Min(min, max);
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
        Vector3 a(1.0f, 2.0f, 3.0f);
        Vector3 b(4.0f, 5.0f, 6.0f);

        float t = 0.5f;

        Vector3 expected(2.5f, 3.5f, 4.5f);
        Vector3 actual;

        actual = Vector3::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector3f, Vector3f, float)
    // Lerp test with factor zero

    TEST(Vector3, LerpTest1)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);
        Vector3 b(4.0f, 5.0f, 6.0f);

        float t = 0.0f;
        Vector3 expected(1.0f, 2.0f, 3.0f);
        Vector3 actual = Vector3::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector3f, Vector3f, float)
    // Lerp test with factor one

    TEST(Vector3, LerpTest2)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);
        Vector3 b(4.0f, 5.0f, 6.0f);

        float t = 1.0f;
        Vector3 expected(4.0f, 5.0f, 6.0f);
        Vector3 actual = Vector3::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector3f, Vector3f, float)
    // Lerp test with factor > 1

    TEST(Vector3, LerpTest3)
    {
        Vector3 a(0.0f, 0.0f, 0.0f);
        Vector3 b(4.0f, 5.0f, 6.0f);

        float t = 2.0f;
        Vector3 expected(8.0f, 10.0f, 12.0f);
        Vector3 actual = Vector3::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector3f, Vector3f, float)
    // Lerp test with factor < 0

    TEST(Vector3, LerpTest4)
    {
        Vector3 a(0.0f, 0.0f, 0.0f);
        Vector3 b(4.0f, 5.0f, 6.0f);

        float t = -2.0f;
        Vector3 expected(-8.0f, -10.0f, -12.0f);
        Vector3 actual = Vector3::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector3f, Vector3f, float)
    // Lerp test with special float value
    
    TEST(Vector3, LerpTest5)
    {
        Vector3 a(45.67f, 90.0f, 0.0f);
        Vector3 b(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::lowest(), 0);

        float t = 0.408f;
        Vector3 actual = Vector3::Lerp(a, b, t);
        EXPECT_TRUE(IsPositiveInfinity(actual.x));
        EXPECT_TRUE(IsNegativeInfinity(actual.y));
    }
    
    // A test for Lerp (Vector3f, Vector3f, float)
    // Lerp test from the same point

    TEST(Vector3, LerpTest6)
    {
        Vector3 a(1.68f, 2.34f, 5.43f);
        Vector3 b = a;

        float t = 0.18f;
        Vector3 expected(1.68f, 2.34f, 5.43f);
        Vector3 actual = Vector3::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector3f, Vector3f, float)
    // Lerp test with values known to be innacurate with the old lerp impl

    TEST(Vector3, LerpTest7)
    {
        Vector3 a(0.44728136f, 0.44728136f, 0.44728136f);
        Vector3 b(0.46345946f, 0.46345946f, 0.46345946f);

        float t = 0.26402435f;

        Vector3 expected(0.45155275f, 0.45155275f, 0.45155275f);
        Vector3 actual = Vector3::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector3f, Vector3f, float)
    // Lerp test with values known to be innacurate with the old lerp impl
    // (Old code incorrectly gets 0.33333588)

    TEST(Vector3, LerpTest8)
    {
        Vector3 a(-100, -100, -100);
        Vector3 b(0.33333334f, 0.33333334f, 0.33333334f);

        float t = 1.0f;

        Vector3 expected(0.33333334f, 0.33333334f, 0.33333334f);
        Vector3 actual = Vector3::Lerp(a, b, t);
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

        Vector3 expected = -n;
        Vector3 actual = Vector3::Reflect(a, n);
        EXPECT_EQ(expected, actual);
    }

    // A test for Reflect (Vector3f, Vector3f)
    // Reflection when normal and source are negation

    TEST(Vector3, ReflectTest2)
    {
        Vector3 n(0.45f, 1.28f, 0.86f);
        n = Vector3::Normalize(n);
        Vector3 a = -n;

        Vector3 expected = n;
        Vector3 actual = Vector3::Reflect(a, n);
        EXPECT_EQ(expected, actual);
    }

    // A test for Reflect (Vector3f, Vector3f)
    // Reflection when normal and source are perpendicular (a dot n = 0)

    TEST(Vector3, ReflectTest3)
    {
        Vector3 n(0.45f, 1.28f, 0.86f);
        Vector3 temp(1.28f, 0.45f, 0.01f);
        // find a perpendicular vector of n
        Vector3 a = Vector3::Cross(temp, n);

        Vector3 expected = a;
        Vector3 actual = Vector3::Reflect(a, n);

        EXPECT_NEAR(expected.x, actual.x, 0.01f);
        EXPECT_NEAR(expected.y, actual.y, 0.01f);
        EXPECT_NEAR(expected.z, actual.z, 0.01f);
    }

    // A test for Transform(Vector3f, Matrix4)

    TEST(Vector3, TransformTest)
    {
        Vector3 v(1.0f, 2.0f, 3.0f);
        Matrix4 m =
            Matrix4::CreateRotationX(ToRadian(30.0f)) *
            Matrix4::CreateRotationY(ToRadian(30.0f)) *
            Matrix4::CreateRotationZ(ToRadian(30.0f));
        m.m41 = 10.0f;
        m.m42 = 20.0f;
        m.m43 = 30.0f;

        Vector3 expected(12.191987f, 21.533493f, 32.616024f);
        Vector3 actual;
        
        actual = m.Transform(v);
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
        Vector3 v(1.0f, 2.0f, 3.0f);
        Matrix4 m =
            Matrix4::CreateRotationX(ToRadian(30.0f)) *
            Matrix4::CreateRotationY(ToRadian(30.0f)) *
            Matrix4::CreateRotationZ(ToRadian(30.0f));
        m.m41 = 10.0f;
        m.m42 = 20.0f;
        m.m43 = 30.0f;

        Vector3 expected(2.19198728f, 1.53349364f, 2.61602545f);
        Vector3 actual;

        actual = m.TransformNormal(v);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector3f, Quaternion)

    TEST(Vector3, TransformByQuaternionTest)
    {
        Vector3 v(1.0f, 2.0f, 3.0f);

        Matrix4 m =
            Matrix4::CreateRotationX(ToRadian(30.0f)) *
            Matrix4::CreateRotationY(ToRadian(30.0f)) *
            Matrix4::CreateRotationZ(ToRadian(30.0f));
        Quaternion q = Quaternion::CreateFromRotationMatrix(m);

        Vector3 expected = m.Transform(v);
        Vector3 actual = q.Transform(v);

        EXPECT_NEAR(expected.x, actual.x, 0.01f);
        EXPECT_NEAR(expected.y, actual.y, 0.01f);
        EXPECT_NEAR(expected.z, actual.z, 0.01f);
    }

    // A test for Transform (Vector3f, Quaternion)
    // Transform vector3 with zero quaternion

    TEST(Vector3, TransformByQuaternionTest1)
    {
        Vector3 v(1.0f, 2.0f, 3.0f);
        Quaternion q;
        Vector3 expected = v;

        Vector3 actual = q.Transform(v);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector3f, Quaternion)
    // Transform vector3 with identity quaternion

    TEST(Vector3, TransformByQuaternionTest2)
    {
        Vector3 v(1.0f, 2.0f, 3.0f);
        Quaternion q = Quaternion::CreateIdentity();
        Vector3 expected = v;

        Vector3 actual = q.Transform(v);
        EXPECT_EQ(expected, actual);
    }

    // A test for Normalize (Vector3f)

    TEST(Vector3, NormalizeTest)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);

        Vector3 expected(
            0.26726124191242438468455348087975f,
            0.53452248382484876936910696175951f,
            0.80178372573727315405366044263926f);
        Vector3 actual = Vector3::Normalize(a);
        EXPECT_EQ(expected, actual);
    }

    // A test for Normalize (Vector3f)
    // Normalize vector of length one

    TEST(Vector3, NormalizeTest1)
    {
        Vector3 a(1.0f, 0.0f, 0.0f);

        Vector3 expected(1.0f, 0.0f, 0.0f);
        Vector3 actual = Vector3::Normalize(a);
        EXPECT_EQ(expected, actual);
    }

    // A test for Normalize (Vector3f)
    // Normalize vector of length zero

    TEST(Vector3, NormalizeTest2)
    {
        Vector3 a(0.0f, 0.0f, 0.0f);

        Vector3 expected(0.0f, 0.0f, 0.0f);
        Vector3 actual = Vector3::Normalize(a);
        EXPECT_EQ(expected, actual);
    }

    // A test for operator - (Vector3f)

    TEST(Vector3, UnaryNegationTest)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);

        Vector3 expected(-1.0f, -2.0f, -3.0f);
        Vector3 actual;

        actual = -a;

        EXPECT_EQ(expected, actual);
    }


    TEST(Vector3, UnaryNegationTest1)
    {
        Vector3 a = -Vector3(NaN(), std::numeric_limits<float>::max(), std::numeric_limits<float>::lowest());
        Vector3 b = -Vector3(0.0f, 0.0f, 0.0f);
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
        Vector3 a(4.0f, 2.0f, 3.0f);

        Vector3 b(1.0f, 5.0f, 7.0f);

        Vector3 expected(3.0f, -3.0f, -4.0f);
        Vector3 actual;

        actual = a - b;

        EXPECT_EQ(expected, actual);
    }

    // A test for operator * (Vector3f, float)

    TEST(Vector3, MultiplyOperatorTest)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);

        float factor = 2.0f;

        Vector3 expected(2.0f, 4.0f, 6.0f);
        Vector3 actual;

        actual = a * factor;

        EXPECT_EQ(expected, actual);
    }

    // A test for operator * (float, Vector3f)

    TEST(Vector3, MultiplyOperatorTest2)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);

        const float factor = 2.0f;

        Vector3 expected(2.0f, 4.0f, 6.0f);
        Vector3 actual;

        actual = factor * a;

        EXPECT_EQ(expected, actual);
    }

    // A test for operator * (Vector3f, Vector3f)

    TEST(Vector3, MultiplyOperatorTest3)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);

        Vector3 b(4.0f, 5.0f, 6.0f);

        Vector3 expected(4.0f, 10.0f, 18.0f);
        Vector3 actual = a * b;

        EXPECT_EQ(expected, actual);
    }

    // A test for operator / (Vector3f, float)

    TEST(Vector3, DivisionTest)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);

        float div = 2.0f;

        Vector3 expected(0.5f, 1.0f, 1.5f);
        Vector3 actual = a / div;

        EXPECT_EQ(expected, actual);
    }

    // A test for operator / (Vector3f, Vector3f)

    TEST(Vector3, DivisionTest1)
    {
        Vector3 a(4.0f, 2.0f, 3.0f);

        Vector3 b(1.0f, 5.0f, 6.0f);

        Vector3 expected(4.0f, 0.4f, 0.5f);
        Vector3 actual = a / b;

        EXPECT_EQ(expected, actual);
    }

    // A test for operator / (Vector3f, Vector3f)
    // Divide by zero
    
    TEST(Vector3, DivisionTest2)
    {
        Vector3 a(-2.0f, 3.0f, MaxFloat);

        float div = 0.0f;

        Vector3 actual = a / div;

        EXPECT_TRUE(IsNegativeInfinity(actual.x));
        EXPECT_TRUE(IsPositiveInfinity(actual.y));
        EXPECT_TRUE(IsPositiveInfinity(actual.z));
    }

    // A test for operator / (Vector3f, Vector3f)
    // Divide by zero

    TEST(Vector3, DivisionTest3)
    {
        Vector3 a(0.047f, -3.0f, std::numeric_limits<float>::lowest());
        Vector3 b;

        Vector3 actual = a / b;

        EXPECT_TRUE(IsPositiveInfinity(actual.x));
        EXPECT_TRUE(IsNegativeInfinity(actual.y));
        EXPECT_TRUE(IsNegativeInfinity(actual.z));
    }
    
    // A test for operator + (Vector3f, Vector3f)

    TEST(Vector3, AdditionTest)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);
        Vector3 b(4.0f, 5.0f, 6.0f);

        Vector3 expected(5.0f, 7.0f, 9.0f);
        Vector3 actual = a + b;

        EXPECT_EQ(expected, actual);
    }

    // A test for Vector3f (float, float, float)

    TEST(Vector3, ConstructorTest)
    {
        float x = 1.0f;
        float y = 2.0f;
        float z = 3.0f;

        Vector3 target(x, y, z);
        EXPECT_EQ(target.x, x);
        EXPECT_EQ(target.y, y);
		EXPECT_EQ(target.z, z);
    }

    TEST(Vector3, ConstructorTest3)
    {
        Vector3 a;

        EXPECT_EQ(0.0f, a.x);
        EXPECT_EQ(0.0f, a.y);
        EXPECT_EQ(0.0f, a.z);
    }

    // A test for Vector2f (float, float)
    // Constructor with special floating values
    
    TEST(Vector3, ConstructorTest4)
    {
        Vector3 target(NaN(), MaxFloat, std::numeric_limits<float>::infinity());

        EXPECT_TRUE(IsNaN(target.x));
        EXPECT_TRUE(MaxFloat == target.y);
        EXPECT_TRUE(IsPositiveInfinity(target.z));
    }
    
    // A test for Add (Vector3f, Vector3f)

    TEST(Vector3, AddTest)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);
        Vector3 b(5.0f, 6.0f, 7.0f);

        Vector3 expected(6.0f, 8.0f, 10.0f);
        Vector3 actual;

        actual = Vector3::Add(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Divide (Vector3f, float)

    TEST(Vector3, DivideTest)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);
        float div = 2.0f;
        Vector3 expected(0.5f, 1.0f, 1.5f);
        Vector3 actual;
        actual = Vector3::Divide(a, div);
        EXPECT_EQ(expected, actual);
    }

    // A test for Divide (Vector3f, Vector3f)

    TEST(Vector3, DivideTest1)
    {
        Vector3 a(1.0f, 6.0f, 7.0f);
        Vector3 b(5.0f, 2.0f, 3.0f);

        Vector3 expected(1.0f / 5.0f, 6.0f / 2.0f, 7.0f / 3.0f);
        Vector3 actual;

        actual = Vector3::Divide(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Multiply (Vector3f, float)

    TEST(Vector3, MultiplyTest)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);
        const float factor = 2.0f;
        Vector3 expected(2.0f, 4.0f, 6.0f);
        Vector3 actual = Vector3::Multiply(a, factor);
        EXPECT_EQ(expected, actual);
    }

    // A test for Multiply (float, Vector3f)

    TEST(Vector3, MultiplyTest2)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);
        const float factor = 2.0f;
        Vector3 expected(2.0f, 4.0f, 6.0f);
        Vector3 actual = Vector3::Multiply(factor, a);
        EXPECT_EQ(expected, actual);
    }

    // A test for Multiply (Vector3f, Vector3f)

    TEST(Vector3, MultiplyTest3)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);
        Vector3 b(5.0f, 6.0f, 7.0f);

        Vector3 expected(5.0f, 12.0f, 21.0f);
        Vector3 actual;

        actual = Vector3::Multiply(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Negate (Vector3f)

    TEST(Vector3, NegateTest)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);

        Vector3 expected(-1.0f, -2.0f, -3.0f);
        Vector3 actual;

        actual = Vector3::Negate(a);
        EXPECT_EQ(expected, actual);
    }

    // A test for operator != (Vector3f, Vector3f)

    TEST(Vector3, InequalityTest)
    {
        Vector3 a(1.0f, 2.0f, 3.0f);
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
        Vector3 a(1.0f, 6.0f, 3.0f);
        Vector3 b(5.0f, 2.0f, 3.0f);

        Vector3 expected(-4.0f, 4.0f, 0.0f);
        Vector3 actual;

        actual = Vector3::Subtract(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for One

    TEST(Vector3, OneTest)
    {
        Vector3 val(1.0f, 1.0f, 1.0f);
        EXPECT_EQ(val, Vector3::One());
    }

    // A test for UnitX

    TEST(Vector3, UnitXTest)
    {
        Vector3 val(1.0f, 0.0f, 0.0f);
        EXPECT_EQ(val, Vector3::UnitX());
    }

    // A test for UnitY

    TEST(Vector3, UnitYTest)
    {
        Vector3 val(0.0f, 1.0f, 0.0f);
        EXPECT_EQ(val, Vector3::UnitY());
    }

    // A test for UnitZ

    TEST(Vector3, UnitZTest)
    {
        Vector3 val(0.0f, 0.0f, 1.0f);
        EXPECT_EQ(val, Vector3::UnitZ());
    }

    // A test for Zero

    TEST(Vector3, ZeroTest)
    {
        Vector3 val(0.0f, 0.0f, 0.0f);
        EXPECT_EQ(val, Vector3::Zero());
    }

    // A test for Vector3f comparison involving NaN values

    TEST(Vector3, EqualsNanTest)
    {
        Vector3 a(NaN(), 0, 0);
        Vector3 b(0, NaN(), 0);
        Vector3 c(0, 0, NaN());

        EXPECT_FALSE(a == Vector3::Zero());
        EXPECT_FALSE(b == Vector3::Zero());
        EXPECT_FALSE(c == Vector3::Zero());

        EXPECT_TRUE(a != Vector3::Zero());
        EXPECT_TRUE(b != Vector3::Zero());
        EXPECT_TRUE(c != Vector3::Zero());
    }


    TEST(Vector3, AbsTest)
    {
        Vector3 v1(-2.5f, 2.0f, 0.5f);
        Vector3 v3 = Vector3::Abs(Vector3(0.0f, std::numeric_limits<float>::lowest(), NaN()));
        Vector3 v = Vector3::Abs(v1);
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
