#include "../XRInput.hpp"
#include "../BNMIncludes.hpp"
#include "../BNMResolve.hpp"
#include "../PhotonResolve.hpp"
#include "../httplib.h"
#include "../json.hpp"
#include "../XRInput.hpp"
#include "GunLib.hpp"

class MovementMods {
private:
public:
    static void platforms() {
        static GameObject *platR = nullptr;
        static GameObject *platL = nullptr;

        bool rightGrab = XRInput::GetBoolFeature(BoolFeature::GripButton, Controller::Right);
        bool leftGrab  = XRInput::GetBoolFeature(BoolFeature::GripButton, Controller::Left);

        auto createPlatform = [](char *handName) -> GameObject * {
            GameObject *plat = GameObject::CreatePrimitive(PrimitiveType::Cube);

            Renderer *renderer = (Renderer *)plat->GetComponent(Renderer::GetType());
            if (renderer) {
                Material *mat = renderer->GetMaterial();
                if (mat) {
                    mat->SetShader(Shader::Find("Standard"));
                    mat->SetColor(Settings::backgroundColor);
                }
            }

            Transform *handTransform = GameObject::Find(handName)->GetTransform();
            plat->GetTransform()->SetLocalScale(Vector3(0.025f, 0.3f, 0.4f));
            plat->GetTransform()->SetLocalPosition(
                    handTransform->GetPosition() + Vector3(0.0f, -0.07f, 0.0f));
            plat->GetTransform()->SetLocalRotation(handTransform->GetRotation());

            return plat;
        };

        auto destroyPlatform = [](GameObject *plat) {
            if (!plat) return;
            plat->AddComponent(Rigidbody::GetType());
            GameObject::Destroy(plat->GetComponent(Collider::GetType()));
            GameObject::Destroy(plat, 2.0f);
        };

        if (leftGrab) {
            if (!platL) platL = createPlatform("LeftHand Controller");
        } else if (platL) {
            destroyPlatform(platL);
            platL = nullptr;
        }

        if (rightGrab) {
            if (!platR) platR = createPlatform("RightHand Controller");
        } else if (platR) {
            destroyPlatform(platR);
            platR = nullptr;
        }
    }
    static void PlatformGun() {
        static GunLib gun;
        auto createPlatform = [](GameObject* pointer) -> GameObject * {
            GameObject *plat = GameObject::CreatePrimitive(PrimitiveType::Cube);

            Renderer *renderer = (Renderer *)plat->GetComponent(Renderer::GetType());
            if (renderer) {
                Material *mat = renderer->GetMaterial();
                if (mat) {
                    mat->SetShader(Shader::Find("Standard"));
                    mat->SetColor(Settings::backgroundColor);
                }
            }

            Transform *pointerTransform = pointer->GetTransform();
            plat->GetTransform()->SetLocalScale(Vector3(0.025f, 0.3f, 0.4f));
            plat->GetTransform()->SetLocalPosition(
                    pointerTransform->GetPosition() + Vector3(0.0f, -0.07f, 0.0f));
            plat->GetTransform()->SetLocalRotation(pointerTransform->GetRotation());

            return plat;
        };

        if (XRInput::GetBoolFeature(BoolFeature::GripButton, Controller::Right)) {
            GunData data = gun.RenderGun();
            RaycastHit ray = data.raycastHit;
            GameObject* pointer = data.pointer;
            if (XRInput::GetBoolFeature(BoolFeature::TriggerButton, Controller::Right)) {
                createPlatform(pointer);
            }
        } else {
            gun.Cleanup();
        }
    }
};