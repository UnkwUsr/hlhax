#include "funcs/misc/steamid_changer/steamid_changer.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include <dlfcn.h>
#include <cstring>



namespace Cvars {
    cvar_t* steamid;
    cvar_t* steamid_custom;
}

namespace SteamidChanger {
    DEF_HOOK(InitiateGameConnection)

    revEmuTicket_t revEmuTicket;


    void Init()
    {
        ADD_HOOK(InitiateGameConnection, gp_steamclient_funcs)

        Cvars::steamid = CREATE_CVAR("steamid", "1");
        Cvars::steamid_custom = CREATE_CVAR("steamid_custom", "3333333");
    }

    int InitiateGameConnection(void* this_ptr, void* pData, int cbMaxData, uint64 steamID, uint32 hidword_steamID, uint32_t byteswap_unIPServer, uint32 ror2_usPortServer, bool bSecure)
    {
        if(Cvars::steamid->value == 0)
        {
            return CALL_ORIG(InitiateGameConnection, this_ptr, pData, cbMaxData, steamID, hidword_steamID, byteswap_unIPServer, ror2_usPortServer, bSecure);
        }

        // Credits: thx 2010kohtep (https://github.com/2010kohtep/MultiEmulator)

        else if(Cvars::steamid->value == 1)
        {
            gp_Engine->Con_Printf("steamid type 'GenerateSteamEmu'\n");

            // GenerateSteamEmu
            int nSteamID = Cvars::steamid_custom->value;
            auto pTicket = (int *)pData;

            pTicket[20] = -1;   // +80, dproto/reunion wants this value to be -1, but if this value
                                // does not match -1, then instead of SteamID in [21] cell
                                // client IP address that xored with 0x25730981 number should
                                // be used. But dproto/reunion will just skip ticket validation
                                // in that case.

            pTicket[21] = nSteamID; // +84, SteamId, low part. Actually, this is just system volume serial
                                    // number, which comes from GetVolumeInformationA() function. If
                                    // function failed (returned 0), then instead of volume serial number
                                    // 777 number will be written to the ticket.
            return 768;
        }
        else if(Cvars::steamid->value == 2)
        {
            gp_Engine->Con_Printf("steamid type 'GenerateSetti'\n");

            // GenerateSetti
            auto pTicket = (int *)pData;

            pTicket[0] = 0xD4CA7F7B;
            pTicket[1] = 0xC7DB6023;
            pTicket[2] = 0x6D6A2E1F;
            pTicket[5] = 0xB4C43105;

            return 768;
        }
        else if(Cvars::steamid->value == 3)
        {
            gp_Engine->Con_Printf("steamid type 'GenerateOldRevEmu'\n");

            // GenerateOldRevEmu
            int nSteamID = Cvars::steamid_custom->value;
            auto pTicket = (int*)pData;
            auto pbTicket = (unsigned char*)pData;

            pTicket[0] = 0xFFFF;                                             // +0, header
            pTicket[1] = (nSteamID ^ 0xC9710266) << 1; // +4, SteamId
            *(short *)&pbTicket[8] = 0;                             // +8, unknown, in original emulator must be 0

            return 10;
        }
        else if(Cvars::steamid->value == 4)
        {
            gp_Engine->Con_Printf("steamid type 'GenerateAVSMP'\n");

            // GenerateAVSMP
            int nSteamID = Cvars::steamid_custom->value;
            bool bUniverse = false;
            auto pTicket = (int *)pData;

            pTicket[0] = 0x14;                                                                      //  +0, header
            pTicket[3] = (nSteamID << 1) | (bUniverse ? 1 : 0);  // +12, SteamId, Low part
            pTicket[4] = 0x01100001;                                                            // +16, SteamId, High part

            return 28;
        }

        // // from extramirror (thx shelru)
        // const uint8_t g_hashSymbolTable[36] = {
        //  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        //  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
        //  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
        //  'U', 'V', 'W', 'X', 'Y', 'Z'
        // };
        // for (size_t i = 0; i < 7; i++)
        // {
        //  revEmuTicket.hash[i] = g_hashSymbolTable[rand() % 36];
        // }
        // revEmuTicket.hash[7] = '\0';

        // revEmuTicket.version = 'J';
        // revEmuTicket.highPartAuthID = RevHash((const char *)revEmuTicket.hash) & 0x7FFFFFFF;
        // revEmuTicket.signature = 'r' + 'e' + 'v';
        // revEmuTicket.secondSignature = 0;
        // revEmuTicket.authID = RevHash((const char *)revEmuTicket.hash) << 1;
        // revEmuTicket.thirdSignature = 0x01100001;

        // memcpy(pData, &revEmuTicket, sizeof(revEmuTicket));
        // return sizeof(revEmuTicket);

        return CALL_ORIG(InitiateGameConnection, this_ptr, pData, cbMaxData, steamID, hidword_steamID, byteswap_unIPServer, ror2_usPortServer, bSecure);
    }

    uint32_t RevHash(const char *str)
    {
        uint32_t hash = 0x4E67C6A7;
        for (const char *pch = str; *pch != '\0'; pch++)
        {
            hash ^= (hash >> 2) + (hash << 5) + *pch;
        }
        return hash;
    }
} // namespace SteamidChanger
