#pragma once
#include <cmath>
#include <random>
#include "../../BNMResolve.hpp"
#include "../../BNMIncludes.hpp"

struct ExtGradient {
public:
    struct ColorKey {
        Color color;
        float time;
        ColorKey(Color c, float t) : color(c), time(t) {}
    };

    bool rainbow = false;
    bool pastelRainbow = false;
    bool epileptic = false;
    std::vector<ColorKey> colors = GetSolidGradient(Color::magenta);

    static std::vector<ColorKey> GetSolidGradient(Color color) {
        return std::vector<ColorKey>{
                ColorKey(color, 0.f),
                ColorKey(color, 1.f)
        };
    }

    static std::vector<ColorKey> GetSimpleGradient(Color A, Color B) {
        return std::vector<ColorKey>{
                ColorKey(A, 0.f),
                ColorKey(B, 0.5f),
                ColorKey(A, 1.f)
        };
    }

    Color GetColor(int index) const {
        if (rainbow)
            return Color::HSVToRGB(fmod(Time::GetTime() + (index / 8.f), 1.f), 1.f, 1.f);
        if (pastelRainbow)
            return Color::HSVToRGB(Time::GetTime() + (index / 8.f), 0.3f, 1.f);
        if (epileptic) {
            static std::mt19937 rng(std::random_device{}());
            static std::uniform_real_distribution<float> dist(0.f, 1.f);
            return Color(dist(rng), dist(rng), dist(rng));
        }
        return colors[index].color;
    }

    void SetColor(int index, Color color, bool setMirror = true) {
        rainbow = false;
        pastelRainbow = false;
        epileptic = false;

        if (colors.size() <= 2)
            colors = GetSimpleGradient(colors[0].color, colors[colors.size() - 1].color);

        if (setMirror && index == 0) {
            colors[0].color = color;
            colors[colors.size() - 1].color = color;
        } else {
            colors[index].color = color;
        }
    }

    void SetColors(Color color) {
        rainbow = false;
        pastelRainbow = false;
        epileptic = false;

        for (auto& key : colors)
            key.color = color;
    }

    Color GetColorTime(float time) const {
        if (rainbow)       return Color::HSVToRGB(time, 1.f, 1.f);
        if (pastelRainbow) return Color::HSVToRGB(time, .3f, 1.f);
        if (epileptic) {
            static std::mt19937 rng(std::random_device{}());
            static std::uniform_real_distribution<float> dist(0.f, 1.f);
            return Color(dist(rng), dist(rng), dist(rng));
        }

        if (colors.empty()) return Color::magenta;
        if (colors.size() == 1 || time <= colors.front().time) return colors.front().color;
        if (time >= colors.back().time) return colors.back().color;

        for (size_t i = 1; i < colors.size(); ++i) {
            if (time <= colors[i].time) {
                float t = (time - colors[i - 1].time) / (colors[i].time - colors[i - 1].time);
                const Color& a = colors[i - 1].color;
                const Color& b = colors[i].color;
                return Color(
                        a.r + t * (b.r - a.r),
                        a.g + t * (b.g - a.g),
                        a.b + t * (b.b - a.b),
                        a.a + t * (b.a - a.a)
                );
            }
        }
        return colors.back().color;
    }

    Color GetCurrentColor(float offset = 0.f) const {
        return GetColorTime(fmod(offset + (Time::GetTime() * 0.5f), 1.0f));
    }

    bool IsFlat() const {
        return !rainbow && !pastelRainbow && !epileptic &&
               !colors.empty() &&
               std::all_of(colors.begin(), colors.end(), [&](const auto& key) {
                   return key.color == colors[0].color;
               });
    }

    ExtGradient Clone() const {
        return *this;
    }
};