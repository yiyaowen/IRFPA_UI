#include <Windows.h>

#include "UIWindow.h"

int main()
{
#ifndef _DEBUG
    SetDllDirectory(L"d14uikit/lib");
#else
    SetDllDirectory(L"d14uikit/lib_d");
#endif
    Application app;
    UIWindow window;
    app.setLowEnergy(false);
    app.setThemeMode(L"Light");
    app.setLangLocale(L"en-us");
    return app.run();
}
