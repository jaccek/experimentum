#include "world.hpp"

#include <cmath>

using namespace std;
using namespace math;

namespace ray {

    IntersectInfo World::castRay(Ray &ray) {
        // TODO: temporary world has only one sphere
        Vec3 sphereCenter(0.0f, 0.5f, 2.0f);
        float sphereRadius = 0.5f;

        auto rayDirection = ray.direction();
        float distance = ((sphereCenter - ray.castingPoint()).cross(rayDirection)).length();

        IntersectInfo info;
        info.hitsObject = distance <= sphereRadius;

        return info;
    }
}
