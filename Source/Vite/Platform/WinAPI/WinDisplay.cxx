module Vite.Platform.WinDisplay;

namespace Hedron {



#ifdef LEGACY_CODE
//const WindowSize WinWindow::GetDisplaySize() const {
//	//RECT area;
//	//GetWindowRect(WindowHandle, &area);
//	//WindowSize(area.right - area.left, area.bottom - area.top);
//	return Properties.Size;
//}

//const WindowSize WinWindow::GetScreenSize() const {
//	int32_t width = GetSystemMetrics(SM_CXSCREEN);
//	int32_t height = GetSystemMetrics(SM_CYSCREEN);
//
//	return WindowSize(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
//}

//void WinWindow::SetDisplaySize(const uint32_t width, const uint32_t height) {
//    WINDOWPLACEMENT position {};
//	GetWindowPlacement(WindowHandle, &position);
//
//	RECT dimension = {};
//	dimension.left = position.rcNormalPosition.left;
//	dimension.top = position.rcNormalPosition.top;
//	dimension.right = (long)width;
//	dimension.bottom = (long)height;
//
//	AdjustWindowRectEx(&dimension, NULL, FALSE, NULL);
//	if (!SetWindowPos(WindowHandle, 0, dimension.left, dimension.top, dimension.right, dimension.bottom, SWP_NOREPOSITION | SWP_NOZORDER)) {
//        LogError("Error occurred while setting display size!");
//		return;
//	}
//	Properties.Size.Width = width;
//	Properties.Size.Height = height;
//}
#endif

}
