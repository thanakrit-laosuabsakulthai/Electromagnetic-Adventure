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
    Fortuneboard/demonboard.cppm
    
    Divinity/psychology.cppm
    Divinity/physiology.cppm
    Divinity/necrology.cppm
    Divinity/biology.cppm
    Divinity/necromancy.cppm
    Divinity/demonmancy.cppm
    
    Adventure/adventurer.cppm
    Adventure/forgather.cppm
    Adventure/adventure.cppm
    Adventure/traverser.cppm
    
    Cartography/geography.cppm
    Cartography/notation.cppm
    Cartography/expedition.cppm
    Cartography/embark.cppm
    Cartography/encyclopedia.cppm
    Cartography/journey.cppm
    Cartography/accoutrement.cppm
    Cartography/passagedecision.cppm
    Cartography/scoutfly.cppm
    Cartography/peril.cppm
    Cartography/entropy.cppm
    
    Opticular/optoelectronic.cppm
    Opticular/opticalnotation.cppm
    Opticular/marketplace.cppm
    Opticular/marketmedia.cppm
    Opticular/purchasement.cppm
    Opticular/marketeer.cppm
    Opticular/optometrist.cppm
    Opticular/consumption.cppm
    Opticular/order.cppm
    
    Chromaticity/chromaticity.cppm
    Chromaticity/coloreffect.cppm
    
    Showcase/subdivision.cppm
    Showcase/amusement.cppm
    
    Warfare/warfare.cppm
	Warfare/battlefield.cppm
	Warfare/armament.cppm
	Warfare/combat.cppm
	Warfare/simulation.cppm
 )