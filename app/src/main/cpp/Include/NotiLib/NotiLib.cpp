#include "NotiLib.hpp"
// Based off of Lars, "NotificationLib" (https://github.com/larsl2005/GTAG-NotificationLib)
// Lib base from Pubert, "GUIManager" (Discord = pubertcs, GitHub = Pubert-CS)
// Made By Lmko/Ossuary (KawaiiClique)

NotiLib& NotiLib::Instance() {
    static NotiLib instance;
    return instance;
}

NotiLib::NotiLib()
        : _initialized(false),
          _notifInstance(nullptr),
          _notifText(nullptr),
          _notificationDecayTime(150),
          _decayCounter(0),
          _isEnabled(true) {
    BNM_LOG_INFO(BNM_OBFUSCATE("| Notification Lib Started! | [+]"));
}

void NotiLib::Init(Transform* cameraTransform, TextAnchor dockPos, Font* customFont) {
    NotiLib& self = Instance();
    if (self._initialized) return;
    self._initialized = true;

    self._notifInstance = (GameObject*)GameObject::GetClass().CreateNewObjectParameters(CreateMonoString(O("NotifLib")));

    Canvas* canvas = (Canvas*)self._notifInstance->AddComponent(Canvas::GetType());
    canvas->SetRenderMode(RenderMode::WorldSpace);

    RectTransform* notifTransform = (RectTransform*)self._notifInstance->GetComponent(RectTransform::GetType());

    Font* fontToUse = customFont;
    if (!customFont || !customFont->Alive()) {
        fontToUse = (Font*)Resources::GetBuiltinResource(Font::GetType(), "Arial.ttf");
    }

    self._notifText = (Text*)self._notifInstance->AddComponent(Text::GetType());

    Material* guiMaterial = (Material*)Material::GetClass().CreateNewObjectParameters(Shader::Find("GUI/Text Shader"));

    notifTransform->SetParent(cameraTransform, false);
    self._notifText->SetFont(fontToUse);
    notifTransform->SetLocalEulerAngles(Vector3::zero);
    notifTransform->SetSizeDelta(Vector2(300.0f, 250.0f));
    notifTransform->SetLocalPosition(Vector3(-0.1f, -0.3297f, 1.6f));
    notifTransform->SetLocalScale(Vector3(0.005f, 0.005f, 0.005f));

    self._notifText->SetMaterial(guiMaterial);

    CanvasScaler* canvasScaler = (CanvasScaler*)self._notifInstance->AddComponent(CanvasScaler::GetType());
    canvasScaler->SetDynamicPixelsPerUnit(65.f);
    self._notifText->SetFontStyle(FontStyle::Bold);
    self.SetDock(dockPos);

    self._notifText->SetText("");
    self._notifications.clear();
    self._decayCounter = 0;
    self._previousNotification.clear();
}

void NotiLib::Destroy() {
    if (!_initialized) return;
    _initialized = false;

    if (_notifInstance) {
        GameObject::Destroy(_notifInstance);
        _notifInstance = nullptr;
    }
}

void NotiLib::SetText(const std::string& text) {
    _notifText->SetText(text);
}

void NotiLib::SetDock(TextAnchor dockPos) {
    _notifText->SetAlignment((TextAnchor)dockPos);
}

void NotiLib::Update() {
    NotiLib& self = Instance();
    if (!self._initialized || !self._isEnabled) return;

    if (!self._notifications.empty()) {
        self._decayCounter++;
        if (self._decayCounter > self._notificationDecayTime) {
            self._notifications.pop_front();
            self._decayCounter = 0;

            std::string newText;
            for (const auto& line : self._notifications) {
                newText += line + "\n";
            }
            self.SetText(newText);
        }
    }
}

void NotiLib::SendNotification(const std::string& notification) {
    NotiLib& self = Instance();
    if (!self._isEnabled) return;

    std::string notif = notification;
    if (notif.find('\n') == std::string::npos) {
        notif += "\n";
    }
    self._notifications.push_back(notif);
    self._previousNotification = notif;

    std::string newText;
    for (const auto& line : self._notifications) {
        newText += line + "\n";
    }
    self.SetText(newText);
}

void NotiLib::ClearAllNotifications() {
    NotiLib& self = Instance();
    self._notifications.clear();
    self.SetText("");
}

void NotiLib::ClearPastNotifications(int amount) {
    NotiLib& self = Instance();
    if (amount <= 0 || amount >= (int)self._notifications.size()) {
        ClearAllNotifications();
        return;
    }
    for (int i = 0; i < amount; ++i) {
        self._notifications.pop_front();
    }
    std::string newText;
    for (const auto& line : self._notifications) {
        newText += line + "\n";
    }
    self.SetText(newText);
}

void NotiLib::SetEnabled(bool enabled) {
    NotiLib& self = Instance();
    self._isEnabled = enabled;
}

bool NotiLib::GetEnabled() const {
    return _isEnabled;
}

const std::string& NotiLib::GetPreviousNotification() const {
    return _previousNotification;
}
