

typedef enum tag_state {
  INITIAL = 0,
  READY = 1,
  MOVE = 2,
  ELEV_STOP = 3,
  DOORS_OPEN = 4,
  DOORS_CLOSED = 5,
  EMERGENCY_STOP = 6
} state_t;

//Oppdaterer state til statemaskinen heis
void updateState(state_t newState);

//Initialiserer heisen. Setter state til READY når ferdig initialisert.
void initializeElevator();

//Funksjon som kjører statemaskinen
void stateMachine();
