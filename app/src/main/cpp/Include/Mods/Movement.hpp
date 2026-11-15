#include "../XRInput.hpp"
#include "../BNMIncludes.hpp"
#include "../BNMResolve.hpp"
#include "../PhotonResolve.hpp"
#include "../httplib.h"
#include "../json.hpp"
#include "../XRInput.hpp"
#include "GunLib.hpp"
#include "gtag.hpp"

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
                    mat->SetColor(Settings::backgroundColor.GetCurrentColor());
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
                    mat->SetColor(Settings::backgroundColor.GetCurrentColor());
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

    static void HeadFly() {
        float con = XRInput::GetFloatFeature(Trigger, Right); // finds right controller
        if (con < 0.5f) return; // if the controller is not pressed more then half way down, stop
        Transform* hd = gtag::head(); // get head
        Rigidbody* rigidb = gtag::rb();  // get rigidbody
        Transform* root = gtag::roottrans(); // get root transform
        if (!hd || !root) return; // stop if it cant find
        Vector3 s = hd->GetForward() * Time::GetDeltaTime() * 12.0f;  // get wher the head is looking at, then multiply it by how many frames have run since the code ran, times 12
        root->SetPosition(root->GetPosition() + s); // if it can find the rigidbody, move it
        if (rigidb) rigidb->SetVelocity(Vector3(0,0,0)); // stop the rigidbody
    }
};