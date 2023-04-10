#include "XDMADevice.h"

#include <memory>

#include <INITGUID.H>
#include <SetupAPI.h>

#include "xdma_public.h"

XDMADevice::XDMADevice()
{
    //=========================================== Query XDMA device base path.
    HDEVINFO devInfo = SetupDiGetClassDevs(
        &GUID_DEVINTERFACE_XDMA,
        nullptr,
        nullptr,
        DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

    if (devInfo == INVALID_HANDLE_VALUE)
    {
        MessageBox(
            nullptr,
            L"Failed to get devices.",
            L"Error",
            MB_ICONERROR);
        exit(-1);
    }
    SP_DEVICE_INTERFACE_DATA devData = {};
    devData.cbSize = sizeof(devData);

    for (DWORD i = 0;
        SetupDiEnumDeviceInterfaces(
            devInfo,
            nullptr,
            &GUID_DEVINTERFACE_XDMA,
            i,
            &devData); ++i)
    {
        DWORD detailLen = 0;
        if (!SetupDiGetDeviceInterfaceDetail(
            devInfo,
            &devData,
            nullptr,
            0,
            &detailLen,
            nullptr) &&
            GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        {
            MessageBox(
                nullptr,
                L"Failed to get length of device details.",
                L"Error",
                MB_ICONERROR);
            exit(-1);
        }
        auto devDetail = std::make_unique<uint8_t[]>(detailLen);
        auto pDevDetail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)devDetail.get();

        pDevDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        if (!SetupDiGetDeviceInterfaceDetail(
            devInfo,
            &devData,
            pDevDetail,
            detailLen,
            nullptr,
            nullptr))
        {
            MessageBox(
                nullptr,
                L"Failed to get device details.",
                L"Error",
                MB_ICONERROR);
            exit(-1);
        }
        basePath.resize(lstrlen(pDevDetail->DevicePath));
        basePath.copy(pDevDetail->DevicePath, basePath.size());
    }
    SetupDiDestroyDeviceInfoList(devInfo);

    //=========================================== Open target XDMA devices.
    c2h0 = CreateFile(
        (basePath + XDMA_FILE_C2H_0).c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);

    if (c2h0 == INVALID_HANDLE_VALUE)
    {
        MessageBox(
            nullptr,
            L"Failed to open c2h_0 device.",
            L"Error",
            MB_ICONERROR);
        exit(-1);
    }

    user = CreateFile(
        (basePath + XDMA_FILE_USER).c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr);

    if (user == INVALID_HANDLE_VALUE)
    {
        MessageBox(
            nullptr,
            L"Failed to open user device.",
            L"Error",
            MB_ICONERROR);
        exit(-1);
    }
}

XDMADevice::~XDMADevice()
{
    CloseHandle(c2h0);
    CloseHandle(user);
}

void XDMADevice::readImage(std::vector<uint16_t>& image)
{
    constexpr auto pixelNum = 128 * 128;
    constexpr auto bytesNum = pixelNum * sizeof(uint16_t);
    if (image.size() != pixelNum)
    {
        image.resize(pixelNum);
    }
    DWORD numBytesRead = 0;
    if (!ReadFile(
        c2h0,
        image.data(),
        bytesNum,
        &numBytesRead,
        nullptr))
    {
        MessageBox(
            nullptr,
            L"Failed to read c2h0 device.",
            L"Error",
            MB_ICONERROR);
        exit(-1);
    }
    if (numBytesRead != bytesNum)
    {
        MessageBox(
            nullptr,
            L"Read incomplete data from c2h0 device.",
            L"Error",
            MB_ICONERROR);
        exit(-1);
    }
}

uint32_t XDMADevice::readRegsiter(size_t num)
{
    // all registers are readable
    LARGE_INTEGER addrOffset = {};
    addrOffset.QuadPart = regNumToAddrOffset(num);
    if (!SetFilePointerEx(user, addrOffset, nullptr, FILE_BEGIN))
    {
        MessageBox(
            nullptr,
            L"Failed to offset user device.",
            L"Error",
            MB_ICONERROR);
        exit(-1);
    }
    uint32_t data = 0;
    DWORD numBytesRead = 0;
    if (!ReadFile(
        user,
        &data,
        sizeof(data),
        &numBytesRead,
        nullptr))
    {
        MessageBox(
            nullptr,
            L"Failed to read user device.",
            L"Error",
            MB_ICONERROR);
        exit(-1);
    }
    if (numBytesRead != sizeof(data))
    {
        MessageBox(
            nullptr,
            L"Read incomplete data from user device.",
            L"Error",
            MB_ICONERROR);
        exit(-1);
    }
    return data;
}

void XDMADevice::writeRegister(size_t num, uint32_t val)
{
    // only 0, 2, 3, 4, 5, 6, 7, 8, 9 writable
    if (num == 1 || num >= 10) return;
    LARGE_INTEGER addrOffset = {};
    addrOffset.QuadPart = regNumToAddrOffset(num);
    if (!SetFilePointerEx(user, addrOffset, nullptr, FILE_BEGIN))
    {
        MessageBox(
            nullptr,
            L"Failed to offset user device.",
            L"Error",
            MB_ICONERROR);
        exit(-1);
    }
    DWORD numBytesWritten = 0;
    if (!WriteFile(
        user,
        &val,
        sizeof(val),
        &numBytesWritten,
        nullptr))
    {
        MessageBox(
            nullptr,
            L"Failed to write user device.",
            L"Error",
            MB_ICONERROR);
        exit(-1);
    }
    if (numBytesWritten != sizeof(val))
    {
        MessageBox(
            nullptr,
            L"Write incomplete data into user device.",
            L"Error",
            MB_ICONERROR);
        exit(-1);
    }
}

size_t XDMADevice::regNumToAddrOffset(size_t num)
{
    switch (num)
    {
    case  0: return 0x00000000;
    case  1: return 0x00000008;
    case  2: return 0x00010000;
    case  3: return 0x00010008;
    case  4: return 0x00020000;
    case  5: return 0x00020008;
    case  6: return 0x00030000;
    case  7: return 0x00030008;
    case  8: return 0x00040000;
    case  9: return 0x00040008;
    case 10: return 0x00050000;
    case 11: return 0x00050008;
    case 12: return 0x00060000;
    case 13: return 0x00060008;
    case 14: return 0x00070000;
    case 15: return 0x00070008;
    case 16: return 0x00080000;
    case 17: return 0x00080008;
    default: return 0x00000000;
    }
}

XDMADevice::Param XDMADevice::readParam()
{
    Param param = {};
    param.slice32 =
    {
        readRegsiter(10),
        readRegsiter(11),
        readRegsiter(12),
        readRegsiter(13),
        readRegsiter(14),
        readRegsiter(15),
        readRegsiter(16),
        readRegsiter(17)
    };
    return param;
}

void XDMADevice::writeParam(const Param& param)
{
    writeRegister(2, param.slice32._0);
    writeRegister(3, param.slice32._1);
    writeRegister(4, param.slice32._2);
    writeRegister(5, param.slice32._3);
    writeRegister(6, param.slice32._4);
    writeRegister(7, param.slice32._5);
    writeRegister(8, param.slice32._6);
    writeRegister(9, param.slice32._7);
}

bool XDMADevice::CtrlParam::reset_n() const
{
    return slice8._0 & 0x01;
}

void XDMADevice::CtrlParam::set_reset_n(bool value)
{
    if (value) slice8._0 |= 0x01;
    else slice8._0 &= (~0x01);
}

bool XDMADevice::CtrlParam::param_reset_n() const
{
    return slice8._0 & 0x02;
}

void XDMADevice::CtrlParam::set_param_reset_n(bool value)
{
    if (value) slice8._0 |= 0x02;
    else slice8._0 &= (~0x02);
}

bool XDMADevice::CtrlParam::use_def() const
{
    return slice8._0 & 0x04;
}

void XDMADevice::CtrlParam::set_use_def(bool value)
{
    if (value) slice8._0 |= 0x04;
    else slice8._0 &= (~0x04);
}

bool XDMADevice::CtrlParam::writein() const
{
    return slice8._0 & 0x08;
}

void XDMADevice::CtrlParam::set_writein(bool value)
{
    if (value) slice8._0 |= 0x08;
    else slice8._0 &= (~0x08);
}

bool XDMADevice::CtrlParam::readout() const
{
    return slice8._0 & 0x10;
}

void XDMADevice::CtrlParam::set_readout(bool value)
{
    if (value) slice8._0 |= 0x10;
    else slice8._0 &= (~0x10);
}

bool XDMADevice::CtrlParam::test_mode() const
{
    return slice8._0 & 0x20;
}

void XDMADevice::CtrlParam::set_test_mode(bool value)
{
    if (value) slice8._0 |= 0x20;
    else slice8._0 &= (~0x20);
}

bool XDMADevice::CtrlParam::write_ready() const
{
    return slice8._0 & 0x40;
}

void XDMADevice::CtrlParam::set_write_ready(bool value)
{
    if (value) slice8._0 |= 0x40;
    else slice8._0 &= (~0x40);
}

void XDMADevice::writeCtrlParam(const CtrlParam& param)
{
    oldCtrlParam = param;
    writeRegister(0, param.slice32);
}

bool XDMADevice::StateParam::read_ready() const
{
    return slice8._0 & 0x01;
}

XDMADevice::StateParam XDMADevice::readStateParam()
{
    StateParam param = {};
    param.slice32 = readRegsiter(1);
    return param;
}
