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

mesh MeshMaker::Pyramide(float x, float y, float z){
    mesh m;
    m.tris = {
    	// SOUTH
		{ x, y, z,                  x, y, (z+0.125f),                 (x+0.125f), y, (z+0.125f)           },
		{ x, y, z,                  (x+0.125f), y, (z+0.125f),          (x+0.125f), y, z                  },

		// EAST                                                      
		{ (x+0.125f), y, z,           (x+0.125f), y, (z+0.125f),          (x+0.125f), (y+0.125f), (z+0.125f)    },
		{ (x+0.125f), y, z,           (x+0.125f), (y+0.125f), (z+0.125f),   (x+0.125f), (y+0.125f), z           },

		// NORTH                                                     
		{ (x+0.125f), (y+0.125f), z,    (x+0.125f), (y+0.125f), (z+0.125f),   x, (y+0.125f), (z+0.125f)           },
		{ (x+0.125f), (y+0.125f), z,    x, (y+0.125f), (z+0.125f),          x, (y+0.125f), z                  },

		// WEST                                                      
		{ x, (y+0.125f), z,           x, (y+0.125f), (z+0.125f),          x, y, (z+0.125f)                  },
		{ x, (y+0.125f), z,           x, y, (z+0.125f),                 x, y, z                         },

		// TOP                                                       
		{ x, y, (z+0.125f),           x, (y+0.125f), (z+0.125f),          (x+0.125f), (y+0.125f), (z+0.125f)    },
		{ x, y, (z+0.125f),           (x+0.125f), (y+0.125f), (z+0.125f),   (x+0.125f), y, (z+0.125f)           },

		// BOTTOM                                                    
		{ (x+0.125f), (y+0.125f), z,    x, (y+0.125f), z,                 x, y, z                         },
		{ (x+0.125f), (y+0.125f), z,    x, y, z,                        (x+0.125f), y, z                  },
    };
    return m;
}