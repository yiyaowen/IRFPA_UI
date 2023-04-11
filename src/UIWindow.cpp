#include "UIWindow.h"

UIWindow::UIWindow()
{
    setCaptionHeight(36);
    setMaximizeButton(false);

    ui_bkgn = std::make_shared<Panel>();
    setContent(ui_bkgn.get());

    ui_tg = std::make_shared<TabGroup>();
    ui_tg->setParent(ui_bkgn.get());
    ui_tg->setSize({ 800, 500 });
    ui_tg->setPosition({ 0, 60 });
    ui_tg->setCardSize({ 200, 32 });

    ui_capCamera = std::make_shared<TabCaption>();
    ui_capCamera->setClosable(false);
    ui_capCamera->setDraggable(false);
    ui_capCamera->D14_onChangeLangLocale(p, name)
    {
        auto t = (TabCaption*)p;
        if (name == L"en-us")
        {
            t->setFont(Font(L"Default/Normal/16"));
            t->setTitle(L"Camera");
        }
        else if (name == L"zh-cn")
        {
            t->setFont(Font(L"默认/正常/16"));
            t->setTitle(L"相机");
        }
    };
    ui_tabCamera = std::make_shared<UICamera>();
    ui_tg->appendTab({ ui_capCamera.get(), ui_tabCamera.get() });

    ui_capParam = std::make_shared<TabCaption>();
    ui_capParam->setClosable(false);
    ui_capParam->setDraggable(false);
    ui_capParam->D14_onChangeLangLocale(p, name)
    {
        auto t = (TabCaption*)p;
        if (name == L"en-us")
        {
            t->setFont(Font(L"Default/Normal/16"));
            t->setTitle(L"Parameter");
        }
        else if (name == L"zh-cn")
        {
            t->setFont(Font(L"默认/正常/16"));
            t->setTitle(L"参数");
        }
    };
    ui_tabParam = std::make_shared<UIParam>();
    ui_tg->appendTab({ ui_capParam.get(), ui_tabParam.get() });

    ui_capSettings = std::make_shared<TabCaption>();
    ui_capSettings->setClosable(false);
    ui_capSettings->setDraggable(false);
    ui_capSettings->D14_onChangeLangLocale(p, name)
    {
        auto t = (TabCaption*)p;
        if (name == L"en-us")
        {
            t->setFont(Font(L"Default/Normal/16"));
            t->setTitle(L"Settings");
        }
        else if (name == L"zh-cn")
        {
            t->setFont(Font(L"默认/正常/16"));
            t->setTitle(L"设置");
        }
    };
    ui_tabSettings = std::make_shared<UISettings>();
    ui_tg->appendTab({ ui_capSettings.get(), ui_tabSettings.get() });

    ui_tg->setCurrSelected(0);
}

void UIWindow::onChangeLangLocale(const std::wstring& name)
{
    if (name == L"en-us")
    {
        setFontTitle(Font(L"Default/Normal/16"));
        setTitle(L"IRFPA_UI @ IRFPA Test System");
    }
    else if (name == L"zh-cn")
    {
        setFontTitle(Font(L"默认/正常/16"));
        setTitle(L"IRFPA_UI @ 红外成像芯片测试系统");
    }
}
