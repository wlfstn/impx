#include <bit>
#include <array>
#include <cstddef>
#include <type_traits>
#include <chrono>
	
////////////////////////////////
// [DATA ALIASES]
////////////////////////////////

using byte = unsigned char;

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using i8 = signed char;
using i16 = signed short;
using i32 = signed int;
using i64 = signed long long;

using f32 = float;
using f64 = double;

////////////////////////////////
// [GENERAL TEMPLATES]
////////////////////////////////

// [EXAMPLE]			-- were::as<T>(V)
// [DESCRIPTION] 	-- static_cast alias at compile time
template <typename ToType, typename From>
[[nodiscard]] constexpr ToType as(From&& value) noexcept {
	return static_cast<ToType>(value);
}

// [EXAMPLE]			-- were::raw<T>(V)
// [DESCRIPTION]	-- reinterpret_cast alias at compile time
template <typename ToType, typename From>
[[nodiscard]] constexpr ToType raw(From&& value) noexcept {
	return reinterpret_cast<ToType>(value);
}

// [EXAMPLE]			-- were::asBytes(V); || std::array<were::bytes, n>
// [DESCRIPTION]	-- Convert data into an array of bytes
template <typename T>
[[nodiscard]] constexpr auto asBytes(const T& value) noexcept -> std::array<byte, sizeof(T)> {
	static_assert(std::is_trivially_copyable_v<T>, "to_bytes requires a trivially copyable type");
	union {
		T input;
		std::array<byte, sizeof(T)> output;
	} u = { value };
	return u.output;
}

// [EXAMPLE]			-- were::bigEndianSwap(V) 
// [DESCRIPTION]	-- Convert endian order (only on little endian devices)
template <typename T>
constexpr T bigEndianSwap(T value) {
	return std::endian::native == std::endian::little
	? std::byteswap(value)
	: value;
}