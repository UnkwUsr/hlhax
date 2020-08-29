#include "funcs/funcs.h"

#include "funcs/visuals/xqz/xqz.h"
#include "funcs/visuals/info/info.h"
#include "funcs/visuals/thirdperson/thirdperson.h"
#include "funcs/visuals/barrel/barrel.h"
#include "funcs/visuals/wiremodels/wiremodels.h"
#include "funcs/visuals/noflash/noflash.h"
#include "funcs/visuals/tracer/tracer.h"
#include "funcs/visuals/esp/esp.h"

#include "funcs/movement/fps_set/fps_set.h"
#include "funcs/movement/sgs/sgs.h"
#include "funcs/movement/spinhack/spinhack.h"

#include "funcs/misc/steamid_changer/steamid_changer.h"
#include "funcs/misc/triggerbot/triggerbot.h"



void Funcs_Init()
{
    Xqz::Init();
    Info::Init();
    ThirdPerson::Init();
    Barrel::Init();
//  WireModels::Init();
    NoFlash::Init();
    Tracer::Init();
    Esp::Init();

    SteamidChanger::Init();
    TriggerBot::Init();

    FpsSet::Init();
    Sgs::Init();
    Spinhack::Init();
}

void Funcs_Terminate()
{
    Xqz::Terminate();
}
