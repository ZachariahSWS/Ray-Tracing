#pragma once
#include <fstream>
#include "definitions.hpp"

inline void save_image(u32 width, u32 height) {
    std::ofstream outfile("render.ppm");
    outfile << "P3\n" << width << ' ' << height << "\n255\n";
}
