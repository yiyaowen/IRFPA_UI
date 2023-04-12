#include "UICamera.h"

#include <algorithm>

#include "TickTimer.h"
#include "XDMADevice.h"

UICamera::UICamera()
{
    ui_fps = std::make_shared<Label>();
    ui_fps->setParent(this);
    ui_fps->setPosition({ 40, 40 });
    ui_fps->setVertAlign(Label::Top);
    ui_fps->setVertHardAlign(true);
    ui_fps->D14_onChangeLangLocale(p, name)
    {
        auto l = (Label*)p;
        if (name == L"en-us")
        {
            l->setFont(Font(L"Default/Normal/16"));
        }
        else if (name == L"zh-cn")
        {
            l->setFont(Font(L"默认/正常/16"));
        }
    };
    ui_view = std::make_shared<Panel>();
    ui_view->setParent(this);
    ui_view->setSize({ 128, 128 });
    ui_view->setPosition({ 336, 158 });
    ui_view->setOutlineWidth(1);
    ui_view->setOutlineOpacity(1.0f);
    ui_view->D14_onChangeTheme(p, name)
    {
        if (name == L"Dark")
        {
            p->setOutlineColor({ 105, 105, 105 });
        }
        else if (name == L"Light")
        {
            p->setOutlineColor({ 220, 220, 220 });
        }
    };
    constexpr auto rowNum = 128;
    constexpr auto colNum = 128;
    constexpr auto pixelNum = rowNum * colNum;

    data.resize(pixelNum);
    image.resize(pixelNum);
    ui_image = std::make_shared<Image>(colNum, rowNum);
    ui_view->setImage(ui_image.get());

    ui_testMode = std::make_shared<ToggleButton>();
    ui_testMode->setParent(this);
    ui_testMode->setSize({ 200, 50 });
    ui_testMode->setPosition({ 580, 20 });
    ui_testMode->setRoundRadius(5);
    ui_testMode->D14_onChangeLangLocale(p, name)
    {
        auto b = dynamic_cast<Button*>(p);
        if (name == L"en-us")
        {
            b->setFont(Font(L"Default/Normal/16"));
            b->setText(L"Test mode");
        }
        else if (name == L"zh-cn")
        {
            b->setFont(Font(L"默认/正常/16"));
            b->setText(L"测试模式");
        }
    };
    ui_testMode->D14_onStateChange(ToggleButton, obj, state)
    {
        //if (state == ToggleButton::Activated)
        //{
        //    g_xdma->oldCtrlParam.set_test_mode(true);
        //}
        //else if (state == ToggleButton::Deactivated)
        //{
        //    g_xdma->oldCtrlParam.set_test_mode(false);
        //}
        //g_xdma->writeCtrlParam(g_xdma->oldCtrlParam);
    };
}

void UICamera::onUpdate()
{
    //if (g_xdma->readStateParam().read_ready())
    {
        //g_xdma->oldCtrlParam.set_write_ready(false);
        //g_xdma->writeCtrlParam(g_xdma->oldCtrlParam);

        //g_xdma->readImage(data);

        //g_xdma->oldCtrlParam.set_write_ready(true);
        //g_xdma->writeCtrlParam(g_xdma->oldCtrlParam);

        std::transform(data.begin(), data.end(), image.begin(),
        [](uint16_t elem)
        {
            constexpr auto full = (2 << 14) - 1;
            auto gray = uint8_t(elem * 255 / full);
            return Pixel{ gray, gray, gray, 255 };
        });

        constexpr auto rowNum = 128;
        constexpr auto colNum = 128;
        ui_image->copyInFrame({ 0, 0, colNum, rowNum }, image.data());

        g_timer->tick();

        auto app = Application::app();
        if (app->langLocale() == L"en-us")
        {
            ui_fps->setText(L"FPS: " + std::to_wstring(g_timer->fps()));
        }
        else if (app->langLocale() == L"zh-cn")
        {
            ui_fps->setText(L"帧率：" + std::to_wstring(g_timer->fps()));
        }
    }
}
