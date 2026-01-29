#pragma once
#include <functional>
#include <string>

struct ButtonInfo {
    std::string buttonText = "-";
    std::string overlapText = "";
    std::function<void()> method = nullptr;
    std::function<void()> enableMethod = nullptr;
    std::function<void()> disableMethod = nullptr;
    bool enabled = false;
    bool isTogglable = true;
    std::string toolTip = "";
};
