import asyncio
from poke_env.player import Player
from poke_env import AccountConfiguration, ShowdownServerConfiguration
import showdown_bridge
import json
import traceback

class PSBot(Player):
    def choose_move(self, battle):
        try:
            state_json = self.serialize_battle_state(battle)
            action_json = showdown_bridge.choose_move(state_json)
            # print(f"[[Turn decision: {action_json}]]", flush=True)
            order = self.action_from_json(action_json, battle)
        except Exception as e:
            self.logger.warning(f"Bridge call failed, falling back to random move selection! Error: {e}")
            # print("Bridge call failed! Falling back to random choice....", flush=True)
            order = None
        return self.choose_random_move(battle) if order is None else order

    def serialize_battle_state(self, battle):
        state = {
            "active": {"types": [str(t) for t in battle.active_pokemon.types if t]},
            "opponent_active": {"types": [str(t) for t in battle.opponent_active_pokemon.types if t]},
            "team": [self._pokemon_to_dict(p) for p in battle.team.values()],
            "opponent_team": [self._pokemon_to_dict(p) for p in battle.opponent_team.values()],
            "available_moves": [{
                "id": m.id,
                "type": str(m.type),
                "base_power": m.base_power,
                "category": str(m.category),
            } for m in battle.available_moves],
            "available_switches": [p.species for p in battle.available_switches],
            "weather": str(battle.weather),
            "field": [str(f) for f in battle.fields],
        }
        return json.dumps(state)
    
    def action_from_json(self, action_json, battle):
        action = json.loads(action_json)
        if action.get("action") == "move":
            move_id = action.get("move")
            for i in battle.available_moves:
                if i.id == move_id:
                    return self.create_order(i)
        return None

    def _pokemon_to_dict(self, mon):
        if mon is None:
            return None
        return {
            "species": mon.species,
            "hp_fraction": mon.current_hp_fraction,
            "status": str(mon.status) if mon.status else None,
            "boosts": mon.boosts,
            "types": [str(t) for t in mon.types],
            "moves": list(mon.moves.keys()),
            "held_item": mon.item,
            "ability": mon.ability,
        }

async def main(opponent_username: str):
    bot = PSBot(account_configuration=AccountConfiguration("username", "password"), battle_format="gen9randombattle", server_configuration=ShowdownServerConfiguration)
    # print(f"Challenge has been sent to: @{opponent_username}.")

    await bot.send_challenges(opponent_username, n_challenges=1)
    # print(f"'send_challenges()' returned. Current battles: {list(bot.battles.keys())}", flush=True)

    if not bot.battles:
        # print("No battles were created!", flush=True)
        return

    battle = list(bot.battles.values())[0]
    while not battle.finished:
        await asyncio.sleep(1)

    result = "Won" if battle.won else "Lost"
    print(f"Battle vs @{opponent_username} finished! Result: {result}", flush=True)
    
if __name__ == "__main__":
    x = input(">>>\tEnter the username to be challenged: ").strip()
    try:
        asyncio.run(main(x))
    except Exception:
        print("====> Unhandled exception occurred!", flush=True)
        traceback.print_exc()
