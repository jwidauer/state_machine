#ifndef STATE_MACHINE_STATE_MACHINE_H_
#define STATE_MACHINE_STATE_MACHINE_H_

#include <variant>

template <typename InitialState, typename... States>
class StateMachine {
 public:
  template <typename State>
  void transitionTo() {
    current_state_.template emplace<State>();
  }

  template <typename... Events,
            typename = std::enable_if<sizeof...(Events) == 0 ||
                                      sizeof...(Events) == 1>>
  void handle(const Events&... events) {
    auto passEventToState = [this, &events...](const auto& state) {
      auto executeTransition = [this](const auto& transition) {
        transition.execute(this);
      };
      std::visit(executeTransition, state.handle(events...));
    };
    std::visit(passEventToState, current_state_);
  }

 private:
  std::variant<InitialState, States...> current_state_;
};

template <typename State>
struct TransitionTo {
  template <typename Machine>
  void execute(Machine* machine) const {
    machine->template transitionTo<State>();
  }
};

struct Nothing {
  template <typename Machine>
  void execute(Machine* machine) const {}
};

#endif  // STATE_MACHINE_STATE_MACHINE_H_
