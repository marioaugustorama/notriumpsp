typedef struct {
	OSL_IMAGE *img;
	int width, height, cols, rows, offsetx, offsety;
	int start, end, current, max, counter, startx, starty, endx, endy;
	int imgx0,imgy0,imgx1,imgy1;
	bool flipv, fliph, reverse, playing;
	int interval;
} SPRITE;

SPRITE *createSprite(OSL_IMAGE *img, int width, int height, int interval);
void spriteDraw(SPRITE *spt);
void spriteDrawXY(SPRITE *spt, int x, int y);
int spriteNextFrame(SPRITE *spt);
int spriteSetFrame(SPRITE *spt, unsigned int frame);
int spriteSetFrameBounds(SPRITE *spt, unsigned int start, unsigned int end);
int spriteSetFrameXY(SPRITE *spt, unsigned int frame, int *x, int *y);
void spritePlay(SPRITE *spt);
void spriteStop(SPRITE *spt);
