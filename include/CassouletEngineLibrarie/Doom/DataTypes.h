#pragma once
#include <CassouletEngineLibrarie/Doom/Angle.h>


// Subsector Identifier is the 16th bit which
// indicate if the node ID is a subsector.
// The node ID is stored as uint16
// 0x8000 in binary 1000000000000000
#define SUBSECTORIDENTIFIER 0x8000
const float SCALE = 2.5f;

const int MAPBLOCKUNITS = 128;




inline int FixedDiv(int16_t a, int16_t b)
{
	if ((abs(a) >> 14) >= abs(b))
	{
		return (a ^ b) < 0 ? INT_MIN : INT_MAX;
	}
	else
	{
		int64_t result;

		result = ((int64_t)a) / b;

		return (int)result;
	}
}


enum EMAPLUMPSINDEX
{
	eName,
	eTHINGS,
	eLINEDEFS,
	eSIDEDDEFS,
	eVERTEXES,
	eSEAGS,
	eSSECTORS,
	eNODES,
	eSECTORS,
	eREJECT,
	eBLOCKMAP,
	eCOUNT
};

enum ELINEDEFFLAGS
{
	eBLOCKING = 0,
	eBLOCKMONSTERS = 1,
	eTWOSIDED = 2,
	eDONTPEGTOP = 4,
	eDONTPEGBOTTOM = 8,
	eSECRET = 16,
	eSOUNDBLOCK = 32,
	eDONTDRAW = 64,
	eDRAW = 128
};

enum ELINEDEFDLOPETYPE
{
	ST_HORIZONTAL,
	ST_VERTICAL,
	ST_POSITIVE,
	ST_NEGATIVE

};


enum
{
	BOXTOP,
	BOXBOTTOM,
	BOXLEFT,
	BOXRIGHT
};

struct Header
{
	char WADType[5];
	uint32_t DirectoryCount;
	uint32_t DirectoryOffset;
};

struct Directory
{
	uint32_t LumpOffset;
	uint32_t LumpSize;
	char LumpName[9];
};

struct Thing
{
	int16_t XPosition;
	int16_t YPosition;
	uint16_t Angle;
	uint16_t Type;
	uint16_t Flags;
};

struct Vertex
{
	int16_t XPosition;
	int16_t YPosition;
};

struct WADSector
{
	int16_t FloorHeight;
	int16_t CeilingHeight;
	char FloorTexture[8];
	char CeilingTexture[8];
	uint16_t Lightlevel;
	uint16_t Type;
	uint16_t Tag;
};

struct Sector
{
	int16_t FloorHeight;
	int16_t CeilingHeight;
	char FloorTexture[9];
	char CeilingTexture[9];
	uint16_t Lightlevel;
	uint16_t Type;
	uint16_t Tag;
};

struct WADSidedef
{
	int16_t XOffset;
	int16_t YOffset;
	char UpperTexture[8];
	char LowerTexture[8];
	char MiddleTexture[8];
	uint16_t SectorID;
};

struct Sidedef
{
	int16_t XOffset;
	int16_t YOffset;
	char UpperTexture[9];
	char LowerTexture[9];
	char MiddleTexture[9];
	Sector* pSector;
};

struct WADLinedef
{
	uint16_t StartVertexID;
	uint16_t EndVertexID;
	uint16_t Flags;
	uint16_t LineType;
	uint16_t SectorTag;
	uint16_t RightSidedef; //0xFFFF means there is no sidedef
	uint16_t LeftSidedef;  //0xFFFF means there is no sidedef
};

struct Linedef
{
	Vertex* pStartVertex;
	Vertex* pEndVertex;
	int16_t dx;
	int16_t dy;
	uint16_t Flags;
	uint16_t LineType;
	uint16_t SectorTag;
	Sidedef* pRightSidedef;
	Sidedef* pLeftSidedef;
	int16_t bbox[4];
	ELINEDEFDLOPETYPE slopeType;
};

struct WADSeg
{
	uint16_t StartVertexID;
	uint16_t EndVertexID;
	uint16_t SlopeAngle;
	uint16_t LinedefID;
	uint16_t Direction; // 0 same as linedef, 1 opposite of linedef
	uint16_t Offset; // distance along linedef to start of seg
};

struct Seg
{
	Vertex* pStartVertex;
	Vertex* pEndVertex;
	Angle SlopeAngle;
	Linedef* pLinedef;
	uint16_t Direction; // 0 same as linedef, 1 opposite of linedef
	uint16_t Offset; // distance along linedef to start of seg    
	Sector* pRightSector;
	Sector* pLeftSector;
};

struct Subsector
{
	Sector* pSector;
	uint16_t SegCount;
	uint16_t FirstSegID;
};

struct Node
{
	int16_t XPartition;
	int16_t YPartition;
	int16_t ChangeXPartition;
	int16_t ChangeYPartition;

	int16_t RightBoxTop;
	int16_t RightBoxBottom;
	int16_t RightBoxLeft;
	int16_t RightBoxRight;

	int16_t LeftBoxTop;
	int16_t LeftBoxBottom;
	int16_t LeftBoxLeft;
	int16_t LeftBoxRight;

	uint16_t RightChildID;
	uint16_t LeftChildID;
};

struct WADPatchHeader
{
	uint16_t Width;
	uint16_t Height;
	int16_t LeftOffset;
	int16_t TopOffset;
	uint32_t* pColumnOffsets;
};

struct PatchColumnData
{
	uint8_t TopDelta;
	uint8_t Length;
	uint8_t	PaddingPre;
	uint8_t* pColumnData;
	uint8_t PaddingPost;
};

struct WADPNames
{
	uint32_t PNameCount;
	uint32_t PNameOffset;
};

struct WADTextureHeader
{
	uint32_t TexturesCount;
	uint32_t TexturesOffset;
	uint32_t* pTexturesDataOffset;
};

struct WADTexturePatch
{
	int16_t XOffset;
	int16_t YOffset;
	uint16_t PNameIndex;
	uint16_t StepDir; // Unused value.
	uint16_t ColorMap; // Unused value.
};

struct WADTextureData
{
	char TextureName[9];
	uint32_t Flags;
	uint16_t Width;
	uint16_t Height;
	uint32_t ColumnDirectory; // Unused value.
	uint16_t PatchCount;
	WADTexturePatch* pTexturePatch;
};

struct WADPalette
{
	sf::Color Colors[256];
};

struct BlockMapHeader
{
	uint16_t originX;
	uint16_t originY;
	uint16_t nmColum;
	uint16_t nmLine;
};

struct BlockMapOffset
{
	uint16_t offset0;
	uint16_t offset1;
	uint16_t offsetn;
};

double static  CalculateDistance(sf::Vector2f& a, sf::Vector2f& b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

inline  bool isPointBetweenLines(const sf::Vector2f& point, const Linedef& line) {
	int crossProduct = (point.y - line.pStartVertex->YPosition) * (line.pEndVertex->XPosition - line.pStartVertex->XPosition) -
		(point.x - line.pStartVertex->XPosition) * (line.pEndVertex->YPosition - line.pStartVertex->YPosition);

	if (crossProduct != 0) {
		return false; // Le point n'est pas sur la ligne
	}

	int dotProduct = (point.x - line.pStartVertex->XPosition) * (line.pEndVertex->XPosition - line.pStartVertex->XPosition) +
		(point.y - line.pStartVertex->YPosition) * (line.pEndVertex->YPosition - line.pStartVertex->YPosition);
	if (dotProduct < 0) {
		return false; // Le point est derrière le début de la ligne
	}

	int squaredLength = (line.pEndVertex->XPosition - line.pStartVertex->XPosition) * (line.pEndVertex->XPosition - line.pStartVertex->XPosition) +
		(line.pEndVertex->YPosition - line.pStartVertex->YPosition) * (line.pEndVertex->YPosition - line.pStartVertex->YPosition);
	if (dotProduct > squaredLength) {
		return false; // Le point est après la fin de la ligne
	}

	return true; // Le point est sur la ligne ou entre le début et la fin de la ligne
}
