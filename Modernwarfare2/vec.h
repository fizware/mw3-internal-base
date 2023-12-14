#pragma once
#include <limits>
#include <algorithm>
#include <cmath>
#include <d2d1.h>

#define PITCH 0
#define YAW 1
#define ROLL 2

extern float bits_to_float(std::uint32_t i);
#define M_PI 3.14159265358979323846
#define M_RADPI		57.295779513082f
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )

#define FLOAT32_NAN_BITS     ( std::uint32_t ) 0x7FC00000	// not a number!
#define FLOAT32_NAN          bits_to_float( FLOAT32_NAN_BITS )
#define VEC_T_NAN FLOAT32_NAN

typedef unsigned char   uint8;
#define _BYTE  uint8
#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define ASSERT( _exp ) ( (void ) 0 )
#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)

template <typename T>
T clip_number(const T& n, const T& lower, const T& upper) {
	if (n < lower) return lower;
	if (n > upper) return upper;
	return n;
}

class vec3_t {
public:
	vec3_t();
	vec3_t(float, float, float);
	~vec3_t();



	float x, y, z;
	//union
	//{
	//	struct { float x, y, z; };
	//	float v[3];
	//};



	vec3_t& operator+=(const vec3_t& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}
	vec3_t& operator-=(const vec3_t& v) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}
	vec3_t& operator*=(float v) {
		x *= v; y *= v; z *= v; return *this;
	}
	bool operator==(const vec3_t& v) {
		return (x == v.x) && (y == v.y);
	}
	vec3_t operator+(const vec3_t& v) {
		return vec3_t{ x + v.x, y + v.y, z + v.z };
	}
	vec3_t operator-(const vec3_t& v) {
		return vec3_t{ x - v.x, y - v.y, z - v.z };
	}
	vec3_t operator*(float fl) const {
		return vec3_t(x * fl, y * fl, z * fl);
	}
	vec3_t operator*(const vec3_t& v) const {
		return vec3_t(x * v.x, y * v.y, z * v.z);
	}
	vec3_t& operator/=(float fl) {
		x /= fl;
		y /= fl;
		z /= fl;
		return *this;
	}
	auto operator-(const vec3_t& other) const -> vec3_t {
		auto buf = *this;

		buf.x -= other.x;
		buf.y -= other.y;
		buf.z -= other.z;

		return buf;
	}

	auto operator/(float other) const {
		vec3_t vec;
		vec.x = x / other;
		vec.y = y / other;
		vec.z = z / other;
		return vec;
	}

	float& operator[](int i) {
		return ((float*)this)[i];
	}
	float operator[](int i) const {
		return ((float*)this)[i];
	}

	inline float Length2D() const
	{
		return sqrt((x * x) + (y * y));
	}
	void crossproduct(vec3_t v1, vec3_t v2, vec3_t cross_p) const //ijk = xyz
	{
		cross_p.x = (v1.y * v2.z) - (v1.z * v2.y); //i
		cross_p.y = -((v1.x * v2.z) - (v1.z * v2.x)); //j
		cross_p.z = (v1.x * v2.y) - (v1.y * v2.x); //k
	}
	vec3_t Cross(const vec3_t& vOther) const
	{
		vec3_t res;
		crossproduct(*this, vOther, res);
		return res;
	}

	vec3_t Zero()
	{
		vec3_t ret;
		ret.x = 0;
		ret.y = 0;
		ret.z = 0;
		return ret;
	}

	inline bool isZero() {
		if (x == 0 && y == 0 && z == 0)
			return true;
		else
			return false;
	}

	void init(float ix, float iy, float iz);
	vec3_t clamp();
	vec3_t clamped();
	vec3_t normalized();
	float normalize_float();
	float distance_to(const vec3_t& other);
	float Distance(const vec3_t& other);
	void normalize();
	float length();
	float length_2d_sqr(void) const;
	float dot(const vec3_t& in);
	float dot(const float* in);
	float dot(const float* in) const;
};

// has to be hear
inline vec3_t operator*(float lhs, const vec3_t& rhs) {
	return vec3_t(rhs.x * lhs, rhs.x * lhs, rhs.x * lhs);
}

struct matrix_t
{
	matrix_t() { }
	matrix_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		mat_val[0][0] = m00;	mat_val[0][1] = m01; mat_val[0][2] = m02; mat_val[0][3] = m03;
		mat_val[1][0] = m10;	mat_val[1][1] = m11; mat_val[1][2] = m12; mat_val[1][3] = m13;
		mat_val[2][0] = m20;	mat_val[2][1] = m21; mat_val[2][2] = m22; mat_val[2][3] = m23;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void init(const vec3_t& xAxis, const vec3_t& yAxis, const vec3_t& zAxis, const vec3_t& vecOrigin)
	{
		mat_val[0][0] = xAxis.x; mat_val[0][1] = yAxis.x; mat_val[0][2] = zAxis.x; mat_val[0][3] = vecOrigin.x;
		mat_val[1][0] = xAxis.y; mat_val[1][1] = yAxis.y; mat_val[1][2] = zAxis.y; mat_val[1][3] = vecOrigin.y;
		mat_val[2][0] = xAxis.z; mat_val[2][1] = yAxis.z; mat_val[2][2] = zAxis.z; mat_val[2][3] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix_t(const vec3_t& xAxis, const vec3_t& yAxis, const vec3_t& zAxis, const vec3_t& vecOrigin)
	{
		init(xAxis, yAxis, zAxis, vecOrigin);
	}

	inline void set_origin(vec3_t const& p)
	{
		mat_val[0][3] = p.x;
		mat_val[1][3] = p.y;
		mat_val[2][3] = p.z;
	}

	inline void invalidate(void)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				mat_val[i][j] = VEC_T_NAN;
			}
		}
	}

	float* operator[](int i) { ASSERT((i >= 0) && (i < 3)); return mat_val[i]; }
	const float* operator[](int i) const { ASSERT((i >= 0) && (i < 3)); return mat_val[i]; }
	float* base() { return &mat_val[0][0]; }
	const float* base() const { return &mat_val[0][0]; }

	float mat_val[3][4];
};

struct vec2_t
{
	vec2_t() = default;

	vec2_t(float xy) : x(xy), y(xy) {};
	vec2_t(float x, float y) : x(x), y(y) {};
	vec2_t(float x, float y, float z) : x(x), y(y) {};
	vec2_t(float* arr) : x(arr[PITCH]), y(arr[YAW]) {};

	inline float length() const
	{
		return sqrt(x * x + y * y);
	}

	inline bool is_zero() const
	{
		return x == 0 && y == 0;
	}

#pragma region assignment
	inline vec2_t& operator=(const vec2_t& in)
	{
		x = in.x;
		y = in.y;

		return *this;
	}
#pragma endregion assignment

#pragma region equality
	inline bool operator!=(const vec2_t& in)
	{
		return (x != in.x || y != in.y);
	}

	inline bool operator==(const vec2_t& in)
	{
		return (x == in.x && y == in.y);
	}
#pragma endregion equality

#pragma region addition
	inline vec2_t operator+(vec2_t in) const
	{
		return vec2_t(
			x + in.x,
			y + in.y
		);
	}

	inline vec2_t operator+(float in) const
	{
		return vec2_t(
			x + in,
			y + in
		);
	}

	inline vec2_t& operator+=(vec2_t in)
	{
		x += in.x;
		y += in.y;

		return *this;
	}

	inline vec2_t& operator+=(float in)
	{
		x += in;
		y += in;

		return *this;
	}
#pragma endregion addition

#pragma region substraction
	inline vec2_t operator-(vec2_t in) const
	{
		return vec2_t(
			x - in.x,
			y - in.y
		);
	}

	inline vec2_t operator-(float in) const
	{
		return vec2_t(
			x - in,
			y - in
		);
	}

	inline vec2_t& operator-=(vec2_t in)
	{
		x -= in.x;
		y -= in.y;

		return *this;
	}

	inline vec2_t& operator-=(float in)
	{
		x -= in;
		y -= in;

		return *this;
	}
#pragma endregion substraction

#pragma region multiplication
	inline vec2_t operator*(vec2_t in) const
	{
		return vec2_t(
			x * in.x,
			y * in.y
		);
	}

	inline vec2_t operator*(float in) const
	{
		return vec2_t(
			x * in,
			y * in
		);
	}

	inline vec2_t& operator*=(vec2_t in)
	{
		x *= in.x;
		y *= in.y;

		return *this;
	}

	inline vec2_t& operator*=(float in)
	{
		x *= in;
		y *= in;

		return *this;
	}
#pragma endregion multiplication

#pragma region division
	inline vec2_t operator/(vec2_t in) const
	{
		return vec2_t(
			x / in.x,
			y / in.y
		);
	}

	inline vec2_t operator/(float in) const
	{
		return vec2_t(
			x / in,
			y / in
		);
	}

	inline vec2_t& operator/=(vec2_t in)
	{
		x /= in.x;
		y /= in.y;

		return *this;
	}

	inline vec2_t& operator/=(float in)
	{
		x /= in;
		y /= in;

		return *this;
	}
#pragma endregion division

	float x, y;
};

struct vec4_t
{
	vec4_t() = default;
	vec4_t(float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {};
	vec4_t(float x, float y) : x(x), y(y), z(x), w(y) {};
	vec4_t(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

	vec2_t get_pos() const
	{
		return vec2_t(x, y);
	}

	vec2_t get_size() const
	{
		return vec2_t(z, w);
	}

	float x, y, z, w;
};

struct Vec4 {
public: union { float v[4]; struct { float x; float y; float z; float w; }; };
};
static Vec4 asVec4V(float x, float y, float z, float w) { Vec4 out; out.x = x; out.y = y; out.z = z; out.w = w; return out; }
struct Matrix4x4 { union { Vec4 v[4]; float m[4][4]; struct { Vec4 right; Vec4 up; Vec4 forward; Vec4 trans; }; }; };
typedef Matrix4x4 LinearTransform;

struct AxisAlignedBox
{
	Vec4 min;
	Vec4 max;
};

struct LinearTransform_AABB
{
public:
	LinearTransform m_Transform;
	AxisAlignedBox m_Box;
	char _pad[0x200];
};