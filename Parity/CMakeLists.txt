add_executable(Parity parity-main.cppm)
# add_executable(Parity geography.cppm)
target_sources(Parity PRIVATE diceroll.cppm biology.cppm overworld.cppm fortuneboard.cppm parity.cppm geography.cppm parity-main.cppm)