export module Vite.Core.Standard;

export import std;

export namespace Vite {

// Concurency
using std::atomic;
using std::condition_variable;
using std::future;
using std::mutex;
using std::thread;

// Container
using std::array;
using std::byte;
using std::function;
using std::list;
using std::map;
using std::queue;
using std::string;
using std::string_view;
using std::unordered_map;
using std::vector;
using std::wstring;
using std::wstring_view;

// Stream
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::wifstream;
using std::wofstream;

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
