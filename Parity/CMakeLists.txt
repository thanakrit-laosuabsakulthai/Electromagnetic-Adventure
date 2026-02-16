add_executable(Parity parity-main.cppm)
# add_executable(Parity geography.cppm)
# add_executable(Parity announcement.cppm)
target_sources(Parity PRIVATE announcement.cppm biology.cppm diceroll.cppm embark.cppm expedition.cppm fortuneboard.cppm geography.cppm  notation.cppm overworld.cppm parity.cppm physiology.cppm)

