module;

#include "Vite/Base/Bridges/WinAPI.h"

/// Definitions
#ifndef HID_USAGE_GENERIC_MOUSE
    #define HID_USAGE_GENERIC_MOUSE ((USHORT) 0x02)
#endif
#ifndef HID_USAGE_PAGE_GENERIC
    #define HID_USAGE_PAGE_GENERIC  ((USHORT) 0x01)
#endif

module Vite.Platform.WinEvent;

import Vite.Event;
import Vite.Platform.WinWindow;

namespace Hedron {

/// Default
WinEventHandler::WinEventHandler(void *window) {
    mWindowHandle = reinterpret_cast<HWND>(window);

    mRawInputDevice[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
    mRawInputDevice[0].usUsage = HID_USAGE_GENERIC_MOUSE;
    mRawInputDevice[0].dwFlags = RIDEV_INPUTSINK;
    mRawInputDevice[0].hwndTarget = mWindowHandle;
    RegisterRawInputDevices(mRawInputDevice, 1, sizeof(mRawInputDevice[0]));
}

WinEventHandler::~WinEventHandler() {
    RegisterRawInputDevices(mRawInputDevice, 1, sizeof(mRawInputDevice[0]));
    mWindowHandle = nullptr;
}


/// Events
bool WinEventHandler::Callback(void *event) {
    MSG &message = *reinterpret_cast<MSG *>(event);
    return Dispatch(message);
}

void WinEventHandler::Update() {
    MSG message {};
    while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}


/// Methods
bool WinEventHandler::Dispatch(MSG message) {
	// Properties
    HWND &hWnd = message.hwnd;
    UINT &uMsg = message.message;
    WPARAM &wParam = message.wParam;
    LPARAM &lParam = message.lParam;

    ///
	/// Do the magic
	/// Sources:
	/// - Raw Input:        https://docs.microsoft.com/en-us/windows/win32/inputdev/raw-input-notifications
	/// - Keyboard Input:	https://docs.microsoft.com/en-us/windows/win32/inputdev/keyboard-input-notifications
	/// - Mouse Input:		https://docs.microsoft.com/en-us/windows/win32/inputdev/mouse-input-notifications
    /// - Touch Input:		?
    ///
	switch (uMsg) {
		///
		/// App
        ///

        /// Raw (must be requested by HighPrecision flag)
        case WM_INPUT: {
            if (mRawInputDevice[0].hwndTarget != hWnd) break;

            UINT dwSize = 40;
            static BYTE lpb[40];
            auto rawInputData = GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
            auto *raw = reinterpret_cast<RAWINPUT *>(lpb);

            switch (raw->header.dwType) {
                case RIM_TYPEMOUSE: {
                    //MouseEvent event;
                    //event.Action = MouseAction::Raw;

                    //Publish(event);
                    break;
                }

                case RIM_TYPEKEYBOARD: {
                    //KeyboardEvent event;
                    //event.Action = KeyAction::Raw;

                    //Publish(event);
                    break;
                }
                
                default: {
                    break;
                }
            }
            
            break;
        }
		
        /// Window
        // @note: These serve only for notification purposes, the windows handle the events on their own.
        
        /// Actions
        case WM_CREATE: {
            WindowEvent event;
            event.Action = WindowAction::Create;
            
            Publish(event);
            return false;
        }
        case WM_DESTROY: {
            WindowEvent event;
            event.Action = WindowAction::Destroy;
            
            Publish(event);
            return false;
        }
        case WM_MOVE: {
            WindowEvent event;
            event.Action = WindowAction::Move;

            auto x = static_cast<float>(GET_X_LPARAM(lParam));
            auto y = static_cast<float>(GET_Y_LPARAM(lParam));

            static float lastX = 0.0f;
            static float lastY = 0.0f;

            event.DeltaPosition = { x - lastX, y - lastY };
            event.LastPosition = { lastX, lastY };

            lastX = x;
            lastY = y;

            event.Position = { x, y };
            
            Publish(event);
            return false;
        }
        case WM_PAINT: {
            WindowEvent event;
            event.Action = WindowAction::Draw;

            Publish(event);
            return false;
        }
        case WM_SIZE: {
            WindowEvent event;
            switch (wParam) {
            	case SIZE_MAXIMIZED:    { event.Action = WindowAction::Maximize;    break; }
            	case SIZE_MINIMIZED:    { event.Action = WindowAction::Minimize;    break; }
                case SIZE_RESTORED:     { event.Action = WindowAction::Resize;      break; }
            }
            
            auto width = static_cast<float>(LOWORD(lParam));
            auto height = static_cast<float>(HIWORD(lParam));

            static float lastWidth = 0.0f;
            static float lastHeight = 0.0f;

            event.DeltaSize = { width - lastWidth, height - lastHeight };
            event.LastSize = { lastWidth, lastHeight };

            lastWidth = width;
            lastHeight = height;

            event.Size = { width, height };

            Publish(event);
            return false;
        }

        /// States
        case WM_ACTIVATE: {
            WindowEvent event;
            event.Action = (bool)wParam ? WindowAction::Activate : WindowAction::Deactivate;

            Publish(event);
            return false;
        }
        case WM_DPICHANGED: {
            WindowEvent event;
            event.Action = WindowAction::DpiUpdate;
            event.DpiValue = static_cast<float>(GetDpiForWindow(hWnd));

            Publish(event);
            return false;
        }
        case WM_KILLFOCUS: {
            WindowEvent event;
            event.Action = WindowAction::Defocus;

            Publish(event);
            return false;
        }
        case WM_SETFOCUS: {
            WindowEvent event;
            event.Action = WindowAction::Focus;

            Publish(event);
            return false;
        }
        case WM_SHOWWINDOW: {
            WindowEvent event;
            event.Action = (bool)wParam ? WindowAction::Show : WindowAction::Hide;

            Publish(event);
            return false;
        }
        case WM_SYSCOMMAND: {
            switch (wParam) {
                // Devices
                case SC_MONITORPOWER: {
                    //DeviceEvent event;
                    //event.Action = DeviceAction::Null;
                    //Emitter.publish(event);
                    break;
                }

                // Power
                case SC_SCREENSAVE: {
                    //PowerEventevent event;
                    //event.Action = PowerAction::Null;
                    //Emitter.publish(event);
                    break;
                }

                // Default
                default: {
                    break;
                }
            }
            return false;
        }

        ///
        /// Keyboard
        ///
		
        /// Character Input
		case WM_CHAR:       [[fallthrough]];
        case WM_SYSCHAR:    [[fallthrough]];
        case WM_UNICHAR: {
            KeyboardEvent event;
            event.Action = KeyAction::Input;

            event.Character = static_cast<wchar_t>(wParam);

            char utf8Character[5] = { 0 };
            int length = WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<LPCWCH>(&wParam), 1, utf8Character, sizeof(utf8Character), nullptr, nullptr);

            if (length > 0) {
                event.Utf8Character = std::string(utf8Character, length);
            }
        
            Publish(event);
            return true;
		}
        
        /// Key
		case WM_KEYDOWN:    [[fallthrough]];
		case WM_KEYUP:      [[fallthrough]];
        case WM_SYSKEYUP:   [[fallthrough]];
        case WM_SYSKEYDOWN: {
			KeyboardEvent event;
            event.Action = KeyAction::Raw;

            auto code = LOWORD(wParam);
            auto flags = HIWORD(lParam);
            auto scanCode = static_cast<WORD>(LOBYTE(flags));
            auto extended = static_cast<bool>((flags & KF_EXTENDED) == KF_EXTENDED);
            auto repeat = static_cast<bool>((flags & KF_REPEAT) == KF_REPEAT);
            auto release = static_cast<bool>((flags & KF_UP) == KF_UP);

            if (extended) MAKEWORD(scanCode, 0xE0);
            if (code) {
                switch (wParam) {
                    case VK_CONTROL: [[fallthrough]];
                    case VK_SHIFT:   [[fallthrough]];
                    case VK_MENU: {
                        code = LOWORD(MapVirtualKey(scanCode, MAPVK_VSC_TO_VK_EX));
                    }
                }
            }

            event.Key = static_cast<KeyCode>(code);
            event.Repeats = static_cast<uint16>(LOWORD(lParam));
            
            if (release) event.State = KeyState::Release;
            else if (repeat) event.State = KeyState::Repeat;
            else event.State = KeyState::Press;

            event.Modifiers = GetModifiers();

			// Finalization
            Publish(event);
            return true;
		}
		
        ///
		/// Mouse
        ///
        
        /// Double Click
		case WM_LBUTTONDBLCLK:  [[fallthrough]];
        case WM_MBUTTONDBLCLK:  [[fallthrough]];
        case WM_RBUTTONDBLCLK:  [[fallthrough]];
        case WM_XBUTTONDBLCLK: {
			MouseEvent event;
			event.Action = MouseAction::DoubleClick;
            event.State = MouseButtonState::Press;

			// Get MouseButton
			switch (uMsg) {
				case WM_LBUTTONDBLCLK: {
					event.Button = MouseButton::Left;
					break;
				}
				case WM_MBUTTONDBLCLK: {
					event.Button = MouseButton::Middle;
					break;
				}
				case WM_RBUTTONDBLCLK: {
					event.Button = MouseButton::Right;
					break;
				}
				case WM_XBUTTONDBLCLK: {
					short button = GET_XBUTTON_WPARAM(wParam);
					event.Button = (button == XBUTTON1 ? MouseButton::Extra1 : MouseButton::Extra2);
					break;
				}
				default: {
					break;
				}
			}

            event.Modifiers = GetModifiers();

            Publish(event);
            return true;
		}

        /// Click
		case WM_LBUTTONDOWN:    [[fallthrough]];
        case WM_MBUTTONDOWN:    [[fallthrough]];
        case WM_RBUTTONDOWN:    [[fallthrough]];
        case WM_XBUTTONDOWN:    [[fallthrough]];
		case WM_LBUTTONUP:  [[fallthrough]];
        case WM_MBUTTONUP:  [[fallthrough]];
        case WM_RBUTTONUP:  [[fallthrough]];
        case WM_XBUTTONUP: {
			MouseEvent event;
			event.Action = MouseAction::Click;

			// Get MouseButton
			switch (uMsg) {
				case WM_LBUTTONDOWN:	case WM_LBUTTONUP: {
					event.Button = MouseButton::Left;
					event.State = (uMsg == WM_LBUTTONDOWN ? MouseButtonState::Press : MouseButtonState::Release);

					break;
				}
				case WM_MBUTTONDOWN:	case WM_MBUTTONUP: {
					event.Button = MouseButton::Middle;
					event.State = (uMsg == WM_MBUTTONDOWN ? MouseButtonState::Press : MouseButtonState::Release);
					break;
				}
				case WM_RBUTTONDOWN:	case WM_RBUTTONUP: {
					event.Button = MouseButton::Right;
					event.State = (uMsg == WM_RBUTTONDOWN ? MouseButtonState::Press : MouseButtonState::Release);
					break;
				}
				case WM_XBUTTONDOWN:	case WM_XBUTTONUP: {
					short button = GET_XBUTTON_WPARAM(wParam);
					event.Button = (button & XBUTTON1 ? MouseButton::Extra1 : MouseButton::Extra2);
					event.State = (uMsg == WM_XBUTTONDOWN ? MouseButtonState::Press : MouseButtonState::Release);
                    break;
				}
				default: {
					break;
				}
			}

            event.Modifiers = GetModifiers();

            Publish(event);
            return true;
		}

        /// Move
		case WM_MOUSEMOVE: {
            MouseEvent event;
            event.Action = MouseAction::Move;

            auto x = static_cast<float>(GET_X_LPARAM(lParam)); // static_cast<short>(LOWORD(lParam));
            auto y = static_cast<float>(GET_Y_LPARAM(lParam)); // static_cast<short>(HIWORD(lParam));

            mMouseLastPosition = mMousePosition;
            mMousePosition = { x, y };
            mMouseDeltaPosition = { mMousePosition.X - mMouseLastPosition.X, mMousePosition.Y - mMouseLastPosition.Y };

            event.LastPosition = mMouseLastPosition;
            event.Position = mMousePosition;
            event.DeltaPosition = mMouseDeltaPosition;

			switch (wParam) {
				case MK_LBUTTON: {
					event.Button = MouseButton::Left;
                    break;
				}
				case MK_MBUTTON: {
					event.Button = MouseButton::Middle;
                    break;
				}
				case MK_RBUTTON: {
					event.Button = MouseButton::Right;
                    break;
				}
				case MK_XBUTTON1: {
					event.Button = MouseButton::Extra1;
                    break;
				}
				case MK_XBUTTON2: {
					event.Button = MouseButton::Extra2;
                    break;
				}
				default: {
					event.Button = MouseButton::Undefined;
                    break;
				}
			}

            Publish(event);
            return true;

			// Capture the mouse in case the user wants to drag it outside
			// Get the client area of the window
			//RECT area;
			//GetClientRect(msg.hwnd, &area);

			//event.X = static_cast<unsigned int>(area.left <= x && x <= area.right ? x - area.left : 0xFFFFFFFF);
			//event.Y = static_cast<unsigned int>(area.top <= y && y <= area.bottom ? y - area.top : 0xFFFFFFFF);
			//event.ScreenX = static_cast<unsigned int>(x);
			//event.ScreenY = static_cast<unsigned int>(y);
			//event.DeltaX = static_cast<int>(x - pWindow->prevMouseX);
			//event.DeltaY = static_cast<int>(y - pWindow->prevMouseY);
			//pWindow->prevMouseX = static_cast<unsigned int>(x);
			//pWindow->prevMouseY = static_cast<unsigned int>(y);

			/*
			// Capture the mouse in case the user wants to drag it outside
			if ((msg.wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 | MK_XBUTTON2)) == 0) {
			// Only release the capture if we really have it
			if (GetCapture() == hwnd)
			ReleaseCapture();
			}
			else if (GetCapture() != hwnd)
			{
			// Set the capture to continue receiving mouse events
			SetCapture(hwnd);
			}

			// If the cursor is outside the client area...
			if ((x < area.left) || (x > area.right) || (y < area.top) || (y > area.bottom)) {
			// and it used to be inside, the mouse left it.
			if (m_mouseInside) {
			m_mouseInside = false;

			// No longer care for the mouse leaving the window
			setTracking(false);

			// Generate a MouseLeft event
			Event event;
			event.type = Event::MouseLeft;
			pushEvent(event);
			}
			} else {
			// and vice-versa
			if (!m_mouseInside) {
			m_mouseInside = true;

			// Look for the mouse leaving the window
			setTracking(true);

			// Generate a MouseEntered event
			Event event;
			event.type = Event::MouseEntered;
			pushEvent(event);
			}
            break;
			}*/
		}
        case WM_MOUSELEAVE: {
            MouseEvent event;
            //event.Action = MouseAction::Leave;

            Publish(event);
            return true;
        }

        /// Wheel
		case WM_MOUSEWHEEL: {
			MouseEvent event;
			event.Action = MouseAction::Wheel;

            auto deltaWheelY = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);

            mMouseLastDeltaWheel = mMouseDeltaWheel;
            mMouseDeltaWheel = { 0.0f, deltaWheelY };

            event.DeltaWheel = mMouseDeltaWheel;

            event.Modifiers = GetModifiers();

            Publish(event);
            return true;
		}
		case WM_MOUSEHWHEEL: {
			MouseEvent event;
			event.Action = MouseAction::Wheel;

            auto deltaWheelX = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);

            mMouseLastDeltaWheel = mMouseDeltaWheel;
            mMouseDeltaWheel = { deltaWheelX, 0.0f };

            event.DeltaWheel = mMouseDeltaWheel;

            event.Modifiers = GetModifiers();

            Publish(event);
            return true;
		}

        ///
        /// Touch
        ///
		case WM_TOUCH: {
            TouchEvent event;
            
            Publish(event);
            return false;
		}

        ///
        /// Default
        ///
        /// Nothing of interest
		default: {
            break;
		}
	}

    return false;
}

KeyModifier WinEventHandler::GetModifiers() {
    KeyModifier result = KeyModifier::None;

    if ((bool)::GetAsyncKeyState(VK_MENU)) result |= KeyModifier::Alt;
    if ((bool)::GetAsyncKeyState(VK_CONTROL)) result |= KeyModifier::Control;
    if ((bool)::GetAsyncKeyState(VK_SHIFT)) result |= KeyModifier::Shift;
    if ((bool)::GetAsyncKeyState(VK_LWIN) || (bool)::GetAsyncKeyState(VK_RWIN)) result |= KeyModifier::Super;

    return result;
}

}
