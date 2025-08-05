#pragma once

#include "Angle.hpp"
#include "units/Vector2D.hpp"
#include "units/units.hpp"

namespace units {

template<typename derivatives>
class FAbstractPose;

/**
 * @class Pose
 *
 * @brief A class that represents a position and orientation in 2D space
 *
 * This class inherits from Vector2D<Length / derivatives>, and has an
 * additional Orientation component of type <Angle / derivatives>, where
 * derivatives is a power of time.
 */
template<typename derivatives>
class AbstractPose
    : public Vector2D<Divided<Length, Exponentiated<Time, derivatives>>> {
    using Len = Divided<Length, Exponentiated<Time, derivatives>>;
    using Vector = Vector2D<Len>;

  public:
    Divided<Angle, Exponentiated<Time, derivatives>>
      orientation; /** Orientation */

    /**
     * @brief Construct a new Pose object
     *
     * This constructor initializes x, y, and orientation to 0
     */
    constexpr AbstractPose()
        : Vector(),
          orientation(0.0) {}

    /**
     * @brief Construct a new Pose object
     *
     * This constructor initializes orientation to 0
     *
     * @param v position
     */
    constexpr AbstractPose(Vector v)
        : Vector(v),
          orientation(0.0) {}

    /**
     * @brief Construct a new Pose object
     *
     * @param v position
     * @param orientation orientation
     */
    constexpr AbstractPose(
      Vector v,
      Divided<Angle, Exponentiated<Time, derivatives>> orientation)
        : Vector(v),
          orientation(orientation) {}

    /**
     * @brief Construct a new Pose object
     *
     * This constructor initializes orientation to 0
     *
     * @param x x position
     * @param y y position
     */
    constexpr AbstractPose(Len x, Len y)
        : Vector(x, y),
          orientation(0.0) {}

    /**
     * @brief Construct a new Pose object
     *
     * @param x x position
     * @param y y position
     * @param orientation orientation
     */
    constexpr AbstractPose(
      Len x,
      Len y,
      Divided<Angle, Exponentiated<Time, derivatives>> orientation)
        : Vector(x, y),
          orientation(orientation) {}

    constexpr AbstractPose(FAbstractPose<derivatives> pose)
        : Vector(pose.x, pose.y),
          orientation(pose.orientation) {}
};

// float variant
template<typename derivatives>
class FAbstractPose
    : public Vector2D<Divided<FLength, Exponentiated<FTime, derivatives>>> {
    using Len = Divided<FLength, Exponentiated<FTime, derivatives>>;
    using Vector = Vector2D<Len>;

  public:
    Divided<FAngle, Exponentiated<FTime, derivatives>>
      orientation; /** Orientation */

    /**
     * @brief Construct a new Pose object
     *
     * This constructor initializes x, y, and orientation to 0
     */
    constexpr FAbstractPose()
        : Vector(),
          orientation(0.0) {}

    /**
     * @brief Construct a new Pose object
     *
     * This constructor initializes orientation to 0
     *
     * @param v position
     */
    constexpr FAbstractPose(Vector v)
        : Vector(v),
          orientation(0.0) {}

    /**
     * @brief Construct a new Pose object
     *
     * @param v position
     * @param orientation orientation
     */
    constexpr FAbstractPose(
      Vector v,
      Divided<FAngle, Exponentiated<Time, derivatives>> orientation)
        : Vector(v),
          orientation(orientation) {}

    /**
     * @brief Construct a new Pose object
     *
     * This constructor initializes orientation to 0
     *
     * @param x x position
     * @param y y position
     */
    constexpr FAbstractPose(Len x, Len y)
        : Vector(x, y),
          orientation(0.0) {}

    /**
     * @brief Construct a new Pose object
     *
     * @param x x position
     * @param y y position
     * @param orientation orientation
     */
    constexpr FAbstractPose(
      Len x,
      Len y,
      Divided<FAngle, Exponentiated<FTime, derivatives>> orientation)
        : Vector(x, y),
          orientation(orientation) {}

    constexpr FAbstractPose(AbstractPose<derivatives> pose)
        : Vector(pose.x, pose.y),
          orientation(pose.orientation) {}
};

// Position Pose (Length, Angle)
using Pose = AbstractPose<std::ratio<0>>;
// Velocity Pose (Length / Time, Angle / Time)
using VelocityPose = AbstractPose<std::ratio<1>>;
// AccelerationPose (Length / Time^2, Angle / Time^2)
using AccelerationPose = AbstractPose<std::ratio<2>>;

// Position Pose (Length, Angle)
using FPose = FAbstractPose<std::ratio<0>>;
// Velocity Pose (Length / Time, Angle / Time)
using FVelocityPose = FAbstractPose<std::ratio<1>>;
// AccelerationPose (Length / Time^2, Angle / Time^2)
using FAccelerationPose = FAbstractPose<std::ratio<2>>;

} // namespace units

template<>
struct std::formatter<units::Pose, char> : std::formatter<double, char> {
    // Parse specifiers (using the base class's parse function)
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        // Call parse on the current object (base class subobject)
        return std::formatter<double, char>::parse(ctx);
    }

    // Format the units::Pose object
    template<typename FormatContext>
    auto format(const units::Pose& vector, FormatContext& ctx) const {
        auto it = ctx.out();
        it = format_to(it, "(");

        // Create temporary formatter objects for Length and Angle
        std::formatter<Length, char> fmtLength {};
        std::formatter<Angle, char> fmtAngle {};

        // Use the temporary objects to format each component.
        it = fmtLength.format(vector.x, ctx);
        it = format_to(it, ", ");
        it = fmtLength.format(vector.y, ctx);
        it = format_to(it, ", ");
        it = fmtAngle.format(vector.orientation, ctx);
        it = format_to(it, ")");

        return it;
    }
};

template<>
struct std::formatter<units::FPose, char> : std::formatter<float, char> {
    // Parse specifiers (using the base class's parse function)
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        // Call parse on the current object (base class subobject)
        return std::formatter<float, char>::parse(ctx);
    }

    // Format the units::Pose object
    template<typename FormatContext>
    auto format(const units::FPose& vector, FormatContext& ctx) const {
        auto it = ctx.out();
        it = format_to(it, "(");

        // Create temporary formatter objects for Length and Angle
        std::formatter<FLength, char> fmtLength {};
        std::formatter<FAngle, char> fmtAngle {};

        // Use the temporary objects to format each component.
        it = fmtLength.format(vector.x, ctx);
        it = format_to(it, ", ");
        it = fmtLength.format(vector.y, ctx);
        it = format_to(it, ", ");
        it = fmtAngle.format(vector.orientation, ctx);
        it = format_to(it, ")");

        return it;
    }
};
