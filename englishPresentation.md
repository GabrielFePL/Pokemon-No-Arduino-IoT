# Insight
Two players will engage in a PvP battle in a game inspired by the Pokémon franchise. The "console" will be composed of an Arduino Uno R3, along with sensors and components.

## Game Mechanics
- **Players** will have a predefined team of 6 Pokémon, each belonging to one of the following types: Fighting, Fire, Water, Ghost, Psychic, and Normal. 
- **Objective:** Players take turns battling until one player reduces all the opponent's Pokémon's lives to 0 or less.
- **Active Pokémon:** Each player has one active Pokémon that can attack or be attacked.
- **Moves:** All Pokémon can use 6 moves of the mentioned types to damage the opponent's active Pokémon.
- **Lives:** Each Pokémon starts the battle with 5 lives. Damage inflicted depends on type weaknesses and resistances.

### Damage Mechanics
- **Neutral Attack:** Deals 2 life points of damage.
- **STAB (Same Type Attack Bonus):** If a Pokémon uses a move of its own type, the damage is multiplied by 1.5x.
- **Effectiveness:**
  - **Super Effective:** Damage is doubled (x2).
  - **Not Very Effective:** Damage is halved (x0.5).
  - **No Effect:** Damage is nullified (x0).

Attacking ends the player's turn.

### Sensor Interaction
- Certain moves require activating specific sensors within a time limit to execute the attack successfully. Failure to do so results in a missed attack that deals no damage.
- **Normal-Type Moves:** Do not require sensors and deal damage automatically based on STAB, Weakness, and Resistance mechanics.
- **Sensors required for other move types:**
  - **Fighting:** Ultrasonic Distance Sensor.
  - **Water:** Rain Sensor.
  - **Fire:** Temperature and Pressure Sensor.
  - **Psychic:** Infrared Sensor.
  - **Ghost:** Presence Sensor.

### Switching Pokémon
- Players can switch Pokémon for strategic advantage.
- During their turn, they can view their own and their opponent's Pokémon without limit. However, selecting one of their Pokémon as the active one ends their turn.
- Players can only switch to a Pokémon that has 1 or more lives.

---

## Components, Sensors, Functions, and Required Ports
| Component/Sensor            | Function                   | Required Ports        |
|-----------------------------|---------------------------|-----------------------|
| **Button**                  | Normal-Type Attack         | 1 pd                 |
| **Ultrasonic Distance Sensor** | Fighting-Type Attack      | 1 pd, 1 pd pwm        |
| **Temperature & Pressure Sensor** | Fire-Type Attack        | 1 pa                 |
| **Rain Sensor**             | Water-Type Attack          | 1 pa                 |
| **Presence Sensor**         | Ghost-Type Attack          | 1 pd                 |
| **Infrared Sensor**         | Psychic-Type Attack        | 1 pa                 |
| **Button**                  | Action Selection/Cancel    | 1 pd                 |
| **Buzzer**                  | Sound Effects              | 1 pd pwm             |
| **RGB LED**                 | Visual Effects             | 3 pd pwm             |
| **LCD**                     | Pixel Art and Display      | 2 pa                 |

### Key:
- **pd:** Digital Port  
- **pd pwm:** Digital Port with Pulse Width Modulation  
- **pa:** Analog Port  

This configuration ensures efficient port usage and delivers an engaging gameplay experience with interactive components.
