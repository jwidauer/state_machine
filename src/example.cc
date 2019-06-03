#include <iostream>
#include <variant>

#include "state_machine/state_machine.h"

struct OpenEvent {};

struct CloseEvent {};

struct ClosedState;
struct OpenState;

struct ClosedState {
  ClosedState() {
    std::cout << "ClosedState: constructor called." << std::endl;
  }

  ~ClosedState() { std::cout << "ClosedState: destructor called" << std::endl; }

  std::variant<Nothing> handle() const {
    std::cout << "ClosedState: empty handle called." << std::endl;
    return {};
  }

  std::variant<TransitionTo<OpenState>> handle(const OpenEvent&) const {
    std::cout << "ClosedState: Opening door..." << std::endl;
    return {};
  }

  std::variant<Nothing> handle(const CloseEvent&) const {
    std::cout << "ClosedState: Door already closed..." << std::endl;
    return {};
  }
};

struct OpenState {
  OpenState() { std::cout << "OpenState: constructor called." << std::endl; }

  ~OpenState() { std::cout << "OpenState: destructor called." << std::endl; }

  std::variant<Nothing> handle() const {
    std::cout << "OpenState: empty handle called." << std::endl;
    return {};
  }

  std::variant<Nothing> handle(const OpenEvent&) const {
    std::cout << "OpenState: Door already open..." << std::endl;
    return {};
  }

  std::variant<TransitionTo<ClosedState>> handle(const CloseEvent&) {
    std::cout << "CloseEvent: Closing door..." << std::endl;
    return {};
  }
};

int main() {
  StateMachine<ClosedState, OpenState> door;

  door.handle();
  door.handle(OpenEvent{});
}
