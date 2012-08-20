#ifndef __nbody_H
#define __nbody_H

#include <GL/glew.h>
#include "types.h"

class nbody {
	public:
		nbody(int nodes);
		~nbody();

		void draw();
		void reset();
		void tick();
		void locate(float x, float y, float z);

	private:
		vec3 loc;
		vec3 *pos;
		vec3 *vel;
		vec3 *acc;
		vec3 *accT;
		int nodes;
		unsigned int randSeed;

		float sfrand(void);
		inline void accel(int i, vec3 &acc);
		inline void selfGravitation(int i, vec3 &acc);
		inline vec3 force(vec3 &a, vec3 &b);

		static const float dt = 0.0001f;
};

#endif
