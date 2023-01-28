#ifndef PHYSICALOBJECTSCALE_HPP
#define PHYSICALOBJECTSCALE_HPP

#include "PhysicalObject.hpp"

namespace asteroids {

    class PhysicalObjectScale : public PhysicalObject<PhysicalObjectScale> {
    public:

        using Ptr = std::shared_ptr<PhysicalObjectScale>;

        explicit PhysicalObjectScale(float radius): PhysicalObject<PhysicalObjectScale>(radius) {}
        PhysicalObjectScale() = default;
        virtual ~PhysicalObjectScale() = default;

        virtual float getScale() = 0;
    };


}

#endif // PHYSICALOBJECTSCALE_HPP
