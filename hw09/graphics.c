/**
* @file graphics.c
* @author Peter Lee
* @date DATE HERE
* @brief A graphics library for drawing geometry, for Homework 9 of Georgia Tech
*        CS 2110, Fall 2018.
*/

// Please take a look at the header file below to understand what's required for
// each of the functions.
#include "graphics.h"
// Don't touch this. It's used for sorting for the drawFilledPolygon function.
int int_cmp(const void *a, const void *b)
{
    const int *ia = (const int *)a;
    const int *ib = (const int *)b;
    return *ia  - *ib;
}

Pixel noFilter(Pixel c) {
    // Don't touch this.
    return c;
}

#define coordtoidx(x,y,width) ((width*y) +x)
#define signum(x) ((x > 0) - (x < 0))

// TODO: Complete according to the prototype in graphics.h
Pixel greyscaleFilter(Pixel c) {
	Pixel r = c & 0x001f;
	Pixel g = (c>>5) & 0x001f;
	Pixel b = (c>>10) & 0x001f;
	Pixel n = ((r*77)+(g*151)+(b*28)) >> 8;
	c = n + (n<<5) + (n<<10);
    return c;
}

// TODO: Complete according to the prototype in graphics.h
Pixel redOnlyFilter(Pixel c) {
	Pixel red = c & 0x001f;
    return red;
}

// TODO: Complete according to the prototype in graphics.h
Pixel brighterFilter(Pixel c) {
	Pixel r = c & 0x001f;
	Pixel g = (c>>5) & 0x001f;
	Pixel b = (c>>10) & 0x001f;
	r = r + ((31 - r) >> 1);
	g = g + ((31 - g) >> 1);
	b = b + ((31 - b) >> 1);
	c = (b<<10) + (g<<5) + (r);
    return c;
}


// TODO: Complete according to the prototype in graphics.h
void drawPixel(Screen *screen, Vector coordinates, Pixel pixel) {
	int width = screen->size.x;
	int height = screen->size.y;
	int index = coordinates.x + width*coordinates.y;
	if (coordinates.x < 0 || coordinates.y < 0) {
	} else if (coordinates.x >= width || coordinates.y >= height) {
	} else {
		screen->buffer[index] = pixel;
	}
}

// TODO: Complete according to the prototype in graphics.h
void drawFilledRectangle(Screen *screen, Rectangle *rectangle) {
	int widthScreen = screen->size.x;
	int heightScreen = screen->size.y;
	int start = rectangle->top_left.x + widthScreen*rectangle->top_left.y;
	int width = rectangle->size.x;
	int height = rectangle->size.y;
	int index = start;
	Pixel color = rectangle->color;

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				index = i + rectangle->top_left.x + widthScreen * (j + rectangle->top_left.y);
				if (i + rectangle->top_left.x < widthScreen ) {
					if (j + rectangle->top_left.y < heightScreen) {
						screen->buffer[index] = color;
					}
				}
			}
		}
}
// TODO: Complete according to the prototype in graphics.h

void drawLine(Screen *screen, Line *line) {
	int widthScreen = screen->size.x;
	int heightScreen = screen->size.y;
	int changed = 0;
	int x = line->start.x;
	int y = line->start.y;
	int dx = abs(line->end.x - line->start.x);
	int dy = abs(line->end.y - line->start.y);
	int signx = signum(line->end.x - line->start.x);
	int signy = signum(line->end.y - line->start.y);
	if (dy > dx) {
		int temp = dx;
		dx = dy;
		dy = temp;
		changed = 1;
	}
	int e = (2 * dy) - dx;
	for (int i = 1; i <= dx; i++) {
		if (x < widthScreen && y < heightScreen) {
			int index = coordtoidx(x,y,widthScreen);
			screen->buffer[index] = line->color;
		}
        while (e >= 0) {
            if (changed) {
                x = x + signx;
            } else {
                y = y + signy;
            }
            e = e-(2*dx);
        }
        if (changed) {
    		y += signy;
        } else{
            x += signx;
        }
        e += 2 * dy;
    }
    x = line->end.x;
    y = line->end.y;
    if (x < widthScreen && y < heightScreen) {
    	int index = coordtoidx(line->end.x,line->end.y,widthScreen);
    	screen->buffer[index] = line->color;
	}
}

// TODO: Complete according to the prototype in graphics.h
void drawPolygon(Screen *screen, Polygon *polygon) {
	int size = polygon->num_vertices;
	for (int i = 0; i < size - 1; i++) {
		Line line = {
    		.start = polygon->vertices[i],
    		.end = polygon->vertices[i + 1],
    		.color = polygon->color
    	};
		drawLine(screen,  &line);
	}
	Line line;
    line.start = polygon->vertices[size - 1];
    line.end = polygon->vertices[0];
    line.color = polygon->color;
	drawLine(screen,  &line);
}

void plot (int x, int y, Pixel color, Screen *screen) {
	if (x >= screen->size.x || y >= screen->size.y || x < 0 || y < 0) {
	} else {
	int index = coordtoidx(x,y,screen->size.x);
    screen->buffer[index] = color;
}
}
// TODO: Complete according to the prototype in graphics.h
void drawFilledPolygon(Screen *screen, Polygon *polygon) {
	if (!screen || !polygon) {
		return;
	}
	int min_y = INT_MAX;
    int max_y = INT_MIN;
    //Pixel* screenBuffer = screen->buffer;

    // -------------------------------------------------------------------------
    // TODO: Here, write some code that will find the minimum and maximum
    // Y values that belong to vertices of the polygon, and store them as
    // min_y and max_y.
    // -------------------------------------------------------------------------

    for (int i = 0; i < polygon->num_vertices; i++) {
    	int current = (polygon->vertices[i]).y;
    	if (current < min_y) {
    		min_y = current;
    	}
    	if (current > max_y) {
    		max_y = current;
    	}
    }

    // -------------------------------------------------------------------------
    // END OF TODO
    // -------------------------------------------------------------------------

    // Now we iterate through the rows of our polygon
	for (int row = min_y; row <= max_y; row++) {
        // This variable contains the number of nodes found. We start with 0.
		int nNodes = 0;

        // This array will contain the X coords of the nodes we find.
        // Note that there are at most num_vertices of those. We allocate
        // that much room, but at any time only the first nNodes ints will
        // be our actual data.
        int nodeX[polygon->num_vertices];

        // This loop finds the nodes on this row. It intersects the line
        // segments between consecutive pairs of vertices with the horizontal
        // line corresponding to the row we're on. Don't worry about the
        // details, it just works.
		int j = polygon->num_vertices - 1;
		for (int i = 0; i < polygon->num_vertices; i++) {
			if ((polygon->vertices[i].y < row && polygon->vertices[j].y >= row) ||
				(polygon->vertices[j].y < row && polygon->vertices[i].y >= row)) {
				nodeX[nNodes++] = (polygon->vertices[i].x +
                    (row - polygon->vertices[i].y) *
                    (polygon->vertices[j].x - polygon->vertices[i].x) /
                    (polygon->vertices[j].y - polygon->vertices[i].y));
			}
			j = i;
		}

        // ---------------------------------------------------------------------
        // TODO: Make a call to qsort here to sort the nodeX array we made,
        // from small to large x coordinate. Note that there are nNodes elements
        // that we want to sort, and each is an integer. We give you int_cmp
        // at the top of the file to use as the comparator for the qsort call,
        // so you can just pass it to qsort and not need to write your own
        // comparator.
        // ---------------------------------------------------------------------
        qsort(nodeX, nNodes, sizeof(int), int_cmp);

        // ---------------------------------------------------------------------
        // END OF TODO
        // ---------------------------------------------------------------------

        // ---------------------------------------------------------------------
        // TODO: Now we fill the x coordinates corresponding to the interior of
        // the polygon. Note that after every node we switch sides on the
        // polygon, that is, if we are on the outside, when we pass a node we
        // end up on the inside, and if are inside, we end up on the outside.
        // As a result, all you need to do is start at the 0th node, iterate
        // through all of the even-indexed nodes, and fill until the next node.
        // For example, you need to fill between nodes 0-1, between nodes 2-3,
        // nodes 4-5 etc. but not between nodes 1-2, or nodes 3-4.
        // ---------------------------------------------------------------------

        for (int i = 0; i < nNodes - 1; i += 2) {
        	for (int j = nodeX[i]; j < nodeX[i + 1]; j++) {
        		//int index = j*screen->size.x + i;
        		//screen->buffer[index] = polygon->color;
        		drawPixel(screen, (Vector) {j, row}, polygon->color);
        	}
        }

        // ---------------------------------------------------------------------
        // END OF TODO
        // ---------------------------------------------------------------------
	}
}

// TODO: Complete according to the prototype in graphics.h
void drawRectangle(Screen *screen, Rectangle *rectangle) {
	if (!screen || !rectangle) {
		return;
	}

	Vector t1 = {rectangle->top_left.x, rectangle->top_left.y};
	Vector t2 = {rectangle->top_left.x + rectangle->size.x - 1, rectangle->top_left.y};
	Vector t3 = {rectangle->top_left.x + rectangle->size.x-1, rectangle->top_left.y -1 + rectangle->size.y};
	Vector t4 = {rectangle->top_left.x, rectangle->top_left.y + rectangle->size.y-1};


	Vector vertices[4] = {
		t1, t2, t3, t4
	};
	Polygon polygon = {vertices, 4, rectangle->color};
	drawPolygon(screen, &polygon);
}


// TODO: Complete according to the prototype in graphics.h
void drawCircle(Screen *screen, Circle *circle) {
	int x = 0;
	int y = circle->radius;
	int d = 1 - circle->radius;
	int mx = circle->center.x;
	int my = circle->center.y;
	while (x <= y) {
        plot(mx + x, my + y, circle->color, screen);
        plot(mx + x, my - y, circle->color, screen);
        plot(mx - x, my + y, circle->color, screen);
        plot(mx - x, my - y, circle->color, screen);
		plot(mx + y, my + x, circle->color, screen);
        plot(mx + y, my - x, circle->color, screen);
        plot(mx - y, my + x, circle->color, screen);
        plot(mx - y, my - x, circle->color, screen);
        if (d < 0) {
            d = d + 2*x + 3;
            x += 1;
        } else {
            d = d + 2*(x-y) + 5;
            x += 1;
            y -= 1;
        }
    }
}

// TODO: Complete according to the prototype in graphics.h
void drawFilledCircle(Screen *screen, Circle *circle) {
	int radius = circle->radius;
	int mx = circle->center.x;
	int my = circle->center.y;
    int x = 0;
    int y = radius;
    int d = 1 - radius;
	while (x <= y) {
		Vector p1 = {mx + x, my + y };
		Vector p2 = {mx + x, (my > y) ? (my - y) : 0};
		Line line = {p1,p2,circle->color};
        drawLine(screen, &line);

        if (mx >= x) {
        	Vector p3 = {mx - x, my + y};
   	   		Vector p4 = {mx - x, (my > y) ? my - y : 0};
			Line line1 = {p3, p4, circle->color};
          	drawLine(screen, &line1);
      	}

      	Vector p5 = {mx + y, my + x};
     	Vector p6 = {mx + y, (my > x) ? (my - x) : 0};
     	Line line2 = {p5,p6,circle->color};
     	drawLine(screen, &line2);

      	if (mx >= y) {
          	Vector p7 = {mx - y, my + x};
          	Vector p8 = {mx - y, (my > x) ? (my - x) : 0};
          	Line line3 = {p7,p8,circle->color};
          	drawLine(screen, &line3);
      	}

      	if (d < 0) {
          	d = d + 2 * x + 3;
          	x += 1;
      	} else {
          	d = d + 2 * (x-y) + 5;
          	x += 1;
          	y -= 1;
      	}
  	}
}

// TODO: Complete according to the prototype in graphics.h
void drawImage(Screen *screen, Image *image, Pixel (*colorFilter)(Pixel)) {
    for (int x = 0; x < (image->size.x); x++) {
    	for (int y = 0; y < (image->size.y); y++) {
    		int dx = image->top_left.x + x;
    		int dy = image->top_left.y + y;
    		if ((dx >= 0) && (dx < screen->size.x) && (dy >= 0) && (dy < screen->size.y)) {
    			Pixel pixel = image->buffer[x + image->size.x*y];
    			Pixel filterpixel = (*colorFilter)(pixel);
    			//int index = y*width + x;
    			drawPixel(screen, (Vector) {dx,dy}, filterpixel);
    		}
    		
    	}
    }
}

// TODO: Complete according to the prototype in graphics.
Image rotateImage(Image *image, int degrees) {
	//UNUSED(image);
	//UNUSED(degrees)
	int width = image->size.x;
	int height = image->size.y;
	Pixel* oldBuffer = image->buffer;
	Vector topleft = image->top_left;
	Vector size = image->size;

	Pixel* newBuffer = (Pixel*) malloc(sizeof(Pixel)*width*height);
	Image new = (Image) {topleft, size, newBuffer};
	//Image newImage = {image->top_left, image->size, newBuffer};
	if ((degrees) % 360 == 0)  {
		//newImage = *image;
		for (int i = 0; i < width*height; i++) {
				newBuffer[i] = oldBuffer[i];
		}
		//newImage.buffer = newBuffer;
	} else if (degrees % 180 == 0) {
		for (int i = 0; i < width*height; i++) {
				newBuffer[i] = oldBuffer[width*height -1 - i];
		}

	}else if (degrees < 0 ? abs(degrees % 360) == 90: degrees % 360 == 270) {
		//270
		//(x = 0, y = 0) -> (y = 0, height - x)
		//(x = width, y = 0) -> (y = 0, x = 0)
		//(x = 1, y = 1) - > (1, width - 1)
		//(x = width, y = height) -> (y = height, x = abs(x - width))

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				//x y becomes  -> y, x + depth
				//xdepth ydepth, -> ydepth, xdepth - depth
				newBuffer[abs(i)*height + abs(height - j - 1)] = oldBuffer[i + j*width];
			}
		}
		new.size = (Vector) {size.y, size.x};

	} else if (degrees < 0 ? (abs(degrees % 360) == 270): degrees % 360 == 90) {
		//90
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				//x y becomes  -> y, x + depth
				//xdepth ydepth, -> ydepth, xdepth - depth
				newBuffer[abs(width - i - 1)*height + j] = oldBuffer[i + j*width];
			}
		}
		new.size = (Vector) {size.y, size.x};

	}
 	return new;
}