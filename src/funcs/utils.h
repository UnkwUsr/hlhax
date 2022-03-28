#include "sdk.h"

bool isAlive(entity_state_t ent);
char* getPlayerNameByIndex(int index);
bool WorldToScreen(float* pflOrigin, float* pflVecScreen);
void DrawLine(float* from, float* to, float r, float g, float b, float a,
              float life, float width);
