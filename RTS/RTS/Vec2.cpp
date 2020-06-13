#include "Vec2.h"

#include <math.h>

#include <string>

#pragma region Attributes

	const QXvec2	QXvec2::zero {0.f, 0.f};
	const QXvec2	QXvec2::up {0.f, 1.f};
	const QXvec2	QXvec2::down {0.f, -1.f};
	const QXvec2	QXvec2::left {-1.f, 0.f};
	const QXvec2	QXvec2::right {1.f, 0.f};

#pragma endregion

#pragma region Constructors

	QXvec2::QXvec2(const float& posX, const float& posY) noexcept :
		x {posX},
		y {posY}
	{}

	QXvec2::QXvec2(const QXvec2& vect) noexcept :
		x{ vect.x },
		y{ vect.y }
	{}

	QXvec2::QXvec2(QXvec2&& vec) noexcept :
		x { std::move(vec.x) },
		y { std::move(vec.y) }
	{}

#pragma endregion

#pragma region Operators

	QXvec2& QXvec2::operator=(const QXvec2& vect) noexcept
	{
		x = vect.x;
		y = vect.y;

		return *this;
	}

	QXvec2& QXvec2::operator=(QXvec2&& vect) noexcept
	{
		x = std::move(vect.x);
		y = std::move(vect.y);

		return *this;
	}

	QXvec2& QXvec2::operator+=(const QXvec2& vect) noexcept
	{
		x += vect.x;
		y += vect.y;

		return *this;
	}

	QXvec2	QXvec2::operator+(const QXvec2& vect) const noexcept
	{
		QXvec2	res;

		res.x = x + vect.x;
		res.y = y + vect.y;

		return res;
	}

	QXvec2& QXvec2::operator-=(const QXvec2& vect) noexcept
	{
		x -= vect.x;
		y -= vect.y;

		return *this;
	}

	QXvec2	QXvec2::operator-(const QXvec2& vect) const noexcept
	{
		QXvec2	res;

		res.x = x - vect.x;
		res.y = y - vect.y;

		return res;
	}

	QXvec2	QXvec2::operator-() const noexcept
	{
		QXvec2	res;

		res.x = -x;
		res.y = -y;

		return res;
	}

	QXvec2& QXvec2::operator/=(float value) noexcept
	{
		x /= value;
		y /= value;

		return *this;
	}

	QXvec2	QXvec2::operator/(float value) const noexcept
	{
		QXvec2	res;

		res.x = x / value;
		res.y = y / value;

		return res;
	}

	QXvec2& QXvec2::operator*=(float nb) noexcept
	{
		x *= nb;
		y *= nb;

		return *this;
	}

	QXvec2	QXvec2::operator*(float value) const noexcept
	{
		QXvec2	res;

		res.x = x * value;
		res.y = y * value;

		return res;
	}

	bool	QXvec2::operator==(const QXvec2& vect) const noexcept
	{
		return SqrLength() == vect.SqrLength();
	}

	bool	QXvec2::operator!=(const QXvec2& vect) const noexcept
	{
		return SqrLength() != vect.SqrLength();
	}

	bool	QXvec2::operator<(const QXvec2& vect) const noexcept
	{
		return SqrLength() < vect.SqrLength();
	}

	bool	QXvec2::operator<=(const QXvec2& vect) const noexcept
	{
		return SqrLength() <= vect.SqrLength();
	}

	bool	QXvec2::operator>(const QXvec2& vect) const noexcept
	{
		return SqrLength() > vect.SqrLength();
	}

	bool	QXvec2::operator>=(const QXvec2& vect) const noexcept
	{
		return SqrLength() >= vect.SqrLength();
	}

	const float QXvec2::operator[](const unsigned int idx) const noexcept
	{
		return e[idx];
	}

	float& QXvec2::operator[](const unsigned int idx) noexcept
	{
		return e[idx];
	}

#pragma endregion

#pragma region Functions

	float QXvec2::Angle(const QXvec2& vect) const noexcept
	{
		return std::atan2(vect.y - y, vect.x - x);	
	}

	float QXvec2::Cross(const QXvec2& vect) const noexcept
	{
		return x * vect.y - vect.x * y;
	}


	float QXvec2::Dot(const QXvec2& vect) const noexcept
	{
		return x * vect.x + y * vect.y;
	}

	bool QXvec2::IsCollinear(const QXvec2& vect) const noexcept
	{
		float res{ Dot(vect) };
		if (res == 1 || res == -1)
			return true;
		return false;
	}

	float	QXvec2::Length() const noexcept
	{
		return sqrt(x * x + y * y);
	}

	QXvec2& QXvec2::Normalize() noexcept
	{
		float	size{ Length() };

		if (size == 0)
			return *this;

		x = x / size;
		y = y / size;

		return *this;
	}

	QXvec2	QXvec2::Normalized() const noexcept
	{
		QXvec2	res;

		float size{ Length() };

	    if (size == 0)
	    	return res;

		res.x = x / size;
		res.y = y / size;

		return res;
	}

	QXvec2& QXvec2::Scale(float nb) noexcept
	{
		x = x * nb;
		y = y * nb;

		return *this;
	}

	QXvec2	QXvec2::Scale(float nb) const noexcept
	{
		QXvec2	res;

		res.x = x * nb;
		res.y = y * nb;

		return res;
	}

	float	QXvec2::SqrLength() const noexcept
	{
		return x * x + y * y;
	}

	std::string	QXvec2::ToString() const noexcept
	{
		std::string vec = std::to_string(x) + ", " + std::to_string(y) + "\n";

		return vec;
	}
#pragma endregion

	std::ostream& operator<<(std::ostream& os, const QXvec2& vect) noexcept
	{
		os << vect.x << ", " << vect.y << std::endl;

		return os;
	}

	std::string operator+(std::string& str, const QXvec2& vect) noexcept
	{
		std::string	res = str + "x : " + std::to_string(vect.x) +
			" , y : " + std::to_string(vect.y);

		return res;
	}
