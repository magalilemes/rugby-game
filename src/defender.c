// Standard headers
#include <stdio.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
    position_t defender_position, Spy attacker_spy) {
  // TODO: unused parameters, remove these lines later
  UNUSED(attacker_spy);

  int i;

  static direction_t directions_priorities[] = {DIR_UP_LEFT, DIR_DOWN_LEFT,
  DIR_LEFT, DIR_UP, DIR_DOWN, DIR_UP_RIGHT, DIR_DOWN_RIGHT, DIR_RIGHT};

  static position_t previous_position = { .i = 0, .j = 0};

  /* Se na rodada anterior, o defensor tentou se mexer, mas não conseguiu */
  if (previous_position.i == defender_position.i && previous_position.j == defender_position.j){

    /* Modifica a prioridade das direções em 1 para esquerda */
    direction_t tmp = directions_priorities[0];
    for (i = 0; i < 7; i++)
      directions_priorities[i] = directions_priorities[i + 1];
    directions_priorities[7] = tmp;
  }

  previous_position = defender_position;

  return directions_priorities[0];;
}

/*----------------------------------------------------------------------------*/
