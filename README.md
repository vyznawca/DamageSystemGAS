# DamageSystemGAS
Simple damage system based on the GAS Plugin in Unreal Engine 5.7.4, with a few damage and resistance types.



Info

- Weapons have different damage and heal values
- Ammo has different properties
- Fire ammo can apply Fire DOT effect only if target has no fire resistance at all. 
Fire Ammo can still deal damage if resistance is smaller than fire damage per bullet
- Fire DOT is dealing 1 damage as base per tick (1 per second)
- Water ammo is not dealing any damage, just puts out the fire
- Resistance can be negative - then given ammo deals more damage
- Resistance bigger than 0 stops special effects of ammo like setting up fire or putting it down

