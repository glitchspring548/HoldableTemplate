#pragma once
#include <BNMIncludes.hpp>
#include <NotiLib/NotiLib.hpp>
#include "MenuManager.hpp"
#include "ModMenu.hpp"
#include "Buttons.hpp"
#include "Settings.hpp"
#include "ButtonInfo.hpp"

using namespace BNM;
using namespace BNM::Structures;
using namespace BNM::Structures::Unity;
using namespace BNM::IL2CPP;

void ModMenu::Init() {
    Settings::noti = new NotiLib();
    Settings::noti->Init(GameObject::Find("Main Camera")->GetTransform(), TextAnchor::MiddleLeft, nullptr);
    Settings::Init();

}

void ModMenu::Update() {
    Render();
}

void ModMenu::Render() {
    MenuManager::Prefix();
    Settings::noti->Update();
}