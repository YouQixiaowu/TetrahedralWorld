﻿// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
#include <windows.h>
#include <atomic>
#include <thread>
#include <mutex>
#include <functional>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <tuple>
#include <string>
//
#include "glad.h"
#include "glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
//
#include "Window.h"
#endif //PCH_H
