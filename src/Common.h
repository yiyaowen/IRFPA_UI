#pragma once

#include "AppEntry.h"
#include "Application.h"
#include "Callback.h"
#include "CheckBox.h"
#include "ComboBox.h"
#include "ComboBoxItem.h"
#include "GridLayout.h"
#include "Image.h"
#include "Label.h"
#include "MainWindow.h"
#include "PopupMenu.h"
#include "RawTextBox.h"
#include "TabCaption.h"
#include "TabGroup.h"
#include "ToggleButton.h"

using namespace d14uikit;

struct TickTimer;
extern std::unique_ptr<TickTimer> g_timer;

class XDMADevice;
extern std::unique_ptr<XDMADevice> g_xdma;
