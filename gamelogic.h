// gamelogic.h
typedef struct {
	float x;
	float y;
} vec2;

typedef struct {
  vec2 position;
  float angle;
} cam;

typedef struct {
	int width;
	int height;
	char * blocks;
} map;
void init_logic();
void destroy_logic();
char get_block_type(vec2 p);
float distance( vec2 p, vec2 q );
vec2 vec2_scalar_mult(vec2 p, float t);
vec2 vec2_add(vec2 p, vec2 q);
vec2 get_ray_intersection(cam c);
void move_vec(vec2 * v, float angle, float d);

