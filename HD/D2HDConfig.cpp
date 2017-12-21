/****************************************************************************
*                                                                           *
*   D2HDConfig.cpp                                                          *
*   Copyright (C) 2017 Mir Drualga                                          *
*                                                                           *
*   Licensed under the Apache License, Version 2.0 (the "License");         *
*   you may not use this file except in compliance with the License.        *
*   You may obtain a copy of the License at                                 *
*                                                                           *
*   http://www.apache.org/licenses/LICENSE-2.0                              *
*                                                                           *
*   Unless required by applicable law or agreed to in writing, software     *
*   distributed under the License is distributed on an "AS IS" BASIS,       *
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*
*   See the License for the specific language governing permissions and     *
*   limitations under the License.                                          *
*                                                                           *
*---------------------------------------------------------------------------*
*                                                                           *
*   Defines the functions that read and write to a configuration file.      *
*   By default, this file is D2HD.ini.                                      *
*                                                                           *
*   This file can be modified to add more configuration options.            *
*                                                                           *
*****************************************************************************/

#include "D2HDConfig.h"
#include "D2HDColor.h"

std::string Config::archiveName;
std::string Config::configPath = "./D2HD.ini";

DWORD ReadColor(std::string sectionName, std::string keyName, DWORD defaultColor);

void Config::ReadConfig() {
    ReadMainSettings();
    ReadExperimentalSettings();
}

void Config::ReadMainSettings() {
    const std::string sectionName = "Settings";

#if USE_CUSTOM_MPQ_FILE
    char tempArchiveName[MAX_PATH] = { '\0' };
    GetPrivateProfileStringA(sectionName.c_str(), "MPQ Name", nullptr, tempArchiveName, MAX_PATH, configPath.c_str());
    archiveName = std::string(tempArchiveName);

    if (archiveName == "") {
        archiveName = "D2MultiRes.mpq";
        WritePrivateProfileStringA(sectionName.c_str(), "MPQ Name", archiveName.c_str(), configPath.c_str());
    }
#endif

    const DWORD defaultColor = 0xFFFFFFFF;

    DWORD rgbColor = ReadColor(sectionName, "Left Panel Background Color", defaultColor);
    LeftPanelBackgroundColor = HD::D2HDColor::createFromRGBFormat(rgbColor);

    rgbColor = ReadColor(sectionName, "Left Panel Border Color", defaultColor);
    LeftPanelBorderColor = HD::D2HDColor::createFromRGBFormat(rgbColor);

    rgbColor = ReadColor(sectionName, "Right Panel Border Color", defaultColor);
    RightPanelBorderColor = HD::D2HDColor::createFromRGBFormat(rgbColor);

    rgbColor = ReadColor(sectionName, "Right Panel Background Color", defaultColor);
    RightPanelBackgroundColor = HD::D2HDColor::createFromRGBFormat(rgbColor);

    EnableD2MRPanelBorderStyle = GetPrivateProfileIntA(sectionName.c_str(), "Enable D2MR Border Panel Style", true, configPath.c_str());
    if (EnableD2MRPanelBorderStyle == true) {
        WritePrivateProfileStringA(sectionName.c_str(), "Enable D2MR Border Panel Style", "1", configPath.c_str());
    }

    InvertD2MRControlPanel = GetPrivateProfileIntA(sectionName.c_str(), "Invert D2MR Bottom Control Panel", true, configPath.c_str());
    if (InvertD2MRControlPanel == true) {
        WritePrivateProfileStringA(sectionName.c_str(), "Invert D2MR Bottom Control Panel", "1", configPath.c_str());
    }

    EnableD2MRBackgroundRibbon = GetPrivateProfileIntA(sectionName.c_str(), "Enable D2MR Panel Background Ribbon", true, configPath.c_str());
    if (EnableD2MRBackgroundRibbon == true) {
        WritePrivateProfileStringA(sectionName.c_str(), "Enable D2MR Panel Background Ribbon", "1", configPath.c_str());
    }

    Enable800ControlPanel = GetPrivateProfileIntA(sectionName.c_str(), "Enable 800x600 Style Control Panel", true, configPath.c_str());
    if (Enable800ControlPanel == true) {
        WritePrivateProfileStringA(sectionName.c_str(), "Enable 800x600 Style Control Panel", "1", configPath.c_str());
    }

    int registryResolution = GetPrivateProfileIntA(sectionName.c_str(), "Resolution", 0, configPath.c_str());
    if (registryResolution == 0 || registryResolution < 0 || registryResolution > NUMBER_OF_CUSTOM_RESOLUTIONS) {
        WritePrivateProfileStringA(sectionName.c_str(), "Resolution", "0", configPath.c_str());
    }

    CustomWidth = GetPrivateProfileIntA(sectionName.c_str(), "Custom Width (can't be larger than 1344)", 1068, configPath.c_str());
    if (CustomWidth == 1068) {
        WritePrivateProfileStringA(sectionName.c_str(), "Custom Width (can't be larger than 1344)", "1068", configPath.c_str());
    } else if (CustomWidth >= 1344 || CustomWidth < 320) {
        CustomWidth = 1344;
    }

    CustomHeight = GetPrivateProfileIntA(sectionName.c_str(), "Custom Height (can't be larger than 700)", 600, configPath.c_str());
    if (CustomHeight == 600) {
        WritePrivateProfileStringA(sectionName.c_str(), "Custom Height (can't be larger than 700)", "600", configPath.c_str());
    } else if (CustomHeight >= 700 || CustomHeight < 240) {
        CustomHeight = 700;
    }
}

void Config::ReadExperimentalSettings() {
    std::string sectionName = "Experimental";
}

void __stdcall Config::WriteRegistryResolution(int mode) {
    const std::string sectionName = "Settings";
    WritePrivateProfileStringA(sectionName.c_str(), "Resolution", std::to_string(mode).c_str(), configPath.c_str());
}

void __stdcall Config::ReadRegistryResolution(int* mode) {
    const std::string sectionName = "Settings";
    *mode = GetPrivateProfileIntA(sectionName.c_str(), "Resolution", 0, configPath.c_str());
}

DWORD ReadColor(std::string sectionName, std::string keyName, DWORD defaultColor) {
    DWORD color = GetPrivateProfileIntA(sectionName.c_str(), keyName.c_str(), defaultColor, Config::configPath.c_str());
    if (color == defaultColor) {
        std::stringstream stream;
        stream << "0x" << std::hex << defaultColor;
        std::string defaultColorStr = stream.str();
        WritePrivateProfileStringA(sectionName.c_str(), keyName.c_str(), defaultColorStr.c_str(), Config::configPath.c_str());
    }

    return color;
}
