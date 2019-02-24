#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "defines.h"
#include "gamelogic.h"
map m; 
vec2 origin;
// init level
void init_logic(){
	origin.x = 0;
	origin.y = 0;
	m.height=16;
	m.width=16;
	m.blocks = (char *) malloc(sizeof(char) * m.width * m.height );
	char tmp_blocks[]={
	 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	 1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
	 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	 1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
	 1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
	 1,0,0,0,0,0,2,3,0,0,0,0,0,0,0,1,
	 1,0,0,0,0,0,0,0,2,3,0,0,0,0,0,1,
	 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	};
	for (int i=0; i<m.width * m.height; i++){
		m.blocks[i] = tmp_blocks[i];
	}
	origin.x = 0;
	origin.y = 0;

}
// 
void destroy_logic(){
	free(m.blocks);
}


// return block value from world coordinates p 
char get_block_type(vec2 p){
	char x = floor(p.x / 64.f);
	char y = floor(p.y / 64.f);
	return m.blocks[x + y * m.width];
}

// returns distance between two points p and q
float distance( vec2 p, vec2 q ){
	float dx = p.x - q.x;
	float dy = p.y - q.y;
	return sqrt (dx*dx + dy*dy);
}
vec2 get_unit_vector(float angle){
	vec2 uvec;
	uvec.x = cos(angle);
	uvec.y = sin(angle);
	return uvec;
}
vec2 vec2_scalar_mult(vec2 p, float t){
	vec2 q = {.x = t * p.x, .y = t * p.y};
	return q;
}
vec2 vec2_add(vec2 p, vec2 q){
	vec2 newvec = {.x = p.x + q.x, .y = p.y + q.y};
	return newvec;
}
void move_vec(vec2 * v, float angle, float d){
	vec2 uvec = get_unit_vector(angle);
	v->x += uvec.x * d;
	v->y += uvec.y *d;
}
vec2 get_ray_intersection(cam c){
	time_t t = clock();
	vec2 uvec;
	vec2 newvec;
	char blocktype;
	uvec = get_unit_vector(c.angle);
	for (int i = 0; i < RENDER_DIST; i+=1){
		newvec.x = c.position.x + uvec.x * i;
		newvec.y = c.position.y + uvec.y * i;
		blocktype = get_block_type(newvec);	
		if (blocktype != 0){
			return newvec;
		}
	}
	newvec.x = 0;
	newvec.y = 0;
	return newvec ;
}
