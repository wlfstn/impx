#include <iostream>
#include <string>
#include <vector>
#include <cctype> // for std::isdigit
#include <algorithm> // for std::all_of
#include <optional>

#include "./vendor/werelib.hpp"

using namespace were;

std::optional<int> parseFeetInches(const std::string& s) {
	auto pos = s.find('f');
	if (pos == std::string::npos) return std::nullopt; // no 'f' found
	if (pos == 0 || pos == s.size() - 1) return std::nullopt;

	std::string feet_str   = s.substr(0, pos);
	std::string inches_str = s.substr(pos + 1);

	if (!std::all_of(feet_str.begin(), feet_str.end(),
		[](byte c){ return std::isdigit(c); }))
	return std::nullopt;

  if (!std::all_of(inches_str.begin(), inches_str.end(),
		[](byte c){ return std::isdigit(c); }))
	return std::nullopt;

	int feet   = std::stoi(feet_str);
	int inches = std::stoi(inches_str);
	return feet * 12 + inches;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args(argv, argv + argc);

	for (const auto& arg : args) {
		if (auto totalInches = parseFeetInches(arg)) {
			std::cout << arg << " = " << *totalInches << " inches\n";
		}
	}

	u64 inches = 0;
}