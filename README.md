# HoldableTemplate

An Android native-mod template for Unity IL2CPP VR projects, with a controller-operated, world-space menu and a C++20 codebase built through the Android Gradle Plugin and CMake.

The current native entry point is configured to locate `GorillaLocomotion.Player` in `Assembly-CSharp.dll` and hook its `Awake` and `LateUpdate` methods. Feel free to change this as you see fit.

[![GitHub Stars](https://img.shields.io/github/stars/glitchspring548/HoldableTemplate?style=for-the-badge&logo=github)](https://github.com/glitchspring548/HoldableTemplate)
[![Discord Members](https://img.shields.io/badge/dynamic/json?url=https%3A%2F%2Fdiscord.com%2Fapi%2Finvites%2FSXByg9hAHX%3Fwith_counts%3Dtrue&query=%24.approximate_member_count&label=Discord%20Members&logo=discord&logoColor=white&color=5865F2&style=for-the-badge)](https://discord.gg/SXByg9hAHX)

## Stars
Please star this little project of mine. 

It means a lot :D

## Build

Clone the repository and open its root directory in Android Studio, or build from a terminal.

## Customizing the template

1. **Update the target hooks.** In `app/src/main/cpp/native-lib.cpp`, change the class, assembly, and method names to match the IL2CPP game version you are targeting. The current values are game-specific.
2. **Add or change mod actions.** Implement your own functionality in the relevant headers under `app/src/main/cpp/Include/Mods/`, then add button definitions or callbacks in `Include/Menu/Buttons.hpp`.
3. **Configure the menu.** Edit `Include/Menu/Settings.cpp` to adjust default colors, menu size, page capacity, font, and settings.

## Credits and third-party components

The repository's current source contains attribution references to the following people/projects:

- **iiDk** — created the original template.
- **Ossuary**, **Pubert**, and **Notfishvr** — credited in the in-menu Credits page for helping during development.
- **Lmko / KawaiiClique** — created the `NotiLib`.
- **BNM-Android**, **Dobby**, and **OpenSSL** — native dependencies CMake build

# Please give credits
When I ([@glitchspring548](https://www.github.com/glitchspring548)) originaly created this template people immediately started to clam that it was not mine and instead was theirs.
