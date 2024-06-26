#include <CassouletEngineLibrarie/System/Libs.h>
#include <CassouletEngineLibrarie/Doom/Header.h>


struct lump {
	char* name;
	uint8_t* data;
	uint32_t size;

};

 struct wad {
	char* id;
	uint32_t num_lumps;

	lump* lumps;
} ;

int  wad_load_from_file(const char* filename, wad* wad);
void wad_free(wad* wad);

int wad_find_lump(const char* lumpname, const wad* wad);
int wad_read_map(const char* mapname, map* map, const wad* wad);