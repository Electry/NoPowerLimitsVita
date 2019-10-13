# NoPowerLimits

A PSVita kernel plugin that removes some restrictions placed by [ScePower](https://docs.vitasdk.org/group__ScePowerUser.html#ga9c95226b6af51ff89c04b61ee1fe01da).

Namely:
- **77% brightness limit** - when a game requests power mode C or D (166MHz GPU + network features)
![brightness_limit](https://user-images.githubusercontent.com/12598379/66714100-bbaab800-edb2-11e9-9058-8d8f5711a4c1.gif)
- **Disabled WLAN (network features)** - when a game requests power mode B (166MHz GPU + full brightness)
![network_features_disabled](https://user-images.githubusercontent.com/12598379/66714102-c82f1080-edb2-11e9-9157-655f7eed19df.jpg)

Previously with 166+MHz on the GPU, you either had available WLAN ***or*** 100% brightness. Now you can have them both in all four power modes (A/B/C/D).

___
### How to install
1. Put [NoPowerLimits.skprx](https://github.com/Electry/NoPowerLimitsVita/releases) in ur0:tai/ folder
2. Copy this to ur0:tai/config.txt
```
*KERNEL
ur0:tai/NoPowerLimits.skprx
```
3. Reboot your Vita
