#include "../XRInput.hpp"
#include "../BNMIncludes.hpp"
#include "../BNMResolve.hpp"
#include "../PhotonResolve.hpp"
#include "../httplib.h"
#include "../json.hpp"
#include "../XRInput.hpp"

class Utilities {
public:
    static std::vector<Player*> GetAllPlayers() {
        return PhotonNetwork::GetPlayerList();
    }
};