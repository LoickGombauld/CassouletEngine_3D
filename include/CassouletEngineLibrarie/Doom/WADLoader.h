#pragma once

#include <CassouletEngineLibrarie/System/Libs.h>
#include <CassouletEngineLibrarie/Doom/WADReader.h>

class Map;

class CASSOULET_DLL WADLoader
{
public:
    WADLoader();
    void SetWADFilePath(const std::string& sWADFilePath);
    bool LoadWADToMemory();
    bool LoadMapData(Map* pMap);
    bool LoadPalette(std::vector<WADPalette>& allPalette);
    bool LoadPatch(const std::string& sPatchName);
    bool LoadTextures(const std::string& sTextureName);
    bool LoadPNames();
   std::string GetTextureName(int index);

    ~WADLoader();

protected:
    bool OpenAndLoad();
    bool ReadDirectories();
    bool ReadMapVertexes(Map* pMap);
    bool ReadMapLinedefs(Map* pMap);
    bool ReadBlockMap(Map* pmap);
    bool ReadMapThings(Map* pMap);
    bool ReadMapNodes(Map* pMap);
    bool ReadMapSubsectors(Map* pMap);
    bool ReadMapSectors(Map* pMap);
    bool ReadMapSidedefs(Map* pMap);
    bool ReadMapSegs(Map* pMap);


    int FindMapIndex(Map* pMap);

    int FindLumpByName(const std::string& LumpName);

    std::vector<std::string> m_texturesNames;

    std::string m_sWADFilePath;
    std::ifstream m_WADFile;
    std::vector<Directory> m_WADDirectories;
    std::unique_ptr<uint8_t[]> m_pWADData;
    WADReader m_Reader;
};
