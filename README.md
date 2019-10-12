# NoPowerLimits

A PSVita kernel plugin that removes some restrictions placed by [ScePower](https://docs.vitasdk.org/group__ScePowerUser.html#ga9c95226b6af51ff89c04b61ee1fe01da).

Namely:
- 80% (77%) brightness limit when a game requests power mode C or D (aka. 166+ MHz on the GPU)
- Disabled WLAN (wireless features) when a game requests power mode B

___
### How to install
1. Put [NoPowerLimits.skprx](https://github.com/Electry/NoPowerLimitsVita/releases) in ur0:tai/ folder
2. Copy this to ur0:tai/config.txt
```
*KERNEL
ur0:tai/NoPowerLimits.skprx
```
