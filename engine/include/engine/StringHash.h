#pragma once
#include <functional>
#include <string_view>

struct StringHash
{
    using is_transparent = void;  // Enable heterogeneous lookup
    
    [[nodiscard]] size_t operator()(const std::string_view sv) const noexcept {
        return std::hash<std::string_view>{}(sv);
    }
};