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

  int i;
  static int rounds = 1;

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

  /* Usar Spy depois de 5 rodadas */
  if (rounds == 5){

    position_t attacker_position = get_spy_position(attacker_spy);

    /* Se o atacante estiver à direita do defensor */
    if (attacker_position.j > defender_position.j){

      /* Atacante está abaixo do defensor */
      if (attacker_position.i > defender_position.i){
        directions_priorities[0] = (direction_t) DIR_DOWN_RIGHT;
        directions_priorities[1] = (direction_t) DIR_RIGHT;
        directions_priorities[2] = (direction_t) DIR_DOWN;
        directions_priorities[3] = (direction_t) DIR_DOWN_LEFT;
        directions_priorities[4] = (direction_t) DIR_UP_RIGHT;
        directions_priorities[5] = (direction_t) DIR_LEFT;
        directions_priorities[6] = (direction_t) DIR_UP_LEFT;
        directions_priorities[7] = (direction_t) DIR_UP;
      }
      else if (attacker_position.i < defender_position.i){ /* Em cima */
        directions_priorities[0] = (direction_t) DIR_UP_RIGHT;
        directions_priorities[1] = (direction_t) DIR_RIGHT;
        directions_priorities[2] = (direction_t) DIR_UP;
        directions_priorities[3] = (direction_t) DIR_UP_LEFT;
        directions_priorities[4] = (direction_t) DIR_DOWN_RIGHT;
        directions_priorities[5] = (direction_t) DIR_LEFT;
        directions_priorities[6] = (direction_t) DIR_DOWN_LEFT;
        directions_priorities[7] = (direction_t) DIR_DOWN;
      }
      else{ /* Mesma altura */
        directions_priorities[0] = (direction_t) DIR_RIGHT;
        directions_priorities[1] = (direction_t) DIR_UP_RIGHT;
        directions_priorities[2] = (direction_t) DIR_DOWN_RIGHT;
        directions_priorities[3] = (direction_t) DIR_UP;
        directions_priorities[4] = (direction_t) DIR_UP_LEFT;
        directions_priorities[5] = (direction_t) DIR_LEFT;
        directions_priorities[6] = (direction_t) DIR_DOWN_LEFT;
        directions_priorities[7] = (direction_t) DIR_DOWN;
      }
    }
    else if (attacker_position.j > defender_position.j){ /* Esquerda */

      /* Atacante está abaixo do defensor */
      if (attacker_position.i > defender_position.i){
        directions_priorities[0] = (direction_t) DIR_DOWN_LEFT;
        directions_priorities[1] = (direction_t) DIR_LEFT;
        directions_priorities[2] = (direction_t) DIR_DOWN;
        directions_priorities[3] = (direction_t) DIR_DOWN_RIGHT;
        directions_priorities[4] = (direction_t) DIR_UP_LEFT;
        directions_priorities[5] = (direction_t) DIR_RIGHT;
        directions_priorities[6] = (direction_t) DIR_UP_RIGHT;
        directions_priorities[7] = (direction_t) DIR_UP;
      }
      else if (attacker_position.i < defender_position.i){ /* Atacante em cima */
        directions_priorities[0] = (direction_t) DIR_UP_LEFT;
        directions_priorities[1] = (direction_t) DIR_LEFT;
        directions_priorities[2] = (direction_t) DIR_UP;
        directions_priorities[3] = (direction_t) DIR_UP_RIGHT;
        directions_priorities[4] = (direction_t) DIR_DOWN_LEFT;
        directions_priorities[5] = (direction_t) DIR_RIGHT;
        directions_priorities[6] = (direction_t) DIR_DOWN_RIGHT;
        directions_priorities[7] = (direction_t) DIR_DOWN;
      }
      else{ /* Mesma altura */
        directions_priorities[0] = (direction_t) DIR_LEFT;
        directions_priorities[1] = (direction_t) DIR_UP_LEFT;
        directions_priorities[2] = (direction_t) DIR_UP;
        directions_priorities[3] = (direction_t) DIR_UP_RIGHT;
        directions_priorities[4] = (direction_t) DIR_DOWN_LEFT;
        directions_priorities[5] = (direction_t) DIR_RIGHT;
        directions_priorities[6] = (direction_t) DIR_DOWN_RIGHT;
        directions_priorities[7] = (direction_t) DIR_DOWN;
      }
    }
    else{ /* Mesma coluna */

      /* Atacante está abaixo do defensor */
      if (attacker_position.i > defender_position.i){
        directions_priorities[0] = (direction_t) DIR_DOWN_RIGHT;
        directions_priorities[1] = (direction_t) DIR_DOWN;
        directions_priorities[2] = (direction_t) DIR_RIGHT;
        directions_priorities[3] = (direction_t) DIR_DOWN_LEFT;
        directions_priorities[4] = (direction_t) DIR_UP_LEFT;
        directions_priorities[5] = (direction_t) DIR_UP_RIGHT;
        directions_priorities[6] = (direction_t) DIR_UP;
        directions_priorities[7] = (direction_t) DIR_LEFT;
      }
      else if (attacker_position.i < defender_position.i){ /* Atacante em cima */
        directions_priorities[0] = (direction_t) DIR_UP_RIGHT;
        directions_priorities[1] = (direction_t) DIR_UP;
        directions_priorities[2] = (direction_t) DIR_RIGHT;
        directions_priorities[3] = (direction_t) DIR_UP_LEFT;
        directions_priorities[4] = (direction_t) DIR_DOWN_RIGHT;
        directions_priorities[5] = (direction_t) DIR_DOWN_LEFT;
        directions_priorities[6] = (direction_t) DIR_DOWN;
        directions_priorities[7] = (direction_t) DIR_LEFT;
      }
    }

  }

  rounds++;

  previous_position = defender_position;

  return directions_priorities[0];;
}

/*----------------------------------------------------------------------------*/
