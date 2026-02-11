add_executable(Parity parity-main.cppm)
target_sources(Parity PRIVATE diceroll.cppm biology.cppm overworld.cppm fortuneboard.cppm parity.cppm)