#pragma once
#include <string_view>

struct CommandMetadata {
  std::string_view name;
  std::string_view category;
  std::string_view description;
};

#define COMMAND_METADATA(NAME, CATEGORY, DESC)                                 \
  static constexpr CommandMetadata metadata{NAME, CATEGORY, DESC};
