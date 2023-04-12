#include "UIParam.h"

#include <algorithm>

void UIParam::initialize()
{
    GeoInfo info = {};

    setHorzCellCount(16);
    setVertCellCount(8);
    setHorzSpacing(6);
    setVertSpacing(6);

    ui_paramInLabel = std::make_shared<Label>();
    info = {};
    info.x = { 0, 1 };
    info.y = { 0, 1 };
    info.spacing = { 6, 6, 0, 0 };
    addElement(ui_paramInLabel.get(), info);
    ui_paramInLabel->setFont(Font(L"Default/Normal/14"));
    ui_paramInLabel->setText(L"==>");

    ui_paramInInput = std::make_shared<RawTextBox>();
    info = {};
    info.x = { 1, 14 };
    info.y = { 0, 1 };
    info.spacing.top = 6;
    addElement(ui_paramInInput.get(), info);
    ui_paramInInput->setRoundRadius(5);
    ui_paramInInput->setText
    (
        L"0000_0000_0000_0000_"
        L"0000_0000_0000_0000_"
        L"0000_0000_0000_0000_"
        L"0000_0000_0000_0000"
    );
    ui_paramInInput->setTextRect(
    {
        10,
        5,
        ui_paramInInput->width() - 10,
        ui_paramInInput->height() - 5
    });
    ui_paramInInput->D14_onLoseFocus(p, this)
    {
        auto i = (RawTextBox*)p;
        i->setText(paramToText(textToParam(i->text())));
    };

    ui_paramInLed = std::make_shared<Panel>();
    ui_paramInLed->setSize({ 16, 16 });
    info = {};
    info.fixedSize = true;
    info.x = { 15, 1 };
    info.y = { 0, 1 };
    ui_paramInLed->setRoundRadius(8);
    addElement(ui_paramInLed.get(), info);
    ui_paramInLed->setColor({ 50, 205, 50 });
    ui_paramInLed->setOpacity(1.0f);

    ui_paramOutLabel = std::make_shared<Label>();
    info = {};
    info.x = { 0, 1 };
    info.y = { 1, 1 };
    info.spacing = { 6, 0, 0, 6 };
    addElement(ui_paramOutLabel.get(), info);
    ui_paramOutLabel->setFont(Font(L"Default/Normal/14"));
    ui_paramOutLabel->setText(L"<==");

    ui_paramOutInput = std::make_shared<RawTextBox>();
    ui_paramOutInput->setEditable(false);
    info = {};
    info.x = { 1, 14 };
    info.y = { 1, 1 };
    info.spacing.bottom = 6;
    addElement(ui_paramOutInput.get(), info);
    ui_paramOutInput->setRoundRadius(5);
    ui_paramOutInput->setText
    (
        L"0000_0000_0000_0000_"
        L"0000_0000_0000_0000_"
        L"0000_0000_0000_0000_"
        L"0000_0000_0000_0000"
    );
    ui_paramOutInput->setTextRect(
    {
        10,
        5,
        ui_paramOutInput->width() - 10,
        ui_paramOutInput->height() - 5
    });

    ui_paramOutLed = std::make_shared<Panel>();
    ui_paramOutLed->setSize({ 16, 16 });
    info = {};
    info.fixedSize = true;
    info.x = { 15, 1 };
    info.y = { 1, 1 };
    ui_paramOutLed->setRoundRadius(8);
    addElement(ui_paramOutLed.get(), info);
    ui_paramOutLed->setColor({ 50, 205, 50 });
    ui_paramOutLed->setOpacity(1.0f);

    auto compareParamInOut = [this](RawTextBox*, const std::wstring&)
    {
        if (ui_paramInInput->text() == ui_paramOutInput->text())
        {
            ui_paramInLed->setColor({ 50, 205, 50 });
            ui_paramOutLed->setColor({ 50, 205, 50 });
        }
        else // param_i doesn't match param_o !!!
        {
            ui_paramInLed->setColor({ 220, 20, 60 });
            ui_paramOutLed->setColor({ 220, 20, 60 });
        }
    };
    ui_paramInInput->callback().onTextChange = compareParamInOut;
    ui_paramOutInput->callback().onTextChange = compareParamInOut;

    ui_reset_n = std::make_shared<ToggleButton>();
    info = {};
    info.x = { 0, 3 };
    info.y = { 2, 1 };
    info.spacing.left = 6;
    addElement(ui_reset_n.get(), info);
    ui_reset_n->setRoundRadius(5);
    ui_reset_n->setText(L"reset_n");
    ui_reset_n->D14_onStateChange(ToggleButton, obj, state)
    {
        bool value = (state == ToggleButton::Activated);
        //g_xdma->oldCtrlParam.set_reset_n(value);
        //g_xdma->writeCtrlParam(g_xdma->oldCtrlParam);
    };
    ui_param_reset_n = std::make_shared<ToggleButton>();
    info = {};
    info.x = { 3, 4 };
    info.y = { 2, 1 };
    addElement(ui_param_reset_n.get(), info);
    ui_param_reset_n->setRoundRadius(5);
    ui_param_reset_n->setText(L"param_reset_n");
    ui_param_reset_n->D14_onStateChange(ToggleButton, obj, state, this)
    {
        bool value = (state == ToggleButton::Activated);
        ui_use_def->setEnabled(value);
        ui_writein->setEnabled(value);
        ui_readout->setEnabled(value);
        //g_xdma->oldCtrlParam.set_param_reset_n(value);
        //g_xdma->writeCtrlParam(g_xdma->oldCtrlParam);
    };
    ui_use_def = std::make_shared<FilledButton>();
    ui_use_def->setEnabled(false);
    info = {};
    info.x = { 7, 3 };
    info.y = { 2, 1 };
    addElement(ui_use_def.get(), info);
    ui_use_def->setRoundRadius(5);
    ui_use_def->setText(L"use_def");
    ui_use_def->D14_onMouseButtonPress(clkp, e)
    {
        //g_xdma->oldCtrlParam.set_use_def(true);
        //g_xdma->writeCtrlParam(g_xdma->oldCtrlParam);
    };
    ui_use_def->D14_onMouseButtonRelease(clkp, e)
    {
        //g_xdma->oldCtrlParam.set_use_def(false);
        //g_xdma->writeCtrlParam(g_xdma->oldCtrlParam);
    };
    ui_writein = std::make_shared<FilledButton>();
    ui_writein->setEnabled(false);
    info = {};
    info.x = { 10, 3 };
    info.y = { 2, 1 };
    addElement(ui_writein.get(), info);
    ui_writein->setRoundRadius(5);
    ui_writein->setText(L"writein");
    ui_writein->D14_onMouseButtonPress(clkp, e, this)
    {
        //g_xdma->writeParam(textToParam(ui_paramInInput->text()));
        //g_xdma->oldCtrlParam.set_writein(true);
        //g_xdma->writeCtrlParam(g_xdma->oldCtrlParam);
    };
    ui_writein->D14_onMouseButtonRelease(clkp, e)
    {
        //g_xdma->oldCtrlParam.set_writein(false);
        //g_xdma->writeCtrlParam(g_xdma->oldCtrlParam);
    };
    ui_readout = std::make_shared<FilledButton>();
    ui_readout->setEnabled(false);
    info = {};
    info.x = { 13, 3 };
    info.y = { 2, 1 };
    info.spacing.right = 6;
    addElement(ui_readout.get(), info);
    ui_readout->setRoundRadius(5);
    ui_readout->setText(L"readout");
    ui_readout->D14_onMouseButtonPress(clkp, e)
    {
        //g_xdma->oldCtrlParam.set_readout(true);
        //g_xdma->writeCtrlParam(g_xdma->oldCtrlParam);
    };
    ui_readout->D14_onMouseButtonRelease(clkp, e, this)
    {
        //ui_paramOutInput->setText(paramToText(g_xdma->readParam()));
        //g_xdma->oldCtrlParam.set_readout(false);
        //g_xdma->writeCtrlParam(g_xdma->oldCtrlParam);
    };

    ui_paramTable = std::make_shared<GridLayout>();
    info = {};
    info.x = { 0, 16 };
    info.y = { 3, 5 };
    addElement(ui_paramTable.get(), info);
    ui_paramTable->setHorzCellCount(14);
    ui_paramTable->setVertCellCount(5);
    ui_paramTable->setHorzSpacing(6);
    ui_paramTable->setVertSpacing(6);

    ui_initLenLabel = std::make_shared<Label>();
    info = {};
    info.x = { 2, 3 };
    info.y = { 0, 1 };
    ui_paramTable->addElement(ui_initLenLabel.get(), info);
    ui_initLenLabel->setText(L"init_len");
    ui_initLenLabel->setHorzAlign(Label::HCenter);

    ui_highLenLabel = std::make_shared<Label>();
    info = {};
    info.x = { 5, 3 };
    info.y = { 0, 1 };
    ui_paramTable->addElement(ui_highLenLabel.get(), info);
    ui_highLenLabel->setText(L"high_len");
    ui_highLenLabel->setHorzAlign(Label::HCenter);

    ui_normLowLenLabel = std::make_shared<Label>();
    info = {};
    info.x = { 8, 3 };
    info.y = { 0, 1 };
    ui_paramTable->addElement(ui_normLowLenLabel.get(), info);
    ui_normLowLenLabel->setText(L"norm_low_len");
    ui_normLowLenLabel->setHorzAlign(Label::HCenter);

    ui_overLowLenLabel = std::make_shared<Label>();
    info = {};
    info.x = { 11, 3 };
    info.y = { 0, 1 };
    ui_paramTable->addElement(ui_overLowLenLabel.get(), info);
    ui_overLowLenLabel->setText(L"over_low_len");
    ui_overLowLenLabel->setHorzAlign(Label::HCenter);

    ui_selLabel = std::make_shared<Label>();
    info = {};
    info.x = { 0, 2 };
    info.y = { 1, 1 };
    info.spacing.left = 6;
    ui_paramTable->addElement(ui_selLabel.get(), info);
    ui_selLabel->setText(L"sel");
    ui_selLabel->setHorzAlign(Label::Right);

    ui_rstLabel = std::make_shared<Label>();
    info = {};
    info.x = { 0, 2 };
    info.y = { 2, 1 };
    info.spacing.left = 6;
    ui_paramTable->addElement(ui_rstLabel.get(), info);
    ui_rstLabel->setText(L"rst");
    ui_rstLabel->setHorzAlign(Label::Right);

    ui_stVsyncLabel = std::make_shared<Label>();
    info = {};
    info.x = { 0, 2 };
    info.y = { 3, 1 };
    info.spacing.left = 6;
    ui_paramTable->addElement(ui_stVsyncLabel.get(), info);
    ui_stVsyncLabel->setText(L"st / vsync");
    ui_stVsyncLabel->setHorzAlign(Label::Right);

    ui_drHsyncLabel = std::make_shared<Label>();
    info = {};
    info.x = { 0, 2 };
    info.y = { 4, 1 };
    info.spacing.left = 6;
    ui_paramTable->addElement(ui_drHsyncLabel.get(), info);
    ui_drHsyncLabel->setText(L"dr / hsync");
    ui_drHsyncLabel->setHorzAlign(Label::Right);

    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            int idx = c + r * 4;
            auto& ui_param = ui_params[idx];

            ui_param = std::make_shared<RawTextBox>();
            info = {};
            info.x = { 2 + c * 3, 3 };
            info.y = { 1 + r, 1 };
            ui_paramTable->addElement(ui_param.get(), info);
            ui_param->setRoundRadius(5);
            ui_param->setText(L"0");
            ui_param->setTextRect(
            {
                10,
                5,
                ui_param->width() - 10,
                ui_param->height() - 5
            });
            ui_param->D14_onLoseFocus(p, =)
            {
                auto i = (RawTextBox*)p;
                auto param = textToParam(ui_paramInInput->text());

                param.slices[idx] = (uint16_t)std::clamp(
                    _wtoi(i->text().c_str()), 0, 0xffff);

                i->setText(std::to_wstring(param.slices[idx]));
                ui_paramInInput->setText(paramToText(param));
            };
            ui_param->D14_onKeyboard(p, e, =)
            {
                if (e->pressed())
                {
                    RawTextBox* cell = nullptr;
                    switch (e->vkey())
                    {
                    case vk_left:
                    {
                        cell = ui_params[idx == 0 ? 15 : idx - 1].get();
                        break;
                    }
                    case vk_up:
                    {
                        cell = ui_params[idx < 4 ? idx + 12 : idx - 4].get();
                        break;
                    }
                    case vk_tab:
                    case vk_right:
                    {
                        cell = ui_params[idx == 15 ? 0 : idx + 1].get();
                        break;
                    }
                    case vk_down:
                    {
                        cell = ui_params[idx < 12 ? idx + 4 : idx - 12].get();
                        break;
                    }
                    default: break;
                    }
                    if (cell != nullptr)
                    {
                        cell->setFocused(true);
                        cell->setHiliteRange({ 0, (int)cell->text().size() });
                    }
                }
            };
        }
    }
}

#pragma warning(push)
#pragma warning(disable : 4996)

std::wstring UIParam::paramToText(XDMADevice::Param param)
{
    constexpr auto paramNum = 16;
    constexpr auto paramLen = 79;

    // reserve space for null-terminated
    std::wstring text(paramLen + 1, 0);
    for (int i = 0; i < paramNum; ++i)
    {
        auto ptr = text.data() + i * 5;
        wsprintf(ptr, L"%04X_", param.slices[i]);
    }
    // remember to remove the last '_'
    text.pop_back();

    return text;
}

XDMADevice::Param UIParam::textToParam(std::wstring text)
{
    XDMADevice::Param param = {};

    constexpr auto paramNum = 16;
    constexpr auto paramLen = 79;

    size_t orgSize = text.size();
    if (orgSize < paramLen)
    {
        text += std::wstring(paramLen - orgSize, L'0');
    }
    else if (orgSize > paramLen)
    {
        text.erase(text.begin() + paramLen, text.end());
    }
    for (int i = 0; i < paramLen; ++i)
    {
        if (i % 5 == 4) // should be a '_' here
        {
            text[i] = 0;
        }
        else if (!( // not hex, replace with '0'
            (text[i] >= L'0' && text[i] <= L'9') ||
            (text[i] >= L'a' && text[i] <= L'f') ||
            (text[i] >= L'A' && text[i] <= L'F')))
        {
            text[i] = L'0';
        }
    }
    for (int i = 0; i < paramNum; ++i)
    {
        auto ptr = text.data() + i * 5;
        param.slices[i] = (uint16_t)wcstoul(ptr, nullptr, 16);
    }
    return param;
}

#pragma warning(pop)
