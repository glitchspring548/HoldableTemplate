#pragma once
#include "../BNMResolve.hpp"
#include <cmath>
#include <cstdlib>
#include "../Menu/Settings.hpp"

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
    GunLib() {}
    LineRenderer* GetLineRenderer() { return gunLine; }

    GunData RenderGun() {
        GunData result;
        Class GorillaTagger = Class("", "GorillaTagger", BNM::Image("Assembly-CSharp.dll"));
        Method<BNM::IL2CPP::Il2CppObject*> instance = GorillaTagger.GetMethod("get_Instance", 0);
        Field<BNM::IL2CPP::Il2CppObject*> rightHandTransform = GorillaTagger.GetField("rightHandTransform");
        rightHandTransform.SetInstance(instance.Call());
        if (rightHandTransform.IsValid() == false) {
            BNM_LOG_INFO(BNM_OBFUSCATE("rightHandTransform no worky :("));
            return result;
        }
        Transform* gunTransform = (Transform*)rightHandTransform();

        Vector3 startPosition = gunTransform->GetPosition() + (gunTransform->GetForward() * 0.135f);
        Vector3 direction = gunTransform->GetForward();
        Vector3 up = -gunTransform->GetUp();

        RaycastHit raycastHit;
        bool hit = Physics::Raycast(startPosition, direction, raycastHit);
        Vector3 endPosition = hit ? raycastHit.point : startPosition + direction;

        if (!gunPointer) {
            gunPointer = GameObject::CreatePrimitive(PrimitiveType::Sphere);
            GameObject::Destroy(gunPointer->GetComponent(Rigidbody::GetType()));
            GameObject::Destroy(gunPointer->GetComponent(SphereCollider::GetType()));
            Renderer* renderer = (Renderer*)gunPointer->GetComponent(Renderer::GetType());
            Material* mat = renderer->GetMaterial();
            mat->SetShader(Shader::Find("GUI/Text Shader"));
            mat->SetColor(Settings::backgroundColor);
        }

        gunPointer->SetActive(true);
        gunPointer->GetTransform()->SetLocalScale(Vector3(0.2f, 0.2f, 0.2f));
        gunPointer->GetTransform()->SetPosition(endPosition);

        if (!gunLine) {
            GameObject* lineGO = (GameObject*)GameObject::GetClass().CreateNewObjectParameters(CreateMonoString("GunLine"));
            gunLine = (LineRenderer*)lineGO->AddComponent(LineRenderer::GetType());
            gunLine->SetMaterial((Material*)Material::GetClass().CreateNewObjectParameters(Shader::Find("GUI/Text Shader")));
            gunLine->SetStartWidth(0.025f);
            gunLine->SetEndWidth(0.025f);
            gunLine->SetUseWorldScape(true);
        }

        gunLine->GetGameObject()->SetActive(true);

        Color current = Settings::backgroundColor;
        gunLine->SetStartColor(current);
        gunLine->SetEndColor(current);

        int steps = 2;
        gunLine->SetPositionCount(steps);
        gunLine->SetPosition(0, startPosition);
        gunLine->SetPosition(1, endPosition);

        result.raycastHit = raycastHit;
        result.pointer = gunPointer;
        return result;
    }

    void Cleanup() {
        if (gunPointer) {
            GameObject::Destroy(gunPointer);
            gunPointer = nullptr;
        }

        if (gunLine) {
            GameObject* lineGO = gunLine->GetGameObject();
            if (lineGO) {
                GameObject::Destroy(lineGO);
            }
            gunLine = nullptr;
        }

        midPosition = Vector3::zero;
        midVelocity = Vector3::zero;
    }
};