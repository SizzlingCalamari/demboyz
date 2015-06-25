
#include "net_file.h"
#include "base/bitfile.h"
#include "base/jsonfile.h"

namespace NetHandlers
{
    bool Net_File_BitRead_Internal(BitRead& bitbuf, SourceGameContext& context, NetMsg::Net_File* data)
    {
        data->transferID = bitbuf.ReadUBitLong(32);
        bitbuf.ReadString(data->filename, sizeof(data->filename));
        data->isRequest = bitbuf.ReadOneBit() != 0;
        return !bitbuf.IsOverflowed();
    }

    bool Net_File_BitWrite_Internal(BitWrite& bitbuf, const SourceGameContext& context, NetMsg::Net_File* data)
    {
        bitbuf.WriteUBitLong(data->transferID, 32);
        bitbuf.WriteString(data->filename);
        bitbuf.WriteOneBit(data->isRequest);
        return !bitbuf.IsOverflowed();
    }

    bool Net_File_JsonRead_Internal(JsonRead& jsonbuf, SourceGameContext& context, NetMsg::Net_File* data)
    {
        return true;
    }

    bool Net_File_JsonWrite_Internal(JsonWrite& jsonbuf, const SourceGameContext& context, NetMsg::Net_File* data)
    {
        jsonbuf.StartObject("net_file");
        jsonbuf.WriteUInt32("transferId", data->transferID);
        jsonbuf.WriteString("filename", data->filename);
        jsonbuf.WriteBool("isRequest", data->isRequest);
        jsonbuf.EndObject();
        return true;
    }

    void Net_File_ToString_Internal(std::ostringstream& out, NetMsg::Net_File* data)
    {
        // nothing
    }
}
