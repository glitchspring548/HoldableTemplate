#include "Settings.hpp"
#include <BNMResolve.hpp>
#include <XRInput.hpp>
#include "../NotiLib/NotiLib.hpp"
#include "Classes/ExtGradient.hpp"

using namespace BNM;

NotiLib* Settings::noti;

ExtGradient Settings::backgroundColor;
std::vector<ExtGradient> Settings::buttonColors;
std::vector<Color> Settings::textColors;
Font* Settings::currentFont = nullptr;

bool Settings::fpsCounter = false;
bool Settings::disconnectButton = false;
bool Settings::rightHanded = false;
bool Settings::disableNotifications = false;

Vector3 Settings::menuSize = Vector3::zero;
int Settings::buttonsPerPage = 0;
int Settings::framePressCooldown = 0;

GameObject* Settings::menu = nullptr;
GameObject* Settings::menuBackground = nullptr;
GameObject* Settings::reference = nullptr;
GameObject* Settings::canvasObject = nullptr;
SphereCollider* Settings::buttonCollider = nullptr;
Text* Settings::titleText = nullptr;
Text* Settings::fpsText = nullptr;

int Settings::pageNumber = 0;
int Settings::_currentCategory = 0;

/*
 To change the colors you change the values here
    backgroundColor = ExtGradient { .rainbow = true };
    buttonColors = {
            ExtGradient { .pastelRainbow = true },
            ExtGradient { .colors = ExtGradient::GetSolidGradient(Color::green) }
    };
    textColors = {
            Color::white,
            Color::white
    };
 if you don't want RGB do this
    backgroundColor = ExtGradient { .colors = ExtGradient::GetSolidGradient(Color::red) };
    buttonColors = {
            ExtGradient { .colors = ExtGradient::GetSolidGradient(Color::red) },
            ExtGradient { .colors = ExtGradient::GetSolidGradient(Color::green) }
    };
    textColors = {
            Color::white,
            Color::white
    };
 to change the colors use Color() for more advanced colors or just Color::(insert color name here)
 if you want a normal gradient do this
 ExtGradient { .colors = ExtGradient::GetSimpleGradient(color A, color B) },
*/

void Settings::Init() {
    backgroundColor = ExtGradient { .rainbow = true };
    buttonColors = {
            ExtGradient { .pastelRainbow = true },
            ExtGradient { .colors = ExtGradient::GetSolidGradient(Color::green) }
    };
    textColors = {
            Color::white,
            Color::white
    };

    if (!currentFont) {
        currentFont = (Font*)Resources::GetBuiltinResource(Font::GetType(), BNM_OBFUSCATE("Arial.ttf"));
        if (!currentFont) {
            BNM_LOG_WARN(BNM_OBFUSCATE("Failed to load Arial.ttf"));
        }
    }

    fpsCounter = true;
    disconnectButton = true;
    rightHanded = false;
    disableNotifications = false;

    menuSize = Vector3(0.1f, 1.0f, 1.0f);
    buttonsPerPage = 8;
    framePressCooldown = 0;

    menu = nullptr;
    menuBackground = nullptr;
    reference = nullptr;
    canvasObject = nullptr;
    buttonCollider = nullptr;
    titleText = nullptr;
    fpsText = nullptr;

    pageNumber = 0;
    _currentCategory = 0;
}

void Settings::Update() {

}