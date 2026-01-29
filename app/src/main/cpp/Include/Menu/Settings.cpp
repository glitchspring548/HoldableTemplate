#include "Settings.hpp"
#include <BNMResolve.hpp>
#include <XRInput.hpp>
#include "../NotiLib/NotiLib.hpp"

using namespace BNM;

NotiLib* Settings::noti;

Color Settings::backgroundColor;
std::vector<Color> Settings::buttonColors;
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

void Settings::Init() {
    backgroundColor = Color(0.1f, 0.1f, 0.1f, 0.95f);
    buttonColors = {
            Color::magenta,
            Color::yellow
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