#pragma once

#include "units/units.hpp"

class Angle : public Quantity<std::ratio<0>,
                              std::ratio<0>,
                              std::ratio<0>,
                              std::ratio<0>,
                              std::ratio<1>,
                              std::ratio<0>,
                              std::ratio<0>,
                              std::ratio<0>,
                              double> {
  public:
    explicit constexpr Angle(double value)
        : Quantity<std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<1>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   double>(value) {}

    template<typename OtherFloatType>
    constexpr Angle(Quantity<std::ratio<0>,
                             std::ratio<0>,
                             std::ratio<0>,
                             std::ratio<0>,
                             std::ratio<1>,
                             std::ratio<0>,
                             std::ratio<0>,
                             std::ratio<0>,
                             OtherFloatType> value)
        : Quantity<std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<1>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   double>(value) {};
};

template<>
struct LookupName<Quantity<std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<1>,
                           std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<0>,
                           double>> {
    using Named = Angle;
};

template<>
struct std::formatter<Angle> : std::formatter<double> {
    auto format(const Angle& number, std::format_context& ctx) const {
        auto formatted_float =
          std::formatter<double>::format(number.internal(), ctx);
        return std::format_to(formatted_float, "_stRad");
    }
};

inline std::ostream& operator<<(std::ostream& os, const Angle& quantity) {
    os << quantity.internal() << " rad";
    return os;
}

class FAngle : public Quantity<std::ratio<0>,
                               std::ratio<0>,
                               std::ratio<0>,
                               std::ratio<0>,
                               std::ratio<1>,
                               std::ratio<0>,
                               std::ratio<0>,
                               std::ratio<0>,
                               float> {
  public:
    explicit constexpr FAngle(float value)
        : Quantity<std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<1>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   float>(value) {}

    template<typename OtherFloatType>
    constexpr FAngle(Quantity<std::ratio<0>,
                              std::ratio<0>,
                              std::ratio<0>,
                              std::ratio<0>,
                              std::ratio<1>,
                              std::ratio<0>,
                              std::ratio<0>,
                              std::ratio<0>,
                              OtherFloatType> value)
        : Quantity<std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<1>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   float>(value) {};
};

template<>
struct LookupName<Quantity<std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<1>,
                           std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<0>,
                           float>> {
    using Named = FAngle;
};

template<>
struct std::formatter<FAngle> : std::formatter<float> {
    auto format(const FAngle& number, std::format_context& ctx) const {
        auto formatted_float =
          std::formatter<float>::format(number.internal(), ctx);
        return std::format_to(formatted_float, "_stRad");
    }
};

inline std::ostream& operator<<(std::ostream& os, const FAngle& quantity) {
    os << quantity.internal() << " rad";
    return os;
}

/**
 * @brief DO NOT USE
 *
 * this class prevents conversion errors from compass angles to angles in
 * standard position.
 *
 * consider the following:
 * 0_cDeg gets converted to standard position angles internally, so it's
 * converted to 90 -0_cDeg is converted to standard position angles internally,
 * and only afterwards is the negative applied, so now it equals -90 internally
 *
 * This class solves this problem by introducing the CAngle type. You can do
 * things like negate it, multiply it, etc. without messing up the angle.
 * However, this class can only be created through string literals, you can't do
 * something like CAngle angle = 2_cDeg; because the constructor is private.
 * However, you can do Angle angle = 2_cDeg;
 */
class CAngle {
    // make string literals friends, so they have access to the constructor
    friend constexpr CAngle operator""_cRad(long double value);
    friend constexpr CAngle operator""_cRad(unsigned long long value);
    friend constexpr CAngle operator""_cDeg(long double value);
    friend constexpr CAngle operator""_cDeg(unsigned long long value);
    friend constexpr CAngle operator""_cRot(long double value);
    friend constexpr CAngle operator""_cRot(unsigned long long value);

  public:
    // we don't want CAngle to have move, copy, or assignment operators
    constexpr CAngle& operator=(const CAngle&) = delete;
    constexpr CAngle(const CAngle&) = delete;

    // make CAngle able to be implicitly converted to Angle
    constexpr operator Angle() const {
        return Angle(M_PI_2 - this->value);
    }

    constexpr CAngle operator-() const {
        return CAngle(-this->value);
    }

    constexpr CAngle operator+() const {
        return CAngle(this->value);
    }

  private:
    const double value;

    constexpr CAngle(double value)
        : value(value) {}
};

class FCAngle {
    // make string literals friends, so they have access to the constructor
    friend constexpr FCAngle operator""_FcRad(long double value);
    friend constexpr FCAngle operator""_FcRad(unsigned long long value);
    friend constexpr FCAngle operator""_FcDeg(long double value);
    friend constexpr FCAngle operator""_FcDeg(unsigned long long value);
    friend constexpr FCAngle operator""_FcRot(long double value);
    friend constexpr FCAngle operator""_FcRot(unsigned long long value);

  public:
    // we don't want CAngle to have move, copy, or assignment operators
    constexpr FCAngle& operator=(const FCAngle&) = delete;
    constexpr FCAngle(const FCAngle&) = delete;

    // make CAngle able to be implicitly converted to Angle
    constexpr operator FAngle() const {
        return FAngle(M_PI_2 - this->value);
    }

    constexpr FCAngle operator-() const {
        return FCAngle(-this->value);
    }

    constexpr FCAngle operator+() const {
        return FCAngle(this->value);
    }

  private:
    const float value;

    constexpr FCAngle(float value)
        : value(value) {}
};

/**
 * @brief Angle Distance class
 *
 * yet another helper class to manage the compass angle fiasco (it's getting
 * nuked on May 15 2025)
 *
 * consider the following:
 * Angle exitRange1 = 0_cDeg;
 * Angle exitRange2 = 0_stDeg;
 *
 * It is expected that exitRange1 and exitRange2 is equal to each other.
 * However, this is not the case. 0_cDeg gets converted to 90_stDeg
 * implicitly. So, yet another helper class is necessary (hooray)
 *
 */
// class AngleRange : public Angle {
//   public:
//     explicit constexpr AngleRange(double value)
//         : Angle(fabs(value)) {}
//
//     constexpr AngleRange(Angle value)
//         : Angle(units::abs(value)) {}
//
//     constexpr AngleRange(CAngle value)
//         : Angle(units::abs(Angle(value) - Angle(M_PI_2))) {}
// };

constexpr bool operator==(Angle lhs, CAngle rhs) {
    return lhs == Angle(rhs);
}

constexpr bool operator==(FAngle lhs, FCAngle rhs) {
    return lhs == FAngle(rhs);
}

constexpr Angle rad = Angle(1.0);
constexpr Angle deg = Angle(M_PI / 180);
constexpr Angle rot = Angle(M_TWOPI);

constexpr FAngle Frad = FAngle(1.0);
constexpr FAngle Fdeg = FAngle(M_PI / 180);
constexpr FAngle Frot = FAngle(M_TWOPI);

NEW_UNIT(AngularVelocity, radps, 0, 0, -1, 0, 1, 0, 0, 0)
NEW_UNIT_LITERAL(AngularVelocity, degps, deg / sec)
NEW_UNIT_LITERAL(AngularVelocity, rps, rot / sec)
NEW_UNIT_LITERAL(AngularVelocity, rpm, rot / min)

NEW_UNIT(AngularAcceleration, radps2, 0, 0, -2, 0, 1, 0, 0, 0)
NEW_UNIT_LITERAL(AngularAcceleration, degps2, deg / sec / sec)
NEW_UNIT_LITERAL(AngularAcceleration, rps2, rot / sec / sec)
NEW_UNIT_LITERAL(AngularAcceleration, rpm2, rot / min / min)

NEW_UNIT(AngularJerk, radps3, 0, 0, -3, 0, 1, 0, 0, 0)
NEW_UNIT_LITERAL(AngularJerk, rps3, rot / sec / sec / sec)
NEW_UNIT_LITERAL(AngularJerk, rpm3, rot / min / min / min)

// Angle declaration operators
// Standard orientation
constexpr Angle operator""_stRad(long double value) {
    return Angle(static_cast<double>(value));
}

constexpr Angle operator""_stRad(unsigned long long value) {
    return Angle(static_cast<double>(value));
}

constexpr Angle operator""_stDeg(long double value) {
    return static_cast<double>(value) * deg;
}

constexpr Angle operator""_stDeg(unsigned long long value) {
    return static_cast<double>(value) * deg;
}

constexpr Angle operator""_stRot(long double value) {
    return static_cast<double>(value) * rot;
}

constexpr Angle operator""_stRot(unsigned long long value) {
    return static_cast<double>(value) * rot;
}

// Compass orientation
constexpr CAngle operator""_cRad(long double value) {
    return CAngle(static_cast<double>(value));
}

constexpr CAngle operator""_cRad(unsigned long long value) {
    return CAngle(static_cast<double>(value));
}

constexpr CAngle operator""_cDeg(long double value) {
    return CAngle(static_cast<double>(value) * deg.internal());
}

constexpr CAngle operator""_cDeg(unsigned long long value) {
    return CAngle(static_cast<double>(value) * deg.internal());
}

constexpr CAngle operator""_cRot(long double value) {
    return CAngle(static_cast<double>(value) * rot.internal());
}

constexpr CAngle operator""_cRot(unsigned long long value) {
    return CAngle(static_cast<double>(value) * rot.internal());
}

// Angle functions
namespace units {
constexpr Number sin(const Angle& rhs) {
    return Number(std::sin(rhs.internal()));
}

constexpr Number cos(const Angle& rhs) {
    return Number(std::cos(rhs.internal()));
}

constexpr Number tan(const Angle& rhs) {
    return Number(std::tan(rhs.internal()));
}

template<isQuantity Q>
constexpr Angle asin(const Q& rhs) {
    return Angle(std::asin(rhs.internal()));
}

template<isQuantity Q>
constexpr Angle acos(const Q& rhs) {
    return Angle(std::acos(rhs.internal()));
}

template<isQuantity Q>
constexpr Angle atan(const Q& rhs) {
    return Angle(std::atan(rhs.internal()));
}

template<isQuantity Q>
constexpr Angle atan2(const Q& lhs, const Q& rhs) {
    return Angle(std::atan2(lhs.internal(), rhs.internal()));
}

// returns a number in the range (-360, 360)
inline static Angle constrainAngle360(Angle in) {
    return mod(in, rot);
}

// returns a number in the range [0, 360)
inline static Angle constrainAngle360_2(Angle in) {
    in = mod(in, rot);
    return in < Angle(0) ? in + rot : in;
}

// returns a number in the range (-180, 180)
inline static Angle constrainAngle180(Angle in) {
    in = mod(in + 180 * deg, rot);
    return in < Angle(0) ? in + 180 * deg : in - 180 * deg;
}
} // namespace units

// Angle to/from operators
// Standard orientation
inline constexpr Angle from_stRad(double value) {
    return Angle(value);
}

inline constexpr Angle from_stRad(Number value) {
    return Angle(value.internal());
}

inline constexpr double to_stRad(Angle quantity) {
    return quantity.internal();
}

inline constexpr Angle from_stDeg(double value) {
    return value * deg;
}

inline constexpr Angle from_stDeg(Number value) {
    return value * deg;
}

inline constexpr double to_stDeg(Angle quantity) {
    return quantity.convert(deg);
}

inline constexpr Angle from_stRot(double value) {
    return value * rot;
}

inline constexpr Angle from_stRot(Number value) {
    return value * rot;
}

inline constexpr double to_stRot(Angle quantity) {
    return quantity.convert(rot);
}

// Compass orientation
inline constexpr Angle from_cRad(double value) {
    return 90 * deg - Angle(value);
}

inline constexpr Angle from_cRad(Number value) {
    return 90 * deg - Angle(value.internal());
}

inline constexpr double to_cRad(Angle quantity) {
    return quantity.internal();
}

inline constexpr Angle from_cDeg(double value) {
    return (90 - value) * deg;
}

inline constexpr Angle from_cDeg(Number value) {
    return (90 - value.internal()) * deg;
}

inline constexpr double to_cDeg(Angle quantity) {
    return (90 * deg - quantity).convert(deg);
}

inline constexpr Angle from_cRot(double value) {
    return (90 - value) * deg;
}

inline constexpr Angle from_cRot(Number value) {
    return (90 - value.internal()) * deg;
}

inline constexpr double to_cRot(Angle quantity) {
    return (90 * deg - quantity).convert(rot);
}

/* float variations */

// Angle declaration operators
// Standard orientation
constexpr FAngle operator""_FstRad(long double value) {
    return FAngle(static_cast<float>(value));
}

constexpr FAngle operator""_FstRad(unsigned long long value) {
    return FAngle(static_cast<float>(value));
}

constexpr FAngle operator""_FstDeg(long double value) {
    return static_cast<float>(value) * Fdeg;
}

constexpr FAngle operator""_FstDeg(unsigned long long value) {
    return static_cast<float>(value) * Fdeg;
}

constexpr FAngle operator""_FstRot(long double value) {
    return static_cast<float>(value) * Frot;
}

constexpr FAngle operator""_FstRot(unsigned long long value) {
    return static_cast<float>(value) * Frot;
}

// Compass orientation
constexpr FCAngle operator""_FcRad(long double value) {
    return FCAngle(static_cast<float>(value));
}

constexpr FCAngle operator""_FcRad(unsigned long long value) {
    return FCAngle(static_cast<float>(value));
}

constexpr FCAngle operator""_FcDeg(long double value) {
    return FCAngle(static_cast<float>(value) * Fdeg.internal());
}

constexpr FCAngle operator""_FcDeg(unsigned long long value) {
    return FCAngle(static_cast<float>(value) * Fdeg.internal());
}

constexpr FCAngle operator""_FcRot(long double value) {
    return FCAngle(static_cast<float>(value) * Frot.internal());
}

constexpr FCAngle operator""_FcRot(unsigned long long value) {
    return FCAngle(static_cast<float>(value) * Frot.internal());
}

// FAngle functions
namespace units {
constexpr Number sin(const FAngle& rhs) {
    return Number(std::sin(rhs.internal()));
}

constexpr Number cos(const FAngle& rhs) {
    return Number(std::cos(rhs.internal()));
}

constexpr Number tan(const FAngle& rhs) {
    return Number(std::tan(rhs.internal()));
}

template<isQuantity Q>
constexpr FAngle asin(const Q& rhs) {
    return FAngle(std::asin(rhs.internal()));
}

template<isQuantity Q>
constexpr FAngle acos(const Q& rhs) {
    return FAngle(std::acos(rhs.internal()));
}

template<isQuantity Q>
constexpr FAngle atan(const Q& rhs) {
    return FAngle(std::atan(rhs.internal()));
}

template<isQuantity Q>
constexpr FAngle atan2(const Q& lhs, const Q& rhs) {
    return FAngle(std::atan2(lhs.internal(), rhs.internal()));
}

// returns a number in the range (-360, 360)
inline static FAngle constrainFAngle360(FAngle in) {
    return mod(in, Frot);
}

// returns a number in the range [0, 360)
inline static FAngle constrainFAngle360_2(FAngle in) {
    in = mod(in, Frot);
    return in < FAngle(0) ? in + Frot : in;
}

// returns a number in the range (-180, 180)
inline static FAngle constrainFAngle180(FAngle in) {
    in = mod(in + 180 * Fdeg, Frot);
    return in < FAngle(0) ? in + 180 * Fdeg : in - 180 * Fdeg;
}
} // namespace units

// FAngle to/from operators
// Standard orientation
inline constexpr FAngle from_FstRad(float value) {
    return FAngle(value);
}

inline constexpr FAngle from_FstRad(Number value) {
    return FAngle(value.internal());
}

inline constexpr float to_FstRad(FAngle quantity) {
    return quantity.internal();
}

inline constexpr FAngle from_FstDeg(float value) {
    return value * Fdeg;
}

inline constexpr FAngle from_FstDeg(Number value) {
    return value * Fdeg;
}

inline constexpr float to_FstDeg(FAngle quantity) {
    return quantity.convert(Fdeg);
}

inline constexpr FAngle from_FstRot(float value) {
    return value * Frot;
}

inline constexpr FAngle from_FstRot(Number value) {
    return value * Frot;
}

inline constexpr float to_FstRot(FAngle quantity) {
    return quantity.convert(Frot);
}

// Compass orientation
inline constexpr FAngle from_FcRad(float value) {
    return 90 * Fdeg - FAngle(value);
}

inline constexpr FAngle from_FcRad(Number value) {
    return 90 * Fdeg - FAngle(value.internal());
}

inline constexpr float to_FcRad(FAngle quantity) {
    return quantity.internal();
}

inline constexpr FAngle from_FcDeg(float value) {
    return (90 - value) * Fdeg;
}

inline constexpr FAngle from_FcDeg(Number value) {
    return (90 - value.internal()) * Fdeg;
}

inline constexpr float to_FcDeg(FAngle quantity) {
    return (90 * Fdeg - quantity).convert(Fdeg);
}

inline constexpr FAngle from_FcRot(float value) {
    return (90 - value) * Fdeg;
}

inline constexpr FAngle from_FcRot(Number value) {
    return (90 - value.internal()) * Fdeg;
}

inline constexpr float to_FcRot(FAngle quantity) {
    return (90 * Fdeg - quantity).convert(Frot);
}
