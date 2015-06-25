
#include "svc_tempentities.h"
#include "base/bitfile.h"
#include "base/jsonfile.h"
#include "netcontants.h"
#include "netmath.h"

namespace NetHandlers
{
    bool SVC_TempEntities_BitRead_Internal(BitRead& bitbuf, SourceGameContext& context, NetMsg::SVC_TempEntities* data)
    {
        data->numEntries = bitbuf.ReadUBitLong(EVENT_INDEX_BITS);
        if (context.protocol > 23)
        {
            data->dataLengthInBits = bitbuf.ReadVarInt32();
        }
        else
        {
            data->dataLengthInBits = bitbuf.ReadUBitLong(NET_MAX_PAYLOAD_BITS_OLD);
        }
        data->data.reset(new uint8_t[math::BitsToBytes(data->dataLengthInBits)]);
        bitbuf.ReadBits(data->data.get(), data->dataLengthInBits);
        return !bitbuf.IsOverflowed();
    }

    bool SVC_TempEntities_BitWrite_Internal(BitWrite& bitbuf, const SourceGameContext& context, NetMsg::SVC_TempEntities* data)
    {
        bitbuf.WriteUBitLong(data->numEntries, EVENT_INDEX_BITS);
        if (context.protocol > 23)
        {
            bitbuf.WriteVarInt32(data->dataLengthInBits);
        }
        else
        {
            bitbuf.WriteUBitLong(data->dataLengthInBits, NET_MAX_PAYLOAD_BITS_OLD);
        }
        bitbuf.WriteBits(data->data.get(), data->dataLengthInBits);
        return !bitbuf.IsOverflowed();
    }

    bool SVC_TempEntities_JsonRead_Internal(JsonRead& jsonbuf, SourceGameContext& context, NetMsg::SVC_TempEntities* data)
    {
        return true;
    }

    bool SVC_TempEntities_JsonWrite_Internal(JsonWrite& jsonbuf, const SourceGameContext& context, NetMsg::SVC_TempEntities* data)
    {
        jsonbuf.StartObject("svc_tempentities");
        jsonbuf.WriteUInt32("numEntries", data->numEntries);
        jsonbuf.WriteUInt32("dataLengthInBits", data->dataLengthInBits);
        jsonbuf.WriteBits("data", data->data.get(), data->dataLengthInBits);
        jsonbuf.EndObject();
        return true;
    }

    void SVC_TempEntities_ToString_Internal(std::ostringstream& out, NetMsg::SVC_TempEntities* data)
    {
        out << "svc_TempEntities: number " << data->numEntries
            << ", bytes " << math::BitsToBytes(data->dataLengthInBits);
    }
}
