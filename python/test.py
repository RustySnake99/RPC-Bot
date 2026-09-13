import showdown_bridge, json
state = {
    'active': {'types': ['Ghost', 'Dragon']},
    'opponent_active': {'types': ['Psychic']},
    'available_moves': [
        {'id': 'shadowball', 'type': 'Ghost', 'base_power': 80, 'category': 'Special'},
        {'id': 'dragontail', 'type': 'Dragon', 'base_power': 60, 'category': 'Physical'},
    ],
}
print(showdown_bridge.choose_move(json.dumps(state)))