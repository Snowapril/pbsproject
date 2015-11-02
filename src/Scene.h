#pragma once

#include "Common.h"
#include "Vector.h"
#include "Box.h"
#include "Properties.h"

#include <string>
#include <vector>

namespace pbs {

class Scene {
public:
    struct World {
        Box3f bounds;
    };
    struct Box {
        Box3f bounds;
    };
    struct Sphere {
        Vector3f position;
        float radius;
    };

    Properties settings;

    World world;
    std::vector<Box> boxes;
    std::vector<Sphere> spheres;

    Scene();

    std::string dump() const;

    static Scene load(const std::string &filename);

private:
};


} // namespace pbs
