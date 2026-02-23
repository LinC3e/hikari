#include "WindowsWallpaper.hpp"
#include <windows.h>

namespace WindowsWallpaper {

    bool SetWallpaper(const std::wstring& path) {
        return SystemParametersInfoW(
            SPI_SETDESKWALLPAPER,
            0,
            (PVOID)path.c_str(),
            SPIF_UPDATEINIFILE | SPIF_SENDCHANGE
        );
    }

}