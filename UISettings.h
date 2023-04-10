#pragma once

#include "Common.h"

class UISettings : public Panel
{
public:
    UISettings();

private:
    std::shared_ptr<Label> ui_themeModeTitle = {};
    std::shared_ptr<ComboBox> ui_themeSelector = {};
    std::shared_ptr<ComboBoxItem> ui_darkModeItem = {};
    std::shared_ptr<ComboBoxItem> ui_lightModeItem = {};
    std::shared_ptr<ComboBoxItem> ui_useSystemThemeItem = {};
    
    std::shared_ptr<Label> ui_textRndrTitle = {};
    std::shared_ptr<CheckBox> ui_clearTypeChecker = {};
    std::shared_ptr<Label> ui_clearTypeLabel = {};
    std::shared_ptr<CheckBox> ui_textVertSmoothChecker = {};
    std::shared_ptr<Label> ui_textVertSmoothLabel = {};

    std::shared_ptr<Label> ui_dispLangTitle = {};
    std::shared_ptr<ComboBox> ui_dispLangSelector = {};
    std::shared_ptr<ComboBoxItem> ui_englishLangItem = {};
    std::shared_ptr<ComboBoxItem> ui_chineseLangItem = {};
};
