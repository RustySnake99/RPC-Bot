#include "engine.h"
#include "type_chart.h"
#include<nlohmann/json.hpp>
#include<vector>
#include<algorithm>

using json = nlohmann::json;

rust::String compute_best_move_cpp(rust::Str state_json) {
    std::string input(state_json);
    json state = json::parse(input, nullptr, false);

    if (state.is_discarded()) return rust::String(R"({"action":"none"})");
    std::vector<std::string> my_types = state.value("active", json::object()).value("types", std::vector<std::string>{});
    std::vector<std::string> opp_types = state.value("opponent_active", json::object()).value("types", std::vector<std::string>{});
    std::string best_move_id;
    double best_score = -1.0;

    for (const auto &move : state.value("available_moves", json::array())) {
        double base_power = move.value("base_power", 0.0);
        if (base_power <= 0.0) continue;

        std::string move_type = move.value("type", "Normal");
        double effectiveness = type_effectiveness(move_type, opp_types);
        if (effectiveness == 0) continue;

        bool stab = std::find(my_types.begin(), my_types.end(), move_type) != my_types.end();
        double score = base_power * effectiveness * (stab ? 1.5 : 1.0);

        if (score > best_score) {
            best_score = score;
            best_move_id = move.value("id", "");
        }
    }
    
    json output;
    if (!best_move_id.empty()) {
        output["action"] = "move";
        output["move"] = best_move_id;
    } else {
        output["action"] = "none";
    }
    return rust::String(output.dump());
}