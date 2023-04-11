#pragma once

#include "Common.h"

class UICamera : public Panel
{
public:
    UICamera();

private:
    std::shared_ptr<Label> ui_fps = {};
    
    std::shared_ptr<Panel> ui_view = {};

    std::vector<uint16_t> data = {};
    std::vector<Pixel> image = {};
    std::shared_ptr<Image> ui_image = {};

    std::shared_ptr<ToggleButton> ui_testMode = {};

protected:
    void onUpdate() override;
};
