#include <CassouletEngineLibrarie/Doom/Map.h>
#include <CassouletEngineLibrarie/Doom/Wad.h>
#include <CassouletEngineLibrarie/System/Helper.h>
#include <CassouletEngineLibrarie/Doom/Header.h>


#define READ_I16(buffer, offset)                                               \
  ((buffer)[(offset)] | ((buffer)[(offset + 1)] << 8))

#define READ_I32(buffer, offset)                                               \
  ((buffer)[(offset)] | ((buffer)[(offset + 1)] << 8) |                        \
   ((buffer)[(offset + 2)] << 16) | ((buffer)[(offset + 3)] << 24))

int wad_load_from_file(const char* filename, wad* wad) {
	if (wad == NULL) { return 1; }

	FILE* fp = fopen(filename, "rb");
	if (fp == NULL) { return 2; }

	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	uint8_t* buffer = new uint8_t(size);
	fread(buffer, size, 1, fp);
	fclose(fp);

	// Read header
	if (size < 12) { return 3; }
	wad->id = new char[5];
	memcpy(wad->id, buffer, 4);
	wad->id[4] = 0; // null terminator

	wad->num_lumps =READ_I16(buffer, 4);
	uint32_t directory_offset =READ_I16(buffer, 8);

	wad->lumps = new lump[ wad->num_lumps];
	for (int i = 0; i < wad->num_lumps; i++) {
		uint32_t offset = directory_offset + i * 16;

		uint32_t lump_offset =READ_I16(buffer, offset);
		wad->lumps[i].size =READ_I16(buffer, offset + 4);
		wad->lumps[i].name = new char[9];
		memcpy(wad->lumps[i].name, &buffer[offset + 8], 8);
		wad->lumps[i].name[8] = 0; // null terminator

		wad->lumps[i].data = new uint8_t[wad->lumps[i].size];
		memcpy(wad->lumps[i].data, &buffer[lump_offset], wad->lumps[i].size);
	}

	free(buffer);
	return 0;
}

void wad_free(wad* wad) {
	if (wad == NULL) { return; }

	for (int i = 0; i < wad->num_lumps; i++) {
		free(wad->lumps[i].data);
	}

	free(wad->id);
	free(wad->lumps);

	wad->num_lumps = 0;
}

int wad_find_lump(const char* lumpname, const wad* wad) {
	for (int i = 0; i < wad->num_lumps; i++) {
		if (strcmp(wad->lumps[i].name, lumpname) == 0) { return i; }
	}

	return -1;
}

#define THINGS_IDX   1
#define LINEDEFS_IDX 2
#define SIDEDEFS_IDX 3
#define VERTEXES_IDX 4
#define SEGS_IDX     5
#define SSECTORS_IDX 6
#define NODES_IDX    7
#define SECTORS_IDX  8



void read_vertices(map* pmap, const lump* plump) 
{
	pmap->num_vertices = plump->size / 4; // each vertex is 2+2=4 bytes
	pmap->vertices = new glm::vec2[pmap->num_vertices];

	pmap->min = glm::vec2 (INFINITY, INFINITY );
	pmap->max = glm::vec2(-INFINITY, -INFINITY);

	for (int i = 0, j = 0; i < plump->size; i += 4, j++) {
		pmap->vertices[j].x =Read2Bytes(plump->data, i);
		pmap->vertices[j].y =Read2Bytes(plump->data, i + 2);

		if (pmap->vertices[j].x < pmap->min.x) { pmap->min.x = pmap->vertices[j].x; }
		if (pmap->vertices[j].y < pmap->min.y) { pmap->min.y = pmap->vertices[j].y; }
		if (pmap->vertices[j].x > pmap->max.x) { pmap->max.x = pmap->vertices[j].x; }
		if (pmap->vertices[j].y > pmap->max.y) { pmap->max.y = pmap->vertices[j].y; }
	}
}

void read_linedefs(map* map, const lump* lump) {
	map->num_linedefs = lump->size / 14; // each linedef is 14 bytes
	map->linedefs = new linedef[ map->num_linedefs];

	for (int i = 0, j = 0; i < lump->size; i += 14, j++) {
		map->linedefs[j].start_idx = Read2Bytes(lump->data, i);
		map->linedefs[j].end_idx = Read2Bytes(lump->data, i + 2);
		map->linedefs[j].flags = Read2Bytes(lump->data, i + 4);
		map->linedefs[j].front_sidedef = Read2Bytes(lump->data, i + 10);
		map->linedefs[j].back_sidedef = Read2Bytes(lump->data, i + 12);
	}
}

void read_sidedefs(map* map, const lump* lump) {
	map->num_sidedefs = lump->size / 30; // each sidedef is 30 bytes
	map->sidedefs = new sidedef[map->num_sidedefs];

	for (int i = 0, j = 0; i < lump->size; i += 30, j++) {
		map->sidedefs[j].sector_idx = READ_I16(lump->data, i + 28);
	}
}

void read_sectors(map* pmap, const lump* plump) {
	pmap->num_sectors = plump->size / 26; // each sector is 26 bytes
	pmap->sectors = new sector[pmap->num_sectors];

	for (int i = 0, j = 0; i < plump->size; i += 26, j++) {
		pmap->sectors[j].floor = (int16_t)READ_I16(plump->data, i);
		pmap->sectors[j].ceiling = (int16_t)READ_I16(plump->data, i + 2);
	}
}

int wad_read_map(const char* mapname, map* map, const wad* wad) {
	int map_index = wad_find_lump(mapname, wad);
	if (map_index < 0) { return 1; }

	read_vertices(map, &wad->lumps[map_index + VERTEXES_IDX]);
	read_linedefs(map, &wad->lumps[map_index + LINEDEFS_IDX]);
	read_sidedefs(map, &wad->lumps[map_index + SIDEDEFS_IDX]);
	read_sectors(map, &wad->lumps[map_index + SECTORS_IDX]);

	return 0;
}