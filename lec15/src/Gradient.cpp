#include "Gradient.h"

Gradient::Gradient(const Shape& base, color start, color end,
                   const Projector& shaper,
                   const Modulator& modulator)
        : Shape_decorator{base}
        , start_{start}
        , end_{end}
        , projector_{shaper}
        , modulator_{modulator}
{ }

Shape::color Gradient::color_at(sample weight) const
{
    return interpolate(start_, modulator_.modulate(weight), end_);
}

Shape::color Gradient::color_at(sample x, sample y) const
{
    return color_at(projector_.project(x, y));
}

graphics::color Gradient::color_at(posn point) const
{
    if (contains(point)) {
        sample x = (point.x - get_bbox().left()) / get_bbox().width();
        sample y = (point.y - get_bbox().top()) / get_bbox().height();
        return color_at(x, y);
    } else {
        return color::transparent;
    }
}
