#ifndef PROTODEF

#else
#ifdef PROTO_HAS_CYRF6936
PROTODEF(PROTOCOL_DEVO,   EATRG, DEVO_Cmds, "DEVO")
PROTODEF(PROTOCOL_WK2801, EATRG, WK2x01_Cmds, "WK2801")
#ifndef DEFINE_FUNCS
PROTODEF(PROTOCOL_WK2601, EATRG, WK2x01_Cmds, "WK2601")
PROTODEF(PROTOCOL_WK2401, EATRG, WK2x01_Cmds, "WK2401")
PROTODEF(PROTOCOL_DSM2,   TAERG, DSM2_Cmds,   "DSM2")
#endif
PROTODEF(PROTOCOL_DSMX,   TAERG, DSM2_Cmds,   "DSMX")
PROTODEF(PROTOCOL_J6PRO,  AETRG, J6PRO_Cmds,  "J6Pro")
#endif //PROTO_HAS_CYRF6936
#ifdef PROTO_HAS_A7105
PROTODEF(PROTOCOL_FLYSKY, AETRG, FLYSKY_Cmds, "Flysky")
PROTODEF(PROTOCOL_HUBSAN, AETRG, HUBSAN_Cmds, "Hubsan4")
#endif //PROTO_HAS_A7105
PROTODEF(PROTOCOL_PPM,    EATRG, PPMOUT_Cmds, "PPM")
#endif //PROTODEF
