#pragma once

#include <string>
#include <vector>

#include <Windows.h>

class XDMADevice
{
public:
    XDMADevice();

    ~XDMADevice();

private:
    std::wstring basePath = {};
    HANDLE c2h0 = {};
    HANDLE user = {};

    // 0: ctrl_param, 1: state_param
    // 2 ~ 9: param_i, 10 ~ 17: param_o
    uint32_t readRegsiter(size_t num);

    // 0: ctrl_param, 1: state_param
    // 2 ~ 9: param_i, 10 ~ 17: param_o
    void writeRegister(size_t num, uint32_t val);

    // num[0 ~ 17] mapped to gpio[0 ~ 8]
    size_t regNumToAddrOffset(size_t num);

public:
    void readImage(std::vector<uint16_t>& image);

    union Param
    {
        struct Slice16
        {
            uint16_t SEL_INIT_LEN = 0;
            uint16_t SEL_HIGH_LEN = 0;
            uint16_t SEL_NORM_LOW_LEN = 0;
            uint16_t SEL_OVER_LOW_LEN = 0;

            uint16_t RST_INIT_LEN = 0;
            uint16_t RST_HIGH_LEN = 0;
            uint16_t RST_NORM_LOW_LEN = 0;
            uint16_t RST_OVER_LOW_LEN = 0;

            uint16_t ST_INIT_LEN = 0;
            uint16_t ST_HIGH_LEN = 0;
            uint16_t ST_NORM_LOW_LEN = 0;
            uint16_t ST_OVER_LOW_LEN = 0;

            uint16_t DR_INIT_LEN = 0;
            uint16_t DR_HIGH_LEN = 0;
            uint16_t DR_NORM_LOW_LEN = 0;
            uint16_t DR_OVER_LOW_LEN = 0;
        }
        slice16 = {};

        uint16_t slices[16];

        uint32_t slice32[8];
    };
    Param readParam();
    void writeParam(const Param& param);

    union CtrlParam
    {
        uint32_t slice32 = 0;

        uint8_t slice8[4];
        
        bool reset_n() const;
        void set_reset_n(bool value);

        bool param_reset_n() const;
        void set_param_reset_n(bool value);

        bool use_def() const;
        void set_use_def(bool value);

        bool writein() const;
        void set_writein(bool value);

        bool readout() const;
        void set_readout(bool value);

        bool test_mode() const;
        void set_test_mode(bool value);

        bool write_ready() const;
        void set_write_ready(bool value);
    }
    oldCtrlParam = {};

    void writeCtrlParam(const CtrlParam& param);

    union StateParam
    {
        uint32_t slice32 = 0;

        uint8_t slice8[4];

        bool read_ready() const;
    };
    StateParam readStateParam();
};
