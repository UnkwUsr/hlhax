#include "funcs/funcs.h"

#include "funcs/filter/filter.h"

#include "funcs/visuals/xqz/xqz.h"
#include "funcs/visuals/info/info.h"
#include "funcs/visuals/thirdperson/thirdperson.h"
#include "funcs/visuals/barrel/barrel.h"
#include "funcs/visuals/noflash/noflash.h"
#include "funcs/visuals/tracer/tracer.h"
#include "funcs/visuals/esp/esp.h"
#include "funcs/visuals/fullbright/fullbright.h"

#include "funcs/movement/fps_set/fps_set.h"
#include "funcs/movement/sgs/sgs.h"
#include "funcs/movement/spinhack/spinhack.h"
#include "funcs/movement/speedhack/speedhack.h"

#include "funcs/misc/steamid_changer/steamid_changer.h"

#include "funcs/aim/fastzoom/fastzoom.h"
#include "funcs/aim/aimbot/aimbot.h"
#include "funcs/aim/triggerbot/triggerbot.h"
#include "funcs/aim/norecoil/norecoil.h"


void Funcs_Init()
{
    Filter::Init();

    Xqz::Init();
    Info::Init();
    ThirdPerson::Init();
    Barrel::Init();
    NoFlash::Init();
    Tracer::Init();
    Esp::Init();
    Fullbright::Init();

    SteamidChanger::Init();

    AimBot::Init();
    TriggerBot::Init();
    NoRecoil::Init();
    FastZoom::Init();

    FpsSet::Init();
    Sgs::Init();
    Spinhack::Init();
    Speedhack::Init();


    // last hooked funcs will process first. We need that
    Filter::SetHooks();
}

void Funcs_Terminate()
{
    Fullbright::Terminate();

    // because of specific gl hooks,
    // if one gl function hooked in two funcs, then
    // Terminate functions shold be called in reversed order relative to Init
    // For example: Init: a, b; then Terminate should be: b, a
    // TODO: gl hooks should be fixed in future
    Xqz::Terminate();

    Filter::Terminate();
}
