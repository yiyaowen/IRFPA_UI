#include <Windows.h>

#include "UIWindow.h"

int main()
{
#ifdef _DEBUG
    SetDllDirectory(L"d14uikit/lib/debug");
#else
    SetDllDirectory(L"d14uikit/lib/release");
#endif
    Application app;
    UIWindow window;
    app.setLowEnergy(false);
    app.setLangLocale(L"en-us");
    app.setBmpQualityInterp(true);
    return app.run();
}
