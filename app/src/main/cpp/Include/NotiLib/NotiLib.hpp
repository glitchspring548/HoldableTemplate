#pragma once
#include <BNMResolve.hpp>
#include <deque>
#include <string>

using namespace BNM;
using namespace BNM::Structures;
using namespace BNM::Structures::Unity;
using namespace BNM::IL2CPP;

#define O(str) BNM_OBFUSCATE(str)

struct NotiLib {
private:
    bool _initialized;
    GameObject* _notifInstance;
    Text* _notifText;
    std::deque<std::string> _notifications;
    int _notificationDecayTime;
    int _decayCounter;
    bool _isEnabled;
    std::string _previousNotification;
    static NotiLib& Instance();
public:
    NotiLib();

    void Init(Transform* cameraTransform, TextAnchor dockPos, Font* customFont = nullptr);
    void Destroy();
    void SetText(const std::string& text);
    void SetDock(TextAnchor dockPos);
    void Update();

    static void SendNotification(const std::string& notification);
    static void ClearAllNotifications();
    static void ClearPastNotifications(int amount);
    static void SetEnabled(bool enabled);

    bool GetEnabled() const;
    const std::string& GetPreviousNotification() const;
};
