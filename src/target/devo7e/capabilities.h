#ifdef CHANDEF
  CHANDEF(AILERON)
  CHANDEF(ELEVATOR)
  CHANDEF(THROTTLE)
  CHANDEF(RUDDER)
  CHANDEF(HOLD0)
  CHANDEF(HOLD1)
  CHANDEF(FMOD0)
  CHANDEF(FMOD1)
#endif

#ifdef UNDEF_INP
#define INP_RUD_DR0 INP_HOLD0
#define INP_RUD_DR1 INP_HOLD1
#define INP_ELE_DR0 INP_HOLD0
#define INP_ELE_DR1 INP_HOLD1
#define INP_AIL_DR0 INP_HOLD0
#define INP_AIL_DR1 INP_HOLD1
#define INP_FMOD2  INP_FMOD1
#define INP_MIX0   INP_FMOD0
#define INP_MIX1   INP_FMOD1
#define INP_MIX2   INP_FMOD1
#define INP_GEAR0  INP_HOLD0
#define INP_GEAR1  INP_HOLD1
#endif
#ifdef CHANMAP
//These are legacy mappings
  CHANMAP("DR",     HOLD1)
  CHANMAP("RUD DR", HOLD1)
  CHANMAP("ELE_DR", HOLD1)
  CHANMAP("AIL_DR", HOLD1)
//Current mappings
  CHANMAP("RUD DR0", HOLD0)
  CHANMAP("RUD DR1", HOLD1)
  CHANMAP("ELE DR0", HOLD0)
  CHANMAP("ELE DR1", HOLD1)
  CHANMAP("AIL DR0", HOLD0)
  CHANMAP("AIL DR1", HOLD1)
  CHANMAP("FMOD2", FMOD1)
  CHANMAP("MIX0", FMOD0)
  CHANMAP("MIX1", FMOD1)
  CHANMAP("MIX2", FMOD1)
#endif

#ifdef BUTTONDEF
  BUTTONDEF(TRIM_LV_NEG) /* LEFT-VERTICAL */
  BUTTONDEF(TRIM_LV_POS)
  BUTTONDEF(TRIM_RV_NEG) /* RIGHT-VERTICAL */
  BUTTONDEF(TRIM_RV_POS)
  BUTTONDEF(TRIM_LH_NEG) /* LEFT-HORIZONTAL */
  BUTTONDEF(TRIM_LH_POS)
  BUTTONDEF(TRIM_RH_NEG) /* RIGHT-HORIZONTAL */
  BUTTONDEF(TRIM_RH_POS)
  BUTTONDEF(LEFT)
  BUTTONDEF(RIGHT)
  BUTTONDEF(DOWN)
  BUTTONDEF(UP)
  BUTTONDEF(ENTER)
  BUTTONDEF(EXIT)
#endif
