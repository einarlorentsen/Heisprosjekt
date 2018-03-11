
//Definerer caser for statemaskinen heis
typedef enum tag_state {
  INITIAL = 0,
  READY = 1,
  MOVE = 2,
  ELEV_STOP = 3,
  DOORS_OPEN = 4,
  DOORS_CLOSED = 5,
  EMERGENCY_STOP = 6
} state_t;

//Oppdaterer state til statemaskinen heis. newState blir ny state
void updateState(state_t newState);

//Initialiserer heisen med retning opp hvis ikke i etasje. Når vi er i etasje settes state til READY.
void initializeElevator();

//Sender oss til EMERGENCY_STATE hvis stoppknapp trykkes
void checkButtonStop();

//Funksjon som kjører statemaskinen heis
void stateMachine();
