#ifndef STEAMID_XQZ_H
#define STEAMID_XQZ_H

#include "sdk.h"
#include "utils/hooks/funcs.h"
#include <inttypes.h>



namespace SteamidChanger {
    void Init();

    DECL_HOOK(int, InitiateGameConnection, void* this_ptr, void* pData, int cbMaxData, uint64 steamID, uint32 hidword_steamID, uint32_t byteswap_unIPServer, uint32 ror2_usPortServer, bool bSecure);

    uint32_t RevHash(const char *str);
    typedef struct revEmuTicket_s {
        uint32_t version;
        uint32_t highPartAuthID;
        uint32_t signature;
        uint32_t secondSignature;
        uint32_t authID;
        uint32_t thirdSignature;
        uint8_t hash[128];
    } revEmuTicket_t;
} // namespace SteamidChanger

#endif // STEAMID_XQZ_H
