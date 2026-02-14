add_executable(Parity parity-main.cppm)
# add_executable(Parity geography.cppm)
target_sources(Parity PRIVATE  biology.cppm diceroll.cppm  fortuneboard.cppm geography.cppm  notation.cppm overworld.cppm parity.cppm)