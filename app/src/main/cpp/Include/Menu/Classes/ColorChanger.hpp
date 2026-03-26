#pragma once
#include <cmath>
#include <random>
#include "ExtGradient.hpp"
#include "../../BNMResolve.hpp"
#include "../../BNMIncludes.hpp"

class ColorChanger {
public:
    struct ColorChangerComp : BNM::UnityEngine::MonoBehaviour
    {
        BNM_CustomClass(ColorChangerComp,
                BNM::CompileTimeClassBuilder(BNM_OBFUSCATE_TMP(O("")), BNM_OBFUSCATE_TMP(O("ColorChangerComp"))).Build(),
                BNM::CompileTimeClassBuilder(BNM_OBFUSCATE_TMP(O("UnityEngine")), BNM_OBFUSCATE_TMP(O("MonoBehaviour")), BNM_OBFUSCATE_TMP(O("UnityEngine.CoreModule"))).Build(),
        {},
        );

        void Constructor() {
            BNM::UnityEngine::MonoBehaviour tmp = *this;
            *this = ColorChangerComp();
            *((BNM::UnityEngine::MonoBehaviour *)this) = tmp;
        }

        GameObject* obj;
        int index;

        void Start() {
            if (obj == nullptr) {
                BNM_LOG_DEBUG(O("Invalid OBJ"));
                GameObject::Destroy(this);
            }
        }

        void Update() {
            if (obj != nullptr) {
                Renderer* rend = (Renderer*)obj->GetComponent(Renderer::GetType());
                if (rend != nullptr) {
                    rend->GetMaterial()->SetColor(getColorFromInt(index));
                } else {
                    BNM_LOG_DEBUG(O("Invalid rend"));
                }
            }
        }

        BNM_CustomField(obj, BNM::Defaults::Get<GameObject*>(), "obj");
        BNM_CustomField(index, BNM::Defaults::Get<int>(), "index");
        BNM_CustomMethod(Update, false, BNM::Defaults::Get<void>(), "Update");
        BNM_CustomMethod(Start, false, BNM::Defaults::Get<void>(), "Start");
        BNM_CustomMethod(Constructor, false, BNM::Defaults::Get<void>(), ".ctor");
    };

    static Color getColorFromInt(int painnnnn = 0) {
        if (painnnnn == 0) {
            return Settings::backgroundColor.GetCurrentColor();
        } else if (painnnnn == 1) {
            return Settings::buttonColors[0].GetCurrentColor();
        } else if (painnnnn == 2) {
            return Settings::buttonColors[1].GetCurrentColor();
        } else {
            return Settings::backgroundColor.GetCurrentColor();
        }
    }
};