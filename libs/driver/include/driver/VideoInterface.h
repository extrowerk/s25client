// Copyright (c) 2005 - 2017 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.
#ifndef VIDEOINTERFACE_H_INCLUDED
#define VIDEOINTERFACE_H_INCLUDED

#pragma once

#include "KeyEvent.h"
#include "Point.h"
#include "VideoMode.h"
#include "exportImport.h"
#include <string>
#include <vector>

/// Function type for loading OpenGL methods
using OpenGL_Loader_Proc = void* (*)(const char*);

class IVideoDriver
{
public:
    virtual ~IVideoDriver() = 0;

    /// Funktion zum Auslesen des Treibernamens.
    virtual const char* GetName() const = 0;

    virtual bool Initialize() = 0;

    /// Erstellt das Fenster mit entsprechenden Werten.
    virtual bool CreateScreen(const std::string& title, const VideoMode& newSize, bool fullscreen) = 0;

    virtual bool ResizeScreen(const VideoMode& newSize, bool fullscreen) = 0;

    /// Schliesst das Fenster.
    virtual void DestroyScreen() = 0;

    /// Wechselt die OpenGL-Puffer.
    virtual bool SwapBuffers() = 0;

    /// Die Nachrichtenschleife.
    virtual bool MessageLoop() = 0;

    /// Return the current tick count (time since epoch in ms)
    virtual unsigned long GetTickCount() const = 0;

    /// Funktion zum Holen einer Subfunktion.
    virtual OpenGL_Loader_Proc GetLoaderFunction() const = 0;

    virtual void ListVideoModes(std::vector<VideoMode>& video_modes) const = 0;

    /// Funktion zum Auslesen der Mauskoordinaten.
    virtual Position GetMousePos() const = 0;

    /// Funktion zum Setzen der Mauskoordinaten.
    virtual void SetMousePos(Position pos) = 0;

    /// Return true when left mouse button is pressed
    virtual bool GetMouseStateL() const = 0;
    /// Return true when right mouse button is pressed
    virtual bool GetMouseStateR() const = 0;

    /// Get the size of the window in screen coordinates
    virtual VideoMode GetWindowSize() const = 0;
    /// Get the size of the render region in pixels
    virtual Extent GetRenderSize() const = 0;
    virtual bool IsFullscreen() const = 0;

    /// Get state of the modifier keys
    virtual KeyEvent GetModKeyState() const = 0;

    /// Get pointer to window (device-dependent!), HWND unter Windows
    virtual void* GetMapPointer() const = 0;

    virtual bool IsInitialized() const = 0;
    /// Shall we support OpenGL? (Disabled for tests)
    virtual bool IsOpenGL() const = 0;
};

class VideoDriverLoaderInterface;

/// Instanzierungsfunktion der Treiber.
RTTR_DECL IVideoDriver* CreateVideoInstance(VideoDriverLoaderInterface* CallBack);
RTTR_DECL void FreeVideoInstance(IVideoDriver* driver);

#endif // !VIDEOINTERFACE_H_INCLUDED
