#include "../XRInput.hpp"
#include "../BNMIncludes.hpp"
#include "../BNMResolve.hpp"
#include "../PhotonResolve.hpp"
#include "../httplib.h"
#include "../json.hpp"
#include "../XRInput.hpp"

class OverpoweredMods {
private:
public:
    inline static float crashDelay = 0.0f;
    static void crashall() {
        if (Time.time <= crashDelay) {
            return;
        }

        crashDelay = Time.time + 0.6f;
        PhotonNetwork::SetMasterClient(PhotonNetwork::GetLocalPlayer())

        auto plrs = Utilities::GetAllPlayers();
        for (Player* plr : plrs) {
            if (!plr) {
                continue;
            }
            if (plr == PhotonNetwork::GetLocalPlayer()) {
                continue;
            }
            PhotonNetwork::DestroyPlayerObjects(plr->GetActorNumber())
        }
    }
};