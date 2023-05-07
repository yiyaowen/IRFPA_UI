# IRPFA_UI

PC app for IRFPA test system. The UI part depends on D14UIKit (https://github.com/yiyaowen/D14UIKit), so you need to prepare the C++ wrapper at the project root directory before getting started. Since D14UIKit project is under developing, it is better to use **version 0.1** in case of interface changes (i.e. **d14uikit_cpp_v0_1**).

Download the latest **d14uikit_cpp_v0_1.zip** and extract it into **d14uikit** subdirectory:

* d14uikit
  * include
  * lib
    * debug / D14UIKit.dll
    * release / D14UIKit.dll
    * D14UIKit.lib
* include
* src
* Other project files in IRFPA_UI

After the environment is setup, simply select **Debug / Release (x64)** to build the application.