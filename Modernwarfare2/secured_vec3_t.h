#pragma once
#include "vec.h"

class secured_vec3_t
{
private:
    int keys[5];

    __forceinline uintptr_t base(int idx) const
    {
        return reinterpret_cast<uintptr_t>(&keys[idx]);
    }
public:
    vec3_t get() const
    {
        int v42 = 0, v54[3] = {};
        v42 = keys[3];
        v54[0] = static_cast<int>(keys[0] ^ ((base(0) ^ v42) * ((base(0) ^ v42) + 2)));
        v54[1] = static_cast<int>(keys[1] ^ ((base(1) ^ v42) * ((base(1) ^ v42) + 2)));
        v54[2] = static_cast<int>(keys[2] ^ ((v42 ^ base(2)) * ((v42 ^ base(2)) + 2)));
        return vec3_t(*reinterpret_cast<float*>(&v54[0]), *reinterpret_cast<float*>(&v54[1]), *reinterpret_cast<float*>(&v54[2]));
    }

    void set(float x, float y, float z)
    {
        int v42, v43, v54[3];
        v42 = keys[3];
        v54[0] = static_cast<int>(keys[0] ^ ((base(0) ^ v42) * ((base(0) ^ v42) + 2)));
        v54[1] = static_cast<int>(keys[1] ^ ((base(1) ^ v42) * ((base(1) ^ v42) + 2)));
        v54[2] = static_cast<int>(keys[2] ^ ((v42 ^ base(2)) * ((v42 ^ base(2)) + 2)));

        *reinterpret_cast<float*>(&v54[0]) = x;
        *reinterpret_cast<float*>(&v54[1]) = y;
        *reinterpret_cast<float*>(&v54[2]) = z;

        v43 = v42 + keys[4];
        keys[3] = v43;
        keys[0] = static_cast<int>(v54[0] ^ ((v43 ^ base(0)) * ((v43 ^ base(0)) + 2)));
        keys[1] = static_cast<int>(v54[1] ^ ((v43 ^ base(1)) * ((v43 ^ base(1)) + 2)));
        keys[2] = static_cast<int>(v54[2] ^ ((v43 ^ base(2)) * ((v43 ^ base(2)) + 2)));
    }

    void set(vec3_t value)
    {
        return set(value.x, value.y, value.z);
    }
};