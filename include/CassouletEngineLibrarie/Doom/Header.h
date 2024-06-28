#pragma once
#include <CassouletEngineLibrarie/System/Libs.h>

#define LINEDEF_FLAGS_TWO_SIDED 0x0004

struct sector {
	int16_t floor, ceiling;
};

 struct sidedef {
	 uint16_t sector_idx;
 };

 struct linedef {
	 uint16_t start_idx, end_idx;
	 uint16_t flags;
	 uint16_t front_sidedef, back_sidedef;
 };

 struct map {
	 size_t  num_vertices;
	 glm::vec2* vertices;
	 glm::vec2  min, max;

	 size_t     num_linedefs;
	 linedef* linedefs;

	 size_t     num_sidedefs;
	 sidedef* sidedefs;

	 size_t    num_sectors;
	 sector* sectors;
 };

