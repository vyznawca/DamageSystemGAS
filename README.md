# DamageSystemGAS
Simple damage system based on the GAS Plugin in Unreal Engine 5.7.4, with a few damage and resistance types.
Based on First Person Template and some code from Lyra.



Info

- Weapons have different damage and heal values
- Ammo has different properties
- Fire ammo can apply Fire DOT effect only if target has no fire resistance at all. 
Fire Ammo can still deal damage if resistance is smaller than fire damage per bullet
- Fire DOT is dealing 1 damage as base per tick (1 per second)
- Water ammo is not dealing any damage, just puts out the fire
- Resistance can be negative - then given ammo deals more damage
- Resistance bigger than 0 stops special effects of ammo like setting up fire or putting it down

I'm using execution class and additional attribute called "Damage" which holds the return value we calculated in our calculation class. Thanks to that we can easly pass params to gameplay cue and show values.
This is my effect that is dealing damage
<img width="1114" height="818" alt="image" src="https://github.com/user-attachments/assets/17b1935c-5435-41a5-b1a3-092545dd3d78" />

This is damage calculation class
<img width="1514" height="700" alt="image" src="https://github.com/user-attachments/assets/b2adfffe-c5e5-4ca8-829e-ab6f3456e139" />

And here is my base effect im aplying and the start of the game that holds info about resistances of given character. I have this kind of modifier for each of my resistances.
<img width="1043" height="373" alt="image" src="https://github.com/user-attachments/assets/796cb228-e5ac-4f00-a278-34b7d0bfcc22" />

