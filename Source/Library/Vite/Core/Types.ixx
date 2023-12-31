export module Vite.Core.Types;

export import std;

export namespace Vite {

// Container
using std::array;
using std::list;
using std::string;
using std::string_view;
using std::vector;
using std::wstring;
using std::wstring_view;

// Smart-Pointer
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;

// Types
using empty = std::monostate;
using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;
using intptr = std::intptr_t;
using size = std::size_t;
using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;
using uintptr = std::uintptr_t;

}
