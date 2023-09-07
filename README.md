# IRPFA_UI

PC app for IRFPA test system. The UI part depends on D14UIKit (still under development).

## Prepare

Download ``d14uikit_cpp_v0_1.zip`` from https://github.com/yiyaowen/D14UIKit and extract it into ``d14uikit`` subdirectory (created by yourself):

* d14uikit
  * include
  * lib
    * debug / D14UIKit.dll
    * release / D14UIKit.dll
    * D14UIKit.lib
* include
* src
* Other project files in IRFPA_UI

## Usage

There's a global macro ``IRFPA_UI_PCIE`` in the ``src/Common.h`` header, which is commented out by default and thus the app doesn't create the XDMA device for PCIe communication (only UI). If you have done with the PCIe works, simply enable the macro to use the complete test system.
