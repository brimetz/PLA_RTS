#ifndef __VEC2_H__
#define __VEC2_H__

#include <ostream>

	/**
	* @brief Vector3 structure
	*/
	struct QXvec2
	{
#pragma region Attributes

		union
		{
			struct { float x, y; };
			struct { float r, g; };
			float e[2];
		};

		static const QXvec2	zero;
		static const QXvec2	up;
		static const QXvec2	down;
		static const QXvec2	left;
		static const QXvec2	right;

#pragma endregion Attributes

#pragma region Constructors

		/**
		 * @brief Construct a new QXvec2 object
		 * 
		 * @param posX Value for x parameter 0 by default
		 * @param posY Value for y parameter 0 by default
		 */
		QXvec2(const float& posX = 0.f, const float& posY = 0.f) noexcept;

		/**
		 * @brief Construct a new QXvec2 object
		 * 
		 * @param vec Vector to copy
		 */
		QXvec2(const QXvec2& vec)noexcept;

		/**
		 * @brief Construct a new QXvec2 object
		 * 
		 * @param vec Vector to move
		 */
		QXvec2(QXvec2&& vec) noexcept;

		/**
		 * @brief Destroy the QXvec2 object
		 */
		~QXvec2() = default;

#pragma endregion Constructors

#pragma region Functions

		/**
		 * @brief Compute Angle between two vectors
		 * 
		 * @param vector Destination vector 
		 * @return float Angle value in radian
		 */
		float 	Angle(const QXvec2& vect) const noexcept;

		/**
		 * @brief Cross product between two vectors
		 * 
		 * @param vector Vector to compute cross product
		 * @return float float result of the cross product
		 */
		float		Cross(const QXvec2& vect) const noexcept;

		/**
		 * @brief Dot product between two vectors
		 * 
		 * @param vector Vector to compute dot product
		 * @return float Result of the dot product
		 */
		float		Dot(const QXvec2& vect) const noexcept;

		/**
		 * @brief Check if two vectors are collinear
		 * 
		 * @param vector Vector to check collinearity
		 * @return true Vectors are collinear
		 * @return false Vectors are not collinear
		 */
		bool		IsCollinear(const QXvec2& vect) const noexcept;

		/**
		 * @brief Length (magnitude) of current vector
		 * 
		 * @return float Length value
		 */
		float		Length() const noexcept;

		/**
		 * @brief Normalize vector
		 * 
		 * @return QXvec2& Reference of current vector
		 */
		QXvec2&		Normalize() noexcept;

		/**
		 * @brief Normalize vector
		 * 
		 * @return QXvec2 Vector normalized
		 */
		QXvec2		Normalized() const noexcept;

		/**
		 * @brief Multiply vectors values by constant
		 * 
		 * @param value Scaling value
		 * @return QXvec2& Reference of current vector
		 */
		QXvec2&		Scale(float value) noexcept;

		/**
		 * @brief Multiply vectors values by constant
		 * 
		 * @param value Scaling value
		 * @return QXvec2& Scaled vector
		 */
		QXvec2		Scale(float value) const noexcept;

		/**
		 * @brief Square length of current vector
		 * 
		 * @return float Square length value
		 */
		float		SqrLength() const noexcept;

		/**
		 * @brief Make a string with vector values
		 * 
		 * @return std::string String with vector
		 */
		std::string	ToString() const noexcept;

#pragma region Operators
		/* Copy and move operator */

		/**
		 * @brief Operator = by copy
		 *
		 * @param vect Vector to copy
		 * @return QXvec2& reference of current vector
		 */
		QXvec2& operator=(const QXvec2& vect) noexcept;

		/**
		 * @brief Operator = by move
		 *
		 * @param vect Vector to copy
		 * @return QXvec2& reference of current vector
		 */
		QXvec2& operator=(QXvec2&& vect) noexcept;

		/* Mathematics operators */

		/**
		 * @brief Operator for vector addition
		 *
		 * @param vect Vector to add
		 * @return QXvec2& reference of current vector
		 */
		QXvec2& operator+=(const QXvec2& vect) noexcept;

		/**
		 * @brief Operator for addition
		 *
		 * @param vect Vector to substract
		 * @return QXvec2& New vector
		 */
		QXvec2		operator+(const QXvec2& vect) const noexcept;

		/**
		 * @brief Operator for substraction
		 *
		 * @param vect Vector to substract
		 * @return QXvec2& Reference of current vector
		 */
		QXvec2& operator-=(const QXvec2& vect) noexcept;

		/**
		 * @brief Operator for substraction
		 *
		 * @param vect Vector to substract
		 * @return QXvec2 New vector
		 */
		QXvec2		operator-(const QXvec2& vect) const noexcept;

		/**
		 * @brief Create a new QXvec2 as the oposite of the vector
		 *
		 * @return QXvec2 New vector
		 */
		QXvec2		operator-() const noexcept;

		/**
		 * @brief Operator for division by scalar
		 *
		 * @param value Scalar to divide
		 * @return QXvec2& Reference of current vector
		 */
		QXvec2& operator/=(float value) noexcept;

		/**
		 * @brief Operator for division by scalar
		 *
		 * @param value Scalar to divide
		 * @return QXvec2 New vector
		 */
		QXvec2		operator/(float value) const noexcept;

		/**
		 * @brief Operator for multiplication by scalar
		 *
		 * @param value Scalar to muultiply
		 * @return QXvec2& Reference of current vector
		 */
		QXvec2& operator*=(float nb) noexcept;

		/**
		 * @brief Operator for multiplication by scalar
		 *
		 * @param value Scalar to multiply
		 * @return QXvec2 New vector
		 */
		QXvec2		operator*(float value) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vect Vector to compare
		 * @return true Vectors have same length
		 * @return false Vectors have different length
		 */
		bool		operator==(const QXvec2& vect) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vect Vector to compare
		 * @return true Vectors have different length
		 * @return false Vectors have same length
		 */
		bool		operator!=(const QXvec2& vect) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vect Vector to compare
		 * @return true Vector length is inferior to compared vector
		 * @return false Vector length strickly superior to compared vector
		 */
		bool		operator<=(const QXvec2& vect) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vect Vector to compare
		 * @return true Vector length is strickly inferior to compared vector
		 * @return false Vector length is superior or equal to compared vector
		 */
		bool		operator<(const QXvec2& vect) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vect Vector to compare
		 * @return true Vector length is superior or equal to compared vector
		 * @return false Vector length is strickly inferior to compared vector
		 */
		bool		operator>=(const QXvec2& vect) const noexcept;

		/**
		 * @brief Operator to compare vector length
		 *
		 * @param vect Vector to compare
		 * @return true Vector length is strickly superior to compared vector
		 * @return false Vector length is inferior or equal to compared vector
		 */
		bool		operator>(const QXvec2& vect) const noexcept;

		/* Operator accessor*/

		/**
		 * @brief Operator to access vector values as an array
		 *
		 * @param idx Index of the array
		 * @return float& reference of the vector value
		 */
		const float 	operator[](const unsigned int idx) const noexcept;

		/**
		 * @brief Operator to access vector values as an array
		 *
		 * @param idx Index of the array
		 * @return float& reference of the vector value
		 */
		float& operator[](const unsigned int idx) noexcept;

#pragma endregion Operators

#pragma endregion Functions
	};

	/**
	 * @brief Operator to print vector
	 *
	 * @param stream Stream to add the vector
	 * @param vector Vector to add to the stream
	 * @return std::ostream& Reference to the stream
	 */
	std::ostream&	operator<<(std::ostream& os, const QXvec2& vect) noexcept;

	/**
	 * @brief Operator to add a print of vector in string
	 *
	 * @param string string to add the vector
	 * @param vector Vector to add to the stream
	 * @return std::string New string
	 */
	std::string		operator+(std::string& str, const QXvec2& vect) noexcept;

namespace std
{
	template<>
	struct hash<QXvec2>
	{
		size_t operator()(const QXvec2& v)
		{
			return std::hash<float>{}(v.x) + std::hash<float>{}(v.y);
		}
	};
}

#endif // __VEC2_H__
