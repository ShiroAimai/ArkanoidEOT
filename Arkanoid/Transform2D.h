#pragma once

struct Vec2;
class Transform2D
{
private:
	//2 rows and 3 columns
	//we spare a row of only 0 and 1
	float _m[2][3];

public:
	Transform2D();
	Transform2D(const Transform2D&);

	static const Transform2D Identity;

	Transform2D& SetIdentity();
	Transform2D& Set(const Vec2& Translation, float Rotation, const Vec2& Scale);

	Transform2D& SetTranslation(const Vec2& Translation);
	Vec2 GetTranslation() const;
	Transform2D& SetRotation(float angle);
	float GetRotation() const;
	Transform2D& SetScale(const Vec2& Scale);
	Vec2 GetScale() const;

	Transform2D& Invert();
	Transform2D GetInverse() const;

	//Second * First -> First is applied first then second
	friend Transform2D operator*(const Transform2D& Second, const Transform2D& First);

	Vec2 Apply(const Vec2& v) const;
};
 
