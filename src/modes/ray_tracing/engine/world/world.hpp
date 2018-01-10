#pragma once

#include "engine/ray/intersect_info.hpp"
#include "engine/ray/ray.hpp"

namespace ray {

    class World {
    public:
        IntersectInfo castRay(Ray &ray);
    };
}
