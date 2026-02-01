#pragma once
#include "../BNMResolve.hpp"
#include "../BNMIncludes.hpp"
#include "../PhotonResolve.hpp"
#include "../Menu/Settings.hpp"
#include <XRInput.hpp>
#include <cmath>
#include <cstdlib>

using namespace BNM;
using namespace BNM::Structures;

struct GunData {
    RaycastHit raycastHit;
    GameObject* pointer;
};


class GunLib {
private:
    GameObject* gunPointer = nullptr;
    LineRenderer* gunLine = nullptr;

    Vector3 midPosition = Vector3::zero;
    Vector3 midVelocity = Vector3::zero;

public:
    float gunLineQuality = 25.0f;

    GunLib() {}
    LineRenderer* GetLineRenderer() { return gunLine; }

    GunData RenderGun() {
        GunData result;
        Class GorillaTagger = Class("", "GorillaTagger", BNM::Image("Assembly-CSharp.dll"));
        static BNM::Method<BNM::IL2CPP::Il2CppObject*> instance = GorillaTagger.GetMethod("get_Instance", 0);
        static BNM::Field<Transform*> gunTransform = GorillaTagger.GetField("rightHandTransform");
        gunTransform.SetInstance(instance.Call());
        if (gunTransform.IsValid() == false) {
            BNM_LOG_INFO(BNM_OBFUSCATE("rightHandTransform not working :("));
            return result;
        }
        Vector3 startPosition = gunTransform()->GetPosition();
        Vector3 direction = gunTransform()->GetForward();

        RaycastHit raycastHit;
        bool hit = Physics::Raycast(startPosition, direction, raycastHit);
        Vector3 endPosition = hit ? raycastHit.point : startPosition + direction;

        if (!gunPointer->Alive()) {
            gunPointer = GameObject::CreatePrimitive(PrimitiveType::Sphere);
            GameObject::Destroy(gunPointer->GetComponent(Rigidbody::GetType()));
            GameObject::Destroy(gunPointer->GetComponent(SphereCollider::GetType()));
        }

        gunPointer->SetActive(true);
        gunPointer->GetTransform()->SetLocalScale(Vector3(0.2f, 0.2f, 0.2f));
        gunPointer->GetTransform()->SetPosition(endPosition);

        Renderer* renderer = (Renderer*)gunPointer->GetComponent(Renderer::GetType());
        Material* mat = renderer->GetMaterial();
        mat->SetColor(XRInput::GetBoolFeature(BoolFeature::TriggerButton, Controller::Right) ? Settings::backgroundColor.RGBMultiplied(Color(.5f, .5f, .5f)) : Settings::backgroundColor);

        if (!gunLine->Alive()) {
            GameObject* lineGO = (GameObject*)GameObject::GetClass().CreateNewObjectParameters(CreateMonoString("GunLine"));
            gunLine = (LineRenderer*)lineGO->AddComponent(LineRenderer::GetType());
            gunLine->SetStartWidth(0.025f);
            gunLine->SetEndWidth(0.025f);
            gunLine->SetUseWorldScape(true);
        }

        gunLine->SetStartColor(Settings::backgroundColor);
        gunLine->SetEndColor(XRInput::GetBoolFeature(BoolFeature::TriggerButton, Controller::Right) ? Settings::backgroundColor.RGBMultiplied(Color(.5f, .5f, .5f)) : Settings::backgroundColor);
        gunLine->SetPosition(0, startPosition);
        gunLine->SetPosition(1, endPosition);

        result.raycastHit = raycastHit;
        result.pointer = gunPointer;
        return result;
    }

    void Cleanup() {
        if (gunPointer) {
            gunPointer->SetActive(false);
            GameObject::Destroy(gunPointer);
            gunPointer = nullptr;
        }

        if (gunLine) {
            GameObject* lineGO = gunLine->GetGameObject();
            if (lineGO) {
                lineGO->SetActive(false);
                GameObject::Destroy(lineGO);
            }
            gunLine = nullptr;
        }

        midPosition = Vector3::zero;
        midVelocity = Vector3::zero;
    }
};