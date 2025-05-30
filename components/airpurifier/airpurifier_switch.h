#pragma once

#include "esphome/components/switch/switch.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"

namespace esphome {
namespace airpurifier {

    class AirpurifierSwitch : public switch_::Switch, public Component {
    public:
        AirpurifierSwitch();

        void setup() override;
        void dump_config() override;

        void set_state_lambda(std::function<optional<bool>()>&& f);
        Trigger<>* get_turn_on_trigger() const;
        Trigger<>* get_turn_off_trigger() const;
        void set_optimistic(bool optimistic);
        void set_assumed_state(bool assumed_state);
        void loop() override;

        float get_setup_priority() const override;

    protected:
        bool assumed_state() override;

        void write_state(bool state) override;

        optional<std::function<optional<bool>()>> f_;
        bool optimistic_ { false };
        bool assumed_state_ { false };
        Trigger<>* turn_on_trigger_;
        Trigger<>* turn_off_trigger_;
        Trigger<>* prev_trigger_ { nullptr };
    };

} // namespace airpurifier
} // namespace esphome
