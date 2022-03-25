// Standard headers
#include <stdio.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy) {

  int i;
  static int rounds = 1;

  static direction_t directions_priorities[] = {DIR_UP_RIGHT, DIR_UP, DIR_RIGHT,
  DIR_DOWN_RIGHT, DIR_DOWN, DIR_UP_LEFT, DIR_DOWN_LEFT, DIR_LEFT};

  static position_t previous_position = { .i = 0, .j = 0};

  /* Se na rodada anterior, o atacante tentou se mexer, mas não conseguiu */
  if (previous_position.i == attacker_position.i && previous_position.j == attacker_position.j){

    /* Modifica a prioridade das direções em 1 para esquerda */
    direction_t tmp = directions_priorities[0];
    for (i = 0; i < 7; i++)
      directions_priorities[i] = directions_priorities[i + 1];
    directions_priorities[7] = tmp;
  }

  /* Usar spy se o atacante estiver andando pra esquerda e a quantidade de
  rodadas for maior que 10 */
  if (get_spy_number_uses(defender_spy) == 0 && directions_priorities[0].j == -1 && rounds > 10){

    position_t defender_position = get_spy_position(defender_spy);

    /* Se ambos atacante e defensor não estiverem na mesma linha */
    if (defender_position.i != attacker_position.i){

      /* Inverte ordem das direções */
      for (i = 0; i < 4; i++){
        direction_t tmp = directions_priorities[i];
        directions_priorities[i] = directions_priorities[7 - i];
        directions_priorities[7 - i] = tmp;
      }
    }
    else if (defender_position.i > attacker_position.i){ /* Se atacante estiver à esquerda do defensor*/
      directions_priorities[0] = (direction_t) DIR_UP;
      directions_priorities[1] = (direction_t) DIR_DOWN;
      directions_priorities[2] = (direction_t) DIR_UP_RIGHT;
      directions_priorities[3] = (direction_t) DIR_DOWN_RIGHT;
      directions_priorities[4] = (direction_t) DIR_UP_LEFT;
      directions_priorities[5] = (direction_t) DIR_DOWN_LEFT;
      directions_priorities[6] = (direction_t) DIR_LEFT;
      directions_priorities[7] = (direction_t) DIR_RIGHT;
    }
  }

  rounds++;

  previous_position = attacker_position;

  return directions_priorities[0];
}

/*----------------------------------------------------------------------------*/
