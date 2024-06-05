#include <CassouletEngineLibrarie/Doom/AssetsManager.h>
#include <CassouletEngineLibrarie/Doom/WADLoader.h>

bool AssetsManager::m_bInitialized = false;
std::unique_ptr<AssetsManager> AssetsManager::m_pInstance = nullptr;

AssetsManager* AssetsManager::GetInstance()
{
    if (!m_bInitialized)
    {
        m_pInstance = std::unique_ptr<AssetsManager>( new AssetsManager());
        m_bInitialized = true;
    }

    return m_pInstance.get();
}

void AssetsManager::Init(WADLoader* pWADLoader)
{
    m_pWADLoader = pWADLoader;
    LoadTextures();
}

AssetsManager::~AssetsManager()
{
    delete(m_pWADLoader);
}

//Patch* AssetsManager::AddPatch(const std::string& sPatchName, WADPatchHeader& PatchHeader)
//{
//    m_PatchesCache[sPatchName] = new Patch(sPatchName);
//    m_PatchesCache[sPatchName]->Initialize(PatchHeader);
//
//    return m_PatchesCache[sPatchName];
//}
//
//Patch* AssetsManager::GetPatch(const std::string& sPatchName)
//{
//    if (m_PatchesCache.count(sPatchName) > 0)
//    {
//        return m_PatchesCache[sPatchName];
//    }
//
//    LoadPatch(sPatchName);
//
//    // Maybe we need to check if the patch is loaded? Maybe that patch name is not in file
//    return m_PatchesCache[sPatchName];
//}
//
//Texture* AssetsManager::AddTexture(WADTextureData& TextureData)
//{
//    m_TexturesCache[TextureData.TextureName] =new Texture(TextureData);
//    return m_TexturesCache[TextureData.TextureName];
//}
//
//Texture* AssetsManager::GetTexture(const std::string& sTextureName)
//{
//    if (!m_TexturesCache.count(sTextureName))
//    {
//        return nullptr;
//    }
//
//    Texture* pTexture = m_TexturesCache[sTextureName];
//    if (!pTexture->IsComposed())
//    {
//        pTexture->Compose();
//    }
//
//    return pTexture;
//}

void AssetsManager::AddPName(const std::string& PName)
{
    m_PNameLookup.push_back(PName);
}

std::string AssetsManager::GetPName(int PNameIndex)
{
    return m_PNameLookup[PNameIndex];
}



void AssetsManager::LoadPatch(const std::string& sPatchName)
{
    m_pWADLoader->LoadPatch(sPatchName);
}

void AssetsManager::LoadTextures()
{
    m_pWADLoader->LoadPNames();
    m_pWADLoader->LoadTextures("TEXTURE1");
    m_pWADLoader->LoadTextures("TEXTURE2");
}