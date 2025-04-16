#pragma once

///////////////////////////////////////////////////////////
// this file is simulate unix uuid/uuid.h

#include "../uuid.h"
#include <string>
#include <cstring>
#include <random>
#include <array>

typedef unsigned char uuid_t[16];

inline uuids::uuid_random_generator& get_uuid_gen() {
    static uuids::uuid_random_generator gen = []() {
        std::random_device rd;
        std::array<int, std::mt19937::state_size> seed_data{};
        std::generate(seed_data.begin(), seed_data.end(), std::ref(rd));
        std::seed_seq seq(seed_data.begin(), seed_data.end());
        std::mt19937 generator(seq);
        return uuids::uuid_random_generator{generator};
    }();
    return gen;
}

inline void uuid_generate(uuid_t out) {
    uuids::uuid id = get_uuid_gen()();
    std::memcpy(out, id.as_bytes().data(), 16);
}

inline void uuid_unparse(const uuid_t uu, char* out) {
    uuids::uuid id;
    std::memcpy((void*)id.as_bytes().data(), uu, 16);
    std::string s = uuids::to_string(id);
    std::memcpy(out, s.c_str(), 37); // includes null terminator
}

inline void uuid_clear(uuid_t uu) {
    std::memset(uu, 0, 16);
}