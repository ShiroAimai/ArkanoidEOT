#include "pch.h"
#include "Transform2D.h"
#include "Vec2.h"
#include "Util.h"

Transform2D::Transform2D()
{
	SetIdentity();
}

Transform2D::Transform2D(const Transform2D& other)
{
	Set(other.GetTranslation(), other.GetRotation(), other.GetScale());
}

const Transform2D Transform2D::Identity = Transform2D();

Transform2D& Transform2D::SetIdentity()
{
	_m[0][0] = _m[1][1] = 1.f;
	_m[0][1] = _m[0][2] = _m[1][0] = _m[1][2] = 0.f;

	return *this;
}

Transform2D& Transform2D::Set(const Vec2& Translation, float Rotation, const Vec2& Scale)
{
	SetIdentity();
	SetTranslation(Translation);
	SetScale(Scale);
	SetRotation(Rotation);
	
	return *this;
}

Transform2D& Transform2D::SetTranslation(const Vec2& Translation)
{
	_m[0][2] = Translation.x;
	_m[1][2] = Translation.y;

	return *this;
}

Vec2 Transform2D::GetTranslation() const
{
	Vec2 res;
	res.x = _m[0][2];
	res.y = _m[1][2];

	return res;
}

Transform2D& Transform2D::SetRotation(float angle)
{
	const Vec2 CurrentScale = GetScale();
	const float cos = cosf(angle), sin = sinf(angle);
	_m[0][0] = cos * CurrentScale.x;
	_m[0][1] = -sin * CurrentScale.x;
	_m[1][0] = sin * CurrentScale.y;
	_m[1][1] = cos * CurrentScale.y;

	return *this;
}

float Transform2D::GetRotation() const
{
	float xScale = sqrtf(MathUtil::sqr(_m[0][0]) + MathUtil::sqr(_m[0][1])); //lossy scale
	float angle = acosf(_m[0][0] / xScale);
	if (_m[1][0] < -MathUtil::EPS) //it means its an angle near the 360
	{
		angle = DirectX::XM_2PI - angle;
 	}
	return angle;
}

Transform2D& Transform2D::SetScale(const Vec2& Scale)
{
	Vec2 OldScale = GetScale();
	float factorX = Scale.x / OldScale.x;
	float factorY = Scale.y / OldScale.y;
	_m[0][0] *= factorX;
	_m[0][1] *= factorX;
	_m[1][0] *= factorY;
	_m[1][1] *= factorY;
	return *this;
}

Vec2 Transform2D::GetScale() const
{
	return Vec2(sqrtf(MathUtil::sqr(_m[0][0]) + MathUtil::sqr(_m[0][1])),
		sqrtf(MathUtil::sqr(_m[1][0]) + MathUtil::sqr(_m[1][1])));
}

Transform2D& Transform2D::Invert()
{
	Transform2D old(*this);
	const float invDet = 1.f / (_m[0][0] * _m[1][1] - _m[0][1] * _m[1][0]);

	_m[0][0] = old._m[1][1] * invDet;
	_m[0][1] = -old._m[1][0] * invDet;
	_m[0][2] = (old._m[0][1] * old._m[1][2] - old._m[0][2] * old._m[1][1]) * invDet;
	_m[1][0] = -old._m[1][0] * invDet;
	_m[1][1] = old._m[0][0] * invDet;
	_m[1][2] = (old._m[0][2] * old._m[1][0] - old._m[0][0] * old._m[1][2]) * invDet;

	return *this;
}

Transform2D Transform2D::GetInverse() const
{
	Transform2D inverse(*this);
	inverse.Invert();
	return inverse;
}

Vec2 Transform2D::Apply(const Vec2& v) const
{
	// apply s r t
	Vec2 res;
	const Vec2 scale = GetScale();
	res.x *= scale.x;
	res.y = scale.y;
	const float rotation = GetRotation();
	res = res.rotate(rotation);
	const Vec2 translation = GetTranslation();
	return res + translation;
}

Transform2D operator*(const Transform2D& Second, const Transform2D& First)
{
	Transform2D res;
	for (int row = 0; row < 2; ++row)
	{
		res._m[row][0] = Second._m[row][0] * First._m[0][0] + Second._m[row][1] * First._m[1][0];
		res._m[row][1] = Second._m[row][0] * First._m[0][1] + Second._m[row][1] * First._m[1][1];
		res._m[row][2] = Second._m[row][0] * First._m[0][2] + Second._m[row][1] * First._m[1][2] + Second._m[row][2];
	}
	return res;
}
