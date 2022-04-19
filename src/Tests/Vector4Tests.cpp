#include "gtest/gtest.h"

#include "Maths/Math.h"
#include "Maths/Matrix4.h"
#include "Maths/Quaternion.h"
#include "Maths/Vector2.h"
#include "Maths/Vector3.h"
#include "Maths/Vector4.h"

using namespace CasaEngine;

namespace CasaEngineTests
{
    // A test for DistanceSquared (Vector4f, Vector4f)

    TEST(Vector4, DistanceSquaredTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 b(5.0f, 6.0f, 7.0f, 8.0f);

        float expected = 64.0f;
        float actual;

        actual = Vector4::DistanceSquared(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Distance (Vector4f, Vector4f)

    TEST(Vector4, DistanceTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 b(5.0f, 6.0f, 7.0f, 8.0f);

        float expected = 8.0f;
        float actual;

        actual = Vector4::Distance(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Dot (Vector4f, Vector4f)

    TEST(Vector4, DotTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 b(5.0f, 6.0f, 7.0f, 8.0f);

        float expected = 70.0f;
        float actual;

        actual = Vector4::Dot(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Dot (Vector4f, Vector4f)
    // Dot test for perpendicular vector

    TEST(Vector4, DotTest1)
    {
        Vector3 a = Vector3(1.55f, 1.55f, 1);
        Vector3 b = Vector3(2.5f, 3, 1.5f);
        Vector3 c = Vector3::Cross(a, b);

        Vector4 d(a.x, a.y, a.z, 0);
        Vector4 e(c.x, c.y, c.z, 0);

        float actual = Vector4::Dot(d, e);
        EXPECT_EQ(0.0f, actual);
    }

    // A test for Length ()

    TEST(Vector4, LengthTest)
    {
        Vector3 a = Vector3(1.0f, 2.0f, 3.0f);
        float w = 4.0f;

        Vector4 target(a.x, a.y, a.z, w);

        float expected = sqrtf(30.0f);
        float actual;

        actual = target.Length();

        EXPECT_EQ(expected, actual);
    }

    // A test for Length ()
    // Length test where length is zero

    TEST(Vector4, LengthTest1)
    {
        Vector4 target;

        float expected = 0.0f;
        float actual = target.Length();

        EXPECT_EQ(expected, actual);
    }

    // A test for LengthSquared ()

    TEST(Vector4, LengthSquaredTest)
    {
        Vector3 a = Vector3(1.0f, 2.0f, 3.0f);
        float w = 4.0f;

        Vector4 target(a.x, a.y, a.z, w);

        float expected = 30;
        float actual;

        actual = target.LengthSquared();

        EXPECT_EQ(expected, actual);
    }

    // A test for Min (Vector4f, Vector4f)

    TEST(Vector4, MinTest)
    {
        Vector4 a(-1.0f, 4.0f, -3.0f, 1000.0f);
        Vector4 b(2.0f, 1.0f, -1.0f, 0.0f);

        Vector4 expected(-1.0f, 1.0f, -3.0f, 0.0f);
        Vector4 actual;
        actual = Vector4::Min(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Max (Vector4f, Vector4f)

    TEST(Vector4, MaxTest)
    {
        Vector4 a(-1.0f, 4.0f, -3.0f, 1000.0f);
        Vector4 b(2.0f, 1.0f, -1.0f, 0.0f);

        Vector4 expected(2.0f, 4.0f, -1.0f, 1000.0f);
        Vector4 actual;
        actual = Vector4::Max(a, b);
        EXPECT_EQ(expected, actual);
    }


    TEST(Vector4, MinMaxCodeCoverageTest)
    {
        Vector4 min = Vector4::Zero();
        Vector4 max = Vector4::One();
        Vector4 actual;

        // Min.
        actual = Vector4::Min(min, max);
        EXPECT_EQ(actual, min);

        actual = Vector4::Min(max, min);
        EXPECT_EQ(actual, min);

        // Max.
        actual = Vector4::Max(min, max);
        EXPECT_EQ(actual, max);

        actual = Vector4::Max(max, min);
        EXPECT_EQ(actual, max);
    }

    // A test for Clamp (Vector4f, Vector4f, Vector4f)

    TEST(Vector4, ClampTest)
    {
        Vector4 a(0.5f, 0.3f, 0.33f, 0.44f);
        Vector4 min(0.0f, 0.1f, 0.13f, 0.14f);
        Vector4 max(1.0f, 1.1f, 1.13f, 1.14f);

        // Normal case.
        // Case N1: specified value is in the range.
        Vector4 expected(0.5f, 0.3f, 0.33f, 0.44f);
        Vector4 actual = Vector4::Clamp(a, min, max);
        EXPECT_EQ(expected, actual);

        // Normal case.
        // Case N2: specified value is bigger than max value.
        a = Vector4(2.0f, 3.0f, 4.0f, 5.0f);
        expected = max;
        actual = Vector4::Clamp(a, min, max);
        EXPECT_EQ(expected, actual);

        // Case N3: specified value is smaller than max value.
        a = Vector4(-2.0f, -3.0f, -4.0f, -5.0f);
        expected = min;
        actual = Vector4::Clamp(a, min, max);
        EXPECT_EQ(expected, actual);

        // Case N4: combination case.
        a = Vector4(-2.0f, 0.5f, 4.0f, -5.0f);
        expected = Vector4(min.x, a.y, max.z, min.w);
        actual = Vector4::Clamp(a, min, max);
        EXPECT_EQ(expected, actual);

        // User specified min value is bigger than max value.
        max = Vector4(0.0f, 0.1f, 0.13f, 0.14f);
        min = Vector4(1.0f, 1.1f, 1.13f, 1.14f);

        // Case W1: specified value is in the range.
        a = Vector4(0.5f, 0.3f, 0.33f, 0.44f);
        expected = max;
        actual = Vector4::Clamp(a, min, max);
        EXPECT_EQ(expected, actual);

        // Normal case.
        // Case W2: specified value is bigger than max and min value.
        a = Vector4(2.0f, 3.0f, 4.0f, 5.0f);
        expected = max;
        actual = Vector4::Clamp(a, min, max);
        EXPECT_EQ(expected, actual);

        // Case W3: specified value is smaller than min and max value.
        a = Vector4(-2.0f, -3.0f, -4.0f, -5.0f);
        expected = max;
        actual = Vector4::Clamp(a, min, max);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector4f, Vector4f, float)

    TEST(Vector4, LerpTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 b(5.0f, 6.0f, 7.0f, 8.0f);

        float t = 0.5f;

        Vector4 expected(3.0f, 4.0f, 5.0f, 6.0f);
        Vector4 actual;

        actual = Vector4::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector4f, Vector4f, float)
    // Lerp test with factor zero

    TEST(Vector4, LerpTest1)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 b(4.0f, 5.0f, 6.0f, 7.0f);

        float t = 0.0f;
        Vector4 expected(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 actual = Vector4::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector4f, Vector4f, float)
    // Lerp test with factor one

    TEST(Vector4, LerpTest2)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 b(4.0f, 5.0f, 6.0f, 7.0f);

        float t = 1.0f;
        Vector4 expected(4.0f, 5.0f, 6.0f, 7.0f);
        Vector4 actual = Vector4::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector4f, Vector4f, float)
    // Lerp test with factor > 1

    TEST(Vector4, LerpTest3)
    {
        Vector4 a(0.0f, 0.0f, 0.0f, 0.0f);
        Vector4 b(4.0f, 5.0f, 6.0f, 7.0f);

        float t = 2.0f;
        Vector4 expected(8.0f, 10.0f, 12.0f, 14.0f);
        Vector4 actual = Vector4::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector4f, Vector4f, float)
    // Lerp test with factor < 0

    TEST(Vector4, LerpTest4)
    {
        Vector4 a(0.0f, 0.0f, 0.0f, 0.0f);
        Vector4 b(4.0f, 5.0f, 6.0f, 7.0f);

        float t = -2.0f;
        Vector4 expected = -(b * 2);
        Vector4 actual = Vector4::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector4f, Vector4f, float)
    // Lerp test with special float value

    TEST(Vector4, LerpTest5)
    {
        Vector4 a(45.67f, 90.0f, 0, 0);
        Vector4 b(MaxFloat, -MaxFloat, 0, 0);

        float t = 0.408f;
        Vector4 actual = Vector4::Lerp(a, b, t);
        EXPECT_TRUE(IsPositiveInfinity(actual.x));
        EXPECT_TRUE(IsNegativeInfinity(actual.y));
    }

    // A test for Lerp (Vector4f, Vector4f, float)
    // Lerp test from the same point

    TEST(Vector4, LerpTest6)
    {
        Vector4 a(4.0f, 5.0f, 6.0f, 7.0f);
        Vector4 b(4.0f, 5.0f, 6.0f, 7.0f);

        float t = 0.85f;
        Vector4 expected = a;
        Vector4 actual = Vector4::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector4f, Vector4f, float)
    // Lerp test with values known to be innacurate with the old lerp impl

    TEST(Vector4, LerpTest7)
    {
        Vector4 a(0.44728136f);
        Vector4 b(0.46345946f);

        float t = 0.26402435f;

        Vector4 expected(0.45155275f);
        Vector4 actual = Vector4::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Vector4f, Vector4f, float)
    // Lerp test with values known to be innacurate with the old lerp impl
    // (Old code incorrectly gets 0.33333588)

    TEST(Vector4, LerpTest8)
    {
        Vector4 a(-100);
        Vector4 b(0.33333334f);

        float t = 1.0f;

        Vector4 expected(0.33333334f);
        Vector4 actual = Vector4::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector2f, Matrix4)

    TEST(Vector4, TransformTest1)
    {
        Vector2 v = Vector2(1.0f, 2.0f);

        Matrix4 m =
            Matrix4::CreateRotationX(ToRadian(30.0f)) *
            Matrix4::CreateRotationY(ToRadian(30.0f)) *
            Matrix4::CreateRotationZ(ToRadian(30.0f));
        m.m41 = 10.0f;
        m.m42 = 20.0f;
        m.m43 = 30.0f;

        Vector4 expected(10.316987f, 22.183012f, 30.3660259f, 1.0f);
        Vector4 actual;

        actual = Vector4::Transform(v, m);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector3f, Matrix4)

    TEST(Vector4, TransformTest2)
    {
        Vector3 v = Vector3(1.0f, 2.0f, 3.0f);

        Matrix4 m =
            Matrix4::CreateRotationX(ToRadian(30.0f)) *
            Matrix4::CreateRotationY(ToRadian(30.0f)) *
            Matrix4::CreateRotationZ(ToRadian(30.0f));
        m.m41 = 10.0f;
        m.m42 = 20.0f;
        m.m43 = 30.0f;

        Vector4 expected(12.19198728f, 21.53349376f, 32.61602545f, 1.0f);
        Vector4 actual;

        actual = Vector4::Transform(v, m);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector4f, Matrix4)

    TEST(Vector4, TransformVector4Test)
    {
        Vector4 v(1.0f, 2.0f, 3.0f, 0.0f);

        Matrix4 m =
            Matrix4::CreateRotationX(ToRadian(30.0f)) *
            Matrix4::CreateRotationY(ToRadian(30.0f)) *
            Matrix4::CreateRotationZ(ToRadian(30.0f));
        m.m41 = 10.0f;
        m.m42 = 20.0f;
        m.m43 = 30.0f;

        Vector4 expected(2.19198728f, 1.53349376f, 2.61602545f, 0.0f);
        Vector4 actual;

        actual = Vector4::Transform(v, m);
        EXPECT_EQ(expected, actual);

        //
        v.w = 1.0f;

        expected = Vector4(12.19198728f, 21.53349376f, 32.61602545f, 1.0f);
        actual = Vector4::Transform(v, m);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector4f, Matrix4)
    // Transform vector4 with zero matrix

    TEST(Vector4, TransformVector4Test1)
    {
        Vector4 v(1.0f, 2.0f, 3.0f, 0.0f);
        Matrix4 m = Matrix4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        Vector4 expected(0, 0, 0, 0);

        Vector4 actual = Vector4::Transform(v, m);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector4f, Matrix4)
    // Transform vector4 with identity matrix

    TEST(Vector4, TransformVector4Test2)
    {
        Vector4 v(1.0f, 2.0f, 3.0f, 0.0f);
        Matrix4 m = Matrix4::CreateIdentity();
        Vector4 expected(1.0f, 2.0f, 3.0f, 0.0f);

        Vector4 actual = Vector4::Transform(v, m);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector3f, Matrix4)
    // Transform Vector3f test

    TEST(Vector4, TransformVector3Test)
    {
        Vector4 v = Vector4(1.0f, 2.0f, 3.0f, 1.0f);

        Matrix4 m =
            Matrix4::CreateRotationX(ToRadian(30.0f)) *
            Matrix4::CreateRotationY(ToRadian(30.0f)) *
            Matrix4::CreateRotationZ(ToRadian(30.0f));
        m.m41 = 10.0f;
        m.m42 = 20.0f;
        m.m43 = 30.0f;

        Vector4 expected = Vector4::Transform(v, m);
        Vector4 actual = Vector4::Transform(v, m);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector3f, Matrix4)
    // Transform vector3 with zero matrix

    TEST(Vector4, TransformVector3Test1)
    {
        Vector3 v = Vector3(1.0f, 2.0f, 3.0f);
        Matrix4 m = Matrix4();
        Vector4 expected(0, 0, 0, 0);

        Vector4 actual = Vector4::Transform(v, m);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector3f, Matrix4)
    // Transform vector3 with identity matrix

    TEST(Vector4, TransformVector3Test2)
    {
        Vector3 v = Vector3(1.0f, 2.0f, 3.0f);
        Matrix4 m = Matrix4::CreateIdentity();
        Vector4 expected(1.0f, 2.0f, 3.0f, 1.0f);

        Vector4 actual = Vector4::Transform(v, m);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector2f, Matrix4)
    // Transform Vector2f test

    TEST(Vector4, TransformVector2Test)
    {
        Vector4 v = Vector4(1.0f, 2.0f, 0.0f, 1.0f);

        Matrix4 m =
            Matrix4::CreateRotationX(ToRadian(30.0f)) *
            Matrix4::CreateRotationY(ToRadian(30.0f)) *
            Matrix4::CreateRotationZ(ToRadian(30.0f));
        m.m41 = 10.0f;
        m.m42 = 20.0f;
        m.m43 = 30.0f;

        Vector4 expected = Vector4::Transform(v, m);
        Vector4 actual = Vector4::Transform(v, m);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector2f, Matrix4)
    // Transform Vector2f with zero matrix

    TEST(Vector4, TransformVector2Test1)
    {
        Vector2 v = Vector2(1.0f, 2.0f);
        Matrix4 m = Matrix4();
        Vector4 expected(0, 0, 0, 0);

        Vector4 actual = Vector4::Transform(v, m);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector2f, Matrix4)
    // Transform vector2 with identity matrix

    TEST(Vector4, TransformVector2Test2)
    {
        Vector2 v = Vector2(1.0f, 2.0f);
        Matrix4 m = Matrix4::CreateIdentity();
        Vector4 expected(1.0f, 2.0f, 0, 1.0f);

        Vector4 actual = Vector4::Transform(v, m);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector2f, Quaternion)

    TEST(Vector4, TransformVector2QuaternionTest)
    {
        Vector2 v = Vector2(1.0f, 2.0f);

        Matrix4 m =
            Matrix4::CreateRotationX(ToRadian(30.0f)) *
            Matrix4::CreateRotationY(ToRadian(30.0f)) *
            Matrix4::CreateRotationZ(ToRadian(30.0f));

        Quaternion q = Quaternion::CreateFromRotationMatrix(m);

        Vector4 expected = Vector4::Transform(v, m);
        Vector4 actual;

        actual = Vector4::Transform(v, q);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector3f, Quaternion)

    TEST(Vector4, TransformVector3Quaternion)
    {
        Vector3 v = Vector3(1.0f, 2.0f, 3.0f);

        Matrix4 m =
            Matrix4::CreateRotationX(ToRadian(30.0f)) *
            Matrix4::CreateRotationY(ToRadian(30.0f)) *
            Matrix4::CreateRotationZ(ToRadian(30.0f));
        Quaternion q = Quaternion::CreateFromRotationMatrix(m);

        Vector4 expected = Vector4::Transform(v, m);
        Vector4 actual;

        actual = Vector4::Transform(v, q);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector4f, Quaternion)

    TEST(Vector4, TransformVector4QuaternionTest)
    {
        Vector4 v(1.0f, 2.0f, 3.0f, 0.0f);

        Matrix4 m =
            Matrix4::CreateRotationX(ToRadian(30.0f)) *
            Matrix4::CreateRotationY(ToRadian(30.0f)) *
            Matrix4::CreateRotationZ(ToRadian(30.0f));
        Quaternion q = Quaternion::CreateFromRotationMatrix(m);

        Vector4 expected = Vector4::Transform(v, m);
        Vector4 actual;

        actual = Vector4::Transform(v, q);
        EXPECT_EQ(expected, actual);

        //
        v.w = 1.0f;
        expected.w = 1.0f;
        actual = Vector4::Transform(v, q);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector4f, Quaternion)
    // Transform vector4 with zero quaternion

    TEST(Vector4, TransformVector4QuaternionTest1)
    {
        Vector4 v(1.0f, 2.0f, 3.0f, 0.0f);
        Quaternion q = Quaternion();
        Vector4 expected = v;

        Vector4 actual = Vector4::Transform(v, q);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector4f, Quaternion)
    // Transform vector4 with identity matrix

    TEST(Vector4, TransformVector4QuaternionTest2)
    {
        Vector4 v(1.0f, 2.0f, 3.0f, 0.0f);
        Quaternion q = Quaternion::CreateIdentity();
        Vector4 expected(1.0f, 2.0f, 3.0f, 0.0f);

        Vector4 actual = Vector4::Transform(v, q);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector3f, Quaternion)
    // Transform Vector3f test
    
    TEST(Vector4, TransformVector3QuaternionTest)
    {
        Vector3 v = Vector3(1.0f, 2.0f, 3.0f);

        Matrix4 m =
            Matrix4::CreateRotationX(ToRadian(30.0f)) *
            Matrix4::CreateRotationY(ToRadian(30.0f)) *
            Matrix4::CreateRotationZ(ToRadian(30.0f));
        Quaternion q = Quaternion::CreateFromRotationMatrix(m);

        Vector4 expected = Vector4::Transform(v, m);
        Vector4 actual = Vector4::Transform(v, q);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector3f, Quaternion)
    // Transform vector3 with zero quaternion

    TEST(Vector4, TransformVector3QuaternionTest1)
    {
        Vector4 v = Vector4(1.0f, 2.0f, 3.0f, 1.0f);
        Quaternion q;
        Vector4 expected(1.0f, 2.0f, 3.0f, 1.0f);

        Vector4 actual = Vector4::Transform(v, q);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector3f, Quaternion)
    // Transform vector3 with identity quaternion

    TEST(Vector4, TransformVector3QuaternionTest2)
    {
        Vector3 v = Vector3(1.0f, 2.0f, 3.0f);
        Quaternion q = Quaternion::CreateIdentity();
        Vector4 expected(1.0f, 2.0f, 3.0f, 1.0f);

        Vector4 actual = Vector4::Transform(v, q);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector2f, Quaternion)
    // Transform Vector2f by quaternion test

    TEST(Vector4, TransformVector2QuaternionTest0)
    {
        Vector2 v = Vector2(1.0f, 2.0f);

        Matrix4 m =
            Matrix4::CreateRotationX(ToRadian(30.0f)) *
            Matrix4::CreateRotationY(ToRadian(30.0f)) *
            Matrix4::CreateRotationZ(ToRadian(30.0f));
        Quaternion q = Quaternion::CreateFromRotationMatrix(m);

        Vector4 expected = Vector4::Transform(v, m);
        Vector4 actual = Vector4::Transform(v, q);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector2f, Quaternion)
    // Transform Vector2f with zero quaternion

    TEST(Vector4, TransformVector2QuaternionTest1)
    {
        Vector2 v = Vector2(1.0f, 2.0f);
        Quaternion q = Quaternion();
        Vector4 expected(1.0f, 2.0f, 0, 1.0f);

        Vector4 actual = Vector4::Transform(v, q);
        EXPECT_EQ(expected, actual);
    }

    // A test for Transform (Vector2f, Matrix4)
    // Transform vector2 with identity Quaternion

    TEST(Vector4, TransformVector2QuaternionTest2)
    {
        Vector2 v = Vector2(1.0f, 2.0f);
        Quaternion q = Quaternion::CreateIdentity();
        Vector4 expected(1.0f, 2.0f, 0, 1.0f);

        Vector4 actual = Vector4::Transform(v, q);
        EXPECT_EQ(expected, actual);
    }

    // A test for Normalized (Vector4f)

    TEST(Vector4, NormalizeTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);

        Vector4 expected(
            0.1825741858350553711523232609336f,
            0.3651483716701107423046465218672f,
            0.5477225575051661134569697828008f,
            0.7302967433402214846092930437344f);
        Vector4 actual;

        actual = Vector4::Normalize(a);
        EXPECT_EQ(expected, actual);
    }

    // A test for Normalized (Vector4f)
    // Normalized vector of length one

    TEST(Vector4, NormalizeTest1)
    {
        Vector4 a(1.0f, 0.0f, 0.0f, 0.0f);

        Vector4 expected(1.0f, 0.0f, 0.0f, 0.0f);
        Vector4 actual = Vector4::Normalize(a);
        EXPECT_EQ(expected, actual);
    }

    // A test for Normalized (Vector4f)
    // Normalized vector of length zero

    TEST(Vector4, NormalizeTest2)
    {
        Vector4 a(0.0f, 0.0f, 0.0f, 0.0f);

        Vector4 expected(0.0f, 0.0f, 0.0f, 0.0f);
        Vector4 actual = Vector4::Normalize(a);
        EXPECT_TRUE(IsNaN(actual.x) && IsNaN(actual.y) && IsNaN(actual.z) && IsNaN(actual.w));
    }

    // A test for operator - (Vector4f)

    TEST(Vector4, UnaryNegationTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);

        Vector4 expected(-1.0f, -2.0f, -3.0f, -4.0f);
        Vector4 actual;

        actual = -a;

        EXPECT_EQ(expected, actual);
    }

    // A test for operator - (Vector4f, Vector4f)

    TEST(Vector4, SubtractionTest)
    {
        Vector4 a(1.0f, 6.0f, 3.0f, 4.0f);
        Vector4 b(5.0f, 2.0f, 3.0f, 9.0f);

        Vector4 expected(-4.0f, 4.0f, 0.0f, -5.0f);
        Vector4 actual;

        actual = a - b;

        EXPECT_EQ(expected, actual);
    }

    // A test for operator * (Vector4f, float)

    TEST(Vector4, MultiplyOperatorTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);

        const float factor = 2.0f;

        Vector4 expected(2.0f, 4.0f, 6.0f, 8.0f);
        Vector4 actual;

        actual = a * factor;
        EXPECT_EQ(expected, actual);
    }

    // A test for operator * (float, Vector4f)

    TEST(Vector4, MultiplyOperatorTest2)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);

        const float factor = 2.0f;
        Vector4 expected(2.0f, 4.0f, 6.0f, 8.0f);
        Vector4 actual;

        actual = factor * a;
        EXPECT_EQ(expected, actual);
    }

    // A test for operator * (Vector4f, Vector4f)

    TEST(Vector4, MultiplyOperatorTest3)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 b(5.0f, 6.0f, 7.0f, 8.0f);

        Vector4 expected(5.0f, 12.0f, 21.0f, 32.0f);
        Vector4 actual;

        actual = a * b;

        EXPECT_EQ(expected, actual);
    }

    // A test for operator / (Vector4f, float)

    TEST(Vector4, DivisionTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);

        float div = 2.0f;

        Vector4 expected(0.5f, 1.0f, 1.5f, 2.0f);
        Vector4 actual;

        actual = a / div;

        EXPECT_EQ(expected, actual);
    }

    // A test for operator / (Vector4f, Vector4f)

    TEST(Vector4, DivisionTest1)
    {
        Vector4 a(1.0f, 6.0f, 7.0f, 4.0f);
        Vector4 b(5.0f, 2.0f, 3.0f, 8.0f);

        Vector4 expected(1.0f / 5.0f, 6.0f / 2.0f, 7.0f / 3.0f, 4.0f / 8.0f);
        Vector4 actual;

        actual = a / b;

        EXPECT_EQ(expected, actual);
    }

    // A test for operator / (Vector4f, Vector4f)
    // Divide by zero

    TEST(Vector4, DivisionTest2)
    {
        Vector4 a(-2.0f, 3.0f, MaxFloat, NaN());

        float div = 0.0f;

        Vector4 actual = a / div;

        EXPECT_TRUE(IsNegativeInfinity(actual.x));
        EXPECT_TRUE(IsPositiveInfinity(actual.y));
        EXPECT_TRUE(IsPositiveInfinity(actual.z));
        EXPECT_TRUE(IsNaN(actual.w));
    }

    // A test for operator / (Vector4f, Vector4f)
    // Divide by zero

    TEST(Vector4, DivisionTest3)
    {
        Vector4 a(0.047f, -3.0f, -MaxFloat, -MaxFloat);
        Vector4 b;

        Vector4 actual = a / b;

        EXPECT_TRUE(IsPositiveInfinity(actual.x));
        EXPECT_TRUE(IsNegativeInfinity(actual.y));
        EXPECT_TRUE(IsNegativeInfinity(actual.z));
        EXPECT_TRUE(IsNegativeInfinity(actual.w));
    }

    // A test for operator + (Vector4f, Vector4f)

    TEST(Vector4, AdditionTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 b(5.0f, 6.0f, 7.0f, 8.0f);

        Vector4 expected(6.0f, 8.0f, 10.0f, 12.0f);
        Vector4 actual;

        actual = a + b;

        EXPECT_EQ(expected, actual);
    }


    TEST(Vector4, OperatorAddTest)
    {
        Vector4 v1(2.5f, 2.0f, 3.0f, 3.3f);
        Vector4 v2(5.5f, 4.5f, 6.5f, 7.5f);

        Vector4 v3 = v1 + v2;
        Vector4 v5(-1.0f, 0.0f, 0.0f, NaN());
        Vector4 v4 = v1 + v5;
        EXPECT_EQ(8.0f, v3.x);
        EXPECT_EQ(6.5f, v3.y);
        EXPECT_EQ(9.5f, v3.z);
        EXPECT_EQ(10.8f, v3.w);
        EXPECT_EQ(1.5f, v4.x);
        EXPECT_EQ(2.0f, v4.y);
        EXPECT_EQ(3.0f, v4.z);
        EXPECT_TRUE(IsNaN(v4.w));
    }

    // A test for Vector4f (float, float, float, float)

    TEST(Vector4, ConstructorTest)
    {
        float x = 1.0f;
        float y = 2.0f;
        float z = 3.0f;
        float w = 4.0f;

        Vector4 target(x, y, z, w);

        EXPECT_EQ(target.x, x);
        EXPECT_EQ(target.y, y);
        EXPECT_EQ(target.z, z);
        EXPECT_EQ(target.w, w);
    }
    
    // A test for Vector4f ()
    // Constructor with no parameter

    TEST(Vector4, ConstructorTest4)
    {
        Vector4 a;

        EXPECT_EQ(0.0f, a.x);
        EXPECT_EQ(0.0f, a.y);
        EXPECT_EQ(0.0f, a.z);
        EXPECT_EQ(0.0f, a.w);
    }

    // A test for Vector4f ()
    // Constructor with special floating values

    TEST(Vector4, ConstructorTest5)
    {
        Vector4 target(NaN(), MaxFloat, MaxFloat, Epsilon);

        EXPECT_TRUE(IsNaN(target.x));
        EXPECT_TRUE(MaxFloat, target.y);
        EXPECT_TRUE(IsPositiveInfinity(target.z));
        EXPECT_TRUE(Epsilon, target.w);
    }
    
    // A test for Add (Vector4f, Vector4f)

    TEST(Vector4, AddTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 b(5.0f, 6.0f, 7.0f, 8.0f);

        Vector4 expected(6.0f, 8.0f, 10.0f, 12.0f);
        Vector4 actual;

        actual = Vector4::Add(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Divide (Vector4f, float)

    TEST(Vector4, DivideTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        float div = 2.0f;
        Vector4 expected(0.5f, 1.0f, 1.5f, 2.0f);
        Vector4 actual;
        actual = Vector4::Divide(a, div);
        EXPECT_EQ(expected, actual);
    }

    // A test for Divide (Vector4f, Vector4f)

    TEST(Vector4, DivideTest1)
    {
        Vector4 a(1.0f, 6.0f, 7.0f, 4.0f);
        Vector4 b(5.0f, 2.0f, 3.0f, 8.0f);

        Vector4 expected(1.0f / 5.0f, 6.0f / 2.0f, 7.0f / 3.0f, 4.0f / 8.0f);
        Vector4 actual;

        actual = Vector4::Divide(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Multiply (float, Vector4f)

    TEST(Vector4, MultiplyTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        const float factor = 2.0f;
        Vector4 expected(2.0f, 4.0f, 6.0f, 8.0f);
        Vector4 actual = Vector4::Multiply(factor, a);
        EXPECT_EQ(expected, actual);
    }

    // A test for Multiply (Vector4f, float)

    TEST(Vector4, MultiplyTest2)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        const float factor = 2.0f;
        Vector4 expected(2.0f, 4.0f, 6.0f, 8.0f);
        Vector4 actual = Vector4::Multiply(a, factor);
        EXPECT_EQ(expected, actual);
    }

    // A test for Multiply (Vector4f, Vector4f)

    TEST(Vector4, MultiplyTest3)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 b(5.0f, 6.0f, 7.0f, 8.0f);

        Vector4 expected(5.0f, 12.0f, 21.0f, 32.0f);
        Vector4 actual;

        actual = Vector4::Multiply(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Negate (Vector4f)

    TEST(Vector4, NegateTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);

        Vector4 expected(-1.0f, -2.0f, -3.0f, -4.0f);
        Vector4 actual;

        actual = Vector4::Negate(a);
        EXPECT_EQ(expected, actual);
    }

    // A test for operator != (Vector4f, Vector4f)

    TEST(Vector4, InequalityTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 b(1.0f, 2.0f, 3.0f, 4.0f);

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

    // A test for operator == (Vector4f, Vector4f)

    TEST(Vector4, EqualityTest)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 b(1.0f, 2.0f, 3.0f, 4.0f);

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

    // A test for Subtract (Vector4f, Vector4f)

    TEST(Vector4, SubtractTest)
    {
        Vector4 a(1.0f, 6.0f, 3.0f, 4.0f);
        Vector4 b(5.0f, 2.0f, 3.0f, 9.0f);

        Vector4 expected(-4.0f, 4.0f, 0.0f, -5.0f);
        Vector4 actual;

        actual = Vector4::Subtract(a, b);

        EXPECT_EQ(expected, actual);
    }

    // A test for UnitW

    TEST(Vector4, UnitWTest)
    {
        Vector4 val(0.0f, 0.0f, 0.0f, 1.0f);
        EXPECT_EQ(val, Vector4::UnitW());
    }

    // A test for UnitX

    TEST(Vector4, UnitXTest)
    {
        Vector4 val(1.0f, 0.0f, 0.0f, 0.0f);
        EXPECT_EQ(val, Vector4::UnitX());
    }

    // A test for UnitY

    TEST(Vector4, UnitYTest)
    {
        Vector4 val(0.0f, 1.0f, 0.0f, 0.0f);
        EXPECT_EQ(val, Vector4::UnitY());
    }

    // A test for UnitZ

    TEST(Vector4, UnitZTest)
    {
        Vector4 val(0.0f, 0.0f, 1.0f, 0.0f);
        EXPECT_EQ(val, Vector4::UnitZ());
    }

    // A test for One

    TEST(Vector4, OneTest)
    {
        Vector4 val(1.0f, 1.0f, 1.0f, 1.0f);
        EXPECT_EQ(val, Vector4::One());
    }

    // A test for Zero

    TEST(Vector4, ZeroTest)
    {
        Vector4 val(0.0f, 0.0f, 0.0f, 0.0f);
        EXPECT_EQ(val, Vector4::Zero());
    }

    // A test for Equals (Vector4f)

    TEST(Vector4, EqualsTest1)
    {
        Vector4 a(1.0f, 2.0f, 3.0f, 4.0f);
        Vector4 b(1.0f, 2.0f, 3.0f, 4.0f);

        // case 1: compare between same values
        EXPECT_TRUE(a == b);

        // case 2: compare between different values
        b.x = 10.0f;
        EXPECT_FALSE(a == b);
    }

    // A test for Vector4f (float)

    TEST(Vector4, ConstructorTest6)
    {
        float value = 1.0f;
        Vector4 target(value);

        Vector4 expected(value, value, value, value);
        EXPECT_EQ(expected, target);

        value = 2.0f;
        target = Vector4(value);
        expected = Vector4(value, value, value, value);
        EXPECT_EQ(expected, target);
    }

    // A test for Vector4f comparison involving NaN values

    TEST(Vector4, EqualsNanTest)
    {
        Vector4 a(NaN(), 0, 0, 0);
        Vector4 b(0, NaN(), 0, 0);
        Vector4 c(0, 0, NaN(), 0);
        Vector4 d(0, 0, 0, NaN());

        EXPECT_FALSE(a == Vector4::Zero());
        EXPECT_FALSE(b == Vector4::Zero());
        EXPECT_FALSE(c == Vector4::Zero());
        EXPECT_FALSE(d == Vector4::Zero());

        EXPECT_TRUE(a != Vector4::Zero());
        EXPECT_TRUE(b != Vector4::Zero());
        EXPECT_TRUE(c != Vector4::Zero());
        EXPECT_TRUE(d != Vector4::Zero());
    }


    TEST(Vector4, AbsTest)
    {
        Vector4 v1(-2.5f, 2.0f, 3.0f, 3.3f);
        Vector4 v3 = Vector4::Abs(Vector4(MaxFloat, 0.0f, -MaxFloat, NaN()));
        Vector4 v = Vector4::Abs(v1);
        EXPECT_EQ(2.5f, v.x);
        EXPECT_EQ(2.0f, v.y);
        EXPECT_EQ(3.0f, v.z);
        EXPECT_EQ(3.3f, v.w);
        EXPECT_EQ(MaxFloat, v3.x);
        EXPECT_EQ(0.0f, v3.y);
        EXPECT_EQ(MaxFloat, v3.z);
        EXPECT_TRUE(IsNaN(v3.w));
    }


    TEST(Vector4, SqrtTest)
    {
        Vector4 v1(-2.5f, 2.0f, 3.0f, 3.3f);
        Vector4 v2(5.5f, 4.5f, 6.5f, 7.5f);
        EXPECT_EQ(2, (int)Vector4::SquareRoot(v2).x);
        EXPECT_EQ(2, (int)Vector4::SquareRoot(v2).y);
        EXPECT_EQ(2, (int)Vector4::SquareRoot(v2).z);
        EXPECT_EQ(2, (int)Vector4::SquareRoot(v2).w);
        EXPECT_TRUE(IsNaN(Vector4::SquareRoot(v1).x));
    }
}
