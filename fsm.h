

typedef enum tag_state {
  INITIAL = 0,
  READY = 1,
  MOVE = 2,
  ELEV_STOP = 3,
  DOORS_OPEN = 4,
  DOORS_CLOSED = 5,
  EMERGENCY_STOP = 6
} state_t;

void updateState(state_t newState);

void initializeElevator();

void stateMachine();
