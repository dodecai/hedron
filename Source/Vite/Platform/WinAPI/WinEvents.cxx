module;

#define NOMINMAX
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WindowsX.h>

module Vite.Platform.WinEvent;

import Vite.Device.Input;
import Vite.Event;
import Vite.Platform.WinWindow;

namespace {

/// Properties
RAWINPUTDEVICE RawInputDevice[1];

#ifndef HID_USAGE_GENERIC_MOUSE
    #define HID_USAGE_GENERIC_MOUSE ((USHORT) 0x02)
#endif
#ifndef HID_USAGE_PAGE_GENERIC
    #define HID_USAGE_PAGE_GENERIC  ((USHORT) 0x01)
#endif

}

namespace Hedron {

WinEventHandler::WinEventHandler() {
}

//// Events
bool WinEventHandler::Callback(void *event) {
    MSG &message = *reinterpret_cast<MSG *>(event);
    return Dispatch(message) ? false : true;
}

void WinEventHandler::Update() {
    MSG message {};
    while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}

bool WinEventHandler::Dispatch(MSG message) {
	// Properties
    HWND &hWnd = message.hwnd;
    UINT &uMsg = message.message;
    WPARAM &wParam = message.wParam;
    LPARAM &lParam = message.lParam;
    bool result { false };

    // ToDo: Move to Constructor
    static auto once = true;
    if (once) {
        RawInputDevice[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
        RawInputDevice[0].usUsage = HID_USAGE_GENERIC_MOUSE;
        RawInputDevice[0].dwFlags = RIDEV_INPUTSINK;
        RawInputDevice[0].hwndTarget = hWnd;
        RegisterRawInputDevices(RawInputDevice, 1, sizeof(RawInputDevice[0]));
        once = false;
    }

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

        // Raw (must be requested by HighPrecision flag)
        case WM_INPUT: {
            //if (MouseEvent.Empty()) break; // || KeyboardEvent.Empty()
            break;
            //static int32_t lastX = 0;
            //static int32_t lastY = 0;

            //MouseEventevent event;
            //event.Action = MouseAction::Raw;
            //event.LastX = lastX;
            //event.LastY = lastY;
            //UINT dwSize = 40;
            //static BYTE lpb[40];

            //// Get event
            //uint32_t lr = GetRawInputevent((HRAWINPUT)msg.lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
            //if (lr != dwSize) OutputDebugString(TEXT("GetRawInputevent does not return correct size !\n"));
            //RAWINPUT *raw = (RAWINPUT *)lpb;

            //// Extract raw event
            //switch (raw->header.dwType) {
            //	case RIM_TYPEKEYBOARD: {
            //		break;
            //	}
            //	case RIM_TYPEMOUSE: {
            //		event.X = raw->event.mouse.lLastX;
            //		event.Y = raw->event.mouse.lLastY;
            //		break;
            //	}
            //}
            //event.DeltaX = event.X - event.LastX;
            //event.DeltaY = event.Y - event.LastY;
            //lastX = event.X;
            //lastY = event.Y;

            //// Finalization
            //MouseEvent.Publish(event);
            break;
        }
		
		// State
		case WM_ACTIVATE: {
            WindowEvent event;
            //event.Action = WindowAction::Activate;
            //event.Active = (bool)msg.wParam;;
            
            Publish(event);
			break;
		}
		case WM_KILLFOCUS: {
            WindowEvent event;
            //event.Action = WindowAction::Focus;
            //event.Focus = false;
            
            Publish(event);
			break;
		}
		case WM_SETFOCUS: {
            WindowEvent event;
            //event.Action = WindowAction::Focus;
            //event.Focus = true;
            
            Publish(event);
			break;
		}

		// System
		case WM_DPICHANGED: {
            // ToDo: Something like DPI event would be nice.
            WindowEvent event;
            //event.Action = WindowAction::DpiUpdate;
            
            Publish(event);
			break;
		}
		case WM_SYSCOMMAND: {
            switch (wParam) {
            	// Devices
            	case SC_MONITORPOWER: {
                    //DeviceEventevent event;
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
			break;
		}

        // Window
        // @note: They serve only for notification purposes, the windows handle the events on their own.
        case WM_CREATE: {
            WindowEvent event;
            //event.Action = WindowAction::Create;
            
            Publish(event);
            break;
        }
        case WM_DESTROY: {
            WindowEvent event;
            //event.Action = WindowAction::Destroy;
            
            Publish(event);
            break;
        }
        case WM_PAINT: {
            WindowEvent event;
            //event.Action = WindowAction::Draw;
             
            Publish(event);
            break;
        }
        case WM_SHOWWINDOW: {
            WindowEvent event;
            //event.Action = WindowAction::Show;
            //event.Visible = (bool)msg.wParam;

            Publish(event);
            break;
        }
        case WM_SIZING: {
            WindowEvent event;
            //event.Action = WindowAction::Resize;
            //PRECT pWindowDimension = reinterpret_cast<PRECT>(msg.lParam);
            //event.X = pWindowDimension->left;
            //event.Y = pWindowDimension->top;
            //event.Width = pWindowDimension->right - pWindowDimension->left;
            //event.Height = pWindowDimension->bottom - pWindowDimension->top;
            
            Publish(event);
            break;
        }
        case WM_MOVE: {
            WindowEvent event;
            //event.Action = WindowAction::Move;
            //event.X = GET_X_LPARAM(msg.lParam);
            //event.Y = GET_Y_LPARAM(msg.lParam);
            
            Publish(event);
            break;
        }
        case WM_SIZE: {
            WindowEvent event;
            //event.Action = WindowAction::Show;
            //
            //switch (msg.wParam) {
            //	case SIZE_MAXIMIZED: {
            //		event.Action = WindowAction::Maximize;
            //		break;
            //	}
            //	case SIZE_MINIMIZED: {
            //		event.Action = WindowAction::Minimize;
            //		break;
            //	}
            //	case SIZE_RESTORED: {
            //		event.Action = WindowAction::Restore;
            //	}
            //}
            //event.Width = static_cast<uint32_t>((UINT64)msg.lParam & 0xFFFF);
            //event.Height = static_cast<uint32_t>((UINT64)msg.lParam >> 16);

            Publish(event);
            break;
        }

        ///
        /// Keyboard
        ///
		
        // Character Input
		case WM_CHAR:       [[fallthrough]];
        case WM_SYSCHAR:    [[fallthrough]];
        case WM_UNICHAR: {
            //// Preparation
            KeyboardEvent event;
            //event.Action = KeyboardAction::Input;
            //event.State = KeyState::Undefined;
            //event.Character = (char)msg.wParam;
            //event.Key = KeyCode{ (KeyCode)msg.wParam };
                        
            Publish(event);
            result = true;
			break;
		}
        
        // Key
		case WM_KEYDOWN:    [[fallthrough]];
		case WM_KEYUP:      [[fallthrough]];
        case WM_SYSKEYUP:   [[fallthrough]];
        case WM_SYSKEYDOWN: {
			// Preparation
			KeyboardEvent event;

			// Get Key Code
            event.Key = KeyCode{ static_cast<KeyCode>(wParam) };
			if (HIWORD(lParam) & KF_EXTENDED) {
				switch (wParam) {
					case VK_CONTROL:	{ event.Key = KeyCode::RControl;    break; }
					case VK_SHIFT:		{ event.Key = KeyCode::RShift;	    break; }
					case VK_MENU:		{ event.Key = KeyCode::RAlt;		break; }
					case VK_RETURN:		{ event.Key = KeyCode::Return;	    break; }
					default:			{ break; }
				}
			}

			// Get Key State
			switch (uMsg) {
				case WM_KEYDOWN:	case WM_SYSKEYDOWN: {
                    event.State = KeyState::Press;
					break;
				}
				case WM_KEYUP:		case WM_SYSKEYUP: {
                    event.State = KeyState::Release;
					break;
				}
				default: {
                    // ToDo: Add hold state
					break;
				}
			}

			// Get Modifiers
            event.Modifiers |= (bool)GetAsyncKeyState(VK_MENU) ? KeyModifier::Alt : KeyModifier::None;
            event.Modifiers |= (bool)GetAsyncKeyState(VK_CONTROL) ? KeyModifier::Control : KeyModifier::None;
            event.Modifiers |= (bool)GetAsyncKeyState(VK_SHIFT) ? KeyModifier::Shift : KeyModifier::None;
            event.Modifiers |= (bool)(GetAsyncKeyState(VK_LWIN) | GetAsyncKeyState(VK_RWIN)) ? KeyModifier::Super : KeyModifier::None;

			if (GetSystemMetrics(SM_SWAPBUTTON)) {
				// Mouse Buttons as modifiers ... yes we can :)
			}

			// Finalization
            Publish(event);
			result = true;
			break;
		}
		
        ///
		/// Mouse
        ///
        
		case WM_MOUSEACTIVATE: {
			//if (HIWORD(lParam) == WM_LBUTTONDBLCLK) {
			//	if (LOWORD(lParam) == HTCLIENT) {
			//		// Don't capture mouse on title click
			//	}
			//}
			break;
		}

        // Double Click
		case WM_LBUTTONDBLCLK:  [[fallthrough]];
        case WM_MBUTTONDBLCLK:  [[fallthrough]];
        case WM_RBUTTONDBLCLK:  [[fallthrough]];
        case WM_XBUTTONDBLCLK: {
			MouseEvent event;
			event.Action = MouseAction::DoubleClick;

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
					event.Button = (button == XBUTTON1 ? MouseButton::X1 : MouseButton::X2);
					break;
				}
				default: {
					event.Button = MouseButton::Undefined;
					break;
				}
			}

            // Get Modifiers
            event.Modifiers |= (bool)GetAsyncKeyState(VK_MENU) ? KeyModifier::Alt : KeyModifier::None;
            event.Modifiers |= (bool)GetAsyncKeyState(VK_CONTROL) ? KeyModifier::Control : KeyModifier::None;
            event.Modifiers |= (bool)GetAsyncKeyState(VK_SHIFT) ? KeyModifier::Shift : KeyModifier::None;
            event.Modifiers |= (bool)(GetAsyncKeyState(VK_LWIN) | GetAsyncKeyState(VK_RWIN)) ? KeyModifier::Super : KeyModifier::None;

			event.State = MouseButtonState::Press;

            Publish(event);
			result = true;
			break;
		}

        // Click
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
					event.Button = (button & XBUTTON1 ? MouseButton::X1 : MouseButton::X2);
					event.State = (uMsg == WM_XBUTTONDOWN ? MouseButtonState::Press : MouseButtonState::Release);
                    break;
				}
				default: {
					break;
				}
			}

            // Get Modifiers
            event.Modifiers |= (bool)GetAsyncKeyState(VK_MENU) ? KeyModifier::Alt : KeyModifier::None;
            event.Modifiers |= (bool)GetAsyncKeyState(VK_CONTROL) ? KeyModifier::Control : KeyModifier::None;
            event.Modifiers |= (bool)GetAsyncKeyState(VK_SHIFT) ? KeyModifier::Shift : KeyModifier::None;
            event.Modifiers |= (bool)(GetAsyncKeyState(VK_LWIN) | GetAsyncKeyState(VK_RWIN)) ? KeyModifier::Super : KeyModifier::None;

            Publish(event);
			result = true;
			break;
		}

        // Move
		case WM_MOUSEMOVE: {
            auto x = static_cast<float>(GET_X_LPARAM(lParam)); // static_cast<short>(LOWORD(lParam));
            auto y = static_cast<float>(GET_Y_LPARAM(lParam)); // static_cast<short>(HIWORD(lParam));
			static float lastX = 0.0f;
			static float lastY = 0.0f;

			MouseEvent event;
			event.Action = MouseAction::Move;

            event.DeltaPosition = { x - lastX, y - lastY };
            event.LastPosition = { lastX, lastY };
            event.Position = { x, y };

            lastX = x;
			lastY = y;

			// Get Modifiers
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
					event.Button = MouseButton::X1;
                    break;
				}
				case MK_XBUTTON2: {
					event.Button = MouseButton::X2;
                    break;
				}
				default: {
					event.Button = MouseButton::Undefined;
                    break;
				}
			}

            // Get Modifiers
            event.Modifiers |= (bool)GetAsyncKeyState(VK_MENU) ? KeyModifier::Alt : KeyModifier::None;
            event.Modifiers |= (bool)GetAsyncKeyState(VK_CONTROL) ? KeyModifier::Control : KeyModifier::None;
            event.Modifiers |= (bool)GetAsyncKeyState(VK_SHIFT) ? KeyModifier::Shift : KeyModifier::None;
            event.Modifiers |= (bool)(GetAsyncKeyState(VK_LWIN) | GetAsyncKeyState(VK_RWIN)) ? KeyModifier::Super : KeyModifier::None;

            Publish(event);
			result = true;
			break;
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

        // Wheel
		case WM_MOUSEWHEEL: {
			MouseEvent event;
			event.Action = MouseAction::Wheel;

            auto deltaWheelY = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
            event.DeltaWheel = { 0.0f, deltaWheelY };

            Publish(event);
			result = true;
			break;
		}
		case WM_MOUSEHWHEEL: {
			MouseEvent event;
			event.Action = MouseAction::Wheel;

            auto deltaWheelX = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
            event.DeltaWheel = { deltaWheelX, 0.0f };

            Publish(event);
			result = true;
			break;
		}

        ///
        /// Touch
        ///
		case WM_TOUCH: {
            TouchEvent event;
            
            Publish(event);
            //result = true;
			break;
		}

        /// Nothing of interest
		default: {
			break;
		}
	}

	return result;
}

}
