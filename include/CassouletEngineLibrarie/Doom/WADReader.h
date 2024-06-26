#pragma once
#include <CassouletEngineLibrarie/Doom/DataTypes.h>
#include <CassouletEngineLibrarie/System/Libs.h>
#include <cstdint>

class CASSOULET_DLL WADReader
{
public:
    WADReader();
    ~WADReader();

    void ReadHeaderData(const uint8_t* pWADData, int offset, Header& header);
    void ReadDirectoryData(const uint8_t* pWADData, int offset, Directory& directory);
    void ReadVertexData(const uint8_t* pWADData, int offset, Vertex& vertex);
    void ReadSectorData(const uint8_t* pWADData, int offset, WADSector& sector);
    void ReadSidedefData(const uint8_t* pWADData, int offset, WADSidedef& sidedef);
    void ReadLinedefData(const uint8_t* pWADData, int offset, WADLinedef& linedef);
    void ReadThingData(const uint8_t* pWADData, int offset, Thing& thing);
    void ReadNodeData(const uint8_t* pWADData, int offset, Node& node);
    void ReadSubsectorData(const uint8_t* pWADData, int offset, Subsector& subsector);
    void ReadSegData(const uint8_t* pWADData, int offset, WADSeg& seg);
    void ReadPalette(const uint8_t* pWADData, int offset, WADPalette& palette);
    void ReadPatchHeader(const uint8_t* pWADData, int offset, WADPatchHeader& patchheader);
    void ReadPName(const uint8_t* pWADData, int offset, WADPNames& PNames);
    void ReadBlockMapHeader(const uint8_t* pWADData, int offset, BlockMapHeader& blockmapheader);
    void ReadBlockMapOffset(const uint8_t* pWADData, int offset, BlockMapOffset& blockmapoffset, int nOffset);
    void ReadTextureHeader(const uint8_t* pWADData, int offset, WADTextureHeader& textureheader);
    void ReadTextureData(const uint8_t* pWADData, int offset, WADTextureData& texture);
    void ReadTexturePatch(const uint8_t* pWADData, int offset, WADTexturePatch& texturepatch);
    void Read8Characters(const uint8_t* pWADData, int offset, char* pName);

    int ReadPatchColumn(const uint8_t* pWADData, int offset, PatchColumnData& patch);
};