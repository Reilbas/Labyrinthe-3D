#include "MeshMaker.h"

mesh MeshMaker::Cube(float x, float y, float z){
    mesh m;
    m.tris = {
    	// SOUTH
		{ x, y, z,                  x, y, (z+1.0f),                 (x+1.0f), y, (z+1.0f)           },
		{ x, y, z,                  (x+1.0f), y, (z+1.0f),          (x+1.0f), y, z                  },

		// EAST                                                      
		{ (x+1.0f), y, z,           (x+1.0f), y, (z+1.0f),          (x+1.0f), (y+1.0f), (z+1.0f)    },
		{ (x+1.0f), y, z,           (x+1.0f), (y+1.0f), (z+1.0f),   (x+1.0f), (y+1.0f), z           },

		// NORTH                                                     
		{ (x+1.0f), (y+1.0f), z,    (x+1.0f), (y+1.0f), (z+1.0f),   x, (y+1.0f), (z+1.0f)           },
		{ (x+1.0f), (y+1.0f), z,    x, (y+1.0f), (z+1.0f),          x, (y+1.0f), z                  },

		// WEST                                                      
		{ x, (y+1.0f), z,           x, (y+1.0f), (z+1.0f),          x, y, (z+1.0f)                  },
		{ x, (y+1.0f), z,           x, y, (z+1.0f),                 x, y, z                         },

		// TOP                                                       
		{ x, y, (z+1.0f),           x, (y+1.0f), (z+1.0f),          (x+1.0f), (y+1.0f), (z+1.0f)    },
		{ x, y, (z+1.0f),           (x+1.0f), (y+1.0f), (z+1.0f),   (x+1.0f), y, (z+1.0f)           },

		// BOTTOM                                                    
		{ (x+1.0f), (y+1.0f), z,    x, (y+1.0f), z,                 x, y, z                         },
		{ (x+1.0f), (y+1.0f), z,    x, y, z,                        (x+1.0f), y, z                  },
    };
    return m;
}

mesh MeshMaker::fromObj(std::string nomfic, float x, float y, float z ,float size){
	mesh m;

	std::ifstream f(nomfic);
	if (!f.is_open())
		return m;

	// Local cache of verts
	std::vector<vec3d> verts;

	while (!f.eof()){
		char line[128];
		f.getline(line, 128);

		std::stringstream s;
		s << line;

		char junk;

		if (line[0] == 'v'){
			vec3d v;
			s >> junk >> v.x >> v.y >> v.z;

			v.x = x + (size * v.x);
			v.y = y + (size * v.y);
			v.z = z + (size * v.z);
			verts.push_back(v);
		}

		if (line[0] == 'f'){
			int f[3];
			s >> junk >> f[0] >> f[1] >> f[2];
			m.tris.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
		}
	}

    return m;
}