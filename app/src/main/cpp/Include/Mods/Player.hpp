#include "../XRInput.hpp"
#include "../BNMIncludes.hpp"
#include "../BNMResolve.hpp"
#include "../PhotonResolve.hpp"
#include "../httplib.h"
#include "../json.hpp"
#include "../XRInput.hpp"
#include "gtag.hpp"
class PlayerMods {
private:
public:

    static void LongArms() {
        gtag::setpv3("rightHandOffset", Vector3(0, 0, 0.35f));  // kinda hard to explain but finds GorillaLocomotion.Player and sets the rightHandOffset to Vector3(0, 0, 0.35f)
        gtag::setpv3("leftHandOffset",  Vector3(0, 0, 0.35f));
}
};