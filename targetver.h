#pragma once

// SDKDDKVer.h를 포함하면 최고 수준의 가용성을 가진 Windows 플랫폼이 정의됩니다.

// 이전 Windows 플랫폼에 대해 애플리케이션을 빌드하려는 경우에는 SDKDDKVer.h를 포함하기 전에
// WinSDKVer.h를 포함하고 _WIN32_WINNT 매크로를 지원하려는 플랫폼으로 설정하십시오.

// Windows XP 지원을 위한 플랫폼 버전 설정
//#include <WinSDKVer.h>

// Windows XP = 0x0501
// Windows XP SP2 / Server 2003 = 0x0502
//#define _WIN32_WINNT  0x0501
//#define WINVER        0x0501
//#define _WIN32_IE     0x0600   // IE 6.0 (XP 기본)
//#define NTDDI_VERSION NTDDI_WINXP

#include <SDKDDKVer.h>
