#pragma once

struct Active {
  bool state;

  bool isActive() { return state == true; }
  bool isNotActive() { return state == false; }
};
