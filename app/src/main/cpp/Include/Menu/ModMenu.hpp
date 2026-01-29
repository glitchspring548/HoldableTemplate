#pragma once
#include "ButtonInfo.hpp"
#include <BNM/UnityStructures.hpp>
#include <BNM/Method.hpp>
#include <BNM/Field.hpp>
#include <BNM/Property.hpp>
#include <BNM/MethodBase.hpp>
#include <BNM/FieldBase.hpp>
#include <BNM/PropertyBase.hpp>
#include <BNM/Il2CppHeaders.hpp>
#include <XRInput.hpp>
#include "MenuManager.hpp"

using namespace BNM;
using namespace BNM::Structures;
using namespace BNM::Structures::Unity;
using namespace BNM::IL2CPP;

class ModMenu {
private:

public:
    static void Init();
    static void Update();
    static void Render();
};