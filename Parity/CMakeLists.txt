add_executable(Parity parity-main.cppm)
# add_executable(Parity geography.cppm)
# add_executable(Parity announcement.cppm)
target_sources(Parity PRIVATE
    parity.cppm
    overworld.cppm
    announcement.cppm
    
    Fortuneboard/diceroll.cppm
    Fortuneboard/fortuneboard.cppm
    Fortuneboard/luckyboard.cppm
    Fortuneboard/eventboard.cppm
    Fortuneboard/unluckyboard.cppm
    
    Divinity/physiology.cppm
    Divinity/necrology.cppm
    Divinity/biology.cppm
    Divinity/adventurer.cppm
    Divinity/forgather.cppm
    
    Cartography/geography.cppm
    Cartography/notation.cppm
    Cartography/expedition.cppm
    Cartography/embark.cppm
    Cartography/encyclopedia.cppm
    Cartography/journey.cppm
    Cartography/accoutrement.cppm
    Cartography/passagedecision.cppm
    
    Opticular/optoelectronic.cppm
    Opticular/opticalnotation.cppm
    Opticular/marketplace.cppm
    
    Chromaticity/chromaticity.cppm
    Chromaticity/coloreffect.cppm
 )