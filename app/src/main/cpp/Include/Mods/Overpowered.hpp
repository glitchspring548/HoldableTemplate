#include "../XRInput.hpp"
#include "../BNMIncludes.hpp"
#include "../BNMResolve.hpp"
#include "../PhotonResolve.hpp"
#include "../httplib.h"
#include "../json.hpp"
#include "../XRInput.hpp"
#include "gtag.hpp"


class OverpoweredMods {
private:
public:


    static void NoTagFreeze() {
        // note: this probably doesnt work
        BNM::Class gt = BNM::Class("", "GorillaTagger"); // find the class GorillaTagger
        if (!gt) return; // if it cant find it, stop
        auto gi = gt.GetMethod("get_Instance").cast<void *>(); // find the method get_Instance inside the class GorillaTagger
        if (!gi.IsValid()) return; //if it isnt valid, stop
        static BNM::Field<float> tagCooldown = gt.GetField("tagCooldown"); // find a field (float) called tagCooldown inside the class GorillaTagger
        tagCooldown[gi()] = 0.0f; // set the tagCooldown to 0.0f
    }


};
