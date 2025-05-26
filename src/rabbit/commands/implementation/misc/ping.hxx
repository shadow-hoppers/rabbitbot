#pragma once

#include <rabbit/core.hxx>

class PingCommand : public TemplatedCommand<PingCommand> {
public:
    COMMAND_METADATA("ping", "Misc", "Replies with pong.");

    void handle(const dpp::slashcommand_t& event);

private:
    static inline AutoRegister<PingCommand> _auto_reg;
};
