#pragma once
#include "registry.hxx"

template <typename T> struct AutoRegister {
  AutoRegister() { CommandRegistry::instance().add(std::make_unique<T>()); }
};
