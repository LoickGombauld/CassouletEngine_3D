#pragma once

#include <CassouletEngineLibrarie/Doom/DataTypes.h>

class WADLoader;

class CASSOULET_DLL AssetsManager
{
public:
    static AssetsManager* GetInstance();
    void Init(WADLoader* pWADLoader);

    ~AssetsManager();

   /* Patch* AddPatch(const std::string& sPatchName, WADPatchHeader& PatchHeader);
    Patch* GetPatch(const std::string& sPatchName);

    Texture* AddTexture(WADTextureData& TextureData);
    Texture* GetTexture(const std::string& sTextureName);*/

    void AddPName(const std::string& PName);
    std::string GetPName(int PNameIndex);


protected:
    static bool m_bInitialized;
    static std::unique_ptr <AssetsManager> m_pInstance;

    AssetsManager() {};

    void LoadPatch(const std::string& sPatchName);
    void LoadTextures();


  //  std::map<std::string, Patch*> m_PatchesCache;
  // std::map<std::string, Texture*> m_TexturesCache;


    std::vector<std::string> m_PNameLookup;

    WADLoader* m_pWADLoader;
};