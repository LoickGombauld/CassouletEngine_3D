#include <CassouletEngineLibrarie/Doom/WADLoader.h>
#include <CassouletEngineLibrarie/Doom/AssetsManager.h>
#include <CassouletEngineLibrarie/Doom/Map.h>
#include <CassouletEngineLibrarie/Doom/Things.h>

WADLoader::WADLoader() : m_pWADData(nullptr)
{
	m_sWADFilePath = std::filesystem::path("Resources/DOOM1.WAD").string();
}

WADLoader::~WADLoader()
{
}

void WADLoader::SetWADFilePath(const std::string& sWADFilePath)
{
	m_sWADFilePath = sWADFilePath;
}

bool WADLoader::LoadWADToMemory()
{
	if (!OpenAndLoad())
	{
		return false;
	}

	if (!ReadDirectories())
	{
		return false;
	}

	return true;
}

bool WADLoader::OpenAndLoad()
{
	std::cout << "Info: Loading WAD file: " << m_sWADFilePath << std::endl;

	m_WADFile.open(m_sWADFilePath, std::ifstream::binary);
	if (!m_WADFile.is_open())
	{
		std::cout << "Error: Failed to open WAD file" << m_sWADFilePath << std::endl;
		return false;
	}

	m_WADFile.seekg(0, m_WADFile.end);
	size_t length = m_WADFile.tellg();

	m_pWADData = std::unique_ptr<uint8_t[]>(new uint8_t[length]);
	if (m_pWADData == nullptr)
	{
		std::cout << "Error: Failed allocate memory for WAD file of size " << length << std::endl;
		return false;
	}

	m_WADFile.seekg(std::ifstream::beg);
	m_WADFile.read((char*)m_pWADData.get(), length);

	m_WADFile.close();

	std::cout << "Info: Loading complete." << std::endl;

	return true;
}

bool WADLoader::ReadDirectories()
{
	Header header;
	m_Reader.ReadHeaderData(m_pWADData.get(), 0, header);

	Directory directory;

	for (unsigned int i = 0; i < header.DirectoryCount; ++i)
	{
		m_Reader.ReadDirectoryData(m_pWADData.get(), header.DirectoryOffset + i * 16, directory);
		m_WADDirectories.push_back(directory);
	}

	return true;
}

bool WADLoader::LoadMapData(Map* pMap)
{
	std::cout << "Info: Parsing Map: " << pMap->GetName() << std::endl;

	std::cout << "Info: Processing Map Vertexes" << std::endl;
	if (!ReadMapVertexes(pMap))
	{
		std::cout << "Error: Failed to load map vertexes data MAP: " << pMap->GetName() << std::endl;
		return false;
	}

	// Load Sector
	std::cout << "Info: Processing Map Sectors" << std::endl;
	if (!ReadMapSectors(pMap))
	{
		std::cout << "Error: Failed to load map sectors data MAP: " << pMap->GetName() << std::endl;
		return false;
	}

	// Load Sidedef
	std::cout << "Info: Processing Map Sidedefs" << std::endl;
	if (!ReadMapSidedefs(pMap))
	{
		std::cout << "Error: Failed to load map Sidedefs data MAP: " << pMap->GetName() << std::endl;
		return false;
	}

	std::cout << "Info: Processing Map Linedefs" << std::endl;
	if (!ReadMapLinedefs(pMap))
	{
		std::cout << "Error: Failed to load map linedefs data MAP: " << pMap->GetName() << std::endl;
		return false;
	}

	std::cout << "Info: Processing Map Segs" << std::endl;
	if (!ReadMapSegs(pMap))
	{
		std::cout << "Error: Failed to load map segs data MAP: " << pMap->GetName() << std::endl;
		return false;
	}

	std::cout << "Info: Processing Map Things" << std::endl;
	if (!ReadMapThings(pMap))
	{
		std::cout << "Error: Failed to load map things data MAP: " << pMap->GetName() << std::endl;
		return false;
	}

	std::cout << "Info: Processing Map Nodes" << std::endl;
	if (!ReadMapNodes(pMap))
	{
		std::cout << "Error: Failed to load map nodes data MAP: " << pMap->GetName() << std::endl;
		return false;
	}

	std::cout << "Info: Processing Map Subsectors" << std::endl;
	if (!ReadMapSubsectors(pMap))
	{
		std::cout << "Error: Failed to load map subsectors data MAP: " << pMap->GetName() << std::endl;
		return false;
	}
	//std::cout << "Info: Processing Block Map" << std::endl;
	//if (!ReadBlockMap(pMap))
	//{
	//	std::cout << "Error: Failed to load map block data MAP: " << pMap->GetName() << std::endl;
	//	return false;
	//}

	return true;
}

int WADLoader::FindMapIndex(Map* pMap)
{
	if (pMap->GetLumpIndex() > -1)
	{
		return pMap->GetLumpIndex();
	}

	pMap->SetLumpIndex(FindLumpByName(pMap->GetName()));

	return pMap->GetLumpIndex();
}

int WADLoader::FindLumpByName(const std::string& LumpName)
{
	for (int i = 0; i < m_WADDirectories.size(); ++i)
	{
		if (m_WADDirectories[i].LumpName == LumpName)
		{
			return i;
		}
	}
	return -1;
}

bool WADLoader::ReadMapVertexes(Map* pMap)
{
	int iMapIndex = FindMapIndex(pMap);

	if (iMapIndex == -1)
	{
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eVERTEXES;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "VERTEXES") != 0)
	{
		return false;
	}

	int iVertexSizeInBytes = sizeof(Vertex);
	int iVertexesCount = m_WADDirectories[iMapIndex].LumpSize / iVertexSizeInBytes;

	Vertex vertex;
	for (int i = 0; i < iVertexesCount; ++i)
	{
		m_Reader.ReadVertexData(m_pWADData.get(), m_WADDirectories[iMapIndex].LumpOffset + i * iVertexSizeInBytes, vertex);
		pMap->AddVertex(vertex);
	}

	return true;
}

bool WADLoader::ReadMapSectors(Map* pMap)
{
	int iMapIndex = FindMapIndex(pMap);

	if (iMapIndex == -1)
	{
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eSECTORS;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "SECTORS") != 0)
	{
		return false;
	}

	int iSectorSizeInBytes = sizeof(WADSector);
	int iSectorsCount = m_WADDirectories[iMapIndex].LumpSize / iSectorSizeInBytes;

	WADSector sector;
	for (int i = 0; i < iSectorsCount; ++i)
	{
		m_Reader.ReadSectorData(m_pWADData.get(), m_WADDirectories[iMapIndex].LumpOffset + i * iSectorSizeInBytes, sector);
		pMap->AddSector(sector);
	}

	return true;
}

bool WADLoader::ReadMapSidedefs(Map* pMap)
{
	int iMapIndex = FindMapIndex(pMap);

	if (iMapIndex == -1)
	{
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eSIDEDDEFS;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "SIDEDEFS") != 0)
	{
		return false;
	}

	int iSidedefSizeInBytes = sizeof(WADSidedef);
	int iSidedefsCount = m_WADDirectories[iMapIndex].LumpSize / iSidedefSizeInBytes;

	WADSidedef sidedef;
	for (int i = 0; i < iSidedefsCount; ++i)
	{
		m_Reader.ReadSidedefData(m_pWADData.get(), m_WADDirectories[iMapIndex].LumpOffset + i * iSidedefSizeInBytes, sidedef);
		pMap->AddSidedef(sidedef);
	}

	return true;
}

bool WADLoader::ReadMapLinedefs(Map* pMap)
{
	int iMapIndex = FindMapIndex(pMap);

	if (iMapIndex == -1)
	{
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eLINEDEFS;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "LINEDEFS") != 0)
	{
		return false;
	}

	int iLinedefSizeInBytes = sizeof(WADLinedef);
	int iLinedefCount = m_WADDirectories[iMapIndex].LumpSize / iLinedefSizeInBytes;

	WADLinedef linedef;
	for (int i = 0; i < iLinedefCount; ++i)
	{
		m_Reader.ReadLinedefData(m_pWADData.get(), m_WADDirectories[iMapIndex].LumpOffset + i * iLinedefSizeInBytes, linedef);
		pMap->AddLinedef(linedef);
	}

	return true;
}

bool WADLoader::ReadBlockMap(Map* pmap)
{
	int iMapIndex = FindMapIndex(pmap);
	if (iMapIndex == -1)
	{
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eBLOCKMAP;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "BLOCKMAP") != 0)
	{
		return false;
	}
	BlockMapHeader header;
	BlockMapOffset offset;


	m_Reader.ReadBlockMapHeader(m_pWADData.get(), m_WADDirectories[iMapIndex].LumpOffset,header);
	short noffset = 8 + 2 * (header.nmColum * header.nmLine -1 );
	m_Reader.ReadBlockMapOffset(m_pWADData.get(), m_WADDirectories[iMapIndex].LumpOffset+ 8, offset,noffset);

	//pmap->AddBlock(Blockmap(header,offset));
	return true;
}

bool WADLoader::ReadMapThings(Map* pMap)
{
	int iMapIndex = FindMapIndex(pMap);

	if (iMapIndex == -1)
	{
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eTHINGS;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "THINGS") != 0)
	{
		return false;
	}


	int iThingsSizeInBytes = sizeof(Thing);
	int iThingsCount = m_WADDirectories[iMapIndex].LumpSize / iThingsSizeInBytes;

	Thing thing;
	for (int i = 0; i < iThingsCount; ++i)
	{
		m_Reader.ReadThingData(m_pWADData.get(), m_WADDirectories[iMapIndex].LumpOffset + i * iThingsSizeInBytes, thing);
		(pMap->GetThings())->AddThing(thing);
	}

	return true;
}

bool WADLoader::ReadMapNodes(Map* pMap)
{
	int iMapIndex = FindMapIndex(pMap);

	if (iMapIndex == -1)
	{
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eNODES;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "NODES") != 0)
	{
		return false;
	}

	int iNodesSizeInBytes = sizeof(Node);
	int iNodesCount = m_WADDirectories[iMapIndex].LumpSize / iNodesSizeInBytes;

	Node node;
	for (int i = 0; i < iNodesCount; ++i)
	{
		m_Reader.ReadNodeData(m_pWADData.get(), m_WADDirectories[iMapIndex].LumpOffset + i * iNodesSizeInBytes, node);

		pMap->AddNode(node);
	}

	return true;
}

bool WADLoader::ReadMapSubsectors(Map* pMap)
{
	int iMapIndex = FindMapIndex(pMap);

	if (iMapIndex == -1)
	{
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eSSECTORS;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "SSECTORS") != 0)
	{
		return false;
	}

	int iSubsectorsSizeInBytes = sizeof(Subsector);
	int iSubsectorsCount = m_WADDirectories[iMapIndex].LumpSize / iSubsectorsSizeInBytes;

	Subsector subsector;
	for (int i = 0; i < iSubsectorsCount; ++i)
	{
		m_Reader.ReadSubsectorData(m_pWADData.get(), m_WADDirectories[iMapIndex].LumpOffset + i * iSubsectorsSizeInBytes, subsector);

		pMap->AddSubsector(subsector);
	}

	return true;
}

bool WADLoader::ReadMapSegs(Map* pMap)
{
	int iMapIndex = FindMapIndex(pMap);

	if (iMapIndex == -1)
	{
		return false;
	}

	iMapIndex += EMAPLUMPSINDEX::eSEAGS;

	if (strcmp(m_WADDirectories[iMapIndex].LumpName, "SEGS") != 0)
	{
		return false;
	}

	int iSegsSizeInBytes = sizeof(WADSeg);
	int iSegsCount = m_WADDirectories[iMapIndex].LumpSize / iSegsSizeInBytes;

	WADSeg seg;
	for (int i = 0; i < iSegsCount; ++i)
	{
		m_Reader.ReadSegData(m_pWADData.get(), m_WADDirectories[iMapIndex].LumpOffset + i * iSegsSizeInBytes, seg);

		pMap->AddSeg(seg);
	}

	return true;
}

bool WADLoader::LoadPalette(std::vector<WADPalette>& allPalette)
{
	std::cout << "Info: Loading PLAYPAL (Color Palettes)" << std::endl;
	int iPlaypalIndex = FindLumpByName("PLAYPAL");

	if (strcmp(m_WADDirectories[iPlaypalIndex].LumpName, "PLAYPAL") != 0)
	{
		return false;
	}

	WADPalette palette;
	for (int i = 0; i < 14; ++i)
	{
		m_Reader.ReadPalette(m_pWADData.get(), m_WADDirectories[iPlaypalIndex].LumpOffset + (i * 3 * 256), palette);
		allPalette.push_back(palette);
	}

	return true;
}

bool WADLoader::LoadPatch(const std::string& sPatchName)
{
	AssetsManager* pAssetsManager = AssetsManager::GetInstance();
	int iPatchIndex = FindLumpByName(sPatchName);
	if (strcmp(m_WADDirectories[iPatchIndex].LumpName, sPatchName.c_str()) != 0)
	{
		return false;
	}

	WADPatchHeader PatchHeader;
	m_Reader.ReadPatchHeader(m_pWADData.get(), m_WADDirectories[iPatchIndex].LumpOffset, PatchHeader);

//	Patch* pPatch = pAssetsManager->AddPatch(sPatchName, PatchHeader);

	PatchColumnData PatchColumn;

	for (int i = 0; i < PatchHeader.Width; ++i)
	{
		int Offset = m_WADDirectories[iPatchIndex].LumpOffset + PatchHeader.pColumnOffsets[i];
		//pPatch->AppendColumnStartIndex();
		do
		{
			Offset = m_Reader.ReadPatchColumn(m_pWADData.get(), Offset, PatchColumn);
		//	pPatch->AppendPatchColumn(PatchColumn);
		} while (PatchColumn.TopDelta != 0xFF);
	}

	return true;
}

bool WADLoader::LoadTextures(const std::string& sTextureName)
{
	AssetsManager* pAssetsManager = AssetsManager::GetInstance();
	int iTextureIndex = FindLumpByName(sTextureName);

	if (iTextureIndex < 0)
	{
		return false;
	}

	if (strcmp(m_WADDirectories[iTextureIndex].LumpName, sTextureName.c_str()) != 0)
	{
		return false;
	}

	WADTextureHeader TextureHeader;
	m_Reader.ReadTextureHeader(m_pWADData.get(), m_WADDirectories[iTextureIndex].LumpOffset, TextureHeader);
	std::string texturesNameList = "";
	WADTextureData TextureData;
	for (int i = 0; i < TextureHeader.TexturesCount; ++i)
	{
		m_Reader.ReadTextureData(m_pWADData.get(), m_WADDirectories[iTextureIndex].LumpOffset + TextureHeader.pTexturesDataOffset[i], TextureData);

		for (int j = 0; j < 9; j++)
		{
			texturesNameList += TextureData.TextureName[j];
		}
		texturesNameList += "\n";
//		pAssetsManager->AddTexture(TextureData);
		delete[] TextureData.pTexturePatch;
		TextureData.pTexturePatch = nullptr;
	}

	std::ofstream outfile;
	outfile.open(std::filesystem::path("Resources/TexturesNameList.txt"));
	outfile << texturesNameList;
	outfile.close();
	delete[] TextureHeader.pTexturesDataOffset;
	TextureHeader.pTexturesDataOffset = nullptr;
	return true;
}

bool WADLoader::LoadPNames()
{
	AssetsManager* pAssetsManager = AssetsManager::GetInstance();
	int iPNameIndex = FindLumpByName("PNAMES");
	if (strcmp(m_WADDirectories[iPNameIndex].LumpName, "PNAMES") != 0)
	{
		return false;
	}

	WADPNames PNames;
	m_Reader.ReadPName(m_pWADData.get(), m_WADDirectories[iPNameIndex].LumpOffset, PNames);
	char Name[9];
	Name[8] = '\0';
	for (int i = 0; i < PNames.PNameCount; ++i)
	{
		m_Reader.Read8Characters(m_pWADData.get(), PNames.PNameOffset, Name);
		pAssetsManager->AddPName(Name);
		PNames.PNameOffset += 8;
	}

	return true;
}