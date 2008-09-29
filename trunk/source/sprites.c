#include <oslib/oslib.h>
#include "sprites.h"

SPRITE *createSprite(OSL_IMAGE *img, int width, int height, int interval) {
	SPRITE *spt;
	spt = (SPRITE*)malloc(sizeof(SPRITE));
	if (!spt){
		if (spt) free(spt);
		return NULL;
	}
	memset(spt, 0, sizeof(SPRITE));
	spt->img = img;
	spt->width = width;
	spt->height = height;
	spt->interval = interval;
	if( img->isCopy ){
		spt->cols = (img->offsetX1 - img->offsetX0) / spt->width;
		spt->rows = (img->offsetY1 - img->offsetY0) / spt->height;
		spt->imgx0 = spt->offsetx = spt->img->offsetX0;
		spt->imgy0 = spt->offsety = spt->img->offsetY0;
		spt->imgx1 = spt->img->offsetX1;
		spt->imgy1 = spt->img->offsetY1;
	} else {
		spt->cols = img->sizeX / spt->width;
		spt->rows = img->sizeY / spt->height;
		spt->imgx0 = spt->offsetx = 0;
		spt->imgy0 = spt->offsety = 0;
		spt->imgx1 = spt->img->sizeX;
		spt->imgy1 = spt->img->sizeY;
	}
	spt->max = spt->rows * spt->cols;
	spt->start = spt->current=1;
	spt->end = spt->max;
	spt->counter = 0;
	spt->startx = spt->offsetx;
	spt->starty = spt->offsety;
	spt->endx = (spt->cols-1)*spt->width;
	spt->endy = (spt->rows-1)*spt->height;
	spt->flipv = 0;
	spt->fliph = 0;
	spt->reverse = 0;
	spt->playing = 1;
	if(img->isCopy){ spriteSetFrameBounds(spt, spt->start, spt->end); }
	return spt;

}

void spriteDraw(SPRITE *spt) {
	if( spt->playing ){ spriteNextFrame(spt); }
	oslSetImageTileSize(spt->img,spt->offsetx,spt->offsety,spt->width,spt->height);
	spt->img->stretchX = spt->fliph ? -spt->width : spt->width;
	spt->img->stretchY = spt->flipv ? -spt->height : spt->height;
	oslDrawImage(spt->img);
}

void spriteDrawXY(SPRITE *spt, int x, int y) {
	spt->img->x = x;
	spt->img->y = y;
	spriteDraw(spt);
}

int spriteNextFrame(SPRITE *spt) {
	if( !(++spt->counter % spt->interval) && spt->playing ){
		if(spt->reverse){
			spt->offsetx -= spt->width;
			if(spt->offsetx < spt->imgx0){
				spt->offsetx = spt->width * (spt->cols-1) + spt->imgx0;
				spt->offsety -= spt->height;
			}
			if( spt->offsety < spt->starty ||
				(spt->offsety == spt->starty && spt->offsetx < spt->startx) ){
				spt->offsetx = spt->endx;
				spt->offsety = spt->endy;
			}
		} else {
			spt->offsetx += spt->width;
			if( spt->offsetx >= spt->imgx1 ){
				spt->offsetx = (spt->img->isCopy ? spt->imgx0 : 0);
				spt->offsety += spt->height;
			}
			if( spt->offsety > spt->endy ||
				(spt->offsety == spt->endy && spt->offsetx > spt->endx) ){
				spt->offsetx = spt->startx;
				spt->offsety = spt->starty;
			}
		}
		if( spt->img->isCopy ){
			spt->current = ((spt->offsetx - spt->imgx0) ? (spt->offsetx - spt->imgx0)/spt->width + 1 : 1) +
				((spt->offsety - spt->imgy0) ? (spt->imgx1 - spt->imgx0)/spt->width * (spt->offsety - spt->imgy0)/spt->height : 0);
		} else {
			spt->current = (spt->offsetx ? spt->offsetx/spt->width + 1 : 1) +
				(spt->offsety? (spt->imgx1 - spt->imgx0)/spt->width * spt->offsety/spt->height : 0);
		}
		spt->counter=0;
	}
	return spt->current;
}

int spriteSetFrame(SPRITE *spt, unsigned int frame) {
	if(frame < 1 || frame > spt->max) return 0;
	spriteSetFrameXY(spt, frame, &spt->offsetx, &spt->offsety );
	spt->current = frame;
	return frame;
}

int spriteSetFrameBounds(SPRITE *spt, unsigned int start, unsigned int end) {
	if(start > end || end > spt->max) return 0;
	spt->start = start;
	spt->end = end;

	spriteSetFrameXY(spt, start, &spt->startx, &spt->starty);
	spriteSetFrameXY(spt, end, &spt->endx, &spt->endy);

	if( spt->current > end || spt->current < start ){
		spt->offsetx =	spt->startx;
		spt->offsety =	spt->starty;
		spt->current = start;
	}
	return spt->current;
}

int spriteSetFrameXY(SPRITE *spt, unsigned int frame, int *x, int *y) {
	int col = frame % spt->cols;
	if(col == 0){ col = spt->cols; }
	*x = (col-1) * spt->width + (spt->img->isCopy ? spt->imgx0 :0);
	int row = frame / spt->cols;
	if(frame % spt->cols == 0){ row--; }
	*y = row * spt->height + (spt->img->isCopy ? spt->imgy0 :0);
	return frame;
}

void spritePlay(SPRITE *spt){
	spt->playing = 1;
}

void spriteStop(SPRITE *spt){
	spt->playing = 0;
}
