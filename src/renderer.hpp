#pragma once
#include <fstream>
#include "definitions.hpp"

inline void save_image(ui32 width, ui32 height) {
    std::ofstream outfile("render.ppm");
    outfile << "P3\n" << width << ' ' << height << "\n255\n";
}
