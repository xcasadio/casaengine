
#include "Base.h"
#include "Log/LogManager.h"

#include "Quaternion.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"
#include "Maths/Vector4.h"

#include "CA_Assert.h"

namespace CasaEngine
{

/////////////////////////////////////////////////////////////
/// Constructeur par défaut
///
/// \param m11 - m44 : Composantes de la matrice
///
////////////////////////////////////////////////////////////
Matrix4::Matrix4(float m11, float m12, float m13, float m14,
                          float m21, float m22, float m23, float m24,
                          float m31, float m32, float m33, float m34,
                          float m41, float m42, float m43, float m44) :
a11(m11), a12(m12), a13(m13), a14(m14),
a21(m21), a22(m22), a23(m23), a24(m24),
a31(m31), a32(m32), a33(m33), a34(m34),
a41(m41), a42(m42), a43(m43), a44(m44)
{

}


/////////////////////////////////////////////////////////////
/// Met la matrice à l'identité
///
////////////////////////////////////////////////////////////
void Matrix4::Identity()
{
    a11 = 1.0f; a12 = 0.0f; a13 = 0.0f; a14 = 0.0f;
    a21 = 0.0f; a22 = 1.0f; a23 = 0.0f; a24 = 0.0f;
    a31 = 0.0f; a32 = 0.0f; a33 = 1.0f; a34 = 0.0f;
    a41 = 0.0f; a42 = 0.0f; a43 = 0.0f; a44 = 1.0f;
}


/////////////////////////////////////////////////////////////
/// Calcule le déterminant de la matrice
///
/// \return Valeur du déterminant
///
////////////////////////////////////////////////////////////
float Matrix4::Determinant() const
{
    float A = a22 * (a33 * a44 - a43 * a34) - a32 * (a23 * a44 - a43 * a24) + a42 * (a23 * a34 - a33 * a24);
    float B = a12 * (a33 * a44 - a43 * a34) - a32 * (a13 * a44 - a43 * a14) + a42 * (a13 * a34 - a33 * a14);
    float C = a12 * (a23 * a44 - a43 * a24) - a22 * (a13 * a44 - a43 * a14) + a42 * (a13 * a24 - a23 * a14);
    float D = a12 * (a23 * a34 - a33 * a24) - a22 * (a13 * a34 - a33 * a14) + a32 * (a13 * a24 - a23 * a14);

    return a11 * A - a21 * B + a31 * C - a41 * D;
}


/////////////////////////////////////////////////////////////
/// Transpose la matrice
///
/// \return Matrice transposée
///
////////////////////////////////////////////////////////////
Matrix4 Matrix4::Transpose() const
{
    return Matrix4(a11, a21, a31, a41,
                    a12, a22, a32, a42,
                    a13, a23, a33, a43,
                    a14, a24, a34, a44);
}


/////////////////////////////////////////////////////////////
/// Inverse la matrice si son déterminant est non nul
///
/// \return Matrice inverse
///
////////////////////////////////////////////////////////////
Matrix4 Matrix4::Invert() const
{
    Matrix4 Ret;
    float Det = Determinant();

    if (std::fabs(Det) > std::numeric_limits<float>::epsilon())
    {
        Ret.a11 =  (a22 * (a33 * a44 - a34 * a43) - a32 * (a23 * a44 - a43 * a24) + a42 * (a23 * a34 - a33 *  a24)) / Det;
        Ret.a12 = -(a12 * (a33 * a44 - a43 * a34) - a32 * (a13 * a44 - a43 * a14) + a42 * (a13 * a34 - a33 *  a14)) / Det;
        Ret.a13 =  (a12 * (a23 * a44 - a43 * a24) - a22 * (a13 * a44 - a43 * a14) + a42 * (a13 * a24 - a23 *  a14)) / Det;
        Ret.a14 = -(a12 * (a23 * a34 - a33 * a24) - a22 * (a13 * a34 - a33 * a14) + a32 * (a13 * a24 - a23 *  a14)) / Det;

        Ret.a21 = -(a21 * (a33 * a44 - a34 * a43) - a23 * (a31 * a44 - a34 * a41) + a24 * (a31 * a43 - a33 *  a41)) / Det;
        Ret.a22 =  (a11 * (a33 * a44 - a34 * a43) - a13 * (a31 * a44 - a34 * a41) + a14 * (a31 * a43 - a33 *  a41)) / Det;
        Ret.a23 = -(a11 * (a23 * a44 - a24 * a43) - a13 * (a21 * a44 - a24 * a41) + a14 * (a21 * a43 - a23 *  a41)) / Det;
        Ret.a24 =  (a11 * (a23 * a34 - a24 * a33) - a13 * (a21 * a34 - a24 * a31) + a14 * (a21 * a33 - a23 *  a31)) / Det;

        Ret.a31 =  (a21 * (a32 * a44 - a34 * a42) - a22 * (a31 * a44 - a34 * a41) + a24 * (a31 * a42 - a32 *  a41)) / Det;
        Ret.a32 = -(a11 * (a32 * a44 - a34 * a42) - a12 * (a31 * a44 - a34 * a41) + a14 * (a31 * a42 - a32 *  a41)) / Det;
        Ret.a33 =  (a11 * (a22 * a44 - a24 * a42) - a12 * (a21 * a44 - a24 * a41) + a14 * (a21 * a42 - a22 *  a41)) / Det;
        Ret.a34 = -(a11 * (a22 * a34 - a24 * a32) - a12 * (a21 * a34 - a24 * a31) + a14 * (a21 * a32 - a22 *  a31)) / Det;

        Ret.a41 = -(a21 * (a32 * a43 - a33 * a42) - a22 * (a31 * a43 - a33 * a41) + a23 * (a31 * a42 - a32 *  a41)) / Det;
        Ret.a42 =  (a11 * (a32 * a43 - a33 * a42) - a12 * (a31 * a43 - a33 * a41) + a13 * (a31 * a42 - a32 *  a41)) / Det;
        Ret.a43 = -(a11 * (a22 * a43 - a23 * a42) - a12 * (a21 * a43 - a23 * a41) + a13 * (a21 * a42 - a22 *  a41)) / Det;
        Ret.a44 =  (a11 * (a22 * a33 - a23 * a32) - a12 * (a21 * a33 - a23 * a31) + a13 * (a21 * a32 - a22 *  a31)) / Det;
    }

    return Ret;
}

/**
 * 
 */
Vector3F Matrix4::GetTranslation() const
{
	return Vector3F(a14, a24, a34);
}

/**
 * 
 */
void Matrix4::SetTranslation(float x, float y, float z)
{
	a14 = x;
	a24 = y;
	a34 = z;
}

/**
 *	
 */
void Matrix4::SetTranslation(Vector3F &trans_)
{
	SetTranslation(trans_.x, trans_.y, trans_.z);
}

/**
 * 
 */
void Matrix4::CreateTranslation(float x, float y, float z)
{
    a11 = 1.0f; a12 = 0.0f; a13 = 0.0f; a14 = x;
    a21 = 0.0f; a22 = 1.0f; a23 = 0.0f; a24 = y;
    a31 = 0.0f; a32 = 0.0f; a33 = 1.0f; a34 = z;
    a41 = 0.0f; a42 = 0.0f; a43 = 0.0f; a44 = 1.0f;
	//bgfx
// 	a11 = 1.0f; a12 = 0.0f; a13 = 0.0f; a14 = 0.0f;
// 	a21 = 0.0f; a22 = 1.0f; a23 = 0.0f; a24 = 0.0f;
// 	a31 = 0.0f; a32 = 0.0f; a33 = 1.0f; a34 = 0.0f;
// 	a41 = x;	a42 = y;	a43 = z;	a44 = 1.0f;
}


/////////////////////////////////////////////////////////////
/// Construit une matrice de mise à l'échelle
///
/// \param x : Facteur de redimensionnement sur l'axe X
/// \param y : Facteur de redimensionnement sur l'axe Y
/// \param z : Facteur de redimensionnement sur l'axe Z
///
////////////////////////////////////////////////////////////
void Matrix4::CreateScale(float x, float y, float z)
{
    a11 = x;    a12 = 0.0f; a13 = 0.0f; a14 = 0.0f;
    a21 = 0.0f; a22 = y;    a23 = 0.0f; a24 = 0.0f;
    a31 = 0.0f; a32 = 0.0f; a33 = z;    a34 = 0.0f;
    a41 = 0.0f; a42 = 0.0f; a43 = 0.0f; a44 = 1.0f;
}

/**
 *
 */
void Matrix4::CreateFromDirection(const Vector3F &forward, const Vector3F &side, const Vector3F &up)
{
	a11 = side.x; a12 = up.x; a13 = -forward.x; a14 = 0.0f;
	a21 = side.y; a22 = up.y; a23 = -forward.y; a24 = 0.0f;
	a31 = side.z; a32 = up.z; a33 = -forward.z; a34 = 0.0f;
	a41 = 0.0f; a42 = 0.0f; a43 = 0.0f; a44 = 1.0f;
}

/////////////////////////////////////////////////////////////
/// Construit une matrice de rotation sur l'axe X
///
/// \param Angle : Angle de rotation en radians
///
////////////////////////////////////////////////////////////
void Matrix4::CreateRotationX(float Angle)
{
	float Cos = cosf(Angle);
	float Sin = sinf(Angle);

    a11 = 1.0f; a12 = 0.0f; a13 = 0.0f; a14 = 0.0f;
    a21 = 0.0f; a22 = Cos;  a23 = Sin;  a24 = 0.0f;
    a31 = 0.0f; a32 = -Sin; a33 = Cos;  a34 = 0.0f;
    a41 = 0.0f; a42 = 0.0f; a43 = 0.0f; a44 = 1.0f;
}


/////////////////////////////////////////////////////////////
/// Construit une matrice de rotation sur l'axe Y
///
/// \param Angle : Angle de rotation en radians
///
////////////////////////////////////////////////////////////
void Matrix4::CreateRotationY(float Angle)
{
    float Cos = cosf(Angle);
    float Sin = sinf(Angle);

    a11 = Cos;  a12 = 0.0f; a13 = -Sin; a14 = 0.0f;
    a21 = 0.0f; a22 = 1.0f; a23 = 0.0f; a24 = 0.0f;
    a31 = Sin;  a32 = 0.0f; a33 = Cos;  a34 = 0.0f;
    a41 = 0.0f; a42 = 0.0f; a43 = 0.0f; a44 = 1.0f;
}


/////////////////////////////////////////////////////////////
/// Construit une matrice de rotation sur l'axe Z
///
/// \param Angle : Angle de rotation en radians
///
////////////////////////////////////////////////////////////
void Matrix4::CreateRotationZ(float Angle)
{
    float Cos = cosf(Angle);
    float Sin = sinf(Angle);

    a11 = Cos;  a12 = Sin;  a13 = 0.0f; a14 = 0.0f;
    a21 = -Sin; a22 = Cos;  a23 = 0.0f; a24 = 0.0f;
    a31 = 0.0f; a32 = 0.0f; a33 = 1.0f; a34 = 0.0f;
    a41 = 0.0f; a42 = 0.0f; a43 = 0.0f; a44 = 1.0f;
}


/////////////////////////////////////////////////////////////
/// Construit une matrice de rotation sur l'axe X
///
/// \param Angle :  Angle de rotation en radians
/// \param Center : Centre de rotation
///
////////////////////////////////////////////////////////////
void Matrix4::CreateRotationX(float Angle, const Vector3F& Center)
{
    Matrix4 Tr1, Tr2, Rot;

    Tr1.CreateTranslation(Center.x, Center.y, Center.z);
    Tr2.CreateTranslation(-Center.x, -Center.y, -Center.z);
    Rot.CreateRotationX(Angle);

    *this = Tr1 * Rot * Tr2;
}


/////////////////////////////////////////////////////////////
/// Construit une matrice de rotation sur l'axe Y
///
/// \param Angle :  Angle de rotation en radians
/// \param Center : Centre de rotation
///
////////////////////////////////////////////////////////////
void Matrix4::CreateRotationY(float Angle, const Vector3F& Center)
{
    Matrix4 Tr1, Tr2, Rot;

    Tr1.CreateTranslation(Center.x, Center.y, Center.z);
    Tr2.CreateTranslation(-Center.x, -Center.y, -Center.z);
    Rot.CreateRotationY(Angle);

    *this = Tr1 * Rot * Tr2;
}


/////////////////////////////////////////////////////////////
/// Construit une matrice de rotation sur l'axe Z
///
/// \param Angle :  Angle de rotation en radians
/// \param Center : Centre de rotation
///
////////////////////////////////////////////////////////////
void Matrix4::CreateRotationZ(float Angle, const Vector3F& Center)
{
    Matrix4 Tr1, Tr2, Rot;

    Tr1.CreateTranslation(Center.x, Center.y, Center.z);
    Tr2.CreateTranslation(-Center.x, -Center.y, -Center.z);
    Rot.CreateRotationZ(Angle);

    *this = Tr1 * Rot * Tr2;
}

/**
 * 
 */
void Matrix4::Transformation(const Vector3F *pscalingcenter, 
			const Quaternion *pscalingrotation, const Vector3F *pscaling, 
			const Vector3F *protationcenter, const Quaternion *protation, 
			const Vector3F *ptranslation)
{
	Matrix4 m1, m2, m3, m4, m5, m6, m7, p1, p2, p3, p4, p5;
	Quaternion prc;
	Vector3F psc, pt;

	if ( !pscalingcenter )
	{
		psc.x = 0.0f;
		psc.y = 0.0f;
		psc.z = 0.0f;
	}
	else
	{
		psc.x = pscalingcenter->x;
		psc.y = pscalingcenter->y;
		psc.z = pscalingcenter->z;
	}
	if ( !protationcenter )
	{
		prc.x = 0.0f;
		prc.y = 0.0f;
		prc.z = 0.0f;
	}
	else
	{
		prc.x = protationcenter->x;
		prc.y = protationcenter->y;
		prc.z = protationcenter->z;
	}
	if ( !ptranslation )
	{
		pt.x = 0.0f;
		pt.y = 0.0f;
		pt.z = 0.0f;
	}
	else
	{
		pt.x = ptranslation->x;
		pt.y = ptranslation->y;
		pt.z = ptranslation->z;
	}

	m1.CreateTranslation(-psc.x, -psc.y, -psc.z);

	if ( !pscalingrotation )
	{
		//m2.Identity();
		//m4.Identity();
	}
	else
	{
		m4 = pscalingrotation->ToMatrix4();
		m2 = m4.Invert();
	}
	if ( !pscaling )
	{
		//D3DXMatrixIdentity(&m3);
	}
	else
	{
		m3.CreateScale(pscaling->x, pscaling->y, pscaling->z);
	}
	if ( !protation )
	{
		//D3DXMatrixIdentity(&m6);
	}
	else
	{
		m6 = protation->ToMatrix4();
	}

	m5.CreateTranslation(psc.x - prc.x,  psc.y - prc.y,  psc.z - prc.z);
	//D3DXMatrixTranslation(&m5, psc.x - prc.x,  psc.y - prc.y,  psc.z - prc.z);
	m7.CreateTranslation(prc.x + pt.x, prc.y + pt.y, prc.z + pt.z);
	//D3DXMatrixTranslation(&m7, prc.x + pt.x, prc.y + pt.y, prc.z + pt.z);

	p1 = m1 * m2;
	p2 = p1 * m3;
	p3 = p2 * m4;
	p4 = p3 * m5;
	p5 = p4 * m6;
	*this = p5 * m7;
}

/////////////////////////////////////////////////////////////
/// Transforme un vecteur à 3 composantes
///
/// \param v : Vecteur à transformer
/// \param w : Composante w
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
Vector3F Matrix4::Transform(const Vector3F& v, float w) const
{
    return Vector3F(v.x * a11 + v.y * a21 + v.z * a31 + w * a41,
                     v.x * a12 + v.y * a22 + v.z * a32 + w * a42,
                     v.x * a13 + v.y * a23 + v.z * a33 + w * a43);
}


/////////////////////////////////////////////////////////////
/// Transforme un vecteur à 4 composantes
///
/// \param v : Vecteur à transformer
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
Vector4F Matrix4::Transform(const Vector4F& v) const
{
    return Vector4F(v.x * a11 + v.y * a21 + v.z * a31 + v.w * a41,
                     v.x * a12 + v.y * a22 + v.z * a32 + v.w * a42,
                     v.x * a13 + v.y * a23 + v.z * a33 + v.w * a43,
                     v.x * a14 + v.y * a24 + v.z * a34 + v.w * a44);
}


/**
 * 
 */
void Matrix4::Transform(const Vector3F &position, Vector3F &result)
{
	result.x = position.x * a11 + position.y * a21 + position.z * a31 + a41;
	result.y = position.x * a12 + position.y * a22 + position.z * a32 + a42;
	result.z = position.x * a13 + position.y * a23 + position.z * a33 + a43;
}

/**
 * 
 */
void Matrix4::Transform(const std::vector<Vector3F> &sourceArray, std::vector<Vector3F> &destinationArray)
{
	CA_ASSERT(destinationArray.size() >= sourceArray.size(), "The destination array is smaller than the source array.");

	int i = 0;

	for (std::vector<Vector3F>::const_iterator it = sourceArray.cbegin();
		it != sourceArray.cend();
		it++)
	{
		Vector3F position = *it;
		destinationArray[i] = Vector3F(
			position.x * a11 + position.y * a21 + position.z * a31 + a41,
			position.x * a12 + position.y * a22 + position.z * a32 + a42,
			position.x * a13 + position.y * a23 + position.z * a33 + a43);
		i++;
	}
}



void Matrix4::TransformNormal(const Vector3F &normal, Vector3F &result) const
{
	result = Vector3F(
		normal.x * a11 + normal.y * a21 + normal.z * a31,
		normal.x * a12 + normal.y * a22 + normal.z * a32,
		normal.x * a13 + normal.y * a23 + normal.z * a33);
}

/**
 * 
 */
void Matrix4::OrthoOffCenter(float _left, float _top, float _right, float _bottom, float _near, float _far, float _offset /*= 0.0f*/)
{
	const float aa = 2.0f/(_right - _left);
	const float bb = 2.0f/(_top - _bottom);
	const float cc = 1.0f/(_far - _near);
	const float dd = (_left + _right)/(_left - _right);
	const float ee = (_top + _bottom)/(_bottom - _top);
	const float ff = _near / (_near - _far);

// 	a11 = aa;	a12 = 0.0f; a13 = 0.0f; a14 = dd + _offset;
// 	a21 = 0.0f;	a22 = bb;	a23 = 0.0f; a24 = ee;
// 	a31 = 0.0f;	a32 = 0.0f; a33 = 1.0f; a34 = ff;
// 	a41 = 0.0f;	a42 = 0.0f; a43 = 0.0f; a44 = 1.0f;

	//bgfx
	a11 = aa;			a12 = 0.0f; a13 = 0.0f; a14 = 0.0f;
	a21 = 0.0f;			a22 = bb;	a23 = 0.0f; a24 = 0.0f;
	a31 = 0.0f;			a32 = 0.0f; a33 = cc;	a34 = 0.0f;
	a41 = dd + _offset;	a42 = ee;	a43 = ff;	a44 = 1.0f;
}


/////////////////////////////////////////////////////////////
/// Construit une matrice de projection perspective
///
/// \param Fov :   Champ de vision en radians
/// \param Ratio : Ratio largeur / hauteur
/// \param Near :  Valeur du plan rapproché
/// \param Far :   Valeur du plan éloigné
///
////////////////////////////////////////////////////////////
void Matrix4::PerspectiveFOV(float Fov, float Ratio, float Near, float Far)
{
    float YScale = 1.0f / std::tan(Fov / 2);
    float XScale = YScale / Ratio;
    float Coeff  = Far / (Far - Near);

	//TODO : righthanded : XScale = -XScale;
	//TODO : lefthanded : XScale = XScale;

    a11 = XScale; a12 = 0.0f;   a13 = 0.0f;  a14 = 0.0f;
    a21 = 0.0f;   a22 = YScale; a23 = 0.0f;  a24 = 0.0f;
    a31 = 0.0f;   a32 = 0.0f;   a33 = Coeff; a34 = Near * -Coeff;
    a41 = 0.0f;   a42 = 0.0f;   a43 = 1.0f;  a44 = 0.0f;
}


/////////////////////////////////////////////////////////////
/// Construit une matrice de vue
///
/// \param From : Position de la caméra
/// \param To :   Cible de la caméra
/// \param Up :   Vecteur up ((0, 1, 0) par défaut)
///
////////////////////////////////////////////////////////////
void Matrix4::LookAt(const Vector3F& From, const Vector3F& To, const Vector3F& Up)
{
    // TODO : gérer le cas où (To - From) et Up sont colinéaires

    Vector3F ZAxis = To - From;
    ZAxis.Normalize();
    Vector3F XAxis = Vector3F::Cross(Up, ZAxis);
    XAxis.Normalize();
    Vector3F YAxis = Vector3F::Cross(ZAxis, XAxis);

    a11 = XAxis.x; a12 = XAxis.y; a13 = XAxis.z; a14 = -Vector3F::Dot(XAxis, From);
    a21 = YAxis.x; a22 = YAxis.y; a23 = YAxis.z; a24 = -Vector3F::Dot(YAxis, From);
    a31 = ZAxis.x; a32 = ZAxis.y; a33 = ZAxis.z; a34 = -Vector3F::Dot(ZAxis, From);
    a41 = 0.0f;    a42 = 0.0f;    a43 = 0.0f;    a44 = 1.0f;
}


/////////////////////////////////////////////////////////////
/// Opérateur + unaire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
Matrix4 Matrix4::operator +() const
{
    return *this;
}


/////////////////////////////////////////////////////////////
/// Opérateur - unaire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
Matrix4 Matrix4::operator -() const
{
    return Matrix4(-a11, -a12, -a13, -a14,
                    -a21, -a22, -a23, -a24,
                    -a31, -a32, -a33, -a34,
                    -a41, -a42, -a43, -a44);
}


/////////////////////////////////////////////////////////////
/// Opérateur + binaire
///
/// \param m : Matrice à additionner
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
Matrix4 Matrix4::operator +(const Matrix4& m) const
{
    return Matrix4(a11 + m.a11, a12 + m.a12, a13 + m.a13, a14 + m.a14,
                    a21 + m.a21, a22 + m.a22, a23 + m.a23, a24 + m.a24,
                    a31 + m.a31, a32 + m.a32, a33 + m.a33, a34 + m.a34,
                    a41 + m.a41, a42 + m.a42, a43 + m.a43, a44 + m.a44);
}


/////////////////////////////////////////////////////////////
/// Opérateur - binaire
///
/// \param m : Matrice à soustraire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
Matrix4 Matrix4::operator -(const Matrix4& m) const
{
    return Matrix4(a11 - m.a11, a12 - m.a12, a13 - m.a13, a14 - m.a14,
                    a21 - m.a21, a22 - m.a22, a23 - m.a23, a24 - m.a24,
                    a31 - m.a31, a32 - m.a32, a33 - m.a33, a34 - m.a34,
                    a41 - m.a41, a42 - m.a42, a43 - m.a43, a44 - m.a44);
}


/////////////////////////////////////////////////////////////
/// Opérateur +=
///
/// \param m : Matrice à additionner
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
const Matrix4& Matrix4::operator +=(const Matrix4& m)
{
    a11 += m.a11; a12 += m.a12; a13 += m.a13; a14 += m.a14;
    a21 += m.a21; a22 += m.a22; a23 += m.a23; a24 += m.a24;
    a31 += m.a31; a32 += m.a32; a33 += m.a33; a34 += m.a34;
    a41 += m.a41; a42 += m.a42; a43 += m.a43; a44 += m.a44;

    return *this;
}


/////////////////////////////////////////////////////////////
/// Opérateur -=
///
/// \param m : Matrice à soustraire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
const Matrix4& Matrix4::operator -=(const Matrix4& m)
{
    a11 -= m.a11; a12 -= m.a12; a13 -= m.a13; a14 -= m.a14;
    a21 -= m.a21; a22 -= m.a22; a23 -= m.a23; a24 -= m.a24;
    a31 -= m.a31; a32 -= m.a32; a33 -= m.a33; a34 -= m.a34;
    a41 -= m.a41; a42 -= m.a42; a43 -= m.a43; a44 -= m.a44;

    return *this;
}


/////////////////////////////////////////////////////////////
/// Opérateur *
///
/// \param m : Matrice à multiplier
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
Matrix4 Matrix4::operator *(const Matrix4& m) const
{
    return Matrix4(a11 * m.a11 + a21 * m.a12 + a31 * m.a13 + a41 * m.a14,
                    a12 * m.a11 + a22 * m.a12 + a32 * m.a13 + a42 * m.a14,
                    a13 * m.a11 + a23 * m.a12 + a33 * m.a13 + a43 * m.a14,
                    a14 * m.a11 + a24 * m.a12 + a34 * m.a13 + a44 * m.a14,

                    a11 * m.a21 + a21 * m.a22 + a31 * m.a23 + a41 * m.a24,
                    a12 * m.a21 + a22 * m.a22 + a32 * m.a23 + a42 * m.a24,
                    a13 * m.a21 + a23 * m.a22 + a33 * m.a23 + a43 * m.a24,
                    a14 * m.a21 + a24 * m.a22 + a34 * m.a23 + a44 * m.a24,

                    a11 * m.a31 + a21 * m.a32 + a31 * m.a33 + a41 * m.a34,
                    a12 * m.a31 + a22 * m.a32 + a32 * m.a33 + a42 * m.a34,
                    a13 * m.a31 + a23 * m.a32 + a33 * m.a33 + a43 * m.a34,
                    a14 * m.a31 + a24 * m.a32 + a34 * m.a33 + a44 * m.a34,

                    a11 * m.a41 + a21 * m.a42 + a31 * m.a43 + a41 * m.a44,
                    a12 * m.a41 + a22 * m.a42 + a32 * m.a43 + a42 * m.a44,
                    a13 * m.a41 + a23 * m.a42 + a33 * m.a43 + a43 * m.a44,
                    a14 * m.a41 + a24 * m.a42 + a34 * m.a43 + a44 * m.a44);
}


/////////////////////////////////////////////////////////////
/// Opérateur *=
///
/// \param m : Matrice à multiplier
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
const Matrix4& Matrix4::operator *=(const Matrix4& m)
{
    *this = *this * m;

    return *this;
}


/////////////////////////////////////////////////////////////
/// Opérateur *= avec un scalaire
///
/// \param t : Scalaire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
const Matrix4& Matrix4::operator *=(float t)
{
    a11 *= t; a12 *= t; a13 *= t; a14 *= t;
    a21 *= t; a22 *= t; a23 *= t; a24 *= t;
    a31 *= t; a32 *= t; a33 *= t; a34 *= t;
    a41 *= t; a42 *= t; a43 *= t; a44 *= t;

    return *this;
}


/////////////////////////////////////////////////////////////
/// Opérateur /= avec un scalaire
///
/// \param t : Scalaire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
const Matrix4& Matrix4::operator /=(float t)
{
    a11 /= t; a12 /= t; a13 /= t; a14 /= t;
    a21 /= t; a22 /= t; a23 /= t; a24 /= t;
    a31 /= t; a32 /= t; a33 /= t; a34 /= t;
    a41 /= t; a42 /= t; a43 /= t; a44 /= t;

    return *this;
}


/////////////////////////////////////////////////////////////
/// Opérateur de comparaison ==
///
/// \param m : Matrice à comparer
///
/// \return True si les deux matrices sont identiques
///
////////////////////////////////////////////////////////////
bool Matrix4::operator ==(const Matrix4& m) const
{
    return std::fabs(a11 - m.a11) < std::numeric_limits<float>::epsilon() && std::fabs(a12 - m.a12) < std::numeric_limits<float>::epsilon() &&
	    std::fabs(a13 - m.a13) < std::numeric_limits<float>::epsilon() && std::fabs(a14 - m.a14) < std::numeric_limits<float>::epsilon() &&
	    std::fabs(a21 - m.a21) < std::numeric_limits<float>::epsilon() && std::fabs(a22 - m.a22) < std::numeric_limits<float>::epsilon() &&
	    std::fabs(a23 - m.a23) < std::numeric_limits<float>::epsilon() && std::fabs(a24 - m.a24) < std::numeric_limits<float>::epsilon() &&
	    std::fabs(a31 - m.a31) < std::numeric_limits<float>::epsilon() && std::fabs(a32 - m.a32) < std::numeric_limits<float>::epsilon() &&
	    std::fabs(a33 - m.a33) < std::numeric_limits<float>::epsilon() && std::fabs(a34 - m.a34) < std::numeric_limits<float>::epsilon() &&
	    std::fabs(a41 - m.a41) < std::numeric_limits<float>::epsilon() && std::fabs(a42 - m.a42) < std::numeric_limits<float>::epsilon() &&
	    std::fabs(a43 - m.a43) < std::numeric_limits<float>::epsilon() && std::fabs(a44 - m.a44) < std::numeric_limits<float>::epsilon();
}


/////////////////////////////////////////////////////////////
/// Opérateur de comparaison !=
///
/// \param m : Matrice à comparer
///
/// \return True si les deux matrices sont différentes
///
////////////////////////////////////////////////////////////
bool Matrix4::operator !=(const Matrix4& m) const
{
    return !(*this == m);
}


/////////////////////////////////////////////////////////////
/// Opérateur d'accès indexé aux éléments
///
/// \param i : Ligne de la composante à récupérer
/// \param j : Colonne de la composante à récupérer
///
/// \return Référence sur la composante (i, j) de la matrice
///
////////////////////////////////////////////////////////////
float& Matrix4::operator ()(std::size_t i, std::size_t j)
{
    return *(&a11 + (i + 4 * j));
}


/////////////////////////////////////////////////////////////
/// Opérateur d'accès indexé aux éléments - constant
///
/// \param i : Ligne de la composante à récupérer
/// \param j : Colonne de la composante à récupérer
///
/// \return Référence sur la composante (i, j) de la matrice
///
////////////////////////////////////////////////////////////
const float& Matrix4::operator ()(std::size_t i, std::size_t j) const
{
    return *(&a11 + (i + 4 * j));
}


/////////////////////////////////////////////////////////////
/// Opérateur de cast en const float*
///
/// \return Pointeur constant sur les composantes du vecteur
///
////////////////////////////////////////////////////////////
Matrix4::operator const float*() const
{
    return &a11;
}


/////////////////////////////////////////////////////////////
/// Opérateur de cast en float*
///
/// \return Pointeur sur les composantes du vecteur
///
////////////////////////////////////////////////////////////
Matrix4::operator float*()
{
    return &a11;
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur * entre une matrice et un scalaire
///
/// \param m : Matrice
/// \param t : Scalaire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
Matrix4 operator *(const Matrix4& m, float t)
{
    return Matrix4( m.a11 * t, m.a12 * t, m.a13 * t, m.a14 * t,
                    m.a21 * t, m.a22 * t, m.a23 * t, m.a24 * t,
                    m.a31 * t, m.a32 * t, m.a33 * t, m.a34 * t,
                    m.a41 * t, m.a42 * t, m.a43 * t, m.a44 * t);
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur * entre un scalaire et une matrice
///
/// \param t : Scalaire
/// \param m : Matrice
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
Matrix4 operator *(float t, const Matrix4& m)
{
    return m * t;
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur / entre une matrice et un scalaire
///
/// \param m : Matrice
/// \param t : Scalaire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
Matrix4 operator /(const Matrix4& m, float t)
{
    return Matrix4(m.a11 / t, m.a12 / t, m.a13 / t, m.a14 / t,
                    m.a21 / t, m.a22 / t, m.a23 / t, m.a24 / t,
                    m.a31 / t, m.a32 / t, m.a33 / t, m.a34 / t,
                    m.a41 / t, m.a42 / t, m.a43 / t, m.a44 / t);
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur >> entre un flux et une matrice
///
/// \param  Stream : Flux d'entrée
/// \param Mat :    Matrice
///
/// \return Référence sur le flux d'entrée
///
////////////////////////////////////////////////////////////
std::istream& operator >>(std::istream& Stream, Matrix4& Mat)
{
    Stream >> Mat.a11 >> Mat.a12 >> Mat.a13 >> Mat.a14;
    Stream >> Mat.a21 >> Mat.a22 >> Mat.a23 >> Mat.a24;
    Stream >> Mat.a31 >> Mat.a32 >> Mat.a33 >> Mat.a34;
    Stream >> Mat.a41 >> Mat.a42 >> Mat.a43 >> Mat.a44;

    return Stream;
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur << entre un flux et une matrice
///
/// \param Stream : Flux de sortie
/// \param Mat :    Matrice
///
/// \return Référence sur le flux de sortie
///
////////////////////////////////////////////////////////////
std::ostream& operator <<(std::ostream& Stream, const Matrix4& Mat)
{
    Stream << Mat.a11 << " " << Mat.a12 << " " << Mat.a13 << " " << Mat.a14 << std::endl;
    Stream << Mat.a21 << " " << Mat.a22 << " " << Mat.a23 << " " << Mat.a24 << std::endl;
    Stream << Mat.a31 << " " << Mat.a32 << " " << Mat.a33 << " " << Mat.a34 << std::endl;
    Stream << Mat.a41 << " " << Mat.a42 << " " << Mat.a43 << " " << Mat.a44 << std::endl;

    return Stream;
}

}
