#pragma once

#include <optional>
#include <cctype> // for std::isdigit
#include <algorithm> // for std::all_of
#include <string>

std::optional<int> parseFeetInches(const std::string& s);