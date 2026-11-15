// note: this isnt mine, this is cz's/ gdrci
// pretty useful tho
#pragma once
namespace gtag {
    static BNM::Class playercls() {
        static BNM::Class c = BNM::Class("GorillaLocomotion", "Player");
        return c;
    }

    static void *player() {
        if (!playercls()) return nullptr;
        static Method<void *> m = playercls().GetMethod("get_Instance");
        return m.IsValid() ? m() : nullptr;
    }

    struct fcacheentry {
        const char *name;
        BNM::FieldBase fb;
    };
    static fcacheentry fcache[32];
    static int fcache_n = 0;

    static BNM::FieldBase cachedfield(const char *name) {
        for (int i = 0; i < fcache_n; ++i) {
            if (fcache[i].name == name) return fcache[i].fb;
        }
        for (int i = 0; i < fcache_n; ++i) {
            if (std::strcmp(fcache[i].name, name) == 0) return fcache[i].fb;
        }
        BNM::FieldBase fb = playercls().GetField(name);
        if (fcache_n < 32) fcache[fcache_n++] = {name, fb};
        return fb;
    }

    static void setpf(const char *name, float val) {
        void *p = player();
        if (!p) return;
        auto fb = cachedfield(name);
        if (!fb.IsValid()) return;
        BNM::Field<float> f = fb;
        f[p].Set(val);
    }

    static float getpf(const char *name) {
        void *p = player();
        if (!p) return 0;
        auto fb = cachedfield(name);
        if (!fb.IsValid()) return 0;
        BNM::Field<float> f = fb;
        return f[p].Get();
    }

    static void setpb(const char *name, bool val) {
        void *p = player();
        if (!p) return;
        auto fb = cachedfield(name);
        if (!fb.IsValid()) return;
        BNM::Field<bool> f = fb;
        f[p].Set(val);
    }

    static void setpv3(const char *name, Vector3 val) {
        void *p = player();
        if (!p) return;
        auto fb = cachedfield(name);
        if (!fb.IsValid()) return;
        BNM::Field<Vector3> f = fb;
        f[p].Set(val);
    }

    static Transform *head() {
        void *p = player();
        if (!p) return nullptr;
        static BNM::FieldBase fb = cachedfield("headCollider");
        if (!fb.IsValid()) return nullptr;
        BNM::Field<Component *> f = fb;
        Component *c = f[p].Get();
        return c ? c->GetTransform() : nullptr;
    }

    static Transform *body() {
        void *p = player();
        if (!p) return nullptr;
        static BNM::FieldBase fb = cachedfield("bodyCollider");
        if (!fb.IsValid()) return nullptr;
        BNM::Field<Component *> f = fb;
        Component *c = f[p].Get();
        return c ? c->GetTransform() : nullptr;
    }

    static Rigidbody *rb() {
        void *p = player();
        if (!p) return nullptr;
        static BNM::FieldBase fb = cachedfield("playerRigidBody");
        if (!fb.IsValid()) return nullptr;
        BNM::Field<Rigidbody *> f = fb;
        return f[p].Get();
    }

    static GameObject *rootobj_cached = nullptr;
    static int rootobj_cd = 0;

    static Transform *roottrans() {
        if (!rootobj_cached || rootobj_cd <= 0) {
            rootobj_cached = GameObject::Find("GorillaPlayer");
            rootobj_cd = 600;
        }
        rootobj_cd--;
        return rootobj_cached ? rootobj_cached->GetTransform() : nullptr;
    }
}