#pragma once

#include "units/units.hpp"

class Temperature : public Quantity<std::ratio<0>,
                                    std::ratio<0>,
                                    std::ratio<0>,
                                    std::ratio<0>,
                                    std::ratio<0>,
                                    std::ratio<1>,
                                    std::ratio<0>,
                                    std::ratio<0>,
                                    double> {
  public:
    explicit constexpr Temperature(double value)
        : Quantity<std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<1>,
                   std::ratio<0>,
                   std::ratio<0>,
                   double>(value) {}

    template<typename OtherFloatType>
    constexpr Temperature(Quantity<std::ratio<0>,
                                   std::ratio<0>,
                                   std::ratio<0>,
                                   std::ratio<0>,
                                   std::ratio<0>,
                                   std::ratio<1>,
                                   std::ratio<0>,
                                   std::ratio<0>,
                                   OtherFloatType> value)
        : Quantity<std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<1>,
                   std::ratio<0>,
                   std::ratio<0>,
                   double>(value) {};
};

template<>
struct LookupName<Quantity<std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<1>,
                           std::ratio<0>,
                           std::ratio<0>,
                           double>> {
    using Named = Temperature;
};

class FTemperature : public Quantity<std::ratio<0>,
                                     std::ratio<0>,
                                     std::ratio<0>,
                                     std::ratio<0>,
                                     std::ratio<0>,
                                     std::ratio<1>,
                                     std::ratio<0>,
                                     std::ratio<0>,
                                     float> {
  public:
    explicit constexpr FTemperature(float value)
        : Quantity<std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<1>,
                   std::ratio<0>,
                   std::ratio<0>,
                   float>(value) {}

    template<typename OtherFloatType>
    constexpr FTemperature(Quantity<std::ratio<0>,
                                    std::ratio<0>,
                                    std::ratio<0>,
                                    std::ratio<0>,
                                    std::ratio<0>,
                                    std::ratio<1>,
                                    std::ratio<0>,
                                    std::ratio<0>,
                                    OtherFloatType> value)
        : Quantity<std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<0>,
                   std::ratio<1>,
                   std::ratio<0>,
                   std::ratio<0>,
                   float>(value) {};
};

template<>
struct LookupName<Quantity<std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<0>,
                           std::ratio<1>,
                           std::ratio<0>,
                           std::ratio<0>,
                           float>> {
    using Named = FTemperature;
};

template<>
struct std::formatter<Temperature> : std::formatter<double> {
    auto format(const Temperature& quantity, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "{}_k", quantity.internal());
    }
};

template<>
struct std::formatter<FTemperature> : std::formatter<float> {
    auto format(const FTemperature& quantity, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "{}_k", quantity.internal());
    }
};

inline std::ostream& operator<<(std::ostream& os, const Temperature& quantity) {
    os << quantity.internal() << " k";
    return os;
}

inline std::ostream& operator<<(std::ostream& os,
                                const FTemperature& quantity) {
    os << quantity.internal() << " k";
    return os;
}

constexpr Temperature kelvin = Temperature(1.0);
constexpr FTemperature Fkelvin = FTemperature(1.0);

constexpr Temperature operator""_kelvin(long double value) {
    return Temperature(static_cast<double>(value));
}

constexpr FTemperature operator""_Fkelvin(long double value) {
    return FTemperature(static_cast<float>(value));
}

constexpr Temperature operator""_kelvin(unsigned long long value) {
    return Temperature(static_cast<double>(value));
}

constexpr FTemperature operator""_Fkelvin(unsigned long long value) {
    return FTemperature(static_cast<float>(value));
}

constexpr Temperature operator""_celsius(long double value) {
    return Temperature(static_cast<double>(value) + 273.15);
}

constexpr FTemperature operator""_Fcelsius(long double value) {
    return FTemperature(static_cast<float>(value) + 273.15);
}

constexpr Temperature operator""_celsius(unsigned long long value) {
    return Temperature(static_cast<double>(value) + 273.15);
}

constexpr FTemperature operator""_Fcelsius(unsigned long long value) {
    return FTemperature(static_cast<float>(value) + 273.15);
}

constexpr Temperature operator""_fahrenheit(long double value) {
    return Temperature((static_cast<double>(value) - 32) * (5.0 / 9.0) + 273.5);
}

constexpr FTemperature operator""_Ffahrenheit(long double value) {
    return FTemperature((static_cast<float>(value) - 32) * (5.0 / 9.0) + 273.5);
}

constexpr Temperature operator""_fahrenheit(unsigned long long value) {
    return Temperature((static_cast<double>(value) - 32) * (5.0 / 9.0) + 273.5);
}

constexpr FTemperature operator""_Ffahrenheit(unsigned long long value) {
    return FTemperature((static_cast<float>(value) - 32) * (5.0 / 9.0) + 273.5);
}

namespace units {

inline constexpr Temperature from_kelvin(Number value) {
    return Temperature(value.internal());
}

inline constexpr FTemperature from_Fkelvin(Number value) {
    return FTemperature(value.internal());
}

inline constexpr double to_kelvin(Temperature quantity) {
    return quantity.internal();
}

inline constexpr float to_Fkelvin(FTemperature quantity) {
    return quantity.internal();
}

inline constexpr Temperature from_celsius(Number value) {
    return Temperature(value.internal() + 273.15);
}

inline constexpr FTemperature from_Fcelsius(Number value) {
    return FTemperature(value.internal() + 273.15);
}

inline constexpr double to_celsius(Temperature quantity) {
    return quantity.internal() - 273.15;
}

inline constexpr float to_Fcelsius(FTemperature quantity) {
    return quantity.internal() - 273.15;
}

inline constexpr Temperature from_fahrenheit(Number value) {
    return Temperature((value.internal() - 32) * (5.0 / 9.0) + 273.15);
}

inline constexpr FTemperature from_Ffahrenheit(Number value) {
    return FTemperature((value.internal() - 32) * (5.0 / 9.0) + 273.15);
}

inline constexpr double to_fahrenheit(Temperature quantity) {
    return (quantity.internal() - 273.15) * (9.0 / 5.0) + 32;
}

inline constexpr float to_Ffahrenheit(FTemperature quantity) {
    return (quantity.internal() - 273.15) * (9.0 / 5.0) + 32;
}

} // namespace units
