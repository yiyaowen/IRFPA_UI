#pragma once

#include "Common.h"
#include "UICamera.h"
#include "UIParam.h"
#include "UISettings.h"

class UIWindow : public MainWindow
{
public:
    UIWindow();

private:
    std::shared_ptr<Panel> ui_bkgn = {};
    std::shared_ptr<TabGroup> ui_tg = {};
    std::shared_ptr<TabCaption> ui_capCamera = {};
    std::shared_ptr<UICamera> ui_tabCamera = {};
    std::shared_ptr<TabCaption> ui_capParam = {};
    std::shared_ptr<UIParam> ui_tabParam = {};
    std::shared_ptr<TabCaption> ui_capSettings = {};
    std::shared_ptr<UISettings> ui_tabSettings = {};

protected:
    void onChangeLangLocale(const std::wstring& name) override;

    void onKeyboard(KeyboardEvent* event) override;
};
