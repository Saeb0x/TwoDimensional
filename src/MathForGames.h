#pragma once

#include <cmath>
#include <limits>
#include <random>


namespace BasicMath
{
	const float PI = 3.14f;
	const float TwoPI = 2.0f * PI;
	const float PIOverTwo = PI / 2.0f;
	const float Infinity = std::numeric_limits<float>::infinity();
	const float NegativeInfinity = -std::numeric_limits<float>::infinity();


	inline float Absolute(float value)
	{
		return fabs(value);
	}

	inline float Square(float value)
	{
		return sqrtf(value);
	}

	inline void RandomSeeding()
	{
		srand((unsigned int)time(NULL));
	}

	inline int Random(int minRangeValue, int maxRangeValue)
	{
		return (minRangeValue + rand() % (maxRangeValue + 1 - minRangeValue));
	}

	// Trigonometry
	inline float Cosine(float angle)
	{
		return cosf(angle);
	}

	inline float Sine(float angle)
	{
		return sinf(angle);
	}

	inline float Tangent(float angle)
	{
		return tanf(angle);
	}

	inline float DegreesToRadians(float degrees)
	{
		return (degrees * PI / 180.0f);
	}
	inline float RadiansToDegrees(float radians)
	{
		return (radians * 180.0f / PI);
	}

	inline bool NearZero(float value, float epsilon = 0.001f)
	{
		if (fabs(value) <= epsilon)
		{
			return true;
		}
		else
			return false;
	}

	// Maximum and Minimum
	template<typename DataType>
	DataType Max(const DataType& num1, const DataType& num2)
	{
		return (num1 > num2 ? num1 : num2);
	}

	template<typename DataType>
	DataType Min(const DataType& num1, const DataType& num2)
	{
		return (num1 > num2 ? num2 : num1);
	}

	template<typename DataType>
	DataType Clamp(const DataType& number, const DataType& minRangeValue, const DataType& maxRangeValue)
	{
		return Min(maxRangeValue, Max(minRangeValue, number));
	}
}

// 2D Vector
class Vector2D
{
public:
	float x;
	float y;
	
	Vector2D() : x(0), y(0) {};
	explicit Vector2D(float pX, float pY) : x(pX), y(pY) {};

	void SetComponents(float pX, float pY)
	{
		x = pX;
		y = pY;
	}

	// Two vectors addition, returns the resultant vector
	friend Vector2D operator+(const Vector2D& vector1, const Vector2D& vector2)
	{
		return Vector2D(vector1.x + vector2.x, vector1.y + vector2.y);
	}

	// Two vectors subtraction
	friend Vector2D operator-(const Vector2D& vector1, const Vector2D& vector2)
	{
		return Vector2D(vector1.x - vector2.x, vector1.y - vector2.y);
	}

	// Component-wise multiplication
	friend Vector2D operator*(const Vector2D& vector1, const Vector2D& vector2)
	{
		return Vector2D(vector1.x * vector2.x, vector1.y * vector2.y);
	}

	// Scalar Multiplication
	friend Vector2D operator*(const Vector2D& vector, float scalar)
	{
		return Vector2D(vector.x * scalar, vector.y * scalar);
	}

	friend Vector2D operator*(float scalar, const Vector2D& vector)
	{
		return Vector2D(vector.x * scalar, vector.y * scalar);
	}

	// Scalar *=
	Vector2D& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	// Vector +=
	Vector2D& operator+=(const Vector2D& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	// Vector -=
	Vector2D& operator-=(const Vector2D& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}

	// Vector's length squared 
	float LengthSquared() const
	{
		return (x * x + y * y);
	}

	// Vector's length
	float Length() const
	{
		return (BasicMath::Square((LengthSquared())));
	}

	// Normalize this vector
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	// Given vector normalization
	static Vector2D Normalize(const Vector2D& vec)
	{
		Vector2D temporary = vec;
		temporary.Normalize();
		return temporary;
	}

	// Dot product between two vectors (a.b)
	static float Dot(const Vector2D& a, const Vector2D& b)
	{
		return (a.x * b.x + a.y * b.y);
	}

	static const Vector2D Zero;
};