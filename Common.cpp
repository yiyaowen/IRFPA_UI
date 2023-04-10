﻿#include "Common.h"

#include "TickTimer.h"
#include "XDMADevice.h"

std::unique_ptr<TickTimer> g_timer = std::make_unique<TickTimer>();

std::unique_ptr<XDMADevice> g_xdma = {};

//std::unique_ptr<XDMADevice> g_xdma = std::make_unique<XDMADevice>();