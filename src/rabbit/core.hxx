#pragma once

#include <dpp/dpp.h>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <rabbit/commands/system/registry.hxx>
#include <rabbit/commands/system/metadata.hxx>
#include <rabbit/commands/system/auto_register.hxx>
#include <rabbit/commands/system/tbase.hxx>
