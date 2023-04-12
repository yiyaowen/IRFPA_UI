#pragma once

#include <array>

#include "Common.h"
#include "XDMADevice.h"

class UIParam : public GridLayout
{
public:
    // The size was not decided when constructing,
    // so we must initialize manually after that.
    void initialize();

private:
    std::shared_ptr<Label> ui_paramInLabel = {};
    std::shared_ptr<RawTextBox> ui_paramInInput = {};
    std::shared_ptr<Panel> ui_paramInLed = {};

    std::shared_ptr<Label> ui_paramOutLabel = {};
    std::shared_ptr<RawTextBox> ui_paramOutInput = {};
    std::shared_ptr<Panel> ui_paramOutLed = {};

    std::shared_ptr<ToggleButton> ui_reset_n = {};
    std::shared_ptr<ToggleButton> ui_param_reset_n = {};
    std::shared_ptr<FilledButton> ui_use_def = {};
    std::shared_ptr<FilledButton> ui_writein = {};
    std::shared_ptr<FilledButton> ui_readout = {};

    std::shared_ptr<GridLayout> ui_paramTable = {};

    std::shared_ptr<Label> ui_initLenLabel = {};
    std::shared_ptr<Label> ui_highLenLabel = {};
    std::shared_ptr<Label> ui_normLowLenLabel = {};
    std::shared_ptr<Label> ui_overLowLenLabel = {};

    std::shared_ptr<Label> ui_selLabel = {};
    std::shared_ptr<Label> ui_rstLabel = {};
    std::shared_ptr<Label> ui_stVsyncLabel = {};
    std::shared_ptr<Label> ui_drHsyncLabel = {};

    std::array<std::shared_ptr<RawTextBox>, 16> ui_params = {};

    std::wstring paramToText(XDMADevice::Param param);
    XDMADevice::Param textToParam(std::wstring text);
};
