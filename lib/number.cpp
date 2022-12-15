#include "number.h"


uint2022_t from_uint(uint32_t i) {
    uint2022_t result;
    result.part[0] = i;
    for (int j = 1; j < 64; j++){
        result.part[j] = 0;
    }
    return result;
}

uint2022_t from_string(const char* buff) {
    uint2022_t result = from_uint(0);
    while ((*buff >= '0') && (*buff <= '9')) {
        uint32_t r = 0;
        uint32_t shift = 1;
        for (int i = 0; (i < 9) && (*buff >= '0' && *buff <= '9'); i++) {
            r = r * 10 + (*buff - '0');
            buff++;
            shift *= 10;
        }
        result = result * shift;
        result = result + from_uint(r);
    }
    return result;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint32_t overflow = 0;
    for (int i = 0; i < 64; i++) {
        result.part[i] = lhs.part[i] + rhs.part[i] + overflow;
        if ( uint64_t (lhs.part[i]) + rhs.part[i] + overflow >= kmax_of_uint32_t + 1 ){
            overflow = 1;
        } else
            overflow = 0;
    }
    return result;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;
    uint32_t overflow = 0;
    for (int i = 0; i < 64; ++i) {
        result.part[i] = lhs.part[i] - rhs.part[i] - overflow;
        if ( int64_t (lhs.part[i]) - rhs.part[i] - overflow < 0){
            overflow = 1;
        } else
            overflow = 0;
    }
    return result;
}

uint2022_t operator*(const uint2022_t& lhs, const uint32_t& rhs) {
    uint2022_t result = from_uint(0);
    uint32_t overflow = 0;
    for (int j = 0; j < 64; ++j) {
        result.part[j] = lhs.part[j] * rhs + overflow;
        overflow = (uint64_t(lhs.part[j]) * rhs + overflow) / (kmax_of_uint32_t + 1);
    }
    return result;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result = from_uint(0);
    uint2022_t t;
    uint32_t overflow = 0;
    for (int i = 0; i < 64; ++i) {
        t = from_uint(0);
        for (int j = 0; i + j < 64; ++j) {
            t.part[i + j] = (lhs.part[j] * rhs.part[i] + overflow);
            overflow = (uint64_t(lhs.part[j]) * rhs.part[i] + overflow) / (kmax_of_uint32_t + 1);

        }
        result = result + t;
    }
    return result;
}

uint2022_t operator/(const uint2022_t &lhs, const uint32_t &rhs) {
    uint2022_t result = from_uint(0);
    uint64_t remainder = 0;
    for (int j = 63; j >= 0; --j) {
        result.part[j] = (remainder * (kmax_of_uint32_t + 1) + lhs.part[j]) / rhs;
        remainder = (remainder * (kmax_of_uint32_t + 1) + lhs.part[j]) % rhs;
    }
    return result;
}

    bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
        for (int i = 0; i < 64; ++i) {
            if ( lhs.part[i] != rhs.part[i] )
                return false;
        }
        return true;
    }

    bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
        return !(lhs == rhs);
    }

    std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
        stream << "Implement me";

        if (value != from_uint(0)) {
            uint2022_t tenth_of_value = value / 10;
            std::cout << tenth_of_value;
            uint2022_t remainder = value - tenth_of_value * from_uint(10);
            std::cout << remainder.part[0];
        }
        return stream;
    }