#pragma once
#include <memory>

template<typename T>
using Ref = std::shared_ptr<T>;

constexpr int TILE_SIZE = 32;
constexpr int HALF_TILE_SIZE = TILE_SIZE / 2;

constexpr int MAP_SIZE = 100;