#pragma once
#include <BNMResolve.hpp>
#include <functional>
#include <string>
#include "ButtonInfo.hpp"
#include "Settings.hpp"
#include "../NotiLib/NotiLib.hpp"
#include "../ModInclude.hpp"

using namespace BNM;
using namespace BNM::IL2CPP;
using namespace BNM::Structures;

class Buttons {
public:
    static inline std::vector<std::vector<ButtonInfo>> buttons = {
            {//main stuff - 0
                    ButtonInfo {.buttonText = "Settings", .method = []() { Settings::setCurrentCategory(1); }, .isTogglable = false, .toolTip = "Opens the settings"},
                    ButtonInfo {.buttonText = "Movement", .method = []() { Settings::setCurrentCategory(2); }, .isTogglable = false, .toolTip = "Opens movement"},
                    ButtonInfo {.buttonText = "Player", .method = []() { Settings::setCurrentCategory(3); }, .isTogglable = false, .toolTip = "Opens player"},
                    ButtonInfo {.buttonText = "Visuals", .method = []() { Settings::setCurrentCategory(4); }, .isTogglable = false, .toolTip = "Opens visuals"},
                    ButtonInfo {.buttonText = "Photon", .method = []() { Settings::setCurrentCategory(5); }, .isTogglable = false, .toolTip = "Opens photon"},
                    ButtonInfo {.buttonText = "Overpowered", .method = []() { Settings::setCurrentCategory(6); }, .isTogglable = false, .toolTip = "Opens overpowered"},
                    ButtonInfo {.buttonText = "Credits", .method = []() { Settings::setCurrentCategory(7); }, .isTogglable = false, .toolTip = "Opens the cedits"},
                    ButtonInfo {.buttonText = "Cool people", .method = []() { Settings::setCurrentCategory(8); }, .isTogglable = false, .toolTip = "Opens the cool people page"},
            },
            {//Settings - 1
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
                    ButtonInfo {.buttonText = "Right hand menu", .enableMethod = []() { Settings::rightHanded = true; }, .disableMethod = []() { Settings::rightHanded = false; }, .toolTip = "Sets the menu to right hand"},
                    ButtonInfo {.buttonText = "Notifications", .enableMethod = []() { NotiLib::SetEnabled(true); }, .disableMethod = []() { NotiLib::SetEnabled(false); }, .enabled = true, .toolTip = "Toggles the notifications"},
                    ButtonInfo {.buttonText = "Disconnect button", .enableMethod = []() { Settings::disconnectButton = true; }, .disableMethod = []() { Settings::disconnectButton = false; }, .enabled = true, .toolTip = "Toggles the disconnect button"},
            },
            {//Movement - 2
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
                    ButtonInfo {.buttonText = "Plats", .method = []() { MovementMods::platforms(); }, .toolTip = "Plats"},
                    ButtonInfo {.buttonText = "Platform Gun", .method = []() { MovementMods::PlatformGun(); }, .toolTip = "Plats"},
            },
            {//Player - 3
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
            },
            {//Visuals - 4
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
            },
            {//Photon - 5
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
            },
            {//Overpowered - 6
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
            },
            {//Credits - 7
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
                    ButtonInfo {.buttonText = "Glitch", .isTogglable = false, .toolTip = "Ported the menu from iiDk's template and the dev of this template"},
                    ButtonInfo {.buttonText = "Ossuary", .isTogglable = false, .toolTip = "Taught me how to mod :D"},
                    ButtonInfo {.buttonText = "Pubert", .isTogglable = false, .toolTip = "Helped me a lot with the code"},
                    ButtonInfo {.buttonText = "Notfishvr", .isTogglable = false, .toolTip = "Helped me a lot debugging"},
            },
            {//Cool people - 8
                    ButtonInfo {.buttonText = "back", .method = []() { Settings::setCurrentCategory(0); }, .isTogglable = false, .toolTip = "Goes back to main menu"},
                    ButtonInfo {.buttonText = "Bsu", .isTogglable = false, .toolTip = "Cool person :D"},
                    ButtonInfo {.buttonText = "Oxg", .isTogglable = false, .toolTip = "Cool person :D"},
                    ButtonInfo {.buttonText = "Crimson", .isTogglable = false, .toolTip = "Cool person :D"},
                    ButtonInfo {.buttonText = "W1ingz", .isTogglable = false, .toolTip = "Cool person :D"},
            },
    };
};