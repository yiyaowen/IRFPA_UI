#include "UISettings.h"

UISettings::UISettings()
{
    ui_themeModeTitle = std::make_shared<Label>();
    ui_themeModeTitle->setParent(this);
    ui_themeModeTitle->setPosition({ 40, 40 });
    ui_themeModeTitle->setVertAlign(Label::Top);
    ui_themeModeTitle->setVertHardAlign(true);
    ui_themeModeTitle->D14_onChangeLangLocale(p, name)
    {
        auto l = (Label*)p;
        if (name == L"en-us")
        {
            l->setFont(Font(L"Default/SemiBold/18"));
            l->setText(L"Theme Mode");
        }
        else if (name == L"zh-cn")
        {
            l->setFont(Font(L"默认/粗体/18"));
            l->setText(L"主题模式");
        }
    };
    ui_themeSelector = std::make_shared<ComboBox>();
    ui_themeSelector->setParent(this);
    ui_themeSelector->setPosition({ 40, 90 });
    ui_themeSelector->setWidth(250);
    ui_themeSelector->setRoundRadius(5);
    {
        ui_darkModeItem = std::make_shared<ComboBoxItem>();
        ui_darkModeItem->D14_onChangeLangLocale(p, name, this)
        {
            auto i = (ComboBoxItem*)p;
            if (name == L"en-us")
            {
                i->setFont(Font(L"Default/Normal/16"));
                i->setText(L"Dark");
            }
            else if (name == L"zh-cn")
            {
                i->setFont(Font(L"默认/正常/16"));
                i->setText(L"黑色");
            }
        };
        ui_lightModeItem = std::make_shared<ComboBoxItem>();
        ui_lightModeItem->D14_onChangeLangLocale(p, name, this)
        {
            auto i = (ComboBoxItem*)p;
            if (name == L"en-us")
            {
                i->setFont(Font(L"Default/Normal/16"));
                i->setText(L"Light");
            }
            else if (name == L"zh-cn")
            {
                i->setFont(Font(L"默认/正常/16"));
                i->setText(L"白色");
            }
        };
        ui_useSystemThemeItem = std::make_shared<ComboBoxItem>();
        ui_useSystemThemeItem->D14_onChangeLangLocale(p, name, this)
        {
            auto i = (ComboBoxItem*)p;
            if (name == L"en-us")
            {
                i->setFont(Font(L"Default/Normal/16"));
                i->setText(L"Use system setting");
            }
            else if (name == L"zh-cn")
            {
                i->setFont(Font(L"默认/正常/16"));
                i->setText(L"使用系统设置");
            }
        };
    }
    ui_themeSelector->dropDownMenu()->setHeight(120);
    ui_themeSelector->dropDownMenu()->setRoundExtension(5);
    ui_themeSelector->dropDownMenu()->appendItem(
    {
        ui_darkModeItem.get(),
        ui_lightModeItem.get(),
        ui_useSystemThemeItem.get()
    });
    ui_themeSelector->setCurrSelected(1);
    ui_themeSelector->setText(L"Light");
    ui_themeSelector->D14_onSelectedChange(ComboBox, obj, text)
    {
        auto app = Application::app();
        if (text == L"Dark" || text == L"黑色")
        {
            app->setThemeMode(L"Dark");
        }
        else if (text == L"Light" || text == L"白色")
        {
            app->setThemeMode(L"Light");
        }
        else app->setUseSystemTheme(true);
    };
    ui_textRndrTitle = std::make_shared<Label>();
    ui_textRndrTitle->setParent(this);
    ui_textRndrTitle->setPosition({ 40, 180 });
    ui_textRndrTitle->setVertAlign(Label::Top);
    ui_textRndrTitle->setVertHardAlign(true);
    ui_textRndrTitle->D14_onChangeLangLocale(p, name)
    {
        auto l = (Label*)p;
        if (name == L"en-us")
        {
            l->setFont(Font(L"Default/SemiBold/18"));
            l->setText(L"Text Rendering");
        }
        else if (name == L"zh-cn")
        {
            l->setFont(Font(L"默认/粗体/18"));
            l->setText(L"文本渲染");
        }
    };
    ui_clearTypeChecker = std::make_shared<CheckBox>();
    ui_clearTypeChecker->setParent(this);
    ui_clearTypeChecker->setPosition({ 40, 220 });
    ui_clearTypeChecker->D14_onStateChange(CheckBox, obj, state)
    {
        auto app = Application::app();
        if (state == CheckBox::Checked)
        {
            app->setClearType(true);
        }
        else app->setClearType(false);
    };
    ui_clearTypeChecker->setState(CheckBox::Checked);
    ui_clearTypeLabel = std::make_shared<Label>();
    ui_clearTypeLabel->setParent(this);
    ui_clearTypeLabel->setHeight(ui_clearTypeChecker->height());
    ui_clearTypeLabel->setPosition({ 80, 220 });
    ui_clearTypeLabel->setFont(Font(L"Default/Normal/16"));
    ui_clearTypeLabel->setText(L"ClearType");

    ui_textVertSmoothChecker = std::make_shared<CheckBox>();
    ui_textVertSmoothChecker->setParent(this);
    ui_textVertSmoothChecker->setPosition({ 40, 260 });
    ui_textVertSmoothChecker->D14_onStateChange(CheckBox, obj, state)
    {
        auto app = Application::app();
        if (state == CheckBox::Checked)
        {
            app->setTextVertSmooth(true);
        }
        else app->setTextVertSmooth(false);
    };
    ui_textVertSmoothChecker->setState(CheckBox::Checked);
    ui_textVertSmoothLabel = std::make_shared<Label>();
    ui_textVertSmoothLabel->setParent(this);
    ui_textVertSmoothLabel->setHeight(ui_textVertSmoothChecker->height());
    ui_textVertSmoothLabel->setPosition({ 80, 260 });
    ui_textVertSmoothLabel->D14_onChangeLangLocale(p, name)
    {
        auto l = (Label*)p;
        if (name == L"en-us")
        {
            l->setFont(Font(L"Default/Normal/16"));
            l->setText(L"Vertical Smooth");
        }
        else if (name == L"zh-cn")
        {
            l->setFont(Font(L"默认/正常/16"));
            l->setText(L"垂直平滑");
        }
    };
    ui_dispLangTitle = std::make_shared<Label>();
    ui_dispLangTitle->setParent(this);
    ui_dispLangTitle->setPosition({ 40, 330 });
    ui_dispLangTitle->setVertAlign(Label::Top);
    ui_dispLangTitle->setVertHardAlign(true);
    ui_dispLangTitle->D14_onChangeLangLocale(p, name)
    {
        auto l = (Label*)p;
        if (name == L"en-us")
        {
            l->setFont(Font(L"Default/SemiBold/18"));
            l->setText(L"Display Language");
        }
        else if (name == L"zh-cn")
        {
            l->setFont(Font(L"默认/粗体/18"));
            l->setText(L"显示语言");
        }
    };
    ui_dispLangSelector = std::make_shared<ComboBox>();
    ui_dispLangSelector->setParent(this);
    ui_dispLangSelector->setPosition({ 40, 380 });
    ui_dispLangSelector->setWidth(250);
    ui_dispLangSelector->setRoundRadius(5);
    {
        ui_englishLangItem = std::make_shared<ComboBoxItem>();
        ui_englishLangItem->setFont(Font(L"Default/Normal/16"));
        ui_englishLangItem->setText(L"English");

        ui_chineseLangItem = std::make_shared<ComboBoxItem>();
        ui_chineseLangItem->setFont(Font(L"默认/正常/16"));
        ui_chineseLangItem->setText(L"简体中文");
    }
    ui_dispLangSelector->dropDownMenu()->setHeight(80);
    ui_dispLangSelector->dropDownMenu()->setRoundExtension(5);
    ui_dispLangSelector->dropDownMenu()->appendItem(
    {
        ui_englishLangItem.get(),
        ui_chineseLangItem.get()
    });
    ui_dispLangSelector->setCurrSelected(0);
    ui_dispLangSelector->setText(L"English");
    ui_dispLangSelector->D14_onSelectedChange(ComboBox, obj, text)
    {
        auto app = Application::app();
        if (text == L"English")
        {
            app->setLangLocale(L"en-us");
        }
        else if (text == L"简体中文")
        {
            app->setLangLocale(L"zh-cn");
        }
    };
}
