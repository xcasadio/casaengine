#include "gtest/gtest.h"

#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"
#include "Maths/Math.h"
#include "Maths/Quaternion.h"

using namespace CasaEngine;

namespace CasaEngineTests
{
    // A test for Dot (Quaternion, Quaternion)

    TEST(Quaternion, DotTest)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion b(5.0f, 6.0f, 7.0f, 8.0f);

        float expected = 70.0f;
        float actual = Quaternion::Dot(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Length ()

    TEST(Quaternion, LengthTest)
    {
        Vector3 v(1.0f, 2.0f, 3.0f);

        float w = 4.0f;

        Quaternion target(v, w);

        float expected = 5.477226f;
        float actual = target.Length();

        EXPECT_EQ(expected, actual);
    }

    // A test for LengthSquared ()

    TEST(Quaternion, LengthSquaredTest)
    {
        Vector3 v(1.0f, 2.0f, 3.0f);
        float w = 4.0f;

        Quaternion target(v, w);

        float expected = 30.0f;
        float actual;

        actual = target.LengthSquared();

        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Quaternion, Quaternion, float)

    TEST(Quaternion, LerpTest)
    {
        Vector3 axis = Vector3::Normalize(Vector3(1.0f, 2.0f, 3.0f));
        Quaternion a = Quaternion::CreateFromAxisAngle(axis, ToRadian(10.0f));
        Quaternion b = Quaternion::CreateFromAxisAngle(axis, ToRadian(30.0f));

        float t = 0.5f;

        Quaternion expected = Quaternion::CreateFromAxisAngle(axis, ToRadian(20.0f));
        Quaternion actual;

        actual = Quaternion::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);

        // Case a and b are same.
        expected = a;
        actual = Quaternion::Lerp(a, a, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Quaternion, Quaternion, float)
    // Lerp test when t = 0

    TEST(Quaternion, LerpTest1)
    {
        Vector3 axis = Vector3::Normalize(Vector3(1.0f, 2.0f, 3.0f));
        Quaternion a = Quaternion::CreateFromAxisAngle(axis, ToRadian(10.0f));
        Quaternion b = Quaternion::CreateFromAxisAngle(axis, ToRadian(30.0f));

        float t = 0.0f;

        Quaternion expected(a.x, a.y, a.z, a.w);
        Quaternion actual = Quaternion::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Quaternion, Quaternion, float)
    // Lerp test when t = 1

    TEST(Quaternion, LerpTest2)
    {
        Vector3 axis = Vector3::Normalize(Vector3(1.0f, 2.0f, 3.0f));
        Quaternion a = Quaternion::CreateFromAxisAngle(axis, ToRadian(10.0f));
        Quaternion b = Quaternion::CreateFromAxisAngle(axis, ToRadian(30.0f));

        float t = 1.0f;

        Quaternion expected(b.x, b.y, b.z, b.w);
        Quaternion actual = Quaternion::Lerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Lerp (Quaternion, Quaternion, float)
    // Lerp test when the two quaternions are more than 90 degree (dot product <0)

    TEST(Quaternion, LerpTest3)
    {
        Vector3 axis = Vector3::Normalize(Vector3(1.0f, 2.0f, 3.0f));
        Quaternion a = Quaternion::CreateFromAxisAngle(axis, ToRadian(10.0f));
        Quaternion b = Quaternion::Negate(a);

        float t = 1.0f;

        Quaternion actual = Quaternion::Lerp(a, b, t);
        // Note that in quaternion world, Q == -Q. In the case of quaternions dot product is zero,
        // one of the quaternion will be flipped to compute the shortest distance. When t = 1, we
        // expect the result to be the same as quaternion b but flipped.
        EXPECT_EQ(a, actual);
    }

    // A test for Conjugate(Quaternion)

    TEST(Quaternion, ConjugateTest1)
    {
        Quaternion a(1, 2, 3, 4);

        Quaternion expected(-1, -2, -3, 4);
        Quaternion actual = Quaternion::Conjugate(a);
        EXPECT_EQ(expected, actual);
    }

    // A test for Normalized (Quaternion)

    TEST(Quaternion, NormalizeTest)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);

        Quaternion expected(0.182574168f, 0.365148336f, 0.5477225f, 0.7302967f);
        Quaternion actual = Quaternion::Normalize(a);
        EXPECT_EQ(expected, actual);
    }

    // A test for Normalized (Quaternion)
    // Normalized zero length quaternion

    TEST(Quaternion, NormalizeTest1)
    {
        Quaternion a(0.0f, 0.0f, -0.0f, 0.0f);

        Quaternion actual = Quaternion::Normalize(a);
        EXPECT_TRUE(IsNaN(actual.x));
        EXPECT_TRUE(IsNaN(actual.y));
        EXPECT_TRUE(IsNaN(actual.z));
        EXPECT_TRUE(IsNaN(actual.w));
    }

    // A test for Concatenate(Quaternion, Quaternion)

    TEST(Quaternion, ConcatenateTest1)
    {
        Quaternion b(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion a(5.0f, 6.0f, 7.0f, 8.0f);

        Quaternion expected(24.0f, 48.0f, 48.0f, -6.0f);
        Quaternion actual;

        actual = Quaternion::Concatenate(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for operator - (Quaternion, Quaternion)

    TEST(Quaternion, SubtractionTest)
    {
        Quaternion a(1.0f, 6.0f, 7.0f, 4.0f);
        Quaternion b(5.0f, 2.0f, 3.0f, 8.0f);

        Quaternion expected(-4.0f, 4.0f, 4.0f, -4.0f);
        Quaternion actual;

        actual = a - b;

        EXPECT_EQ(expected, actual);
    }

    // A test for operator * (Quaternion, float)

    TEST(Quaternion, MultiplyTest)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
        float factor = 0.5f;

        Quaternion expected(0.5f, 1.0f, 1.5f, 2.0f);
        Quaternion actual;

        actual = a * factor;

        EXPECT_EQ(expected, actual);
    }

    // A test for operator * (Quaternion, Quaternion)

    TEST(Quaternion, MultiplyTest1)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion b(5.0f, 6.0f, 7.0f, 8.0f);

        Quaternion expected(24.0f, 48.0f, 48.0f, -6.0f);
        Quaternion actual;

        actual = a * b;

        EXPECT_EQ(expected, actual);
    }

    // A test for operator / (Quaternion, Quaternion)

    TEST(Quaternion, DivisionTest1)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion b(5.0f, 6.0f, 7.0f, 8.0f);

        Quaternion expected(-0.045977015f, -0.09195402f, -7.450581E-9f, 0.402298868f);
        Quaternion actual;

        actual = a / b;

        EXPECT_TRUE(expected == actual, $"Quaternion::operator / did not return the expected value: expected {expected} actual {actual}");
    }

    // A test for operator + (Quaternion, Quaternion)

    TEST(Quaternion, AdditionTest)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion b(5.0f, 6.0f, 7.0f, 8.0f);

        Quaternion expected(6.0f, 8.0f, 10.0f, 12.0f);
        Quaternion actual;

        actual = a + b;

        EXPECT_TRUE(expected == actual, $"Quaternion::operator + did not return the expected value: expected {expected} actual {actual}");
    }

    // A test for Quaternion (float, float, float, float)

    TEST(Quaternion, ConstructorTest)
    {
        float x = 1.0f;
        float y = 2.0f;
        float z = 3.0f;
        float w = 4.0f;

        Quaternion target(x, y, z, w);

        EXPECT_TRUE(target.x == x && target.y == y && target.z == z && target.w == w);
    }

    // A test for Quaternion (Vector3f, float)

    TEST(Quaternion, ConstructorTest1)
    {
        Vector3 v = Vector3(1.0f, 2.0f, 3.0f);
        float w = 4.0f;

        Quaternion target(v, w);
        EXPECT_EQ(target.x, v.x);
		EXPECT_EQ(target.y, v.y);
		EXPECT_EQ(target.z, v.z);
		EXPECT_EQ(target.w, w);
    }

    // A test for CreateFromAxisAngle (Vector3f, float)

    TEST(Quaternion, CreateFromAxisAngleTest)
    {
        Vector3 axis = Vector3::Normalize(Vector3(1.0f, 2.0f, 3.0f));
        float angle = ToRadian(30.0f);

        Quaternion expected(0.0691723f, 0.1383446f, 0.207516879f, 0.9659258f);
        Quaternion actual;

        actual = Quaternion::CreateFromAxisAngle(axis, angle);
        EXPECT_EQ(expected, actual);
    }

    // A test for CreateFromAxisAngle (Vector3f, float)
    // CreateFromAxisAngle of zero vector

    TEST(Quaternion, CreateFromAxisAngleTest1)
    {
        Vector3 axis = Vector3();
        float angle = ToRadian(-30.0f);

        float cos = std::cosf(angle / 2.0f);
        Quaternion actual = Quaternion::CreateFromAxisAngle(axis, angle);

        EXPECT_EQ(actual.x, 0.0f);
        EXPECT_EQ(actual.y, 0.0f);
        EXPECT_EQ(actual.z, 0.0f);
        EXPECT_EQ(actual.w, cos);
    }

    // A test for CreateFromAxisAngle (Vector3f, float)
    // CreateFromAxisAngle of angle = 30 && 750

    TEST(Quaternion, CreateFromAxisAngleTest2)
    {
        Vector3 axis = Vector3(1, 0, 0);
        float angle1 = ToRadian(30.0f);
        float angle2 = ToRadian(750.0f);

        Quaternion actual1 = Quaternion::CreateFromAxisAngle(axis, angle1);
        Quaternion actual2 = Quaternion::CreateFromAxisAngle(axis, angle2);
        EXPECT_EQ(actual1, actual2);
    }

    // A test for CreateFromAxisAngle (Vector3f, float)
    // CreateFromAxisAngle of angle = 30 && 390

    TEST(Quaternion, CreateFromAxisAngleTest3)
    {
        Vector3 axis = Vector3(1, 0, 0);
        float angle1 = ToRadian(30.0f);
        float angle2 = ToRadian(390.0f);

        Quaternion actual1 = Quaternion::CreateFromAxisAngle(axis, angle1);
        Quaternion actual2 = Quaternion::CreateFromAxisAngle(axis, angle2);
        actual1.x = -actual1.x;
        actual1.w = -actual1.w;

        EXPECT_EQ(actual1, actual2);
    }


    TEST(Quaternion, CreateFromYawPitchRollTest1)
    {
        float yawAngle = ToRadian(30.0f);
        float pitchAngle = ToRadian(40.0f);
        float rollAngle = ToRadian(50.0f);

        Quaternion yaw = Quaternion::CreateFromAxisAngle(Vector3::UnitY(), yawAngle);
        Quaternion pitch = Quaternion::CreateFromAxisAngle(Vector3::UnitX(), pitchAngle);
        Quaternion roll = Quaternion::CreateFromAxisAngle(Vector3::UnitZ(), rollAngle);

        Quaternion expected = yaw * pitch * roll;
        Quaternion actual = Quaternion::CreateFromYawPitchRoll(yawAngle, pitchAngle, rollAngle);
        EXPECT_EQ(expected, actual);
    }

    // Covers more numeric rigions

    TEST(Quaternion, CreateFromYawPitchRollTest2)
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

                    Quaternion yaw = Quaternion::CreateFromAxisAngle(Vector3::UnitY(), yawRad);
                    Quaternion pitch = Quaternion::CreateFromAxisAngle(Vector3::UnitX(), pitchRad);
                    Quaternion roll = Quaternion::CreateFromAxisAngle(Vector3::UnitZ(), rollRad);

                    Quaternion expected = yaw * pitch * roll;
                    Quaternion actual = Quaternion::CreateFromYawPitchRoll(yawRad, pitchRad, rollRad);
                    EXPECT_EQ(expected, actual);
                }
            }
        }
    }

    // A test for Slerp (Quaternion, Quaternion, float)

    TEST(Quaternion, SlerpTest)
    {
        Vector3 axis = Vector3::Normalize(Vector3(1.0f, 2.0f, 3.0f));
        Quaternion a = Quaternion::CreateFromAxisAngle(axis, ToRadian(10.0f));
        Quaternion b = Quaternion::CreateFromAxisAngle(axis, ToRadian(30.0f));

        float t = 0.5f;

        Quaternion expected = Quaternion::CreateFromAxisAngle(axis, ToRadian(20.0f));
        Quaternion actual;

        actual = Quaternion::Slerp(a, b, t);
        EXPECT_EQ(expected, actual);

        // Case a and b are same.
        expected = a;
        actual = Quaternion::Slerp(a, a, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Slerp (Quaternion, Quaternion, float)
    // Slerp test where t = 0

    TEST(Quaternion, SlerpTest1)
    {
        Vector3 axis = Vector3::Normalize(Vector3(1.0f, 2.0f, 3.0f));
        Quaternion a = Quaternion::CreateFromAxisAngle(axis, ToRadian(10.0f));
        Quaternion b = Quaternion::CreateFromAxisAngle(axis, ToRadian(30.0f));

        float t = 0.0f;

        Quaternion expected(a.x, a.y, a.z, a.w);
        Quaternion actual = Quaternion::Slerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Slerp (Quaternion, Quaternion, float)
    // Slerp test where t = 1

    TEST(Quaternion, SlerpTest2)
    {
        Vector3 axis = Vector3::Normalize(Vector3(1.0f, 2.0f, 3.0f));
        Quaternion a = Quaternion::CreateFromAxisAngle(axis, ToRadian(10.0f));
        Quaternion b = Quaternion::CreateFromAxisAngle(axis, ToRadian(30.0f));

        float t = 1.0f;

        Quaternion expected(b.x, b.y, b.z, b.w);
        Quaternion actual = Quaternion::Slerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for Slerp (Quaternion, Quaternion, float)
    // Slerp test where dot product is < 0

    TEST(Quaternion, SlerpTest3)
    {
        Vector3 axis = Vector3::Normalize(Vector3(1.0f, 2.0f, 3.0f));
        Quaternion a = Quaternion::CreateFromAxisAngle(axis, ToRadian(10.0f));
        Quaternion b = -a;

        float t = 1.0f;

        Quaternion expected = a;
        Quaternion actual = Quaternion::Slerp(a, b, t);
        // Note that in quaternion world, Q == -Q. In the case of quaternions dot product is zero,
        // one of the quaternion will be flipped to compute the shortest distance. When t = 1, we
        // expect the result to be the same as quaternion b but flipped.
        EXPECT_EQ(actual, expected);
    }

    // A test for Slerp (Quaternion, Quaternion, float)
    // Slerp test where the quaternion is flipped

    TEST(Quaternion, SlerpTest4)
    {
        Vector3 axis = Vector3::Normalize(Vector3(1.0f, 2.0f, 3.0f));
        Quaternion a = Quaternion::CreateFromAxisAngle(axis, ToRadian(10.0f));
        Quaternion b = -Quaternion::CreateFromAxisAngle(axis, ToRadian(30.0f));

        float t = 0.0f;

        Quaternion expected(a.x, a.y, a.z, a.w);
        Quaternion actual = Quaternion::Slerp(a, b, t);
        EXPECT_EQ(expected, actual);
    }

    // A test for operator - (Quaternion)

    TEST(Quaternion, UnaryNegationTest)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);

        Quaternion expected(-1.0f, -2.0f, -3.0f, -4.0f);
        Quaternion actual;

        actual = -a;

        EXPECT_EQ(expected, actual);
    }

    // A test for Inverse (Quaternion)

    TEST(Quaternion, InverseTest)
    {
        Quaternion a(5.0f, 6.0f, 7.0f, 8.0f);

        Quaternion expected(-0.0287356321f, -0.03448276f, -0.0402298868f, 0.04597701f);
        Quaternion actual;

        actual = Quaternion::Inverse(a);
        EXPECT_EQ(expected, actual);
    }

    // A test for Inverse (Quaternion)
    // Invert zero length quaternion

    TEST(Quaternion, InverseTest1)
    {
        Quaternion a(0, 0, 0,0);
        Quaternion actual = Quaternion::Inverse(a);

        EXPECT_TRUE(IsNaN(actual.x));
        EXPECT_TRUE(IsNaN(actual.y));
        EXPECT_TRUE(IsNaN(actual.z));
        EXPECT_TRUE(IsNaN(actual.w));
    }

    // A test for Add (Quaternion, Quaternion)

    TEST(Quaternion, AddTest)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion b(5.0f, 6.0f, 7.0f, 8.0f);

        Quaternion expected(6.0f, 8.0f, 10.0f, 12.0f);
        Quaternion actual;

        actual = Quaternion::Add(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Divide (Quaternion, Quaternion)

    TEST(Quaternion, DivideTest)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion b(5.0f, 6.0f, 7.0f, 8.0f);

        Quaternion expected(-0.045977015f, -0.09195402f, -7.450581E-9f, 0.402298868f);
        Quaternion actual;

        actual = Quaternion::Divide(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Multiply (Quaternion, float)

    TEST(Quaternion, MultiplyTest2)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
        float factor = 0.5f;

        Quaternion expected(0.5f, 1.0f, 1.5f, 2.0f);
        Quaternion actual;

        actual = Quaternion::Multiply(a, factor);
        EXPECT_EQ(expected, actual);
    }

    // A test for Multiply (Quaternion, Quaternion)

    TEST(Quaternion, MultiplyTest3)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion b(5.0f, 6.0f, 7.0f, 8.0f);

        Quaternion expected(24.0f, 48.0f, 48.0f, -6.0f);
        Quaternion actual;

        actual = Quaternion::Multiply(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for Negate (Quaternion)

    TEST(Quaternion, NegateTest)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);

        Quaternion expected(-1.0f, -2.0f, -3.0f, -4.0f);
        Quaternion actual;

        actual = Quaternion::Negate(a);
        EXPECT_EQ(expected, actual);
    }

    // A test for Subtract (Quaternion, Quaternion)

    TEST(Quaternion, SubtractTest)
    {
        Quaternion a(1.0f, 6.0f, 7.0f, 4.0f);
        Quaternion b(5.0f, 2.0f, 3.0f, 8.0f);

        Quaternion expected(-4.0f, 4.0f, 4.0f, -4.0f);
        Quaternion actual;

        actual = Quaternion::Subtract(a, b);
        EXPECT_EQ(expected, actual);
    }

    // A test for operator != (Quaternion, Quaternion)

    TEST(Quaternion, InequalityTest)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion b(1.0f, 2.0f, 3.0f, 4.0f);

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

    // A test for operator == (Quaternion, Quaternion)

    TEST(Quaternion, EqualityTest)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion b(1.0f, 2.0f, 3.0f, 4.0f);

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

    // A test for CreateFromRotationMatrix (Matrix4)
    // Convert Identity matrix test

    TEST(Quaternion, FromRotationMatrixTest1)
    {
        Matrix4 matrix = Matrix4::CreateIdentity();

        Quaternion expected(0.0f, 0.0f, 0.0f, 1.0f);
        Quaternion actual = Quaternion::CreateFromRotationMatrix(matrix);
        EXPECT_EQ(expected, actual);

        // make sure convert back to matrix is same as we passed matrix.
        Matrix4 m2 = Matrix4::CreateFromQuaternion(actual);
        EXPECT_EQ(matrix, m2);
    }

    // A test for CreateFromRotationMatrix (Matrix4)
    // Convert X axis rotation matrix

    TEST(Quaternion, FromRotationMatrixTest2)
    {
        for (float angle = 0; angle < 720; angle += 10)
        {
            Matrix4 matrix = Matrix4::CreateRotationX(angle);

            Quaternion expected = Quaternion::CreateFromAxisAngle(Vector3::UnitX(), angle);
            Quaternion actual = Quaternion::CreateFromRotationMatrix(matrix);
            EXPECT_EQ(expected, actual);

            // make sure convert back to matrix is same as we passed matrix.
            Matrix4 m2 = Matrix4::CreateFromQuaternion(actual);
            EXPECT_EQ(matrix, m2);
        }
    }

    // A test for CreateFromRotationMatrix (Matrix4)
    // Convert Y axis rotation matrix

    TEST(Quaternion, FromRotationMatrixTest3)
    {
        for (float angle = 0; angle < 720; angle += 10)
        {
            Matrix4 matrix = Matrix4::CreateRotationY(angle);

            Quaternion expected = Quaternion::CreateFromAxisAngle(Vector3::UnitY(), angle);
            Quaternion actual = Quaternion::CreateFromRotationMatrix(matrix);
            EXPECT_EQ(expected, actual);

            // make sure convert back to matrix is same as we passed matrix.
            Matrix4 m2 = Matrix4::CreateFromQuaternion(actual);
            EXPECT_EQ(matrix, m2);
        }
    }

    // A test for CreateFromRotationMatrix (Matrix4)
    // Convert Z axis rotation matrix

    TEST(Quaternion, FromRotationMatrixTest4)
    {
        for (float angle = 0; angle < 720; angle += 10)
        {
            Matrix4 matrix = Matrix4::CreateRotationZ(angle);

            Quaternion expected = Quaternion::CreateFromAxisAngle(Vector3::UnitZ(), angle);
            Quaternion actual = Quaternion::CreateFromRotationMatrix(matrix);
            EXPECT_EQ(expected, actual);

            // make sure convert back to matrix is same as we passed matrix.
            Matrix4 m2 = Matrix4::CreateFromQuaternion(actual);
            EXPECT_EQ(matrix, m2);
        }
    }

    // A test for CreateFromRotationMatrix (Matrix4)
    // Convert XYZ axis rotation matrix

    TEST(Quaternion, FromRotationMatrixTest5)
    {
        for (float angle = 0; angle < 720; angle += 10)
        {
            Matrix4 matrix = Matrix4::CreateRotationX(angle) * Matrix4::CreateRotationY(angle) * Matrix4::CreateRotationZ(angle);

            Quaternion expected =
                Quaternion::CreateFromAxisAngle(Vector3::UnitZ(), angle) *
                Quaternion::CreateFromAxisAngle(Vector3::UnitY(), angle) *
                Quaternion::CreateFromAxisAngle(Vector3::UnitX(), angle);

            Quaternion actual = Quaternion::CreateFromRotationMatrix(matrix);
            EXPECT_EQ(expected, actual);

            // make sure convert back to matrix is same as we passed matrix.
            Matrix4 m2 = Matrix4::CreateFromQuaternion(actual);
            EXPECT_EQ(matrix, m2);
        }
    }

    // A test for CreateFromRotationMatrix (Matrix4)
    // X axis is most large axis case

    TEST(Quaternion, FromRotationMatrixWithScaledMatrixTest1)
    {
        float angle = ToRadian(180.0f);
        Matrix4 matrix = Matrix4::CreateRotationY(angle) * Matrix4::CreateRotationZ(angle);

        Quaternion expected = Quaternion::CreateFromAxisAngle(Vector3::UnitZ(), angle) * Quaternion::CreateFromAxisAngle(Vector3::UnitY(), angle);
        Quaternion actual = Quaternion::CreateFromRotationMatrix(matrix);
        EXPECT_EQ(expected, actual);

        // make sure convert back to matrix is same as we passed matrix.
        Matrix4 m2 = Matrix4::CreateFromQuaternion(actual);
        EXPECT_EQ(matrix, m2);
    }

    // A test for CreateFromRotationMatrix (Matrix4)
    // Y axis is most large axis case

    TEST(Quaternion, FromRotationMatrixWithScaledMatrixTest2)
    {
        float angle = ToRadian(180.0f);
        Matrix4 matrix = Matrix4::CreateRotationX(angle) * Matrix4::CreateRotationZ(angle);

        Quaternion expected = Quaternion::CreateFromAxisAngle(Vector3::UnitZ(), angle) * Quaternion::CreateFromAxisAngle(Vector3::UnitX(), angle);
        Quaternion actual = Quaternion::CreateFromRotationMatrix(matrix);
        EXPECT_EQ(expected, actual);

        // make sure convert back to matrix is same as we passed matrix.
        Matrix4 m2 = Matrix4::CreateFromQuaternion(actual);
        EXPECT_EQ(matrix, m2);
    }

    // A test for CreateFromRotationMatrix (Matrix4)
    // Z axis is most large axis case

    TEST(Quaternion, FromRotationMatrixWithScaledMatrixTest3)
    {
        float angle = ToRadian(180.0f);
        Matrix4 matrix = Matrix4::CreateRotationX(angle) * Matrix4::CreateRotationY(angle);

        Quaternion expected = Quaternion::CreateFromAxisAngle(Vector3::UnitY(), angle) * Quaternion::CreateFromAxisAngle(Vector3::UnitX(), angle);
        Quaternion actual = Quaternion::CreateFromRotationMatrix(matrix);
        EXPECT_EQ(expected, actual);

        // make sure convert back to matrix is same as we passed matrix.
        Matrix4 m2 = Matrix4::CreateFromQuaternion(actual);
        EXPECT_EQ(matrix, m2);
    }

    // A test for Equals (Quaternion)

    TEST(Quaternion, EqualsTest1)
    {
        Quaternion a(1.0f, 2.0f, 3.0f, 4.0f);
        Quaternion b(1.0f, 2.0f, 3.0f, 4.0f);

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

    // A test for Zero

    TEST(Quaternion, ZeroTest)
    {
        // A newly constructed value should be equal to a zero value.
        //EXPECT_EQ(Quaternion(), Quaternion::Zero());

        // A newly constructed value with (0, 0, 0, 0) should be equal to a zero value.
        EXPECT_EQ(Quaternion(0, 0, 0, 0), Quaternion::Zero());
    }

    // A test for Identity

    TEST(Quaternion, IdentityTest)
    {
        Quaternion val(0, 0, 0, 1);
        EXPECT_EQ(val, Quaternion::CreateIdentity());
    }

    // A test for IsIdentity

    TEST(Quaternion, IsIdentityTest)
    {
        EXPECT_TRUE(Quaternion::CreateIdentity().IsIdentity());
        EXPECT_TRUE(Quaternion(0, 0, 0, 1).IsIdentity());
        EXPECT_FALSE(Quaternion(1, 0, 0, 1).IsIdentity());
        EXPECT_FALSE(Quaternion(0, 1, 0, 1).IsIdentity());
        EXPECT_FALSE(Quaternion(0, 0, 1, 1).IsIdentity());
        EXPECT_FALSE(Quaternion(0, 0, 0, 0).IsIdentity());
    }

    // A test for Quaternion comparison involving NaN values

    TEST(Quaternion, EqualsNanTest)
    {
        Quaternion a(NaN(), 0, 0, 0);
        Quaternion b(0, NaN(), 0, 0);
        Quaternion c(0, 0, NaN(), 0);
        Quaternion d(0, 0, 0, NaN());

        EXPECT_FALSE(a == Quaternion(0, 0, 0, 0));
        EXPECT_FALSE(b == Quaternion(0, 0, 0, 0));
        EXPECT_FALSE(c == Quaternion(0, 0, 0, 0));
        EXPECT_FALSE(d == Quaternion(0, 0, 0, 0));

        EXPECT_TRUE(a != Quaternion(0, 0, 0, 0));
        EXPECT_TRUE(b != Quaternion(0, 0, 0, 0));
        EXPECT_TRUE(c != Quaternion(0, 0, 0, 0));
        EXPECT_TRUE(d != Quaternion(0, 0, 0, 0));

        EXPECT_FALSE(a.IsIdentity());
        EXPECT_FALSE(b.IsIdentity());
        EXPECT_FALSE(c.IsIdentity());
        EXPECT_FALSE(d.IsIdentity());
    }
}
